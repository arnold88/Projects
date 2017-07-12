// 
// $Id: randomcomputer.hpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Definition of RandomComputer class
//
// Jan Borsodi <jb@ez.no>
// Created on: <16-Oct-1999 14:18:30 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef RANDOMCOMPUTER_HPP
#define RANDOMCOMPUTER_HPP

#include "computerbrain.hpp"
#include <qstring.h>
#include <qobject.h>

class RandomComputer : public ComputerBrain
{
public:
    RandomComputer( QObject *parent = 0, const char *n = 0 );
    RandomComputer( const RandomComputer *b );
    virtual ~RandomComputer();

    virtual void focusIn( Board *b );
    virtual void focusOut();

    virtual Brain *clone();

    virtual QString type() const;

private:
};


#endif // RANDOMCOMPUTER_HPP
