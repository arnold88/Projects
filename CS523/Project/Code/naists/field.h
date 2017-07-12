#ifndef FIELD_H
#define FIELD_H

#include "naists.h"

struct coord
{
  int x;
  int y;
  int color;

};


class field
{
public:
    field();
    ~field();

    void load_players (QGraphicsScene,coord,int, QGraphicsPixmapItem);
    // load coordiate,position type, pixmapitem



private:
    QVector < QVector <int> > grid;

    QGraphicsScene scene;


};



#endif // FIELD_H
