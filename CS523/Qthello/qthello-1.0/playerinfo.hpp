// 
// $Id: playerinfo.hpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Definition of PlayerInfo class
//
// Jan Borsodi <jb@ez.no>
// Created on: <18-Oct-1999 18:08:28 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef PLAYERINFO_HPP
#define PLAYERINFO_HPP

#include "player.hpp"
#include "board.hpp"
#include "brain.hpp"

#include <qlabel.h>
#include <qframe.h>
#include <qstring.h>
#include <qpainter.h>
#include <qwidget.h>
#include <qpushbutton.h>
#include <qcombobox.h>

class PlayerInfo : public QFrame
{
    Q_OBJECT
public:
    PlayerInfo( Board *board, bool first, Player *ply, QWidget *parent = 0, const char *name = 0 );
    virtual ~PlayerInfo();

    QString displayName() const;
    bool first() const { return First; }

private slots:
    void showScore( int score );
//      void configure();
//      void brainActivated( int );
    void playerNameChanged( const QString & );
    void playing( bool p );
    void playerChanged();

//  protected:
//      virtual void drawContents( QPainter *p );

private:
    Player *pPlayer;
    Board *pBoard;
    QLabel *pLab;
    QLabel *pSkip;
    QLabel *pNameLab;
//      QPushButton *Config;
//      QComboBox *Brains;
    QLabel *pBrain;
    bool First;
    bool Playing;
};

#endif // PLAYERINFO_HPP
