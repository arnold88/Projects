// 
// $Id: brain.hpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Definition of Brain class
//
// Jan Borsodi <jb@ez.no>
// Created on: <20-Oct-1999 15:41:38 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef BRAIN_HPP
#define BRAIN_HPP

#include "board.hpp"

#include <qobject.h>
#include <qstring.h>
#include <qwidget.h>
#include <qtextstream.h>

class PlayerProfile;

class Brain : public QObject
{
    Q_OBJECT
public:
    Brain( QObject *parent = 0, const char *name = 0 );
    Brain( const Brain *b );
    virtual ~Brain();

    virtual void focusIn( Board *b ) = 0;
    virtual void focusOut() = 0;
    virtual QString type() const = 0;

    virtual void init();
    virtual void close();

    virtual void configure( QWidget *w );
    virtual bool hasConfig();

    void setNum( int num ) { Num = num; }
    int num() const { return Num; }

    bool hasBrainName() const { return bName; }
    const QString &brainName() const { return Name; }

    void setPlayer( Player *p ) { pPly = p; }
    Player *player() const { return pPly; }
    void setPlayerProfile( PlayerProfile *p ) { pPlyProf = p; }
    PlayerProfile *playerProfile() const { return pPlyProf; }

    virtual Brain *clone() = 0;

    virtual void save( QTextStream &s ) = 0;
    virtual void load( QTextStream &s ) = 0;

signals:
    void changed();

protected:
    void setBrainName( const QString &n );
    void setHasBrainName( bool b );
    Board *board() const;

private:
    PlayerProfile *pPlyProf;
    Player *pPly;
    QString Name;
    bool bName;
    int Num;
};


#endif // BRAIN_HPP
