// 
// $Id: exception.hpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Definition of Exception class
//
// Jan Borsodi <jb@ez.no>
// Created on: <06-Oct-1999 20:44:26 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <qstring.h>

class Exception
{
public:
    Exception( const QString &str ) { Str = str; }
    ~Exception() {}

    const QString &text() const { return Str; }
    void setText( const QString &str ) { Str = str; }

private:
    QString Str;
};


class OutOfRangeException : public Exception
{
public:
    OutOfRangeException( int x, int y )
            : Exception( QString( "Out of range at (%1,%2)" ).arg( x ).arg( y ) ),
              Txt( "Out of range at (%1,%2)" )
        { X = x; Y = y; }
    ~OutOfRangeException() {}

    int x() const { return X; }
    int y() const { return Y; }
    void setX( int x ) { X = x; setText( Txt.arg( X, Y ) ); }
    void setY( int y ) { Y = y; setText( Txt.arg( X, Y ) ); }
    void setPos( int x, int y ) { X = x; Y = y; setText( Txt.arg( X, Y ) ); }

private:
    int X, Y;
    QString Txt;
};

#endif // EXCEPTION_HPP
