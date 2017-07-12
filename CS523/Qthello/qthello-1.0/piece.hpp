// 
// $Id: piece.hpp,v 1.1.1.1 2000/08/06 10:21:08 amos Exp $
//
// Definition of Piece class
//
// Jan Borsodi <jb@ez.no>
// Created on: <06-Oct-1999 19:14:32 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef PIECE_HPP
#define PIECE_HPP

#include <qpainter.h>
#include <qstring.h>

class Piece
{
public:
    enum Type
    {
        Unknown = -1,
        White = 0,
        Black = 1,
        Blank = 2,
        Marked = 4
    };
    Piece( char t = Blank );
    ~Piece();

    char type() const { return PType; }
    void setType( char t ) { PType = t; }
    void setWhite() { setType( White ); }
    void setBlack() { setType( Black ); }
    void setBlank() { setType( Blank ); }
    void setUnknown() { setType( Unknown ); }
    Piece opposite() const;
    void paint( QPainter *p );
    QString text() const;

    bool operator ==( const Piece &p ) const;
    bool operator !=( const Piece &p ) const;
    bool operator ==( char t ) const;
    bool operator !=( char t ) const;

private:
    char PType;
};


inline bool Piece::operator ==( const Piece &p ) const
{
    return PType == p.PType;
}

inline bool Piece::operator !=( const Piece &p ) const
{
    return PType != p.PType;
}

inline bool Piece::operator ==( char t ) const
{
    return PType == t;
}

inline bool Piece::operator !=( char t ) const
{
    return PType != t;
}

inline QString Piece::text() const
{
    if ( PType == Blank )
        return QString( "Blank" );
    else if ( PType == Marked )
        return QString( "Marked" );
    else if ( PType == White )
        return QString( "White" );
    else if ( PType == Black )
        return QString( "Black" );
    else
        return QString( "Unknown" );
}

inline Piece::Piece( char t )
{
    PType = t;
}

/*!
  Destroys the object
*/

inline Piece::~Piece()
{
}

inline Piece Piece::opposite() const
{
    if ( (PType & 0xfe) == 0 )
        return Piece( PType^1 );
    else
        return Piece( PType );
}

#endif // PIECE_HPP
