#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qvector>



QSound vuvu("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/vuvu.wav");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui-> TimerDisplay ->setNumDigits(8);

    posorg = 50;

      time = new QTime(0,0,0,0);
      time->setHMS(0,0,0,0);
      timer = new QTimer(this);

      speed = new QTime(0,0,0,0);
      speed->setHMS(0,0,0,0);
      speeder = new QTimer (this);


      connect(timer, SIGNAL(timeout()), this, SLOT(showclock()));
      connect(speeder, SIGNAL(timeout()), this, SLOT(action()));

          i=0;

            QString text = time->toString("hh:mm:ss");
            ui->TimerDisplay->display(text);

            ui->posRatio->setMinimum(0);
            ui->posRatio->setMaximum(100);
            ui->posRatio->setValue(50);

            ui->onTarget->setMinimum(0);
            ui->onTarget->setMaximum(100);
            ui->onTarget->setValue(0);

            ui->buttonStart->setDisabled(1);

            player1.modify_info(1,1,1,"6302177322@txt.att.net");
         //   player2.modify_info(2,2,1,"7732189615@txt.att.net");
         //   player3.modify_info(3,3,1,"3125330693@vtext.com");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_items(QGraphicsPixmapItem * a,
                            QGraphicsPixmapItem * b,
                            QGraphicsPixmapItem * c,
                            QGraphicsPixmapItem * d,
                            QGraphicsPixmapItem * e,
                            QGraphicsPixmapItem * f,
                            QGraphicsPixmapItem * g,
                            QGraphicsPixmapItem * h,
                            QGraphicsPixmapItem * i,
                            QGraphicsPixmapItem * j,
                            QGraphicsPixmapItem * k,
                            QGraphicsPixmapItem * l,
                            QGraphicsPixmapItem * m,
                            QGraphicsPixmapItem * n,
                            QGraphicsPixmapItem * o,
                            QGraphicsPixmapItem * p)

{
    ball = a;

    def1 = b;
    def2 = c;
    def3 = d;
    def4 = e;
    def5 = f;

    mid1 = g;
    mid2 = h;
    mid3 = i;
    mid4 = j;
    mid5 = k;

    for1 = l;
    for2 = m;
    for3 = n;
    for4 = o;

    gk = p;

}

void MainWindow::program_start()
{
    ui->buttonStart->setDisabled(1);
    ui->buttonPause->setEnabled(1);
    ui->buttonStop->setEnabled(1);

    timer->start(1000);
    speeder->start(100);

    freeze_formation();
    freeze_strategy();

    vuvu.play();
    vuvu.setLoops(-1);
}

void MainWindow::program_pause()
{
    ui->buttonPause->setDisabled(1);
    ui->buttonStart->setEnabled(1);
    ui->buttonStop->setEnabled(1);

    timer->stop();
    speeder->stop();

    unfreeze_formation();
    unfreeze_strategy();

}

void MainWindow::program_stop()
{

    ui->buttonStop->setDisabled(1);
    ui->buttonPause->setEnabled(1);
    ui->buttonStart->setEnabled(1);

    time->setHMS(0,0,0);
    QString text = time->toString("hh:mm:ss");
    ui->TimerDisplay->display(text);
    i=0;

    timer->stop();
    speeder->stop();

    vuvu.stop();

    ui->buttonStop->setDisabled(1);

    unfreeze_formation();
    unfreeze_strategy();

    posorg = 50;

}

void MainWindow::showclock()
{
            QTime newtime;
            i=i+1;
            newtime=time->addSecs(i);
            QString text = newtime.toString("hh:mm:ss");
            ui->TimerDisplay->display(text);

            QTime midnight(0, 0, 0);
            qsrand(midnight.secsTo(QTime::currentTime()));



}


void MainWindow::program_sub()
{
     unfreeze_formation();
     unfreeze_strategy();

     if (i%3000==0)
     {
         freeze_strategy();
         freeze_formation();
     }

}

//************************************************
//default
void MainWindow::fourfourtwo()
{

    resetPos();

      gk1x=10;
      gk1y=240;

      bx = 383;
      by = 240;

      d1x = 150;
      d1y = 90;

      d2x = 150;
      d2y = 180;

      d3x = 150;
      d3y = 270;

      d4x = 150;
      d4y = 360;

      m1x = 230;
      m1y = 90;

      m2x = 230;
      m2y = 180;

      m3x = 230;
      m3y = 270;

      m4x = 230;
      m4y = 360;

      f1x = 300;
      f1y = 180;

      f2x = 300;
      f2y = 270;


     //*******

      ball->setPos(bx,by);
      gk->setPos(gk1x,gk1y);
      def1->setPos(d1x,d1y);
      def2->setPos(d2x,d2y);
      def3->setPos(d3x,d3y);
      def4->setPos(d4x,d4y);
      mid1->setPos(m1x,m1y);
      mid2->setPos(m2x,m2y);
      mid3->setPos(m3x,m3y);
      mid4->setPos(m4x,m4y);
      for1->setPos(f1x,f1y);
      for2->setPos(f2x,f2y);

      ui->buttonStart->setEnabled(1);

}

void MainWindow::fourthreethree()
{
    resetPos();

    gk1x=10;
    gk1y=240;

    bx = 383;
    by = 240;

    d1x = 150;
    d1y = 90;

    d2x = 150;
    d2y = 180;

    d3x = 150;
    d3y = 270;

    d4x = 150;
    d4y = 360;

    m1x = 230;
    m1y = 120;

    m2x = 230;
    m2y = 220;

    m3x = 230;
    m3y = 320;

    f1x = 300;
    f1y = 120;

    f2x = 300;
    f2y = 220;

    f3x = 300;
    f3y = 320;

    ball->setPos(bx,by);
    gk->setPos(gk1x,gk1y);
    def1->setPos(d1x,d1y);
    def2->setPos(d2x,d2y);
    def3->setPos(d3x,d3y);
    def4->setPos(d4x,d4y);
    mid1->setPos(m1x,m1y);
    mid2->setPos(m2x,m2y);
    mid3->setPos(m3x,m3y);
    for3->setPos(f3x,f3y);
    for1->setPos(f1x,f1y);
    for2->setPos(f2x,f2y);

    ui->buttonStart->setEnabled(1);


}

void MainWindow::fivethreetwo()
{
    resetPos();

    gk1x=10;
    gk1y=240;

    bx = 383;
    by = 240;

    d1x = 150;
    d1y = 70;

    d2x = 150;
    d2y = 140;

    d3x = 150;
    d3y = 210;

    d4x = 150;
    d4y = 280;

    d5x = 150;
    d5y = 350;

    m1x = 230;
    m1y = 120;

    m2x = 230;
    m2y = 220;

    m3x = 230;
    m3y = 320;

    f1x = 300;
    f1y = 180;

    f2x = 300;
    f2y = 270;

    ball->setPos(bx,by);
    gk->setPos(gk1x,gk1y);
    def1->setPos(d1x,d1y);
    def2->setPos(d2x,d2y);
    def3->setPos(d3x,d3y);
    def4->setPos(d4x,d4y);
    mid1->setPos(m1x,m1y);
    mid2->setPos(m2x,m2y);
    mid3->setPos(m3x,m3y);
    def5->setPos(d5x,d5y);
    for1->setPos(f1x,f1y);
    for2->setPos(f2x,f2y);


    ui->buttonStart->setEnabled(1);

}

void MainWindow::fourfourtwodiamond()
{

    resetPos();

    gk1x=10;
    gk1y=240;

    bx = 383;
    by = 240;

    d1x = 150;
    d1y = 90;

    d2x = 150;
    d2y = 180;

    d3x = 150;
    d3y = 270;

    d4x = 150;
    d4y = 360;

    m1x = 230;
    m1y = 90;

    m2x = 265;
    m2y = 225;

    m3x = 190;
    m3y = 225;

    m4x = 230;
    m4y = 360;

    f1x = 300;
    f1y = 180;

    f2x = 300;
    f2y = 270;


   //*******

    ball->setPos(bx,by);
    gk->setPos(gk1x,gk1y);
    def1->setPos(d1x,d1y);
    def2->setPos(d2x,d2y);
    def3->setPos(d3x,d3y);
    def4->setPos(d4x,d4y);
    mid1->setPos(m1x,m1y);
    mid2->setPos(m2x,m2y);
    mid3->setPos(m3x,m3y);
    mid4->setPos(m4x,m4y);
    for1->setPos(f1x,f1y);
    for2->setPos(f2x,f2y);

    ui->buttonStart->setEnabled(1);

}

void MainWindow::threefourthree()
{

    resetPos();

    gk1x=10;
    gk1y=240;

    bx = 383;
    by = 240;

    d1x = 150;
    d1y = 120;

    d2x = 150;
    d2y = 220;

    d3x = 150;
    d3y = 320;

    m1x = 230;
    m1y = 90;

    m2x = 230;
    m2y = 180;

    m3x = 230;
    m3y = 270;

    m4x = 230;
    m4y = 360;


    f1x = 300;
    f1y = 120;

    f2x = 300;
    f2y = 220;

    f3x = 300;
    f3y = 320;


    ball->setPos(bx,by);
    gk->setPos(gk1x,gk1y);
    def1->setPos(d1x,d1y);
    def2->setPos(d2x,d2y);
    def3->setPos(d3x,d3y);
    for3->setPos(f3x,f3y);
    mid1->setPos(m1x,m1y);
    mid2->setPos(m2x,m2y);
    mid3->setPos(m3x,m3y);
    mid4->setPos(m4x,m4y);
    for1->setPos(f1x,f1y);
    for2->setPos(f2x,f2y);

    ui->buttonStart->setEnabled(1);

}

void MainWindow::fourfouroneone()
{
    resetPos();

    gk1x=10;
    gk1y=240;

    bx = 383;
    by = 240;

    d1x = 150;
    d1y = 90;

    d2x = 150;
    d2y = 180;

    d3x = 150;
    d3y = 270;

    d4x = 150;
    d4y = 360;

    m1x = 230;
    m1y = 90;

    m2x = 230;
    m2y = 180;

    m3x = 230;
    m3y = 270;

    m4x = 230;
    m4y = 360;

    f1x = 245;
    f1y = 225;

    f2x = 305;
    f2y = 225;


    ball->setPos(bx,by);
    gk->setPos(gk1x,gk1y);
    def1->setPos(d1x,d1y);
    def2->setPos(d2x,d2y);
    def3->setPos(d3x,d3y);
    def4->setPos(d4x,d4y);
    mid1->setPos(m1x,m1y);
    mid2->setPos(m2x,m2y);
    mid3->setPos(m3x,m3y);
    mid4->setPos(m4x,m4y);
    for1->setPos(f1x,f1y);
    for2->setPos(f2x,f2y);

    ui->buttonStart->setEnabled(1);

}

void MainWindow::threefivetwo()
{
    resetPos();

    gk1x=10;
    gk1y=240;

    bx = 383;
    by = 240;

    m1x = 230;
    m1y = 70;

    m2x = 230;
    m2y = 140;

    m3x = 230;
    m3y = 210;

    m4x = 230;
    m4y = 280;

    m5x = 230;
    m5y = 350;

    d1x = 150;
    d1y = 120;

    d2x = 150;
    d2y = 220;

    d3x = 150;
    d3y = 320;

    f1x = 300;
    f1y = 180;

    f2x = 300;
    f2y = 270;

    ball->setPos(bx,by);
    gk->setPos(gk1x,gk1y);
    def1->setPos(d1x,d1y);
    def2->setPos(d2x,d2y);
    def3->setPos(d3x,d3y);
    mid4->setPos(m4x,m4y);
    mid1->setPos(m1x,m1y);
    mid2->setPos(m2x,m2y);
    mid3->setPos(m3x,m3y);
    mid5->setPos(m5x,m5y);
    for1->setPos(f1x,f1y);
    for2->setPos(f2x,f2y);

     ui->buttonStart->setEnabled(1);
}

void MainWindow::fourtwotwotwo()
{
    resetPos();

    gk1x=10;
    gk1y=240;

    bx = 383;
    by = 240;

    d1x = 150;
    d1y = 90;

    d2x = 150;
    d2y = 180;

    d3x = 150;
    d3y = 270;

    d4x = 150;
    d4y = 360;

    m1x = 180;
    m1y = 180;

    m2x = 180;
    m2y = 270;

    m3x = 240;
    m3y = 180;

    m4x = 240;
    m4y = 270;

    f1x = 300;
    f1y = 180;

    f2x = 300;
    f2y = 270;


    ball->setPos(bx,by);
    gk->setPos(gk1x,gk1y);
    def1->setPos(d1x,d1y);
    def2->setPos(d2x,d2y);
    def3->setPos(d3x,d3y);
    def4->setPos(d4x,d4y);
    mid1->setPos(m1x,m1y);
    mid2->setPos(m2x,m2y);
    mid3->setPos(m3x,m3y);
    mid4->setPos(m4x,m4y);
    for1->setPos(f1x,f1y);
    for2->setPos(f2x,f2y);

     ui->buttonStart->setEnabled(1);
}

//*****************************************

void MainWindow::ballchase()
{

}

void MainWindow::zonalmark()
{

}

void MainWindow::wingplay()
{

}

void MainWindow::allattack()
{

}

void MainWindow::alldefend()
{

}

void MainWindow::counter()
{

}

void MainWindow::flatback()
{

}

void MainWindow::zonepress()
{

}

void MainWindow::totalfootball()
{

}

void MainWindow::dumpnrun()
{

}


//****************************

void MainWindow::resetPos()
{

    gk1x=1;
    gk1y=1;

    bx = 1;
    by = 1;

    d1x = 1;
    d1y = 1;

    d2x = 1;
    d2y = 1;

    d3x = 1;
    d3y = 1;

    d4x = 1;
    d4y = 1;

    d5x = 1;
    d5y = 1;

    m1x = 1;
    m1y = 1;

    m2x = 1;
    m2y = 1;

    m3x = 1;
    m3y = 1;

    m4x = 1;
    m4y = 1;

    m5x = 1;
    m5y = 1;

    f1x = 1;
    f1y = 1;

    f2x = 1;
    f2y = 1;

    f3x = 1;
    f3y = 1;


    ball->setPos(bx,by);
    gk->setPos(gk1x,gk1y);
    def1->setPos(d1x,d1y);
    def2->setPos(d2x,d2y);
    def3->setPos(d3x,d3y);
    def4->setPos(d4x,d4y);
    def5->setPos(d5x,d5y);
    mid1->setPos(m1x,m1y);
    mid2->setPos(m2x,m2y);
    mid3->setPos(m3x,m3y);
    mid4->setPos(m4x,m4y);
    mid5->setPos(m5x,m5y);
    for3->setPos(f3x,f3y);
    for1->setPos(f1x,f1y);
    for2->setPos(f2x,f2y);

}

void MainWindow::freeze_formation()
{
    ui->button343->setDisabled(1);
    ui->button433->setDisabled(1);
    ui->button442->setDisabled(1);
    ui->button4222->setDisabled(1);
    ui->button442d->setDisabled(1);
    ui->button352->setDisabled(1);
    ui->button4411->setDisabled(1);
    ui->button532->setDisabled(1);
}

void MainWindow::freeze_strategy()
{

    ui->buttonTF->setDisabled(1);
    ui->buttonZP->setDisabled(1);
    ui->buttonChase->setDisabled(1);
    ui->buttonDNR->setDisabled(1);
    ui->buttonFlat->setDisabled(1);
    ui->buttonCounter->setDisabled(1);
    ui->buttonWing->setDisabled(1);
    ui->buttonAllAtt->setDisabled(1);
    ui->buttonAllDef->setDisabled(1);
    ui->buttonZM->setDisabled(1);

}

void MainWindow::unfreeze_formation()
{
    ui->button343->setEnabled(1);
    ui->button433->setEnabled(1);
    ui->button442->setEnabled(1);
    ui->button4222->setEnabled(1);
    ui->button442d->setEnabled(1);
    ui->button352->setEnabled(1);
    ui->button4411->setEnabled(1);
    ui->button532->setEnabled(1);

}

void MainWindow::unfreeze_strategy()
{
    ui->buttonTF->setEnabled(1);
    ui->buttonZP->setEnabled(1);
    ui->buttonChase->setEnabled(1);
    ui->buttonDNR->setEnabled(1);
    ui->buttonFlat->setEnabled(1);
    ui->buttonCounter->setEnabled(1);
    ui->buttonWing->setEnabled(1);
    ui->buttonAllAtt->setEnabled(1);
    ui->buttonAllDef->setEnabled(1);
    ui->buttonZM->setEnabled(1);

}

void MainWindow::action()
{
    QTime newtime;
    j=j+1;
    newtime=time->addSecs(j);




    QTime midnight(0, 0, 0);
    qsrand(midnight.secsTo(QTime::currentTime()));


    int base = 10 - (qrand() % 20);


    bx = bx + base;
    if (bx <= 0) bx = 25;
    if (bx >= 700) bx = 600;

    base = 10 - (qrand() % 20);
    by = by + base;

    if (by <= 0) by = 25;
    if (by >= 380) by = 350;

   /* base = 10 - (qrand() % 20);
    gk1x = gk1x + base;
    if (gk1x <= 0) gk1x = 25;
    if (gk1x >= 700) gk1x = 600;

    base = 10 - (qrand() % 20);
    gk1y = gk1y + base;
    if (gk1y <= 0) gk1y = 25;
    if (gk1y >= 380) gk1y = 350;*/


    pgk_a = base;

    base = 10 - (qrand() % 20);
    d1x = d1x + base;
    if (d1x <= 0) d1x = 25;
    if (d1x >= 700) d1x = 600;

    base = 10 - (qrand() % 20);
    d1y = d1y + base;
    if (d1y <= 0) d1y = 25;
    if (d1y >= 380) d1y = 350;
    pd1a = base;

    base = 10 - (qrand() % 20);
    d2x = d2x + base;
    if (d2x <= 0) d2x = 25;
    if (d2x >= 700) d2x = 600;

    base = 10 - (qrand() % 20);
    d2y = d2y + base;
    if (d2y <= 0) d2y = 25;
    if (d2y >= 380) d2y = 350;

    pd2a = base;

    base = 10 - (qrand() % 20);
    d3x = d3x + base;
    if (d3x <= 0) d3x = 25;
    if (d3x >= 700) d3x = 600;


    base = 10 - (qrand() % 20);
    d3y = d3y + base;
    if (d3y <= 0) d3y = 25;
    if (d3y >= 380) d3y = 350;
    pd3a = base;

    base = 10 - (qrand() % 20);
    d4x = d4x + base;
    if (d4x <= 0) d4x = 25;
    if (d4x >= 700) d4x = 600;

    base = 10 - (qrand() % 20);
    d4y = d4y + base;
    if (d4y <= 0) d4y = 25;
    if (d4y >= 380) d4y = 350;
    pd4a = base;


    base = 10 - (qrand() % 20);
    d5x = d5x + base;
    if (d5x <= 0) d5x = 25;
    if (d5x >= 700) d5x = 600;

    base = 10 - (qrand() % 20);
    d5y = d5y + base;
    if (d5y <= 0) d5y = 25;
    if (d5y >= 380) d5y = 350;
    pd5a = base;

    base = 10 - (qrand() % 20);
    m1x = m1x + base;
    if (m1x <= 0) m1x = 125;
    if (m1x >= 700) m1x = 600;

    base = 10 - (qrand() % 20);
    m1y = m1y + base;
    if (m1y <= 0) m1y = 25;
    if (m1y >= 380) m1y = 350;
    pm1a = base;

    base = 10 - (qrand() % 20);
    m2x = m2x + base;
    if (m2x <= 0) m2x = 125;
    if (m2x >= 700) m2x = 600;

    base = 10 - (qrand() % 20);
  m2y = m2y + base;
    if (m2y <= 0) m2y = 25;
    if (m2y >= 380) m2y = 350;
 pm2a = base;

    base = 10 - (qrand() % 20);
    m3x = m3x + base;
    if (m3x <= 0) m3x = 125;
    if (m3x >= 700) m3x = 600;

    base = 10 - (qrand() % 20);
    m3y = m3y + base;
    if (m3y <= 0) m3y = 25;
    if (m3y >= 380) m3y = 350;
 pm3a = base;

    base = 10 - (qrand() % 20);
    m4x = m4x + base;
    if (m4x <= 0) m4x = 125;
    if (m4x >= 700) m4x = 600;

    base = 10 - (qrand() % 20);
    m4y = m4y + base;
    if (m4y <= 0) m4y = 125;
    if (m4y >= 380) m4y = 350;
 pm4a = base;


    base = 10 - (qrand() % 20);
    m5x = m5x + base;
    if (m5x <= 0) m5x = 125;
    if (m5x >= 700) m5x = 600;

    base = 10 - (qrand() % 20);
    m5y = m5y + base;
    if (m5y <= 0) m5y = 25;
    if (m5y >= 380) m5y = 350;
 pm5a = base;

    base = 10 - (qrand() % 20);
    f1x = f1x + base;
    if (f1x <= 0) f1x = 225;
    if (f1x >= 700) f1x = 600;

    base = 10 - (qrand() % 20);
    f1y = f1y + base;
    if (f1y <= 0) f1y = 25;
    if (f1y >= 380) f1y = 350;
 pf1a = base;


    base = 10 - (qrand() % 20);
    f2x = f2x + base;
    if (f2x <= 0) f2x = 225;
    if (f2x >= 700) f2x = 600;

    base = 10 - (qrand() % 20);
    f2y = f2y + base;
    if (f2y <= 0) f2y = 25;
    if (f2y >= 380) f2y = 350;
 pf2a = base;


    base = 10 - (qrand() % 20);
    f3x = f3x + base;
    if (f3x <= 0) f3x = 225;
    if (f3x >= 700) f3x = 600;

    base = 10 - (qrand() % 20);
    f3y = f3y + base;
    if (f3y <= 0) f3y = 25;
    if (f3y >= 380) f3y = 350;
    pf3a = base;

 base = 2 - (qrand() % 4);
 posorg = posorg + base;
 if (posorg>100) posorg = 100;
 ui->posRatio->setValue(posorg);


    ball->setPos(bx,by);

    gk->setPos(gk1x,gk1y);
    gk->setRotation(pgk_a);

    def1->setPos(d1x,d1y);
    def1->setRotation(pd1a);

    def2->setPos(d2x,d2y);
    def2->setRotation(pd2a);

    def3->setPos(d3x,d3y);
    def3->setRotation(pd3a);

    def4->setPos(d4x,d4y);
    def4->setRotation(pd4a);

    def5->setPos(d5x,d5y);
    def5->setRotation(pd5a);

    mid1->setPos(m1x,m1y);
    mid1->setRotation(pm1a);

    mid2->setPos(m2x,m2y);
    mid2->setRotation(pm2a);

    mid3->setPos(m3x,m3y);
     mid3->setRotation(pm3a);

    mid4->setPos(m4x,m4y);
     mid4->setRotation(pm4a);

    mid5->setPos(m5x,m5y);
     mid5->setRotation(pm5a);

    for3->setPos(f3x,f3y);
     for3->setRotation(pf3a);

    for1->setPos(f1x,f1y);
    for1->setRotation(pf1a);

    for2->setPos(f2x,f2y);
    for2->setRotation(pf2a);

    //*****************************

    p1msg = "take ball and kick to LF";
    //p2msg = "" +QString(char(f2x%126)) + QString(char(f2y%126));
    //p3msg = "" +QString(char(d1x%126)) + QString(char(d1y%126));


    //*****************************

    player1.load_message(p1msg);
    //player2.load_message(p2msg);
    //player3.load_message(p3msg);

    if (j%150 == 0)
    {
        player1.send();
   //     player2.send();
     //   player3.send();

    }

}
