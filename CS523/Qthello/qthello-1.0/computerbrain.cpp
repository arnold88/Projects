// 
// $Id: computerbrain.cpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Implementation of ComputerBrain class
//
// Jan Borsodi <jb@ez.no>
// Created on: <16-Oct-1999 00:34:34 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//


#include "computerbrain.hpp"
#include "board.hpp"
#include "player.hpp"
#include "computerconfig.hpp"

#include <qstring.h>
#include <qobject.h>
#include <qpoint.h>
#include <qtimer.h>
#include <qwidget.h>
#include <qdialog.h>
#include <qtextstream.h>

/*!
  \class ComputerBrain computerbrain.hpp
  \brief

*/

/*!
  Default constructor
*/

ComputerBrain::ComputerBrain( int limit, const QString &name, QObject *parent, const char *n )
        : Brain( parent, n )
{
    Limit = limit;
    setBrainName( name );
    setHasBrainName( true );

    Timer = new QTimer( this, "randomtimer" );
    connect( Timer, SIGNAL( timeout() ),
             this, SLOT( putIt() ) );
    X = Y = -1;
    TimeoutValue = 1500;
}

ComputerBrain::ComputerBrain( const ComputerBrain *b )
        : Brain( b )
{
    X = b->X;
    Y = b->Y;
    Limit = b->Limit;
    TimeoutValue = b->TimeoutValue;
    Timer = new QTimer( this, "randomtimer" );
    connect( Timer, SIGNAL( timeout() ),
             this, SLOT( putIt() ) );
}

/*!
  Destroys the object
*/

ComputerBrain::~ComputerBrain()
{
}

void ComputerBrain::focusIn( Board * )
{
}

void ComputerBrain::focusOut()
{
}

void ComputerBrain::putIt()
{
    if ( board() != 0 )
        board()->movePiece( player(), X, Y );
}

void ComputerBrain::putPiece( int x, int y )
{
    X = x;
    Y = y;
    board()->overlay().copyFrom( board()->matrix() );
    MatrixRotator m = board()->overlay().on( x, y );
    m.flipPieces( player()->piece() );
    board()->overlayReset();
    Timer->start( TimeoutValue, true );
}

QString ComputerBrain::type() const
{
    return "Computer";
}

void ComputerBrain::configure( QWidget *parent )
{
    ComputerConfig c( playerProfile(), this, parent );
    if ( c.exec() == QDialog::Accepted )
    {
        setTimeout( c.timeoutValue() );
        setLimit( c.limitValue() );
        emit changed();
    }
}

bool ComputerBrain::hasConfig()
{
    return true;
}

void ComputerBrain::setTimeout( int t )
{
    if ( t < 0 )
        t = 0;
    TimeoutValue = t;
}

void ComputerBrain::save( QTextStream &s )
{
    s << TimeoutValue << "\n";
    s << Limit << "\n";
}

void ComputerBrain::load( QTextStream &s )
{
    s >> TimeoutValue;
    s >> Limit;
}
