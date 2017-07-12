// 
// $Id: matrix.hpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Definition of Matrix class
//
// Jan Borsodi <jb@ez.no>
// Created on: <06-Oct-1999 19:19:18 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "piece.hpp"
#include "exception.hpp"

#include <qarray.h>
#include <qpoint.h>

class MatrixIterator;
class MatrixRotator;

class Matrix
{
public:
    friend class MatrixIterator;
    Matrix();
    Matrix( const Matrix &m );
    ~Matrix();

    MatrixRotator on( int x, int y );

    const Piece &at( int x, int y ) const;
    void setAt( int x, int y, const Piece &p );
    void clear();
    void copyFrom( const Matrix &m );

    const Piece &operator []( int i ) { return Pieces[i]; }

private:
    Piece Pieces[8*8];
};


class MatrixIterator
{
public:
    MatrixIterator();
    MatrixIterator( int x, int y, int xi, int yi );
    MatrixIterator( Matrix *mtr, int x, int y, int xi, int yi );
    ~MatrixIterator();

    Matrix *matrix() const { return Mtr; }
    void setMatrix( Matrix *mtr ) { Mtr = mtr; }
    int x() const { if ( Mtr ) return XPos; else return -1; }
    int y() const { if ( Mtr ) return YPos; else return -1; }
    int xIncrement() const { return XInc; }
    int yIncrement() const { return YInc; }
    QPoint at() const { if ( Mtr ) return QPoint( XPos, YPos ); else return QPoint( -1, -1 ); }
    void at( int &x, int &y ) { if ( Mtr ) { x = XPos; y = YPos; } else { x = y = -1; } }

    bool valid() const { return XPos >= 0 && YPos >= 0 && XPos < 8 && YPos < 8; }

    MatrixIterator &operator ++();
    MatrixIterator &operator --();
    const Piece &operator *();
    bool operator ==( const MatrixIterator &m ) { return XPos == m.XPos && YPos == m.YPos; }
    bool operator !=( const MatrixIterator &m ) { return XPos != m.XPos || YPos != m.YPos; }

private:
    Matrix *Mtr;
    int XInc, YInc;
    int XPos, YPos;
};


class MatrixRotator
{
public:
    MatrixRotator();
    MatrixRotator( Matrix *mtr, int x, int y );
    ~MatrixRotator();

    void flipPieces( const Piece &p );
    bool legalMove( const Piece &p );

private:
    void flipLine( MatrixIterator &m, const Piece &p );
    bool checkLine( MatrixIterator &m, const Piece &p );

private:
    Matrix *Mtr;
    int XPos, YPos;
};


inline Matrix::Matrix()
{
    clear();
}

inline Matrix::Matrix( const Matrix &m )
{
    copyFrom( m );
}

inline Matrix::~Matrix()
{
}

inline const Piece &Matrix::at( int x, int y ) const
{
    if ( x < 0 || y < 0 || x > 8-1 || y > 8-1 )
        throw OutOfRangeException( x, y );
    return Pieces[x + y*8];
}

inline void Matrix::setAt( int x, int y, const Piece &p )
{
    if ( x < 0 || y < 0 || x > 8-1 || y > 8-1 )
        throw OutOfRangeException( x, y );
    Pieces[x + y*8] = p;
}

inline void Matrix::clear()
{
    Piece clr;
    for ( unsigned int i = 0; i < 8*8; i++ )
        Pieces[i] = clr;
}

inline void Matrix::copyFrom( const Matrix &m )
{
    for ( int i = 0; i < 8*8; i++ )
        Pieces[i] = m.Pieces[i];
}

inline MatrixRotator Matrix::on( int x, int y )
{
    return MatrixRotator( this, x, y );
}



inline MatrixIterator::MatrixIterator()
{
    Mtr = 0;
    XPos = 0;
    YPos = 0;
    XInc = 1;
    YInc = 0;
}

inline MatrixIterator::MatrixIterator( int x, int y, int xi, int yi )
{
    Mtr = 0;
    XPos = x;
    YPos = y;
    XInc = xi;
    YInc = yi;
    if ( XInc > 1 )
        XInc = 1;
    else if ( XInc < -1 )
        XInc = -1;
    if ( YInc > 1 )
        YInc = 1;
    else if ( YInc < -1 )
        YInc = -1;
}

inline MatrixIterator::MatrixIterator( Matrix *mtr, int x, int y, int xi, int yi )
{
    Mtr = mtr;
    XPos = x;
    YPos = y;
    XInc = xi;
    YInc = yi;
    if ( XInc > 1 )
        XInc = 1;
    else if ( XInc < -1 )
        XInc = -1;
    if ( YInc > 1 )
        YInc = 1;
    else if ( YInc < -1 )
        YInc = -1;
}

inline MatrixIterator::~MatrixIterator()
{
}

inline MatrixIterator &MatrixIterator::operator ++()
{
    if ( !Mtr )
        return *this;
    XPos += XInc;
    YPos += YInc;
    return *this;
}

inline MatrixIterator &MatrixIterator::operator --()
{
    if ( !Mtr )
        return *this;
    XPos -= XInc;
    YPos -= YInc;
    return *this;
}

inline const Piece &MatrixIterator::operator *()
{
    if ( !Mtr || !valid() )
        throw OutOfRangeException( XPos, YPos );
    return Mtr->at( XPos, YPos );
}


inline MatrixRotator::MatrixRotator()
{
    Mtr = 0;
    XPos = 0;
    YPos = 0;
}

inline MatrixRotator::MatrixRotator( Matrix *mtr, int x, int y )
{
    Mtr = mtr;
    XPos = x;
    YPos = y;
}

inline MatrixRotator::~MatrixRotator()
{
}

inline void MatrixRotator::flipPieces( const Piece &p )
{
    if ( !Mtr )
        return;
    MatrixIterator east( Mtr, XPos, YPos, 1, 0 );
    MatrixIterator southeast( Mtr, XPos, YPos, 1, 1 );
    MatrixIterator south( Mtr, XPos, YPos, 0, 1 );
    MatrixIterator southwest( Mtr, XPos, YPos, -1, 1 );
    MatrixIterator west( Mtr, XPos, YPos, -1, 0 );
    MatrixIterator northwest( Mtr, XPos, YPos, -1, -1 );
    MatrixIterator north( Mtr, XPos, YPos, 0, -1 );
    MatrixIterator northeast( Mtr, XPos, YPos, 1, -1 );

    flipLine( east, p );
    flipLine( southeast, p );
    flipLine( south, p );
    flipLine( southwest, p );
    flipLine( west, p );
    flipLine( northwest, p );
    flipLine( north, p );
    flipLine( northeast, p );
    Mtr->setAt( XPos, YPos, p );

    // Uncomment for alternative (Maybe slower) version
//      QValueList<MatrixIterator> ilst;
//      ilist.append( MatrixIterator( Mtr, XPos, YPos, 1, 0 ) );
//      ilist.append( MatrixIterator( Mtr, XPos, YPos, 1, 1 ) );
//      ilist.append( MatrixIterator( Mtr, XPos, YPos, 0, 1 ) );
//      ilist.append( MatrixIterator( Mtr, XPos, YPos, -1, 1 ) );
//      ilist.append( MatrixIterator( Mtr, XPos, YPos, -1, 0 ) );
//      ilist.append( MatrixIterator( Mtr, XPos, YPos, -1, -1 ) );
//      ilist.append( MatrixIterator( Mtr, XPos, YPos, 0, -1 ) );
//      ilist.append( MatrixIterator( Mtr, XPos, YPos, 1, -1 ) );
//      Mtr->setAt( XPos, YPos, p );
//      for ( QValueListIterator it = ilist.begin(); it != ilist.end(); ++it )
//      {
//          flipLine( *it, p );
//      }
}

inline bool MatrixRotator::legalMove( const Piece &p )
{
    if ( !Mtr )
        return false;
    MatrixIterator east( Mtr, XPos, YPos, 1, 0 );
    MatrixIterator southeast( Mtr, XPos, YPos, 1, 1 );
    MatrixIterator south( Mtr, XPos, YPos, 0, 1 );
    MatrixIterator southwest( Mtr, XPos, YPos, -1, 1 );
    MatrixIterator west( Mtr, XPos, YPos, -1, 0 );
    MatrixIterator northwest( Mtr, XPos, YPos, -1, -1 );
    MatrixIterator north( Mtr, XPos, YPos, 0, -1 );
    MatrixIterator northeast( Mtr, XPos, YPos, 1, -1 );
    if ( checkLine( east, p ) )
        return true;
    else if ( checkLine( southeast, p ) )
        return true;
    else if ( checkLine( south, p ) )
        return true;
    else if ( checkLine( southwest, p ) )
        return true;
    else if ( checkLine( west, p ) )
        return true;
    else if ( checkLine( northwest, p ) )
        return true;
    else if ( checkLine( north, p ) )
        return true;
    else if ( checkLine( northeast, p ) )
        return true;
    else
        return false;

    // Uncomment for alternative (Maybe slower) version
//      QValueList<MatrixIterator> ilst;
//      ilist.append( MatrixIterator( Mtr, XPos, YPos, 1, 0 ) );
//      ilist.append( MatrixIterator( Mtr, XPos, YPos, 1, 1 ) );
//      ilist.append( MatrixIterator( Mtr, XPos, YPos, 0, 1 ) );
//      ilist.append( MatrixIterator( Mtr, XPos, YPos, -1, 1 ) );
//      ilist.append( MatrixIterator( Mtr, XPos, YPos, -1, 0 ) );
//      ilist.append( MatrixIterator( Mtr, XPos, YPos, -1, -1 ) );
//      ilist.append( MatrixIterator( Mtr, XPos, YPos, 0, -1 ) );
//      ilist.append( MatrixIterator( Mtr, XPos, YPos, 1, -1 ) );
//      for ( QValueListIterator it = ilist.begin(); it != ilist.end(); ++it )
//      {
//          if ( checkLine( *it, p ) )
//              return true;
//      }
//      return false;
}

inline void MatrixRotator::flipLine( MatrixIterator &m, const Piece &p )
{
    MatrixIterator mcheck = m;
    if ( !checkLine( mcheck, p ) )
        return;
    bool ok = true;
    ++m;
    if ( !m.valid() )
        ok = false;
    else if ( *m == Piece::Blank )
        ok = false;
    else if ( *m == p )
        ok = false;
    while( ok )
    {
        Mtr->setAt( m.x(), m.y(), p );
        ++m;
        if ( !m.valid() )
            ok = false;
        else if ( *m == Piece::Blank )
            ok = false;
        else if ( *m == p )
            ok = false;
    }
}

inline bool MatrixRotator::checkLine( MatrixIterator &m, const Piece &p )
{
    if ( *m != Piece::Blank )
        return false;
    ++m;
    if ( !m.valid() )
        return false;
    else if ( *m == Piece::Blank )
        return false;
    else if ( *m == p )
        return false;
    while( true )
    {
        ++m;
        if ( m.valid() )
        {
            if ( *m != Piece::Blank )
            {
                if ( *m == p )
                    return true;
            }
            else
                return false;
        }
        else
            return false;
    }
}

#endif // MATRIX_HPP
