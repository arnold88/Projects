// 
// $Id: playerlist.hpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Definition of PlayerList class
//
// Jan Borsodi <jb@ez.no>
// Created on: <20-Oct-1999 22:22:34 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef PLAYERLIST_HPP
#define PLAYERLIST_HPP

#include "playerprofile.hpp"
#include "othello.hpp"

#include <qscrollview.h>
#include <qwidget.h>
#include <qlist.h>
#include <qevent.h>
#include <qtimer.h>

class PlayerList : public QScrollView
{
    Q_OBJECT
public:
    virtual ~PlayerList();

    void addPlayer( PlayerProfile *p );
    void removePlayer( PlayerProfile *p );

    const QList<Brain> &brains() const { return Brains; }
    Brain *brain( int num ) { Brain *b = Brains.at( num )->clone(); b->setNum( num ); return b; }
    int brain( Brain *b ) { return Brains.findRef( b ); }

    PlayerProfile *humanProfile( int num );
    PlayerProfile *computerProfile( int num );

    void setOthello( Othello *o ) { pOthello = o; }
    Othello *othello() const { return pOthello; }

    static PlayerList *instance( Othello *oth = 0, QWidget *parent = 0, const char *name = 0 );

    void setPlaying( bool p );

    void save();
    void load();

public slots:
    void addNewHuman();

private slots:
    void doFixup();

protected:
    void calcPlayerPositions();
    virtual void resizeEvent( QResizeEvent *e );
    virtual void viewportMousePressEvent( QMouseEvent *e );
    virtual void polish();

private:
    PlayerList( Othello *oth, QWidget *parent = 0, const char *name = 0 );

    QList<PlayerProfile> HPlayers;
    QList<PlayerProfile> CPlayers;
    QList<PlayerProfile> Redundant;
    QList<Brain> Brains;
    Othello *pOthello;

    QTimer *pTimer;

    static PlayerList *Instance_;
};


#endif // PLAYERLIST_HPP
