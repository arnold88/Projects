// 
// $Id: alphabetanormalcomputer.hpp,v 1.1.1.1 2000/08/06 10:21:10 amos Exp $
//
// Definition of AlphaBetaNormalComputer class
//
// Jan Borsodi <jb@ez.no>
// Created on: <31-Oct-1999 16:59:58 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef ALPHABETANORMALCOMPUTER_HPP
#define ALPHABETANORMALCOMPUTER_HPP

#include "computerbrain.hpp"
#include "weights.hpp"
#include "player.hpp"

#include <qstring.h>
#include <qobject.h>

class AlphaBetaNormalComputer : public ComputerBrain
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
    AlphaBetaNormalComputer( QObject *parent = 0, const char *name = 0 );
    AlphaBetaNormalComputer( const AlphaBetaNormalComputer *b );
    virtual ~AlphaBetaNormalComputer();

    virtual void focusIn( Board *b );
    virtual void focusOut();

    virtual void init();

    virtual Brain *clone();

    virtual QString type() const;

private:
    int alphaBeta( int alpha, int beta, int level, int xpos, int ypos, Matrix &board );
    AlphaBetaResult preAlphaBeta( int alpha, int beta, Matrix &board );
    int staticEvaluation( int level, int xpos, int ypos, Matrix &m  );

    int Weights[8*8];
    float Total;
    int Cnt;
};

inline int AlphaBetaNormalComputer::staticEvaluation( int level, int xpos, int ypos, Matrix &board  )
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
            count += ( m.at( x, y ) == p ? Weights[x + (y<<3)] : 0 );
    return count;
}

#endif // ALPHABETANORMALCOMPUTER_HPP
