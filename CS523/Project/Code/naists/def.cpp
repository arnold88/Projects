#include "def.h"

player::player()
{


     Chost = "smtp.gmail.com";
     host = QString::fromStdString(Chost);

     Cid = "naists@newage2012.org";
     id = QString::fromStdString(Cid);

     Cpw = "Iluvlcp2";
     pw = QString::fromStdString(Cpw);

    mailstuff.setHost(host);
    mailstuff.setPort(465);
    mailstuff.setConnectionType(SmtpClient::SslConnection);
    mailstuff.setUser(id);
    mailstuff.setPassword(pw);
}

player::~player()
{

}

player::player(int a, bool b, int c, int d, int e, int f, int g, int h,
         QString i, coord j,QGraphicsPixmapItem * pix)
{
    jerseynum = a;
    lr_foot = b;
    pos_type = c;
    speed = d;
    agil = e;
    kickpower = f;
    accuracy = g;
    tackling = h;
    address = i;
    location = j;

    picture = pix;

     Chost = "smtp.gmail.com";
    host = QString::fromStdString(Chost);

     Cid = "naists@newage2012.org";
    id = QString::fromStdString(Cid);

     Cpw = "Iluvlcp2";
     pw = QString::fromStdString(Cpw);

    mailstuff.setHost(host);
    mailstuff.setPort(465);
    mailstuff.setConnectionType(SmtpClient::SslConnection);
    mailstuff.setUser(id);
    mailstuff.setPassword(pw);
}

//************************************************************************

int player::acc()
{
  return accuracy;
}

int player::tac()
{
    return tackling;
}

int player::jnum()
{
    return jerseynum;
}

bool player::lr()
{
    return lr_foot;
}

int player::kp()
{
    return kickpower;
}

int player::ag()
{
    return agil;
}

int player::sp()
{
    return speed;
}

coord player::loc()
{
    return location;
}

QString player::pos()
{
    switch (pos_type)
    {
    case 1:
        return "LB";
    case 2:
        return "LCB";
    case 3:
        return "RCB";
    case 4:
        return "RB";
    default:
        return "GK";
    }

}

//*************************************************************************


void player::modify_info (int a,int b,bool c,QString d)
{
    jerseynum = a;
    pos_type = b;
    lr_foot = c;
    address = d;

}

void player::modify_stat (int a, int b, int c,int d,int e)
{
    speed = a;
    agil = b;
    kickpower = c;
    accuracy = d;
    tackling = e;

}


void player::modify_location (int x, int y)
{
    location.x = x;
    location.y = y;

    int marker = (x*20) + y;

    location.color = marker % 5;

}

void player::load_message (QString input)
{

    message = input;
}

void player::send()
{
    message_out.setSender(new EmailAddress("naists@newage2012.org", "New Age Interactive Soccer Training System"));
    message_out.addRecipient(new EmailAddress(address, "Player"));
    message_out.setSubject("Instructions for #3" );

    // Now add some text to the email.
    // First we create a MimeText object.

    text.setText(message);

    // Now add it to the mail

    message_out.addPart(&text);

    // Now we can send the mail

    mailstuff.connectToHost();
    mailstuff.login();
    mailstuff.sendMail(message_out);
    mailstuff.quit();

}

QGraphicsPixmapItem * player::pic_point()
{
    return picture;
}
