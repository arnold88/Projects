// 
// $Id: player.cpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Implementation of Player class
//
// Jan Borsodi <jb@ez.no>
// Created on: <08-Oct-1999 13:25:47 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//


#include "player.hpp"
#include "playerprofile.hpp"
#include "playerlist.hpp"

#include <qstring.h>
#include <qobject.h>
#include <qwidget.h>

/*!
  \class Player player.hpp
  \brief

*/

/*!
  Default constructor
*/

Player::Player( const QString &name, const Piece &p, PlayerProfile *pf, QObject *parent, const char *n )
        : QObject( parent, n ), Color( p )
{
    Name = name;
    Skip = 0;
    Score = 0;
    pBrain = 0;
    pProf = 0;

    setProfile( pf );
}

/*!
  Destroys the object
*/

Player::~Player()
{
//      if ( pBrain != 0 )
//          delete pBrain;
}

void Player::focusIn( Board *b )
{
    setBoard( b );
    if ( pBrain )
        pBrain->focusIn( b );
    else
        qDebug( QString( "Player %1 has no brain" ).arg( playerName() ) );
}

void Player::focusOut()
{
    if ( pBrain )
        pBrain->focusOut();
    else
        qDebug( QString( "Player %1 has no brain" ).arg( playerName() ) );
    setBoard( 0 );
}

void Player::setScore( int sc )
{
    if ( sc == Score )
        return;

    Score = sc;
    emit changed();
}

void Player::setSkip( int skip )
{
    if ( skip == Skip )
        return;

    Skip = skip;
    emit changed();
}

void Player::configure( QWidget *p )
{
    if ( pBrain )
        pBrain->configure( p );
    else
        qDebug( QString( "Player %1 has no brain" ).arg( playerName() ) );
}

bool Player::hasConfig()
{
    if ( pBrain )
        return pBrain->hasConfig();
    else
    {
        qDebug( QString( "Player %1 has no brain" ).arg( playerName() ) );
        return false;
    }
}

const QString &Player::playerName() const
{
    if ( pProf )
    {
        return pProf->profileName();
    }
    else
    {
        qDebug( QString( "%1 has no profile" ).arg( Name ) );
        return Name;
    }
}

//  void Player::setPlayerName( const QString &name )
//  {
//      if ( name == Name )
//          return;
//      Name = name;
//      emit nameChanged( name );
//  }

QString Player::type() const
{
    if ( pBrain )
        return pBrain->type();
    else
    {
        qDebug( QString( "Player %1 has no brain" ).arg( playerName() ) );
        return QString( "Unknown" );
    }
}

void Player::setBrain( Brain *b )
{
    if ( b == pBrain )
        return;
    if ( pBrain )
        delete pBrain;

    pBrain = b;
    if ( pBrain )
    {
        pBrain->setPlayer( this );
    }
    emit brainChanged( b );
}

void Player::setProfile( PlayerProfile *pf )
{
    pProf = pf;
    Score = 0;
    if ( pf != 0 )
    {
        setBrain( pf->brain() );
        connect( pf, SIGNAL( changed() ),
                 this, SLOT( doChanged() ) );
        emit changed();
    }
    else
    {
        setBrain( 0 );
    }
}

void Player::doChanged()
{
    if ( pProf != 0 )
        setBrain( pProf->brain() );
    emit changed();
}
