// 
// $Id: brain.cpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Implementation of Brain class
//
// Jan Borsodi <jb@ez.no>
// Created on: <20-Oct-1999 15:41:37 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//


#include "brain.hpp"
#include "playerprofile.hpp"
#include "player.hpp"

#include <qobject.h>
#include <qwidget.h>
#include <qstring.h>

/*!
  \class Brain brain.hpp
  \brief

*/

/*!
  Default constructor
*/

Brain::Brain( QObject *parent, const char *name )
    : QObject( parent, name )
{
    bName = false;
    pPly = 0;
    pPlyProf = 0;
    Num = -1;
}

Brain::Brain( const Brain *b )
        : QObject( b->parent(), b->name() )
{
    bName = b->bName;
    pPly = b->pPly;
    pPlyProf = b->pPlyProf;
    Name = b->Name;
    Num = b->Num;
}

/*!
  Destroys the object
*/

Brain::~Brain()
{
}

void Brain::configure( QWidget * )
{
}

bool Brain::hasConfig()
{
    return false;
}

Board *Brain::board() const
{
    if ( pPly != 0 )
        return pPly->board();
    else
        return 0;
}

void Brain::setBrainName( const QString &n )
{
    Name = n;
}

void Brain::setHasBrainName( bool b )
{
    bName = b;
}

void Brain::init()
{
}

void Brain::close()
{
}
