// 
// $Id: othello.cpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Implementation of Othello class
//
// Jan Borsodi <jb@ez.no>
// Created on: <08-Oct-1999 16:12:25 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//


#include "othello.hpp"
#include "player.hpp"
#include "playerinfo.hpp"

#include <qwidget.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qstring.h>
#include <qmainwindow.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qpixmap.h>
#include <qmessagebox.h>
#include <qsize.h>
#include <qglobal.h>

/*!
  \class Othello othello.hpp
  \brief

*/

/*!
  Default constructor
*/

Othello::Othello( QWidget *parent, const char *name )
    : QMainWindow( parent, name )
{
    setCaption( "QtHello" );

    cw = new QWidget( this, "central widget" );
    {
        QHBoxLayout *lay = new QHBoxLayout( cw, 2 );
        {
            BWidget = new BoardWidget( cw );
            lay->addWidget( BWidget, 0 );

            QVBoxLayout *vlay = new QVBoxLayout();
            lay->addLayout( vlay, 0 );
            {
//                  NGame = new QPushButton( "&New Game", cw );
//                  vlay->addWidget( NGame, 0 );

                Ply1 = new PlayerInfo( BWidget->playBoard(), true, BWidget->playBoard()->playerOne(), cw, "playerinfo1" );
                vlay->addWidget( Ply1, 1 );

                connect( BWidget->playBoard(), SIGNAL( playing( bool ) ),
                         Ply1, SLOT( playing( bool ) ) );

                Ply2 = new PlayerInfo( BWidget->playBoard(), false, BWidget->playBoard()->playerTwo(), cw, "playerinfo2" );
                vlay->addWidget( Ply2, 1 );

                connect( BWidget->playBoard(), SIGNAL( playing( bool ) ),
                         Ply2, SLOT( playing( bool ) ) );

            }
        }
        lay->setResizeMode( QLayout::Fixed );
    }

    connect( BWidget->playBoard(), SIGNAL( winner( const QString & ) ),
             this, SLOT( winner( const QString & ) ) );

    QToolBar *tb = new QToolBar( this );
    QPixmap pm( "new.xpm" );
    QPixmap pm_magplus( "viewmag+.png" );
    QPixmap pm_magminus( "viewmag-.png" );
    QPixmap pm_stop( "stop.png" );
    (void)new QToolButton( pm, "New Game", "", this, SLOT( startGame() ), tb );
    (void)new QToolButton( pm, "New Games(For two computers)", "", this, SLOT( startMultiple() ), tb );
    (void)new QToolButton( pm_stop, "Stop Game", "", BWidget, SLOT( stopGame() ), tb );
    (void)new QToolButton( pm_magplus, "Increase Size", "", this, SLOT( increaseSize() ), tb );
    (void)new QToolButton( pm_magminus, "Decrease Size", "", this, SLOT( decreaseSize() ), tb );

    setCentralWidget( cw );

    setFixedSize( QSize( 0, 0 ) );

//      connect( NGame, SIGNAL( clicked() ),
//               BWidget, SLOT( newGame() ) );
}

/*!
  Destroys the object
*/

Othello::~Othello()
{
}

//  void Othello::setPlayerScore( Player *p, int score )
//  {
//      QString str = QString( "%1: %2" ).arg( p->piece().text() ).arg( score );
//      if ( p->first() )
//          PlayerOneText->setText( str );
//      else
//          PlayerTwoText->setText( str );
//  }

void Othello::winner( const QString &t )
{
    if ( Multiple )
    {
        qDebug( t );
        if ( --Count > 0 )
            BWidget->newGame();
    }
    else
        QMessageBox::information( this, "And the winner is", t, 1 );
}

void Othello::startGame()
{
    Multiple = false;
    BWidget->newGame();
}

void Othello::startMultiple()
{
    Multiple = true;
    Count = 10;
    BWidget->newGame();
}

void Othello::increaseSize()
{
    if ( BWidget->boardSize() < 256 )
    {
        BWidget->setBoardSize( BWidget->boardSize()*2 );
        layout()->setResizeMode( QLayout::Fixed );
    }
}

void Othello::decreaseSize()
{
    if ( BWidget->boardSize() > 8 )
    {
        BWidget->setBoardSize( BWidget->boardSize()/2 );
        layout()->setResizeMode( QLayout::Fixed );
    }
}
