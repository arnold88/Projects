// 
// $Id: playerprofile.cpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Implementation of PlayerProfile class
//
// Jan Borsodi <jb@ez.no>
// Created on: <20-Oct-1999 21:41:32 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//


#include "playerprofile.hpp"
#include "playerlist.hpp"

#include <qwidget.h>
#include <qframe.h>
#include <qpainter.h>
#include <qrect.h>
#include <qstring.h>
#include <qevent.h>
#include <qpopupmenu.h>

/*!
  \class PlayerProfile playerprofile.hpp
  \brief

*/

/*!
  Default constructor
*/

PlayerProfile::PlayerProfile( PlayerList *owner, QWidget *parent, const char *name )
    : QFrame( parent, name )
{
    pBrain = 0;
    pOwner = owner;
    bComp = false;
    setFrameStyle( QFrame::Raised | QFrame::Box );

}

/*!
  Destroys the object
*/

PlayerProfile::~PlayerProfile()
{
    if ( pBrain != 0 )
        delete pBrain;
}

void PlayerProfile::configure()
{
    if ( pBrain != 0 )
        pBrain->configure( owner() );
}

void PlayerProfile::drawContents( QPainter *p )
{
    QRect r = contentsRect();
    if ( pBrain != 0 )
    {
        QString name = Name;
        if ( pBrain->hasBrainName() )
            name = pBrain->brainName();
        QString type = pBrain->type();
        QString str = name + "\n" + type;
        p->drawText( r, AlignTop | AlignHCenter, str );
    }
    else
        p->drawText( r, AlignCenter, "Brainless" );
}

void PlayerProfile::mousePressEvent( QMouseEvent *e )
{
    if ( e->button() == RightButton )
    {
        QPopupMenu m( this );
        int ply1id = m.insertItem( "as Player1", this, SLOT( asPlayerOne() ) );
        m.setItemEnabled( ply1id, owner()->othello()->playerTwo()->profile() != this || isComputer() );
        int ply2id = m.insertItem( "as Player2", this, SLOT( asPlayerTwo() ) );
        m.setItemEnabled( ply2id, owner()->othello()->playerOne()->profile() != this || isComputer() );
        m.insertSeparator();
        m.insertItem( "Configure", this, SLOT( configure() ) );
        m.insertSeparator();
        m.insertItem( "New Player", owner(), SLOT( addNewHuman() ) );
        if ( !isComputer() )
            m.insertItem( "Delete", this, SLOT( doDelete() ) );
        m.exec( mapToGlobal( e->pos() ) );
    }
    else if ( e->button() == LeftButton )
    {
    }
}

void PlayerProfile::asPlayerOne()
{
    if ( owner()->othello()->playerTwo()->profile() == this && !isComputer() )
        return;
    owner()->othello()->playerOne()->setProfile( this );
}

void PlayerProfile::asPlayerTwo()
{
    if ( owner()->othello()->playerOne()->profile() == this && !isComputer() )
        return;
    owner()->othello()->playerTwo()->setProfile( this );
}

void PlayerProfile::setBrain( Brain *b )
{
    if ( b == pBrain )
        return;
    if ( pBrain != 0 )
        delete pBrain;
    pBrain = b;
    if ( pBrain )
    {
        pBrain->setPlayerProfile( this );
        connect( pBrain, SIGNAL( changed() ),
                 this, SLOT( doChanged() ) );
    }
}

const QString &PlayerProfile::profileName() const
{
    if ( pBrain != 0 )
    {
        if ( pBrain->hasBrainName() )
            return pBrain->brainName();
    }
    return Name;
}

void PlayerProfile::setProfileName( const QString &name )
{
    if ( Name == name )
        return;
    Name = name;
    repaint( true );
}

void PlayerProfile::doChanged()
{
    emit changed();
}

void PlayerProfile::doDelete()
{
    owner()->removePlayer( this );
}

