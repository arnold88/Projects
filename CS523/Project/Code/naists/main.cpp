
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtGui/QApplication>
#include "mainwindow.h"
#include "def.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString fileName("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/field.png");
    QString fileName1("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/def.png");
    QString fileName2("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/ball.png");
    QString fileName3("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/mid.png");
    QString fileName4("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/off.png");
    QString fileName5("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/gk.png");


    // pass a vector of strings, 11 file name, each


    QGraphicsScene scene;

    QGraphicsView view(&scene);


    QGraphicsPixmapItem field (QPixmap(fileName,0,Qt::AutoColor));


    scene.addItem(&field);

    QGraphicsPixmapItem gk_1  (QPixmap("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/gk.png",0,Qt::AutoColor));
    QGraphicsPixmapItem def_1 (QPixmap("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/def.png",0,Qt::AutoColor));
    QGraphicsPixmapItem def_2 (QPixmap("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/def.png",0,Qt::AutoColor));
    QGraphicsPixmapItem def_3 (QPixmap("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/def.png",0,Qt::AutoColor));
    QGraphicsPixmapItem def_4 (QPixmap("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/def.png",0,Qt::AutoColor));
    QGraphicsPixmapItem def_5 (QPixmap("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/def.png",0,Qt::AutoColor));


    QGraphicsPixmapItem mid_1 (QPixmap("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/mid.png",0,Qt::AutoColor));
    QGraphicsPixmapItem mid_2 (QPixmap("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/mid.png",0,Qt::AutoColor));
    QGraphicsPixmapItem mid_3 (QPixmap("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/mid.png",0,Qt::AutoColor));
    QGraphicsPixmapItem mid_4 (QPixmap("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/mid.png",0,Qt::AutoColor));
    QGraphicsPixmapItem mid_5 (QPixmap("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/mid.png",0,Qt::AutoColor));

    QGraphicsPixmapItem for_1 (QPixmap("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/off.png",0,Qt::AutoColor));
    QGraphicsPixmapItem for_2 (QPixmap("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/off.png",0,Qt::AutoColor));
    QGraphicsPixmapItem for_3 (QPixmap("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/off.png",0,Qt::AutoColor));
    QGraphicsPixmapItem for_4 (QPixmap("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/off.png",0,Qt::AutoColor));

    QGraphicsPixmapItem ball (QPixmap("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/ball.png",0,Qt::AutoColor));

    scene.addItem(&gk_1);
    scene.addItem(&def_1);
    scene.addItem(&def_2);
    scene.addItem(&def_3);
    scene.addItem(&def_4);
    scene.addItem(&def_5);
    scene.addItem(&mid_1);
    scene.addItem(&mid_2);
    scene.addItem(&mid_3);
    scene.addItem(&mid_4);
    scene.addItem(&mid_5);
    scene.addItem(&for_1);
    scene.addItem(&for_2);
    scene.addItem(&for_3);
    scene.addItem(&for_4);
    scene.addItem(&ball);


    view.show();

    MainWindow w;

    w.load_items(&ball,&def_1,&def_2,&def_3,&def_4,
                 &def_5,&mid_1,&mid_2,&mid_3,&mid_4,
                 &mid_5,&for_1,&for_2,&for_3,&for_4,&gk_1);




    w.show();

    return a.exec();
}
