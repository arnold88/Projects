// 
// $Id: alphabetacomputer.cpp,v 1.1.1.1 2000/08/06 10:21:10 amos Exp $
//
// Implementation of AlphaBetaComputer class
//
// Jan Borsodi <jb@ez.no>
// Created on: <31-Oct-1999 16:59:57 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//


#include "alphabetacomputer.hpp"
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
  \class AlphaBetaComputer alphabetacomputer.hpp
  \brief

*/

/*!
  Default constructor
*/

const int PositiveInfinite = 0x7fffffff;
const int NegativeInfinite = 0x80000000;

AlphaBetaComputer::AlphaBetaComputer( QObject *parent, const char *name )
    : ComputerBrain( 6, "Smeagol", parent, name )
{
    for ( int i = 0; i < 8*8; i++ )
        Weights[i] = FB_Weights[i];
}

AlphaBetaComputer::AlphaBetaComputer( const AlphaBetaComputer *b )
    : ComputerBrain( b )
{
    for ( int i = 0; i < 8*8; i++ )
        Weights[i] = b->Weights[i];
}

/*!
  Destroys the object
*/

AlphaBetaComputer::~AlphaBetaComputer()
{
}

void AlphaBetaComputer::focusIn( Board *b )
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
//              else
//              {
//                  qDebug( "No move" );
//                  AlphaBetaResult val = preAlphaBeta( NegativeInfinite, PositiveInfinite, b->matrix() );
//                  qDebug( "got %d from alpha/beta at pos[%d,%d]", val.Weight, val.X, val.Y );
//              }
        }
        catch ( OutOfRangeException &e )
        {
            qDebug( QString( "AlphaBetaComputer::FocusIn:error %1" ).arg( e.text() ) );
        }
    }

}

void AlphaBetaComputer::focusOut()
{
    ComputerBrain::focusOut();
}

Brain *AlphaBetaComputer::clone()
{
    return new AlphaBetaComputer( this );
}

QString AlphaBetaComputer::type() const
{
    return "Computer{AlphaBeta}";
}

AlphaBetaComputer::AlphaBetaResult AlphaBetaComputer::preAlphaBeta( int alpha, int beta, Matrix &board )
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

int AlphaBetaComputer::cornerCheck( MatrixIterator &it, const Piece &op )
{
    --it;
    if ( *it == Piece::Blank )
    {
        ++it;
        while ( true )
        {
            ++it;
            if ( it.valid() )
            {
                if ( *it == Piece::Blank )
                    return 8;
                else if ( *it == op )
                {
                    return 16;
                }
            }
            else
                return 0;
        }
    }
    else if ( *it != op )
        return 16;
    return 0;
}

int AlphaBetaComputer::doubleCheck( MatrixIterator &it )
{
    MatrixIterator it2( it.matrix(), it.x(), it.y(), -it.xIncrement(), -it.yIncrement() );
    ++it;
    while ( it.valid() )
    {
        if ( *it == Piece::Blank )
            return 0;
        ++it;
    }
    --it2;
    while ( it2.valid() )
    {
        if ( *it2 == Piece::Blank )
            return 0;
        ++it2;
    }
    return 16;
}

int AlphaBetaComputer::max( int alpha, int beta, int level, int xpos, int ypos, Matrix &board, int *weights )
{
//      int dw[8*8];
//      for ( int i = 0; i < 8*8; i++ )
//          dw[i] = dweights[i];
//      dynamicWeighting( weights, dw, xpos, ypos );
//      qDebug( "%d, %d, %d", alpha, beta, level );
    if ( level >= limit() )
    {
        return minStaticEvaluation( xpos, ypos, board, weights );
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
        return minStaticEvaluation( xpos, ypos, board, weights );
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
            val = min( alpha, beta, level+1, plist[i*2], plist[i*2 + 1], mat, weights );
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

int AlphaBetaComputer::min( int alpha, int beta, int level, int xpos, int ypos, Matrix &board, int *weights )
{
//      int dw[8*8];
//      for ( int i = 0; i < 8*8; i++ )
//          dw[i] = dweights[i];
//      dynamicWeighting( weights, dw, xpos, ypos );
//      qDebug( "%d, %d, %d", alpha, beta, level );
    if ( level >= limit() )
    {
        return maxStaticEvaluation( xpos, ypos, board, weights );
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
        return maxStaticEvaluation( xpos, ypos, board, weights );
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
            val = max( alpha, beta, level+1, plist[i*2], plist[i*2 + 1], mat, weights );
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

void AlphaBetaComputer::init()
{
    for ( int i = 0; i < 8*8; i++ )
        Weights[i] = FB_Weights[i];
    Total = 0.0;
    Cnt = 0;
}
