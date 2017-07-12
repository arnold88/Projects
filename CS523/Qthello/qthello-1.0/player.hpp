// 
// $Id: player.hpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Definition of Player class
//
// Jan Borsodi <jb@ez.no>
// Created on: <08-Oct-1999 13:25:48 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "board.hpp"
#include "brain.hpp"
#include "playerprofile.hpp"

#include <qstring.h>
#include <qobject.h>
#include <qwidget.h>
#include <qlist.h>

class Player : public QObject
{
    Q_OBJECT
public:
    Player( const QString &name, const Piece &p, PlayerProfile *pf, QObject *parent = 0, const char *n = 0 );
    virtual ~Player();

    virtual void focusIn( Board *b );
    virtual void focusOut();
    const QString &playerName() const;
//      void setPlayerName( const QString &name );
    virtual QString type() const;
    const Piece &piece() const { return Color; }
    void setPiece( const Piece &p ) { Color = p; }
    void setBrain( Brain *b );
    Brain *brain() const { return pBrain; }

    void setProfile( PlayerProfile *pf );
    PlayerProfile *profile() const { return pProf; }

    virtual void configure( QWidget *parent );
    virtual bool hasConfig();

    Board *board() const { return pBoard; }

    int score() const { return Score; }
    int skip() const { return Skip; }

signals:
    void doMove( int x, int y );
    void newScore( int score );
    void nameChanged( const QString &name );
    void brainChanged( Brain *b );
    void changed();

public slots:
    void setScore( int sc );
    void setSkip( int skip );
    void doChanged();

protected:
    void setBoard( Board *b ) { pBoard = b; }

private:
    QString Name;
    PlayerProfile *pProf;
    Board *pBoard;
    Piece Color;
    int Score;
    int Skip;
    Brain *pBrain;
};

#endif // PLAYER_HPP
