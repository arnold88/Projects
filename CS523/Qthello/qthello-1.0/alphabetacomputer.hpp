// 
// $Id: alphabetacomputer.hpp,v 1.1.1.1 2000/08/06 10:21:10 amos Exp $
//
// Definition of AlphaBetaComputer class
//
// Jan Borsodi <jb@ez.no>
// Created on: <31-Oct-1999 16:59:58 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef ALPHABETACOMPUTER_HPP
#define ALPHABETACOMPUTER_HPP

#include "computerbrain.hpp"
#include "weights.hpp"
#include "player.hpp"

#include <qstring.h>
#include <qobject.h>

class AlphaBetaComputer : public ComputerBrain
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
    AlphaBetaComputer( QObject *parent = 0, const char *name = 0 );
    AlphaBetaComputer( const AlphaBetaComputer *b );
    virtual ~AlphaBetaComputer();

    virtual void focusIn( Board *b );
    virtual void focusOut();

    virtual void init();

    virtual Brain *clone();

    virtual QString type() const;

private:
    int max( int alpha, int beta, int level, int xpos, int ypos, Matrix &board, int *weights );
    int min( int alpha, int beta, int level, int xpos, int ypos, Matrix &board, int *weights );
    AlphaBetaResult preAlphaBeta( int alpha, int beta, Matrix &board );
    int maxStaticEvaluation( int xpos, int ypos, Matrix &m, int *weights );
    int minStaticEvaluation( int xpos, int ypos, Matrix &m, int *weights );
    int staticEvaluation( int xpos, int ypos, const Piece &p, Matrix &m, int *weights );
    int cornerCheck( MatrixIterator &it, const Piece &op );
    int doubleCheck( MatrixIterator &it );
    void changeWeights( int *weights, int xpos, int ypos );

    int Weights[8*8];
    float Total;
    int Cnt;
};

inline int AlphaBetaComputer::maxStaticEvaluation( int xpos, int ypos, Matrix &board, int *weights )
{
    Piece p;
    Piece op;
    p = player()->piece();
    op = p.opposite();
    return staticEvaluation( xpos, ypos, p, board, weights );
}

inline int AlphaBetaComputer::minStaticEvaluation( int xpos, int ypos, Matrix &board, int *weights )
{
    Piece p;
    Piece op;
    p = player()->piece().opposite();
    op = p.opposite();
    return staticEvaluation( xpos, ypos, p, board, weights );
}

inline int AlphaBetaComputer::staticEvaluation( int xpos, int ypos, const Piece &p, Matrix &board, int *weights )
{
    Matrix m( board );
    MatrixRotator rot = m.on( xpos, ypos );
    rot.flipPieces( p );
    int count = 0;
    for ( int y = 0; y < 8; y++ )
        for ( int x = 0; x < 8; x++ )
            count += ( m.at( x, y ) == p ? weights[x + (y<<3)] : 0 );
    return count;
}

inline void AlphaBetaComputer::changeWeights( int *weights, int xpos, int ypos )
{
    if ( xpos == 0 && ypos == 0 )
    {
        for ( int y = 0; y < 8; y++ )
            for ( int x = 0; x < 8; x++ )
                weights[x + (y<<3)] = ((weights[x + (y<<3)] + FB_WeightsAdjust[x + (y<<3)])>>1);
    }
    else if ( xpos == 7 && ypos == 0 )
    {
        for ( int y = 0; y < 8; y++ )
            for ( int x = 0; x < 8; x++ )
                weights[x + (y<<3)] = ((weights[x + (y<<3)] + FB_WeightsAdjust[(7-x) + (y<<3)])>>1);
    }
    else if ( xpos == 7 && ypos == 7 )
    {
        for ( int y = 0; y < 8; y++ )
            for ( int x = 0; x < 8; x++ )
                weights[x + (y<<3)] = ((weights[x + (y<<3)] + FB_WeightsAdjust[(7-x) + ((7-y)<<3)])>>1);
    }
    else if ( xpos == 0 && ypos == 7 )
    {
        for ( int y = 0; y < 8; y++ )
            for ( int x = 0; x < 8; x++ )
                weights[x + (y<<3)] = ((weights[x + (y<<3)] + FB_WeightsAdjust[x + ((7-y)<<3)])>>1);
    }
}

#endif // ALPHABETACOMPUTER_HPP
