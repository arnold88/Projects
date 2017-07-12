#include "field.h"

field::field()
{
    int row = 40;

    int col = 20;

    grid.resize(40);

    for (int x=0;x<row;x++)
    {
        grid[x].resize(col);
    }


    QString fileName("C:/Users/user/Desktop/CS 523/Project/Code/NAISTS/img/field.png");

    QGraphicsView view(&scene);

    QGraphicsPixmapItem item (QPixmap(fileName,0,Qt::AutoColor));

    scene.addItem(&item);

    view.show();

}

field::~field()
{

}


