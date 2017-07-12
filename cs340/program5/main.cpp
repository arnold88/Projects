/*
Arnold Lee
CS 340 Program #5
CS user id: temp563
Main Program
Date: 04/20/2010
*/

#include <QtGui/QApplication>
#include "mancala.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mancala w;
    w.show();
    return a.exec();
}
