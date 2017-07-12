// 
// $Id: playerlist.cpp,v 1.1.1.1 2000/08/06 10:21:10 amos Exp $
//
// Implementation of PlayerList class
//
// Jan Borsodi <jb@ez.no>
// Created on: <20-Oct-1999 22:22:33 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//


#include "playerlist.hpp"
#include "humanconfig.hpp"
#include "randomcomputer.hpp"
#include "humanbrain.hpp"
#include "randomcomputer.hpp"
#include "firstbestcomputer.hpp"
#include "alphabetacomputer.hpp"
#include "alphabetanormalcomputer.hpp"
#include "alphabetaevalcomputer.hpp"
#include "alphabetadyncomputer.hpp"

#include <qscrollview.h>
#include <qwidget.h>
#include <qlist.h>
#include <qevent.h>
#include <qdialog.h>
#include <qtimer.h>
#include <qpopupmenu.h>
#include <qdir.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qstring.h>
#include <qpoint.h>

PlayerList *PlayerList::Instance_ = (PlayerList *)0;

/*!
  \class PlayerList playerlist.hpp
  \brief

*/

/*!
  Default constructor
*/

PlayerList::PlayerList( Othello *oth, QWidget *parent, const char *name )
    : QScrollView( parent, name )
{
    enableClipper( true );
    setCaption( "Profiles" );
    pOthello = oth;
    setVScrollBarMode( AlwaysOn );
    setHScrollBarMode( AlwaysOff );

    Brains.append( new HumanBrain( this, "humanbrain" ) );
    Brains.append( new RandomComputer( this, "randomcomputerbrain" ) );
    Brains.append( new FirstBestComputer( this, "firstbestcomputerbrain" ) );
    Brains.append( new AlphaBetaComputer( this, "alphabetacomputerbrain" ) );
    Brains.append( new AlphaBetaDynComputer( this, "alphabetacomputerbrain" ) );
    Brains.append( new AlphaBetaNormalComputer( this, "alphabetanormalcomputerbrain" ) );
    Brains.append( new AlphaBetaEvalComputer( this, "alphabetaevalcomputerbrain" ) );

    Redundant.setAutoDelete( true );

    pTimer = new QTimer( this );
    connect( pTimer, SIGNAL( timeout() ),
             this, SLOT( doFixup() ) );

    PlayerProfile *pf = new PlayerProfile( this, this );
    pf->setProfileName( "Player1" );
    pf->setBrain( brain( 0 ) );
    addPlayer( pf );

    pf = new PlayerProfile( this, this );
    pf->setComputer( true );
    pf->setBrain( brain( 1 ) );
    addPlayer( pf );

    pf = new PlayerProfile( this, this );
    pf->setComputer( true );
    pf->setBrain( brain( 2 ) );
    addPlayer( pf );

    pf = new PlayerProfile( this, this );
    pf->setComputer( true );
    pf->setBrain( brain( 3 ) );
    addPlayer( pf );

    pf = new PlayerProfile( this, this );
    pf->setComputer( true );
    pf->setBrain( brain( 4 ) );
    addPlayer( pf );

    pf = new PlayerProfile( this, this );
    pf->setComputer( true );
    pf->setBrain( brain( 5 ) );
    addPlayer( pf );

    pf = new PlayerProfile( this, this );
    pf->setComputer( true );
    pf->setBrain( brain( 6 ) );
    addPlayer( pf );

    load();

    resize( 190, 370 );
}

/*!
  Destroys the object
*/

PlayerList::~PlayerList()
{
    Instance_ = 0;
    save();
}

void PlayerList::addPlayer( PlayerProfile *p )
{
    if ( p->isComputer() )
        CPlayers.append( p );
    else
        HPlayers.append( p );
    p->resize( visibleWidth(), 20 );
    addChild( p );
    p->reparent( viewport(), QPoint( 0, 0 ) );
    p->show();
    calcPlayerPositions();
}

void PlayerList::removePlayer( PlayerProfile *p )
{
    if ( p->isComputer() )
    {
        if ( CPlayers.findRef( p ) != -1 )
        {
            CPlayers.remove( p );
            removeChild( p );
            p->hide();
            Redundant.append( p );
            calcPlayerPositions();
            pTimer->start( 0, true );
        }
    }
    else
    {
        if ( HPlayers.findRef( p ) != -1 )
        {
            if ( othello()->playerOne()->profile() == p )
                othello()->playerOne()->setProfile( computerProfile( 0 ) );
            if ( othello()->playerTwo()->profile() == p )
                othello()->playerTwo()->setProfile( computerProfile( 0 ) );
            HPlayers.remove( p );
            removeChild( p );
            p->hide();
            Redundant.append( p );
            calcPlayerPositions();
            pTimer->start( 0, true );
        }
    }
}

void PlayerList::calcPlayerPositions()
{
    resizeContents( viewport()->width(), HPlayers.count()*60 + 5 + CPlayers.count()*60 );
    int y = 0;
    for ( QListIterator<PlayerProfile> it( HPlayers ); it.current(); ++it )
    {
        moveChild( it.current(), 0, y );
        y += 60;
    }

    y += 5;
    for ( QListIterator<PlayerProfile> it( CPlayers ); it.current(); ++it )
    {
        moveChild( it.current(), 0, y );
        y += 60;
    }
}

void PlayerList::polish()
{
    resizeContents( 1, HPlayers.count()*60 + 5 + CPlayers.count()*60 );
}

void PlayerList::resizeEvent( QResizeEvent *e )
{
    QScrollView::resizeEvent( e );

    resizeContents( 1, HPlayers.count()*60 + 5 + CPlayers.count()*60 );

    for ( QListIterator<PlayerProfile> it( HPlayers ); it.current(); ++it )
    {
        it.current()->resize( visibleWidth(), 60 );
    }

    for ( QListIterator<PlayerProfile> it( CPlayers ); it.current(); ++it )
    {
        it.current()->resize( visibleWidth(), 60 );
    }
}

PlayerList *PlayerList::instance( Othello *oth = 0, QWidget *parent = 0, const char *name = 0 )
{
    if ( Instance_ == 0 )
    {
        Instance_ = new PlayerList( oth, parent, name );
    }
    return Instance_;
}

PlayerProfile *PlayerList::humanProfile( int num )
{
    return HPlayers.at( num );
}

PlayerProfile *PlayerList::computerProfile( int num )
{
    return CPlayers.at( num );
}

void PlayerList::setPlaying( bool p )
{
    setEnabled( !p );
    for ( QListIterator<PlayerProfile> it( HPlayers ); it.current(); ++it )
    {
        it.current()->setEnabled( !p );
    }

    for ( QListIterator<PlayerProfile> it( CPlayers ); it.current(); ++it )
    {
        it.current()->setEnabled( !p );
    }
}

void PlayerList::addNewHuman()
{
    HumanConfig c( tr( "Player" ), true, tr( "Create new human player" ), this );
    if ( c.exec() == QDialog::Accepted )
    {
        PlayerProfile *pf = new PlayerProfile( this, this );
        pf->setProfileName( c.playerName() );
        HumanBrain *b = dynamic_cast<HumanBrain *>(brain( 0 ));
        pf->setBrain( b );
        b->setMarkers( c.markersOn() );
        addPlayer( pf );
//          emit changed();
    }
}

void PlayerList::doFixup()
{
    Redundant.clear();
}

void PlayerList::viewportMousePressEvent( QMouseEvent *e )
{
    if ( e->button() == RightButton )
    {
        QPopupMenu m( this );
        m.insertItem( "New Player", this, SLOT( addNewHuman() ) );
        m.exec( mapToGlobal( e->pos() ) );
    }
}

void PlayerList::save()
{
    QDir d( QDir::homeDirPath() + "/.qthello" );
    if ( !d.exists() )
    {
        d.mkdir( QDir::homeDirPath() + "/.qthello" );
    }

    QFile hf( d.path() + "/HumanProfiles" );
    if ( hf.open( IO_WriteOnly ) )
    {
        QTextStream s( &hf );
        int cnt = HPlayers.count();
        s << cnt << "\n\n";
        for ( QListIterator<PlayerProfile> it( HPlayers ); it.current(); ++it )
        {
            s << it.current()->profileName() << "\n"
              << it.current()->brainReference()->num() << "\n";
            it.current()->brain()->save( s );
            s << "\n";
        }
    }

    QFile cf( d.path()  + "/ComputerProfiles" );
    if ( cf.open( IO_WriteOnly ) )
    {
        QTextStream s( &cf );
        int cnt = CPlayers.count();
        s << cnt << "\n\n";
        for ( QListIterator<PlayerProfile> it( CPlayers ); it.current(); ++it )
        {
            s << it.current()->brain()->num() << "\n";
            it.current()->brainReference()->save( s );
            s << "\n";
        }
    }
}

void PlayerList::load()
{
    QDir d( QDir::homeDirPath() + "/.qthello" );
    if ( !d.exists() )
    {
//          QDir d_tmp( QDir::homeDirPath() );
//          d_tmp.mkdir( ".qthello" );
        return;
    }

    QFile hf( d.path() + "/HumanProfiles" );
    if ( hf.open( IO_ReadOnly ) )
    {
        for ( QListIterator<PlayerProfile> it( HPlayers ); it.current(); ++it )
            Redundant.append( it.current() );
        HPlayers.clear();
        QTextStream s( &hf );
        PlayerProfile *pf;
        int cnt;
        s >> cnt;
        while ( cnt )
        {
            QString name;
            int num;
            s >> name
              >> num;
            pf = new PlayerProfile( this, this );
            pf->setProfileName( name );
            pf->setBrain( brain( num ) );
            addPlayer( pf );
            pf->brainReference()->load( s );
            cnt--;
        }
    }

    QFile cf( d.path()  + "/ComputerProfiles" );
    if ( cf.open( IO_ReadOnly ) )
    {
        for ( QListIterator<PlayerProfile> it( CPlayers ); it.current(); ++it )
            Redundant.append( it.current() );
        CPlayers.clear();
        QTextStream s( &cf );
        PlayerProfile *pf;
        int cnt;
        s >> cnt;
        while ( cnt )
        {
            int num;
            s >> num;
            pf = new PlayerProfile( this, this );
            pf->setComputer( true );
            pf->setBrain( brain( num ) );
            addPlayer( pf );
            pf->brainReference()->load( s );
            cnt--;
        }
    }
    pTimer->start( 0, true );
    calcPlayerPositions();
}
