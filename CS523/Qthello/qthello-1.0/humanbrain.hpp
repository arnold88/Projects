// 
// $Id: humanbrain.hpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Definition of HumanBrain class
//
// Jan Borsodi <jb@ez.no>
// Created on: <08-Oct-1999 14:29:16 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef HUMANBRAIN_HPP
#define HUMANBRAIN_HPP

#include "brain.hpp"

#include <qstring.h>
#include <qobject.h>
#include <qevent.h>
#include <qwidget.h>
#include <qtextstream.h>

class HumanBrain : public Brain
{
    Q_OBJECT
public:
    HumanBrain( QObject *parent = 0, const char *n = 0 );
    HumanBrain( const HumanBrain *b );
    virtual ~HumanBrain();

    virtual void focusIn( Board *b );
    virtual void focusOut();
    virtual QString type() const;

    void setMarkers( bool b );
    bool markersOn() const { return bShowMarkers; }

    virtual void configure( QWidget *parent );
    virtual bool hasConfig();

    virtual Brain *clone();
    virtual void save( QTextStream &s );
    virtual void load( QTextStream &s );

public slots:
    void doMousePress( int x, int y );
    void doMouseMove( int x, int y );
    void doMouseRelease( int x, int y );
    void doEnter();
    void doLeave();

protected:
    void showMarkers();
    void showOverlay( int x, int y );

private:
    int X, Y;
    bool bShowMarkers;
};


#endif // HUMANBRAIN_HPP
