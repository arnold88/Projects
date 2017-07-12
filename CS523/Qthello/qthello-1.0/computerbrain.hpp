// 
// $Id: computerbrain.hpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Definition of ComputerBrain class
//
// Jan Borsodi <jb@ez.no>
// Created on: <16-Oct-1999 00:34:35 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef COMPUTERBRAIN_HPP
#define COMPUTERBRAIN_HPP

#include "brain.hpp"

#include <qstring.h>
#include <qobject.h>
#include <qpoint.h>
#include <qtimer.h>
#include <qwidget.h>
#include <qtextstream.h>

class ComputerBrain : public Brain
{
    Q_OBJECT
public:
    ComputerBrain( int limit, const QString &name, QObject *parent = 0, const char *n = 0 );
    ComputerBrain( const ComputerBrain *b );
    virtual ~ComputerBrain();

    virtual void focusIn( Board *b );
    virtual void focusOut();

    virtual QString type() const;

    virtual void configure( QWidget *parent );
    virtual bool hasConfig();

    int timeout() const { return TimeoutValue; }

    virtual void save( QTextStream &s );
    virtual void load( QTextStream &s );

    int limit() const { return Limit; }
    void setLimit( int l ) { Limit = l; }

protected:
    void putPiece( int x, int y );
    int x() const { return X; }
    int y() const { return Y; }
    QTimer *timer() { return Timer; }
    void setTimeout( int t );

private slots:
    void putIt();

private:
    int X, Y;
    QTimer *Timer;
    int TimeoutValue;
    int Limit;
};


#endif // COMPUTERBRAIN_HPP
