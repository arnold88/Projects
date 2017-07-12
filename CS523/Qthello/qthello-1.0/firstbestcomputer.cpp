// 
// $Id: firstbestcomputer.cpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Implementation of FirstBestComputer class
//
// Jan Borsodi <jb@ez.no>
// Created on: <20-Oct-1999 19:03:37 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//


#include "firstbestcomputer.hpp"
#include "player.hpp"

#include <stdlib.h>
#include <qstring.h>
#include <qpoint.h>
#include <qobject.h>

/*!
  \class FirstBestComputer firstbestcomputer.hpp
  \brief

*/

/*!
  Default constructor
*/

const int FB_Weights[8*8] =
{
    16, 1, 8, 8, 8, 8, 1, 16,
    1,  1, 2, 2, 2, 2, 1, 1,
    8,  2, 4, 4, 4, 4, 2, 8,
    8,  2, 4, 4, 4, 4, 2, 8,
    8,  2, 4, 4, 4, 4, 2, 8,
    8,  2, 4, 4, 4, 4, 2, 8,
    1,  1, 2, 2, 2, 2, 1, 1,
    16, 1, 8, 8, 8, 8, 1, 16
};

FirstBestComputer::FirstBestComputer( QObject *parent, const char *name )
    : ComputerBrain( 1, "Smaug", parent, name )
{
}

FirstBestComputer::FirstBestComputer( const FirstBestComputer *b )
        : ComputerBrain( b )
{
}

/*!
  Destroys the object
*/

FirstBestComputer::~FirstBestComputer()
{
}

void FirstBestComputer::focusIn( Board *b )
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
        QValueList<QPoint> best;
        int wg = 0;
        int index = -1;
        int i = 0;
        Piece p = player()->piece();
        for ( QValueList<QPoint>::Iterator it = plist.begin(); it != plist.end(); ++it, i++ )
        {
            int offs = (*it).x() + (*it).y()*8;
            Matrix m( b->matrix() );
            m.on( (*it).x(), (*it).y() ).flipPieces( p );
            int cnt = 0;
            for ( int y = 0; y < 8; y++ )
                for ( int x = 0; x < 8; x++ )
                    cnt += ( m.at( x, y ) == p ? 1 : 0 );
            if ( FB_Weights[offs] + cnt == wg )
            {
                best.append( *it );
            }
            else if ( FB_Weights[offs] + cnt > wg )
            {
                best.clear();
                best.append( *it );
                wg = FB_Weights[offs];
                index = i;
            }
        }
        int bestcount = best.count();
        index = rand()%bestcount;
        putPiece( best[index].x(), best[index].y() );
    }
}

void FirstBestComputer::focusOut()
{
    ComputerBrain::focusOut();
}

QString FirstBestComputer::type() const
{
    return "Computer{FirstBest}";
}

Brain *FirstBestComputer::clone()
{
    return new FirstBestComputer( this );
}
