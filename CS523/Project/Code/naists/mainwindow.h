#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <QSound>
using namespace::std;

#include <QtGui/QMainWindow>
#include "def.h"
#include "ui_mainwindow.h"




namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

   void load_items (QGraphicsPixmapItem *,
                     QGraphicsPixmapItem *,
                     QGraphicsPixmapItem *,
                     QGraphicsPixmapItem *,
                     QGraphicsPixmapItem *,
                    QGraphicsPixmapItem *,
                    QGraphicsPixmapItem *,
                    QGraphicsPixmapItem *,
                    QGraphicsPixmapItem *,
                    QGraphicsPixmapItem *,
                    QGraphicsPixmapItem *,
                    QGraphicsPixmapItem *,
                    QGraphicsPixmapItem *,
                    QGraphicsPixmapItem *,
                     QGraphicsPixmapItem *,
                     QGraphicsPixmapItem *
                    );

    void load_graphics_scene(QGraphicsScene *);
    //void load_graphics_lib(QVector <QString>);




private slots:
    void program_start();
    void program_stop();
    void program_pause();
    void program_sub();

    void fourfourtwo();
    void fourthreethree();
    void threefivetwo();
    void threefourthree();
    void fourfourtwodiamond();
    void fivethreetwo();
    void fourtwotwotwo();
    void fourfouroneone();

    void ballchase();
    void zonalmark();
    void wingplay ();
    void allattack();
    void alldefend();
    void counter();
    void flatback();
    void zonepress();
    void totalfootball();
    void dumpnrun();

    void showclock();
    void action();


private:
    Ui::MainWindow *ui;

    int i;
    int j;

    QTime *time;
    QTimer *timer;

    QTime *speed;
    QTimer *speeder;



     QGraphicsPixmapItem * ball;
\
     QGraphicsPixmapItem * gk;

     QGraphicsPixmapItem * def1;
     QGraphicsPixmapItem * def2;
     QGraphicsPixmapItem * def3;
     QGraphicsPixmapItem * def4;
     QGraphicsPixmapItem * def5;

     QGraphicsPixmapItem * mid1;
     QGraphicsPixmapItem * mid2;
     QGraphicsPixmapItem * mid3;
     QGraphicsPixmapItem * mid4;
     QGraphicsPixmapItem * mid5;

     QGraphicsPixmapItem * for1;
     QGraphicsPixmapItem * for2;
     QGraphicsPixmapItem * for3;
     QGraphicsPixmapItem * for4;

        int gk1x,gk1y,d1x,d1y,d2x,d2y,d3x,d3y,d4x,d4y,
            d5x,d5y,m1x,m1y,m2x,m2y,m3x,m3y,m4x,m4y,m5x,m5y,
            f1x,f1y,f2x,f2y,f3x,f3y,bx,by;

        int pd1x,pd1y,pd2x,pd2y,pd3x,pd3y,pd4x,pd4y,
            pd5x,pd5y,pm1x,pm1y,pm2x,pm2y,pm3x,pm3y,pm4x,pm4y,pm5x,pm5y,
            pf1x,pf1y,pf2x,pf2y,pf3x,pf3y,pbx,pby;

        int pd1a,pd2a,pd3a,pd4a,pd5a,
        pm1a,pm2a,pm3a,pm4a,pm5a,
        pf1a,pf2a,pf3a,pgk_a;


     bool start_flag;


     void resetPos();
     void freeze_formation();
     void unfreeze_formation();
     void freeze_strategy();
     void unfreeze_strategy();

     int posorg;

     player player1;
     player player2;
     player player3;

     QString p1msg;
     QString p2msg;
     QString p3msg;

};

#endif // MAINWINDOW_H
