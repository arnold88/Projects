// 
// $Id: alphabetadyncomputer.cpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Implementation of AlphaBetaDynComputer class
//
// Jan Borsodi <jb@ez.no>
// Created on: <31-Oct-1999 16:59:57 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//


#include "alphabetadyncomputer.hpp"
#include "player.hpp"
#include "matrix.hpp"
#include "piece.hpp"

#include <qapplication.h>
#include <qstring.h>
#include <qobject.h>
#include <qpoint.h>
#include <qapplication.h>
#include <qdatetime.h>
#include <qglobal.h>
#include <qvaluelist.h>

/*!
  \class AlphaBetaDynComputer AlphaBetaDyncomputer.hpp
  \brief

*/

/*!
  Default constructor
*/


const int PositiveInfinite = 0x7fffffff;
const int NegativeInfinite = 0x80000000;

AlphaBetaDynComputer::AlphaBetaDynComputer( QObject *parent, const char *name )
    : ComputerBrain( 10, "Sauron", parent, name )
{
    for ( int i = 0; i < 8*8; i++ )
        Weights[i] = FB_Weights[i];
}

AlphaBetaDynComputer::AlphaBetaDynComputer( const AlphaBetaDynComputer *b )
    : ComputerBrain( b )
{
    for ( int i = 0; i < 8*8; i++ )
        Weights[i] = b->Weights[i];
}

/*!
  Destroys the object
*/

AlphaBetaDynComputer::~AlphaBetaDynComputer()
{
}

void AlphaBetaDynComputer::focusIn( Board *b )
{
    ComputerBrain::focusIn( b );

    QValueList<QPoint> plist;
    for ( int y = 0; y < 8; y++ )
    {
        for ( int x = 0; x < 8; x++ )
        {
            if ( b->canMove( player(), x, y ) )
            {
                plist.append( QPoint( x, y ) );
            }
         }
    }
    if ( plist.count() > 0 )
    {
        try
        {
            QTime pre = QTime::currentTime();
            AlphaBetaResult val = preAlphaBeta( NegativeInfinite, PositiveInfinite, b->matrix() );
            if ( val.X >= 0 && val.Y >= 0 )
            {
                qDebug( "got %d from alpha/beta at pos[%d,%d]", val.Weight, val.X, val.Y );
                changeWeights( Weights, val.X, val.Y );
                QTime pro = QTime::currentTime();
                int time = pre.msecsTo( pro );
                float sec = (float)time/1000.0;
                Total += sec;
                Cnt++;
                qDebug( QString( "Calculation for %1 levels uses %2 seconds on average" ).arg( limit() ).arg( Total/(float)Cnt ) );
                putPiece( val.X, val.Y );
            }
        }
        catch ( OutOfRangeException &e )
        {
            qDebug( QString( "AlphaBetaComputer::FocusIn:error %1" ).arg( e.text() ) );
        }
    }

}

void AlphaBetaDynComputer::focusOut()
{
    ComputerBrain::focusOut();
}

Brain *AlphaBetaDynComputer::clone()
{
    return new AlphaBetaDynComputer( this );
}

QString AlphaBetaDynComputer::type() const
{
    return "Computer{AlphaBetaDyn}";
}

AlphaBetaDynComputer::AlphaBetaResult AlphaBetaDynComputer::preAlphaBeta( int alpha, int beta, Matrix &board )
{
    int level = 0;
//      qDebug( "Toplevel: %d, %d, %d", alpha, beta, level );

    // No need to recurse, already at max level
    if ( level >= limit() )
    {
        MatrixRotator r;
        Piece p = player()->piece();
        int *plist = new int[8*8*2];
        int count = 0;
        for ( int y = 0; y < 8; y++ )
        {
            for ( int x = 0; x < 8; x++ )
            {
                r = board.on( x, y );
                if ( r.legalMove( p ) )
                {
                    plist[count*2] = x;
                    plist[count*2 + 1] = y;
                    count++;
                }
            }
        }
        if ( count > 0 )
        {
            int wg = 0;
            int i = 0;
            int index = -1;
            while ( i < count )
            {
                int offs = plist[i*2] + ((plist[i*2 + 1])<<3);
                if ( Weights[offs] > wg )
                {
                    wg = Weights[offs];
                    index = i;
                }
                i++;
            }
            qDebug( "Found weight %d at pos[%d, %d]", wg, plist[index*2], plist[index*2 + 1] );
            if ( index < 0 )
                return AlphaBetaResult( -1, -1, wg );
            else
                return AlphaBetaResult( plist[index*2], plist[index*2 + 1], wg );
        }
        else
            return AlphaBetaResult( -1, -1, 0 );
    }

    // Start alpha/beta recursive function
    // and find the best position with the max algorithm

    MatrixRotator r;
    Piece p = player()->piece();
    int *plist = new int[8*8*2];
    int count = 0;
    for ( int y = 0; y < 8; y++ )
    {
        for ( int x = 0; x < 8; x++ )
        {
            r = board.on( x, y );
            if ( r.legalMove( p ) )
            {
                plist[count*2] = x;
                plist[count*2 + 1] = y;
                count++;
            }
        }
    }
    if ( count == 0 )
    {
        delete []plist;
        return AlphaBetaResult( -1, -1, PositiveInfinite );
    }
    else
    {
        Matrix mat;
        int i = 0;
        int select = -1;
        int val;
        while ( alpha < beta && i < count )
        {
            qApp->processEvents();
            mat.copyFrom( board );
            r = mat.on( plist[i*2], plist[i*2 + 1] );
            r.flipPieces( p );
//              qDebug( "Toplevel:checking pos[%d,%d] for level %d", plist[i*2], plist[i*2 + 1], level );
            val = min( alpha, beta, level+1, plist[i*2], plist[i*2 + 1], mat, Weights );
//              qDebug( "Toplevel:got value %d", val );
            if ( val > alpha )
            {
                alpha = val;
                select = i;
            }
            i++;
        }
        AlphaBetaResult result;
        if ( select < 0 )
            result = AlphaBetaResult( -1, -1, alpha );
        else
            result = AlphaBetaResult( plist[select*2], plist[select*2 + 1], alpha );
        delete []plist;
        return result;
//            return alpha;
    }
}

int AlphaBetaDynComputer::max( int alpha, int beta, int level, int xpos, int ypos, Matrix &board, int *weights )
{
    int dw[8*8];
    for ( int i = 0; i < 8*8; i++ )
        dw[i] = weights[i];
    changeWeights( dw, xpos, ypos );
    if ( level >= limit() )
    {
        return minStaticEvaluation( xpos, ypos, board, dw );
    }
    MatrixRotator r;
    Piece p = player()->piece();
    int *plist = new int[8*8*2];
    int count = 0;
    for ( int y = 0; y < 8; y++ )
    {
        for ( int x = 0; x < 8; x++ )
        {
            r = board.on( x, y );
            if ( r.legalMove( p ) )
            {
                plist[count*2] = x;
                plist[count*2 + 1] = y;
                count++;
            }
        }
    }
    if ( count == 0 )
    {
        delete []plist;
        return minStaticEvaluation( xpos, ypos, board, dw );
    }
    else
    {
        Matrix mat;
        int i = 0;
        int select = -1;
        int val;
        while ( alpha < beta && i < count )
        {
            mat.copyFrom( board );
            r = mat.on( plist[i*2], plist[i*2 + 1] );
            r.flipPieces( p );
            val = min( alpha, beta, level+1, plist[i*2], plist[i*2 + 1], mat, dw );
            if ( val > alpha )
            {
                alpha = val;
                select = i;
            }
            i++;
        }
        delete []plist;
        return alpha;
    }
}

int AlphaBetaDynComputer::min( int alpha, int beta, int level, int xpos, int ypos, Matrix &board, int *weights )
{
    int dw[8*8];
    for ( int i = 0; i < 8*8; i++ )
        dw[i] = weights[i];
    changeWeights( dw, xpos, ypos );
    if ( level >= limit() )
    {
        return maxStaticEvaluation( xpos, ypos, board, dw );
    }
    MatrixRotator r;
    Piece p = player()->piece().opposite();
    int *plist = new int[8*8*2];
    int count = 0;
    for ( int y = 0; y < 8; y++ )
    {
        for ( int x = 0; x < 8; x++ )
        {
            r = board.on( x, y );
            if ( r.legalMove( p ) )
            {
                plist[count*2] = x;
                plist[count*2 + 1] = y;
                count++;
            }
        }
    }
    if ( count == 0 )
    {
        delete []plist;
        return maxStaticEvaluation( xpos, ypos, board, dw );
    }
    else
    {
        Matrix mat;
        int i = 0;
        int select = -1;
        int val;
        while ( alpha < beta && i < count )
        {
            mat.copyFrom( board );
            r = mat.on( plist[i*2], plist[i*2 + 1] );
            r.flipPieces( p );
            val = max( alpha, beta, level+1, plist[i*2], plist[i*2 + 1], mat, dw );
            if ( val < beta )
            {
                beta = val;
                select = i;
            }
            i++;
        }
        delete []plist;
        return beta;
    }
}

void AlphaBetaDynComputer::init()
{
    for ( int i = 0; i < 8*8; i++ )
        Weights[i] = FB_Weights[i];
    Total = 0.0;
    Cnt = 0;
}

int AlphaBetaDynComputer::checkBadPos( const Piece &p, Matrix &m, int *weights )
{
    int cnt = 0;
    Piece op = p.opposite();
    cnt += checkBadPosSpecial( p, op, m, weights, 1, 1, 1, 1 ); // Topleft corner

    cnt += checkBadPosSpecial( p, op, m, weights, 6, 1, -1, 1 ); // Topright corner

    cnt += checkBadPosSpecial( p, op, m, weights, 6, 6, -1, -1 ); // Bottomright corner

    cnt += checkBadPosSpecial( p, op, m, weights, 1, 6, 1, -1 ); // Bottomleft corner

    for ( int i = 0; i < 8; i++ )
    {
//          if ( i != 1 && i != 6 )
//          {
            cnt += checkBadPosSpecial( p, op, m, weights, i, 1, 0, 1 ); // Top to bottom
            cnt += checkBadPosSpecial( p, op, m, weights, 1, i, 1, 0 ); // Left to right
            cnt += checkBadPosSpecial( p, op, m, weights, i, 6, 0, -1 ); // Bottom to top
            cnt += checkBadPosSpecial( p, op, m, weights, 6, i, -1, 0 ); // Right to left
//          }
    }
    return cnt;
}

int AlphaBetaDynComputer::checkBadPosSpecial( const Piece &p, const Piece &op, Matrix &m, int *w, int x, int y, int xi, int yi )
{
    int val;
    if ( w[x + (y<<3)] > 0 )
        val = 700/w[x + (y<<3)];
    else
        val = 700;
    if ( m.at( x, y ) == p )
    {
        if ( m.at( x-xi, y-yi ) == Piece::Blank )
        {
            MatrixIterator it( &m, x, y, xi, yi );
            ++it;
            while( it.valid() )
            {
                if ( *it == op )
                {
                    return val;
                }
                ++it;
            }
        }
        else if ( m.at( x-xi, y-yi ) == op )
        {
            return val;
        }
    }
    return 0;
}
