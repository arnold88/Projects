// 
// $Id: boardwidget.hpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Definition of BoardWidget class
//
// Jan Borsodi <jb@ez.no>
// Created on: <08-Oct-1999 14:59:10 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef BOARDWIDGET_HPP
#define BOARDWIDGET_HPP

#include "board.hpp"

#include <qwidget.h>
#include <qevent.h>
#include <qframe.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qtimer.h>
#include <qobject.h>
#include <qsize.h>

class BoardWidget : public QFrame
{
    Q_OBJECT
public:
    BoardWidget( QWidget *parent = 0, const char *name = 0 );
    virtual ~BoardWidget();

    void setBoardSize( int size );
    int boardSize() const { return Size; }
    Board *playBoard() const { return pPlayBoard; }

    virtual QSize sizeHint() const;
    virtual QSizePolicy sizePolicy() const;

public slots:
    void newGame();
    void stopGame();

private slots:
    void doRepaint();
    void doNewPlayer( Player *p );
    void doOverlaySwap();
    void doOverlayReset();
    void doOverlayStop();

protected:
    virtual void mousePressEvent( QMouseEvent *e );
    virtual void mouseMoveEvent( QMouseEvent *e );
    virtual void enterEvent( QEvent *e );
    virtual void leaveEvent( QEvent *e );
    virtual void drawContents( QPainter *p );
    virtual void drawPiece( QPainter *p, const Piece &p );
    void filterMouseMove( int x, int y );

private:
    Board *pPlayBoard;
    int Size;
    QPixmap Black, White;
    QPixmap BlackSized, WhiteSized;
    bool ShowOverlay;
    QTimer *Timer;
    int X, Y;
    QSize SizeHint;
};


#endif // BOARDWIDGET_HPP
