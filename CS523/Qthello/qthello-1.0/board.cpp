// 
// $Id: board.cpp,v 1.1.1.1 2000/08/06 10:21:08 amos Exp $
//
// Implementation of Board class
//
// Jan Borsodi <jb@ez.no>
// Created on: <08-Oct-1999 13:48:47 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//


#include "board.hpp"
#include "player.hpp"
#include "exception.hpp"
#include "playerlist.hpp"

#include <qobject.h>
#include <qevent.h>
#include <qstring.h>
#include <qpoint.h>

/*!
  \class Board board.hpp
  \brief

*/

/*!
  Default constructor
*/

Board::Board( Player *p1, Player *p2, QObject *parent, const char *name )
        : QObject( parent, name )
{
    pPlayer1 = p1;
    pPlayer2 = p2;
    pPlayer = pPlayer1;
    Playing = false;

//    pPlayBoard->setPlayerOne( new RandomComputer( "player1", Piece( Piece::Black ), true, this, "player1" ) );
//      pPlayBoard->setPlayerTwo( new HumanPlayer( "player2", Piece( Piece::White ), false, this, "player2" ) );

    setPlayerOne( new Player( "Player1", Piece( Piece::Black ), PlayerList::instance()->humanProfile( 0 ), this, "player1" ) );
    setPlayerTwo( new Player( "Player2", Piece( Piece::White ), PlayerList::instance()->computerProfile( 0 ), this, "player2" ) );
}

/*!
  Destroys the object
*/

Board::~Board()
{
}

void Board::doMousePressEvent( int x, int y )
{
    emit mousePress( x, y );
}

void Board::doMouseMoveEvent( int x, int y )
{
    emit mouseMove( x, y );
}

void Board::doMouseReleaseEvent( int x, int y )
{
    emit mouseRelease( x, y );
}

void Board::doEnterEvent()
{
    emit enter();
}

void Board::doLeaveEvent()
{
    emit leave();
}

bool Board::canMove( Player *p, int x, int y )
{
    try
    {
        MatrixRotator r = PlayBoard.on( x, y );
        return r.legalMove( p->piece() );
    }
    catch ( OutOfRangeException &e )
    {
        qDebug( QString( "canMove::Error: %1" ).arg( e.text() ) );
        return false;
    }
}

void Board::movePiece( Player *p, int x, int y )
{
    MatrixRotator r = PlayBoard.on( x, y );
    if ( r.legalMove( p->piece() ) )
    {
        try
        {
            r.flipPieces( p->piece() );
            swapPlayer();
            emit repaint();
            showScore();
        }
        catch ( OutOfRangeException &e )
        {
            qDebug( QString( "movePiece::Error: %1" ).arg( e.text() ) );
        }
    }
    else
    {
        qDebug( "Error: Tried illegal move, probably an error in the player code" );
    }
}

QValueList<QPoint> Board::availableMoves( Player *p, Matrix &m )
{
    QValueList<QPoint> plist;
    for ( int y = 0; y < 8; y++ )
    {
        for ( int x = 0; x < 8; x++ )
        {
            MatrixRotator r = m.on( x, y );
            if ( r.legalMove( p->piece() ) )
            {
                plist.append( QPoint( x, y ) );
            }
        }
    }
    return plist;
}

void Board::startGame()
{
    pPlayer1->setScore( 0 );
    pPlayer1->setSkip( 0 );
    pPlayer2->setScore( 0 );
    pPlayer2->setSkip( 0 );
    pPlayer1->brain()->init();
    pPlayer2->brain()->init();
    pPlayer = pPlayer1;
    clearOverlay();
    clearMarker();
    pPlayer->focusIn( this );
    Playing = true;
    PlayerList::instance()->setPlaying( Playing );
    emit playing( Playing );
    emit newPlayer( pPlayer );
    showScore();
}

void Board::stopGame()
{
    pPlayer->focusOut();
    Playing = false;
    PlayerList::instance()->setPlaying( Playing );
    emit playing( Playing );
    showScore();
    pPlayer1->brain()->close();
    pPlayer2->brain()->close();
}

void Board::swapPlayer()
{
    if ( !pPlayer )
    {
        qDebug( "Error: cannot swap players when none is active" );
        return;
    }
    clearOverlay();
    clearMarker();
    pPlayer->focusOut();
    if ( pPlayer == pPlayer1 )
        pPlayer = pPlayer2;
    else
        pPlayer = pPlayer1;
    pPlayer->focusIn( this );
    emit newPlayer( pPlayer );

    if ( mustSkip( pPlayer ) )
    {
        pPlayer->setSkip( pPlayer->skip() + 1 );
        qDebug( QString( "Skipping player %1" ).arg( pPlayer->playerName() ) );
        if ( !pPlayer )
        {
            qDebug( "Error: cannot swap players when none is active" );
            return;
        }
        clearOverlay();
        clearMarker();
        pPlayer->focusOut();
        if ( pPlayer == pPlayer1 )
            pPlayer = pPlayer2;
        else
            pPlayer = pPlayer1;
        pPlayer->focusIn( this );
        emit newPlayer( pPlayer );
        if ( mustSkip( pPlayer ) )
        {
            stopGame();
//              qDebug( "No players can play, stopping game" );
            int cnt1 = pieceCount( pPlayer1 );
            int cnt2 = pieceCount( pPlayer2 );
            if ( cnt1 == cnt2 )
                emit winner( "It's a draw" );
            else
            {
                Player *win;
                Player *loose;
                if ( cnt1 > cnt2 )
                {
                    win = pPlayer1;
                    loose = pPlayer2;
                }
                else
                {
                    win = pPlayer2;
                    loose = pPlayer1;
                }
                emit winner( QString( "%1:%2(%3) wins the game, %4 to %5" )
                             .arg( win->type() )
                             .arg( win->playerName() )
                             .arg( win->piece().text() )
                             .arg( pieceCount( win ) )
                             .arg( pieceCount( loose ) ) );
            }
        }
    }
}

void Board::showScore()
{
    pPlayer1->setScore( pieceCount( pPlayer1 ) );
    pPlayer2->setScore( pieceCount( pPlayer2 ) );
//    emit showPlayerScore( pPlayer1, pieceCount( pPlayer1 ) );
//    emit showPlayerScore( pPlayer2, pieceCount( pPlayer2 ) );
}

int Board::pieceCount( Player *p )
{
    int score = 0;
    for ( int i = 0; i < 8*8; i++ )
    {
        if ( PlayBoard[i] == p->piece() )
            score++;
    }
    return score;
}

void Board::setOverlayPiece( const Piece &p, int x, int y )
{
    try
    {
        OverlayBoard.setAt( x, y, p );
//          emit repaint();
    }
    catch ( OutOfRangeException &e )
    {
        qDebug( QString( "setOverlayPiece::error: %1" ).arg( e.text() ) );
    }
}

void Board::clearOverlay()
{
    OverlayBoard.clear();
//      emit repaint();
}

void Board::clearMarker()
{
    Marker.clear();
}

void Board::overlayReset()
{
    emit doOverlayReset();
}

void Board::overlayStop()
{
    emit doOverlayStop();
}

bool Board::mustSkip( Player *p )
{
    MatrixRotator m;
    for ( int y = 0; y < 8; y++ )
    {
        for ( int x = 0; x < 8; x++ )
        {
            m = PlayBoard.on( x, y );
            if ( m.legalMove( p->piece() ) )
                return false;
        }
    }
    return true;
}

void Board::setPlayer( bool first, Player *p )
{
    if ( first )
        pPlayer1 = p;
    else
        pPlayer2 = p;
}
