#ifndef DEF_H
#define DEF_H

#include <QString>
#include "coord.h"
#include "mail/smtpclient.h"
#include <QGraphicsPixmapItem>



class player
{
public:
    player();
    player(int jerseynum,bool lr_foot,int pos_type,int speed,int agil,int kickpower,
        int accuracy, int tackling, QString address,coord location,QGraphicsPixmapItem *picture);
      ~player();

    void modify_info (int jerseynum,int pos_type,bool lr_foot,QString address);

    void modify_stat (int speed, int agil, int kickpower,int accuracy,int tackling);

    void modify_location (int x, int y);

    void load_message (QString);
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
    QGraphicsPixmapItem * picture;

    QString address;
    QString message;

    coord location;

    SmtpClient mailstuff;
    std::string Chost;


    QString host;

    std::string Cid;
    QString id;

    std::string Cpw;
    QString pw;

    MimeText text;

    MimeMessage message_out;
};

#endif // DEF_H
