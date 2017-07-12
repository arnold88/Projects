// 
// $Id: othello.hpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Definition of Othello class
//
// Jan Borsodi <jb@ez.no>
// Created on: <08-Oct-1999 16:12:26 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef OTHELLO_HPP
#define OTHELLO_HPP

#include "boardwidget.hpp"
#include "playerinfo.hpp"

#include <qwidget.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qmainwindow.h>
#include <qstring.h>
#include <qobject.h>

class Othello : public QMainWindow
{
    Q_OBJECT
public:
    Othello( QWidget *parent = 0, const char *name = 0 );
    virtual ~Othello();

    Player *playerOne() { return BWidget->playBoard()->playerOne(); }
    Player *playerTwo() { return BWidget->playBoard()->playerTwo(); }

public slots:
    void winner( const QString &t );
    void startGame();
    void startMultiple();
    void increaseSize();
    void decreaseSize();

private:
    BoardWidget *BWidget;
//      QPushButton *NGame;
    PlayerInfo *Ply1;
    PlayerInfo *Ply2;
    bool Multiple;
    int Count;
    QWidget *cw;
};


#endif // OTHELLO_HPP
