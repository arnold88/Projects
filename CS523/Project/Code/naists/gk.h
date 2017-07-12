#ifndef GK_H
#define GK_H
#include <QString>
#include "coord.h"
#include "mail/smtpclient.h"

class gk
{
public:
    gk();

    gk(int jerseynum,bool lr_foot,int pos_type,int speed,int agil,int kickpower,
        int accuracy, int tackling, QString address,coord location,QGraphicsPixmapItem *picture );
    ~gk();

    void display();

    void modify_info (int jerseynum,int pos_type,bool lr_foot,QString address);


    void modify_stat (int speed, int agil, int kickpower,int accuracy,int tackling);


    void modify_location (int x, int y);
    void display_loc();

    void send();

    int jnum();
    int kp();
    bool lr();
    QString pos();
    int sp();
    int ag();
    int acc();
    int tac();

    coord loc();

     QGraphicsPixmapItem * pic_point();

private:
    int jerseynum;
    bool lr_foot;
    int pos_type;
    int speed;
    int agil;
    int kickpower;
    int accuracy;
    int tackling;

    QString address;
    QString message;

    QGraphicsPixmapItem *picture;

    coord location;
};

#endif // OFF_H

};

#endif // GK_H
