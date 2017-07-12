// 
// $Id: firstbestcomputer.hpp,v 1.1.1.1 2000/08/06 10:21:09 amos Exp $
//
// Definition of FirstBestComputer class
//
// Jan Borsodi <jb@ez.no>
// Created on: <20-Oct-1999 19:03:37 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#ifndef FIRSTBESTCOMPUTER_HPP
#define FIRSTBESTCOMPUTER_HPP

#include "computerbrain.hpp"
#include <qobject.h>
#include <qstring.h>

class FirstBestComputer : public ComputerBrain
{
public:
    FirstBestComputer( QObject *parent = 0, const char *name = 0 );
    FirstBestComputer( const FirstBestComputer *b );
    virtual ~FirstBestComputer();

    virtual void focusIn( Board *b );
    virtual void focusOut();

    virtual Brain *clone();

    virtual QString type() const;

private:
};


#endif // FIRSTBESTCOMPUTER_HPP
