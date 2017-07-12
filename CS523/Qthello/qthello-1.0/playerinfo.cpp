// 
// $Id: playerinfo.cpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Implementation of PlayerInfo class
//
// Jan Borsodi <jb@ez.no>
// Created on: <18-Oct-1999 18:08:27 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//


#include "playerinfo.hpp"

#include <qframe.h>
#include <qwidget.h>
#include <qpainter.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qstring.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qlist.h>

/*!
  \class PlayerInfo playerinfo.hpp
  \brief

*/

/*!
  Default constructor
*/

PlayerInfo::PlayerInfo( Board *board, bool first, Player *ply, QWidget *parent, const char *name )
        : QFrame( parent, name )
{
    First = first;
    pBoard = board;
    pPlayer = ply;
    Playing = false;
    setFrameStyle( QFrame::Sunken | QFrame::Box );
    setLineWidth( 2 );

    connect( pPlayer, SIGNAL( nameChanged( const QString & ) ),
             this, SLOT( playerNameChanged( const QString & ) ) );
    connect( pPlayer, SIGNAL( changed() ),
             this, SLOT( playerChanged() ) );

    QVBoxLayout *lay = new QVBoxLayout( this, 4 + 3 );
    {
//          Brains = new QComboBox( false, this );
//          QList<Brain> blst = pPlayer->brains();
//          for ( QListIterator<Brain> it( blst ); it.current(); ++it )
//          {
//              Brains->insertItem( it.current()->type() );
//          }
//          connect( Brains, SIGNAL( activated( int ) ),
//                   this, SLOT( brainActivated( int ) ) );
//          lay->addWidget( Brains, 0 );
        pBrain = new QLabel( pPlayer->brain()->type(), this );
        lay->addWidget( pBrain, 0 );

        pNameLab = new QLabel( displayName(), this );
        lay->addWidget( pNameLab, 0 );

        pLab = new QLabel( "", this );
        lay->addWidget( pLab, 0 );

        pSkip = new QLabel( "", this );
        lay->addWidget( pSkip, 0 );

        lay->addStretch( 1 );

//          QHBoxLayout *hlay = new QHBoxLayout();
//          lay->addLayout( hlay, 0 );
//          {
//              hlay->addStretch( 1 );

//              Config = new QPushButton( tr( "Configure" ), this );
//              hlay->addWidget( Config, 0 );
//              if ( pPlayer != 0 )
//                  Config->setEnabled( pPlayer->hasConfig() );

//              connect( Config, SIGNAL( clicked() ),
//                       this, SLOT( configure() ) );
//          }
    }
//      connect( pPlayer, SIGNAL( newScore( int ) ),
//               this, SLOT( showScore( int ) ) );
    playerChanged();
}

/*!
  Destroys the object
*/

PlayerInfo::~PlayerInfo()
{
}

//  void PlayerInfo::drawContents( QPainter *p )
//  {
//  }

void PlayerInfo::showScore( int score )
{
    if ( score < 0 )
        pLab->setText( QString( "" ) );
    else
        pLab->setText( QString( "Score: %1" ).arg( score ) );
}

//  void PlayerInfo::configure()
//  {
//      if ( pPlayer != 0 )
//          pPlayer->configure( parentWidget() );
//  }

QString PlayerInfo::displayName() const
{
    return QString( "%1(%2)" )
        .arg( pPlayer->playerName() )
        .arg( pPlayer->piece().text() );
}

//  void PlayerInfo::brainActivated( int num )
//  {
//      pPlayer->setBrain( pPlayer->brain( num ) );
//      pNameLab->setText( displayName() );
//      if ( pPlayer != 0 )
//          Config->setEnabled( pPlayer->hasConfig() );
//  }

void PlayerInfo::playerNameChanged( const QString & )
{
    pNameLab->setText( displayName() );
}

void PlayerInfo::playing( bool p )
{
//      Brains->setEnabled( !p );
    Playing = p;
}

void PlayerInfo::playerChanged()
{
    pBrain->setText( pPlayer->brain()->type() );
    pNameLab->setText( displayName() );
    pLab->setText( QString( "Score: %1" ).arg( pPlayer->score() ) );
    pSkip->setText( QString( "Skips %1" ).arg( pPlayer->skip() ) );
}
