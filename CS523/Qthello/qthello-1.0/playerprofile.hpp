// 
// $Id: playerprofile.hpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Definition of PlayerProfile class
//
// Jan Borsodi <jb@ez.no>
// Created on: <20-Oct-1999 21:41:33 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef PLAYERPROFILE_HPP
#define PLAYERPROFILE_HPP

#include "brain.hpp"
#include "playerprofile.hpp"

#include <qstring.h>
#include <qwidget.h>
#include <qframe.h>
#include <qpainter.h>
#include <qevent.h>

class PlayerList;

class PlayerProfile : public QFrame
{
    Q_OBJECT
public:
    PlayerProfile( PlayerList *owner, QWidget *parent = 0, const char *name = 0 );
    virtual ~PlayerProfile();

    void setComputer( bool b ) { bComp = b; }
    bool isComputer() const { return bComp; }
    void setProfileName( const QString &name );
    const QString &profileName() const;
    void setBrain( Brain *b );
    Brain *brain() const { return pBrain->clone(); }
    Brain *brainReference() const { return pBrain; }
    PlayerList *owner() const { return pOwner; }

signals:
    void changed();

public slots:
    void configure();
    void asPlayerOne();
    void asPlayerTwo();
    void doChanged();
    void doDelete();

protected:
    virtual void drawContents( QPainter *p );
    virtual void mousePressEvent( QMouseEvent *e );

private:
    bool bComp;
    QString Name;
    Brain *pBrain;
    PlayerList *pOwner;
};

#endif // PLAYERPROFILE_HPP
