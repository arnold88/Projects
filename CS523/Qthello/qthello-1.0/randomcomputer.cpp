// 
// $Id: randomcomputer.cpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Implementation of RandomComputer class
//
// Jan Borsodi <jb@ez.no>
// Created on: <16-Oct-1999 14:18:29 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//


#include "randomcomputer.hpp"

#include <stdlib.h>

#include <qstring.h>
#include <qobject.h>
#include <qpoint.h>

/*!
  \class RandomComputer randomcomputer.hpp
  \brief

*/

/*!
  Default constructor
*/

RandomComputer::RandomComputer( QObject *parent, const char *n )
    : ComputerBrain( 1, "Frodo", parent, n )
{
}

RandomComputer::RandomComputer( const RandomComputer *b )
        : ComputerBrain( b )
{
}

/*!
  Destroys the object
*/

RandomComputer::~RandomComputer()
{
}

void RandomComputer::focusIn( Board *b )
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
        int rnd = rand();
        rnd %= plist.count();
        putPiece( plist[rnd].x(), plist[rnd].y() );
    }
}

void RandomComputer::focusOut()
{
    ComputerBrain::focusOut();
}

QString RandomComputer::type() const
{
    return "Computer{Random}";
}

Brain *RandomComputer::clone()
{
    return new RandomComputer( this );
}
