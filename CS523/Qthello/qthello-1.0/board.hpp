// 
// $Id: board.hpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Definition of Board class
//
// Jan Borsodi <jb@ez.no>
// Created on: <08-Oct-1999 13:48:48 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef BOARD_HPP
#define BOARD_HPP

#include "matrix.hpp"

#include <qobject.h>
#include <qevent.h>
#include <qpoint.h>
#include <qlist.h>
#include <qstring.h>

class Player;

class Board : public QObject
{
    Q_OBJECT
public:
    Board( Player *p1, Player *p2, QObject *parent = 0, const char *name = 0 );
    virtual ~Board();

    void setPlayerOne( Player *p ) { setPlayer( true, p ); }
    void setPlayerTwo( Player *p ) { setPlayer( false, p ); }
    void setPlayer( bool first, Player *p );
    Player *playerOne() const { return pPlayer1; }
    Player *playerTwo() const { return pPlayer2; }
    Player *currentPlayer() const { return pPlayer; }

    void startGame();
    void stopGame();
    bool playing() const { return Playing; }

    void doMousePressEvent( int x, int y );
    void doMouseMoveEvent( int x, int y );
    void doMouseReleaseEvent( int x, int y );
    void doEnterEvent();
    void doLeaveEvent();

    bool canMove( Player *p, int x, int y );
    QValueList<QPoint> availableMoves( Player *p, Matrix &m );
    void setOverlayPiece( const Piece &p, int x, int y );
    void clearOverlay();
    void clearMarker();

    Matrix &matrix() { return PlayBoard; }
    Matrix &marker() { return Marker; }
    Matrix &overlay() { return OverlayBoard; }

signals:
    void mousePress( int x, int y );
    void mouseMove( int x, int y );
    void mouseRelease( int x, int y );
    void enter();
    void leave();
    void repaint();
    void playing( bool p );
    void newPlayer( Player *p );
    void winner( const QString &txt );
    void doOverlayReset();
    void doOverlayStop();
//      void showPlayerScore( Player *p, int sc );

public slots:
    void movePiece( Player *p, int x, int y );
    void overlayReset();
    void overlayStop();

protected:
    void swapPlayer();
    bool mustSkip( Player *p );
    void showScore();
    int pieceCount( Player *p );

private:
    Player *pPlayer1;
    Player *pPlayer2;
    Player *pPlayer;
    Matrix PlayBoard;
    Matrix Marker;
    Matrix OverlayBoard;
    bool Playing;
};


#endif // BOARD_HPP
