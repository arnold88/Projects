// 
// $Id: boardwidget.cpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Implementation of BoardWidget class
//
// Jan Borsodi <jb@ez.no>
// Created on: <08-Oct-1999 14:59:10 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//


#include "boardwidget.hpp"
#include <qwidget.h>
#include <qevent.h>
#include <qframe.h>
#include <qpainter.h>
#include <qrect.h>
#include <qsize.h>
#include <qcolor.h>
#include <qwmatrix.h>
#include <qtimer.h>
#include <qglobal.h>

/*!
  \class BoardWidget boardwidget.hpp
  \brief

*/

/*!
  Default constructor
*/

BoardWidget::BoardWidget( QWidget *parent, const char *name )
    : QFrame( parent, name )
{
    X = Y = -1;
    pPlayBoard = new Board( 0, 0, this );
    connect( pPlayBoard, SIGNAL( repaint() ),
             this, SLOT( doRepaint() ) );
    connect( pPlayBoard, SIGNAL( newPlayer( Player * ) ),
             this, SLOT( doNewPlayer( Player * ) ) );
    connect( pPlayBoard, SIGNAL( doOverlayReset() ),
             this, SLOT( doOverlayReset() ) );
    connect( pPlayBoard, SIGNAL( doOverlayStop() ),
             this, SLOT( doOverlayStop() ) );

    setBackgroundMode( NoBackground );

    setMouseTracking( true );

    if ( !Black.load( "gfx/black.gif" ) )
        qDebug( "Error loading pixmap" );
    if ( !White.load( "gfx/white.gif" ) )
        qDebug( "Error loading pixmap" );

    setBoardSize( 32 );
    ShowOverlay = false;
    Timer = new QTimer( this, "overlay timer" );
    connect( Timer, SIGNAL( timeout() ),
             this, SLOT( doOverlaySwap() ) );
}

/*!
  Destroys the object
*/

BoardWidget::~BoardWidget()
{
}

void BoardWidget::setBoardSize( int size )
{
    if ( size < 1 )
        return;
    Size = size;
    QSize s( 8*(Size+1) + 1, 8*(Size+1) + 1 );
    resize( s );
    SizeHint = s;
    setFixedSize( s );
    QWMatrix mw;
    mw.scale( ((double)Size)/((double)White.width()), ((double)Size)/((double)White.height()) );
    WhiteSized = White.xForm( mw );
    QWMatrix mb;
    mb.scale( (double)Size/(double)Black.width(), (double)Size/(double)Black.height() );
    BlackSized = Black.xForm( mb );
}


QSize BoardWidget::sizeHint() const
{
    return SizeHint;
}

QSizePolicy BoardWidget::sizePolicy() const
{
    return QSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
}

void BoardWidget::mousePressEvent( QMouseEvent *e )
{
    if ( !pPlayBoard )
        return;
    if ( e->x() >= 8*(Size+1) || e->y() >= 8*(Size+1) )
        return;
    int x, y;
    x = e->x();
    y = e->y();
    if ( x % Size+1 > 0 && y % Size+1 > 0 )
    {
        x /= Size+1;
        y /= Size+1;
        pPlayBoard->doMousePressEvent( x, y );
    }
}

void BoardWidget::mouseMoveEvent( QMouseEvent *e )
{
    X = e->x();
    Y = e->y();
    if ( !pPlayBoard )
        return;
    if ( ( e->state() & (LeftButton | RightButton | MidButton ) )  != 0 )
        return;
    filterMouseMove( e->x(), e->y() );
}

void BoardWidget::filterMouseMove( int x, int y )
{
    if ( x >= 8*(Size+1) || y >= 8*(Size+1) )
        return;
    if ( x % Size+1 > 0 && y % Size+1 > 0 )
    {
        x /= Size+1;
        y /= Size+1;
        pPlayBoard->doMouseMoveEvent( x, y );
    }
}

void BoardWidget::drawContents( QPainter *p )
{
    QRect r = contentsRect();
    for ( int y = 0; y <= 8; y++ )
    {
        int ry = r.topLeft().y() + y*(Size+1);
        p->drawLine( r.topLeft().x(), ry, r.topRight().x(), ry );
    }
    for ( int x = 0; x <= 8; x++ )
    {
        int rx = r.topLeft().x() + x*(Size+1);
        p->drawLine( rx, r.topLeft().y(), rx, r.bottomLeft().y() );
    }
    for ( int y = 0; y < 8; y++ )
    {
        for ( int x = 0; x < 8; x++ )
        {
            QRect prect( r.topLeft().x() + x*(Size+1) + 1, r.topLeft().y() + y*(Size+1) + 1,
                         Size, Size );
            p->translate( prect.x(), prect.y() );
            Piece opiece = pPlayBoard->overlay().at( x, y );
            if ( ShowOverlay && opiece != Piece::Blank )
            {
                drawPiece( p, opiece );
            }
            else
            {
                Piece mpiece = pPlayBoard->marker().at( x, y );
                if ( mpiece != Piece::Marked )
                    drawPiece( p, pPlayBoard->matrix().at( x, y ) );
                else
                    drawPiece( p, mpiece );
            }
            p->translate( -prect.x(), -prect.y() );
        }
    }
}

void BoardWidget::drawPiece( QPainter *p, const Piece &piece )
{
    if ( piece.type() == Piece::Blank )
    {
        p->fillRect( 0, 0, Size, Size, QColor( 35, 121, 21 ) );
    }
    else if ( piece.type() == Piece::Marked )
    {
        p->fillRect( 0, 0, Size, Size, QColor( 35, 121, 21 ).dark() );
    }
    else if ( piece.type() == Piece::White )
    {
        p->drawPixmap( 0, 0, WhiteSized );
    }
    else if ( piece.type() == Piece::Black )
    {
        p->drawPixmap( 0, 0, BlackSized );
    }
    else
    {
        p->drawText( QRect( 0, 0, Size, Size ), AlignCenter, "Error" );
    }
}

void BoardWidget::newGame()
{
    if ( pPlayBoard->playing() )
        pPlayBoard->stopGame();
    ShowOverlay = false;

    pPlayBoard->matrix().clear();
    pPlayBoard->matrix().setAt( 3, 3, Piece( Piece::White ) );
    pPlayBoard->matrix().setAt( 4, 4, Piece( Piece::White ) );
    pPlayBoard->matrix().setAt( 3, 4, Piece( Piece::Black ) );
    pPlayBoard->matrix().setAt( 4, 3, Piece( Piece::Black ) );
    doRepaint();

    pPlayBoard->startGame();
    filterMouseMove( X, Y );
    ShowOverlay = true;
}

void BoardWidget::stopGame()
{
    if ( pPlayBoard->playing() )
        pPlayBoard->stopGame();
    Timer->stop();
    ShowOverlay = false;
}

void BoardWidget::doRepaint()
{
    repaint( true );
}

void BoardWidget::doNewPlayer( Player * )
{
    filterMouseMove( X, Y );
    doOverlayReset();
}

void BoardWidget::doOverlaySwap()
{
    ShowOverlay = !ShowOverlay;
    repaint( true );
}

void BoardWidget::doOverlayReset()
{
    Timer->start( 300, false );
    ShowOverlay = true;
    repaint( true );
}

void BoardWidget::doOverlayStop()
{
    Timer->stop();
    ShowOverlay = false;
    repaint( true );
}

void BoardWidget::enterEvent( QEvent * )
{
    pPlayBoard->doEnterEvent();
}

void BoardWidget::leaveEvent( QEvent * )
{
    X = -1;
    Y = -1;
    pPlayBoard->doLeaveEvent();
}
