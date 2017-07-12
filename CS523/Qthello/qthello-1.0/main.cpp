// 
// $Id: main.cpp,v 1.1.1.1 2000/08/06 10:21:08 amos Exp $
//
// Main body implementation
//
// Jan Borsodi <jb@ez.no>
// Created on: <06-Oct-1999 19:13:58 amos>
//
// Copyright (C) 1999-2000 Jan Borsodi.
//

#include "othello.hpp"
#include "playerlist.hpp"

#include <qapplication.h>

int main( int argc, char **argv )
{
    QApplication app( argc, argv );

    PlayerList *pl = PlayerList::instance();
    pl->show();

    Othello w;
    pl->setOthello( &w );
    app.setMainWidget( &w );
    w.show();

    int rc = app.exec();
    delete pl;
    return rc;
}
