// 
// $Id: alphabetaevalcomputer.hpp,v 1.1.1.1 2000/08/06 10:21:10 amos Exp $
//
// Definition of AlphaBetaEvalComputer class
//
// Jan Borsodi <jb@ez.no>
// Created on: <31-Oct-1999 16:59:58 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef ALPHABETAEVALCOMPUTER_HPP
#define ALPHABETAEVALCOMPUTER_HPP

#include "computerbrain.hpp"
#include "weights.hpp"
#include "player.hpp"

#include <qstring.h>
#include <qobject.h>

class AlphaBetaEvalComputer : public ComputerBrain
{
    class AlphaBetaResult
    {
    public:
        AlphaBetaResult()
            {
                X = -1;
                Y = -1;
                Weight = -1;
            }
        AlphaBetaResult( int x, int y, int w )
            {
                X = x;
                Y = y;
                Weight = w;
            }

        int X, Y;
        int Weight;
    };
public:
    AlphaBetaEvalComputer( QObject *parent = 0, const char *name = 0 );
    AlphaBetaEvalComputer( const AlphaBetaEvalComputer *b );
    virtual ~AlphaBetaEvalComputer();

    virtual void focusIn( Board *b );
    virtual void focusOut();

    virtual void init();

    virtual Brain *clone();

    virtual QString type() const;

private:
    int alphaBeta( int alpha, int beta, int level, int xpos, int ypos, Matrix &board );
    AlphaBetaResult preAlphaBeta( int alpha, int beta, Matrix &board );
    int staticEvaluation( int level, int xpos, int ypos, Matrix &m );
    int singleEvaluation( int xpos, int ypos, Matrix &m, Piece &p );

    int Weights[8*8];
    float Total;
    int Cnt;
};

inline int AlphaBetaEvalComputer::staticEvaluation( int level, int xpos, int ypos, Matrix &board )
{
    Piece p;
    Piece op;
    if ( (level & 1) == 0 )
        p = player()->piece().opposite();
    else
        p = player()->piece();
    op = p.opposite();
    Matrix m( board );
    MatrixRotator rot = m.on( xpos, ypos );
    rot.flipPieces( p );
    int count = 0;
    for ( int y = 0; y < 8; y++ )
        for ( int x = 0; x < 8; x++ )
            count += ( m.at( x, y ) == p ? Weights[x + (y<<3)] + singleEvaluation( xpos, ypos, m, p ) : 0 );
//              count += ( m.at( x, y ) == p ? Weights[x + (y<<3)] : 0 );
    return count;
}

inline int AlphaBetaEvalComputer::singleEvaluation( int xpos, int ypos, Matrix &m, Piece &p )
{
    if ( m.at( xpos, ypos ) != p )
        return 0;
    int cnt = 0;
    Piece op = p.opposite();
    if ( xpos > 0 && xpos < 8-1 && ypos > 0 && ypos < 8-1 )
    {
//          qDebug( "Mid" );
        if ( m.at( xpos-1, ypos-1 ) == op )
        {
            if ( m.at( xpos+1, ypos+1 ) == op )
                cnt += 1;
            else
                cnt -= 1;
        }
        if ( m.at( xpos, ypos-1 ) == op )
        {
            if ( m.at( xpos, ypos+1 ) == op )
                cnt += 1;
            else
                cnt -= 1;
        }
        if ( m.at( xpos+1, ypos-1 ) == op )
        {
            if ( m.at( xpos-1, ypos+1 ) == op )
                cnt += 1;
            else
                cnt -= 1;
        }
        if ( m.at( xpos+1, ypos ) == op )
        {
            if ( m.at( xpos-1, ypos ) == op )
                cnt += 1;
            else
                cnt -= 1;
        }
        if ( m.at( xpos+1, ypos+1 ) == op )
        {
            if ( m.at( xpos-1, ypos-1 ) == op )
                cnt += 1;
            else
                cnt -= 1;
        }
        if ( m.at( xpos, ypos+1 ) == op )
        {
            if ( m.at( xpos, ypos-1 ) == op )
                cnt += 1;
            else
                cnt -= 1;
        }
        if ( m.at( xpos-1, ypos+1 ) == op )
        {
            if ( m.at( xpos+1, ypos-1 ) == op )
                cnt += 1;
            else
                cnt -= 1;
        }
        if ( m.at( xpos-1, ypos ) == op )
        {
            if ( m.at( xpos+1, ypos ) == op )
                cnt += 1;
            else
                cnt -= 1;
        }
    }
    else
    {
        if ( ypos == 0 )
        {
            // Top left corner
            if ( xpos == 0 )
            {
//                  qDebug( "Topleft" );
                if ( m.at( xpos + 1, ypos ) == op )
                    cnt += 1;
                if ( m.at( xpos + 1, ypos + 1 ) == op )
                    cnt += 1;
                if ( m.at( xpos, ypos + 1 ) == op )
                    cnt += 1;
            }
            // Top side
            else if ( xpos < 8-1 )
            {
//                  qDebug( "Top" );
                if ( m.at( xpos + 1, ypos ) == op )
                    if ( m.at( xpos - 1, ypos ) == op )
                        cnt += 1;
                    else
                        cnt -= 1;
                if ( m.at( xpos + 1, ypos + 1 ) == op )
                    cnt += 1;
                if ( m.at( xpos, ypos + 1 ) == op )
                    cnt += 1;
                if ( m.at( xpos - 1, ypos + 1 ) == op )
                    cnt += 1;
                if ( m.at( xpos - 1, ypos ) == op )
                    if ( m.at( xpos + 1, ypos ) == op )
                        cnt += 1;
                    else
                        cnt -= 1;
            }
            // Top right corner
            else if ( xpos == 8-1 )
            {
//                  qDebug( "Topright" );
                if ( m.at( xpos, ypos + 1 ) == op )
                    cnt += 1;
                if ( m.at( xpos - 1, ypos + 1 ) == op )
                    cnt += 1;
                if ( m.at( xpos - 1, ypos ) == op )
                    cnt += 1;
            }
        }
        else if ( ypos < 8-1 )
        {
            // Right side
            if ( xpos == 8-1 )
            {
//                  qDebug( "Right" );
                if ( m.at( xpos, ypos - 1 ) == op )
                    if ( m.at( xpos, ypos + 1 ) == op )
                        cnt += 1;
                    else
                        cnt -= 1;
                if ( m.at( xpos - 1, ypos + 1 ) == op )
                    cnt += 1;
                if ( m.at( xpos - 1, ypos ) == op )
                    cnt += 1;
                if ( m.at( xpos - 1, ypos - 1 ) == op )
                    cnt += 1;
                if ( m.at( xpos, ypos + 1 ) == op )
                    if ( m.at( xpos, ypos - 1 ) == op )
                        cnt += 1;
                    else
                        cnt -= 1;
            }
            // Left side
            else if ( xpos == 0 )
            {
//                  qDebug( "Left" );
                if ( m.at( xpos, ypos - 1 ) == op )
                    if ( m.at( xpos, ypos + 1 ) == op )
                        cnt += 1;
                    else
                        cnt -= 1;
                if ( m.at( xpos + 1, ypos + 1 ) == op )
                    cnt += 1;
                if ( m.at( xpos + 1, ypos ) == op )
                    cnt += 1;
                if ( m.at( xpos + 1, ypos - 1 ) == op )
                    cnt += 1;
                if ( m.at( xpos, ypos + 1 ) == op )
                    if ( m.at( xpos, ypos - 1 ) == op )
                        cnt += 1;
                    else
                        cnt -= 1;
            }
        }
        else
        {
            // Bottom left corner
            if ( xpos == 0 )
            {
//                  qDebug( "Bottomleft" );
                if ( m.at( xpos, ypos - 1 ) == op )
                    cnt += 1;
                if ( m.at( xpos + 1, ypos - 1 ) == op )
                    cnt += 1;
                if ( m.at( xpos + 1, ypos ) == op )
                    cnt += 1;
            }
            // Bottom side
            else if ( xpos < 8-1 )
            {
//                  qDebug( "Bottom" );
                if ( m.at( xpos + 1, ypos ) == op )
                    if ( m.at( xpos - 1, ypos ) == op )
                        cnt += 1;
                    else
                        cnt -= 1;
                if ( m.at( xpos + 1, ypos - 1 ) == op )
                    cnt += 1;
                if ( m.at( xpos, ypos - 1 ) == op )
                    cnt += 1;
                if ( m.at( xpos - 1, ypos - 1 ) == op )
                    cnt += 1;
                if ( m.at( xpos - 1, ypos ) == op )
                    if ( m.at( xpos + 1, ypos ) == op )
                        cnt += 1;
                    else
                        cnt -= 1;
            }
            // Bottom right corner
            else if ( xpos == 8-1 )
            {
//                  qDebug( "Bottomright" );
                if ( m.at( xpos, ypos - 1 ) == op )
                    cnt += 1;
                if ( m.at( xpos - 1, ypos - 1 ) == op )
                    cnt += 1;
                if ( m.at( xpos - 1, ypos ) == op )
                    cnt += 1;
            }
        }
    }
    return cnt;
}

#endif // ALPHABETAEVALCOMPUTER_HPP
