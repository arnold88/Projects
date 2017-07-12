#ifndef NAISTS_H
#define NAISTS_H


#include <QString>
#include <QGraphicsScene>
#include <QLabel>
#include <QFile>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <iostream>
#include <QMainWindow>
#include <Qvector>
#include <QList>
#include <Qmatrix>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLCDNumber>
#include <QTime>
#include <QTimer>
#include <QHBoxLayout>
#include <QBasicTimer>
#include <QTimerEvent>
#include <time.h>
#include <cstdio>
#include <ctime>
using namespace::std;

#include "def.h"



class naists
{

public:
    naists();
    ~naists();
     void update_display();
     void send_message();

     void start_sim();
     void pause_sim();
     void stop_sim();

     int i;


private:


     QList <player> first_team;

};

#endif // NAISTS_H
