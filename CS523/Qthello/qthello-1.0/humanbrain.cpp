// 
// $Id: humanbrain.cpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Implementation of HumanBrain class
//
// Jan Borsodi <jb@ez.no>
// Created on: <08-Oct-1999 14:29:15 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//


#include "humanbrain.hpp"
#include "humanconfig.hpp"
#include "player.hpp"

#include <qstring.h>
#include <qobject.h>
#include <qevent.h>
#include <qpoint.h>
#include <qdialog.h>
#include <qwidget.h>
#include <qtextstream.h>

/*!
  \class HumanBrain humanbrain.hpp
  \brief

*/

/*!
  Default constructor
*/

HumanBrain::HumanBrain( QObject *parent, const char *n )
    : Brain( parent, n )
{
    X = -1;
    Y = -1;
    bShowMarkers = true;
}

HumanBrain::HumanBrain( const HumanBrain *b )
        : Brain( b )
{
    X = b->X;
    Y = b->Y;
    bShowMarkers = b->bShowMarkers;
}

/*!
  Destroys the object
*/

HumanBrain::~HumanBrain()
{
}

void HumanBrain::focusIn( Board *b )
{
    X = -1;
    Y = -1;
    connect( b, SIGNAL( mousePress( int, int ) ),
             this, SLOT( doMousePress( int, int ) ) );
    connect( b, SIGNAL( mouseMove( int, int ) ),
             this, SLOT( doMouseMove( int, int ) ) );
    connect( b, SIGNAL( mouseRelease( int, int ) ),
             this, SLOT( doMouseRelease( int, int ) ) );
    connect( b, SIGNAL( enter() ),
             this, SLOT( doEnter() ) );
    connect( b, SIGNAL( leave() ),
             this, SLOT( doLeave() ) );

    if ( bShowMarkers )
    {
        showMarkers();
    }
}

void HumanBrain::focusOut()
{
    disconnect( board(), SIGNAL( mousePress( int, int ) ),
                this, SLOT( doMousePress( int, int ) ) );
    disconnect( board(), SIGNAL( mouseMove( int, int ) ),
                this, SLOT( doMouseMove( int, int ) ) );
    disconnect( board(), SIGNAL( mouseRelease( int, int ) ),
                this, SLOT( doMouseRelease( int, int ) ) );
    disconnect( board(), SIGNAL( enter() ),
                this, SLOT( doEnter() ) );
    disconnect( board(), SIGNAL( leave() ),
                this, SLOT( doLeave() ) );
}

void HumanBrain::doMousePress( int x, int y )
{
    if ( board() )
    {
        if ( board()->canMove( player(), x, y ) )
            board()->movePiece( player(), x, y );
        else
            qDebug( "Cannot place here" );
    }
    else
        qDebug( "HumanBrain::doMousePress::error, no board found" );
}

void HumanBrain::doMouseMove( int x, int y )
{
    if ( x == X && y == Y )
        return;
    X = x;
    Y = y;

    showOverlay( x, y );
}

void HumanBrain::showOverlay( int x, int y )
{
    board()->overlay().copyFrom( board()->matrix() );
    if ( x >= 0 && y >= 0 )
    {
        if ( board()->canMove( player(), x, y ) )
        {
            MatrixRotator m = board()->overlay().on( x, y );
            m.flipPieces( player()->piece() );
        }
    }
    board()->overlayReset();
}

void HumanBrain::doMouseRelease( int , int  )
{
}

void HumanBrain::doEnter()
{
    board()->overlayReset();
}

void HumanBrain::doLeave()
{
    board()->overlayStop();
}

void HumanBrain::setMarkers( bool b )
{
    if ( b == bShowMarkers )
        return;
    bShowMarkers = b;
    if ( b )
        showMarkers();
    else
        if ( board() != 0 )
            board()->clearMarker();
}

void HumanBrain::showMarkers()
{
    if ( board() == 0 )
        return;
    QValueList<QPoint> plst = board()->availableMoves( player(), board()->matrix() );
    for ( QValueList<QPoint>::ConstIterator it = plst.begin(); it != plst.end(); ++it )
    {
        board()->marker().setAt( (*it).x(), (*it).y(), Piece::Marked );
    }
}

void HumanBrain::configure( QWidget *parent )
{
    HumanConfig c( playerProfile()->profileName(), markersOn(), tr( "Configure human player %1" ).arg( playerProfile()->profileName() ), parent );
    if ( c.exec() == QDialog::Accepted )
    {
        playerProfile()->setProfileName( c.playerName() );
        setMarkers( c.markersOn() );
        emit changed();
    }
}

bool HumanBrain::hasConfig()
{
    return true;
}

QString HumanBrain::type() const
{
    return "Human";
}

Brain *HumanBrain::clone()
{
    return new HumanBrain( this );
}

void HumanBrain::save( QTextStream &s )
{
    if ( bShowMarkers )
        s << "true\n";
    else
        s << "false\n";
}

void HumanBrain::load( QTextStream &s )
{
    QString marker;
    s >> marker;
    setMarkers( marker == "true" );
}
