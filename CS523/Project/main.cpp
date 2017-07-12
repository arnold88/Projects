#include <QtGui/QApplication>
#include "mainwindow.h"
#include "field.h"


int main(int argc, char *argv[])
{
    QString fileName("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/field.png");

    QApplication a(argc, argv);

    QGraphicsScene scene;

    QGraphicsView view(&scene);

    QGraphicsPixmapItem item (QPixmap(fileName,0,Qt::AutoColor));



    scene.addItem(&item);

    view.show();




    return a.exec();
}
