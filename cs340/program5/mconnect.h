/*
Arnold Lee
CS 340 Program #5
CS user id: temp563
Connection initialization module
Date: 04/29/2010
*/

#ifndef MCONNECT_H
#define MCONNECT_H

#include <QDialog>
#include <QTcpSocket>
#include <QHostAddress>

namespace Ui {
    class MConnect;
}

class MConnect : public QDialog {
    Q_OBJECT
public:
    MConnect(QWidget *parent = 0);
    ~MConnect();

    public slots:
           bool connect_to_server();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MConnect *ui;
};

#endif // MCONNECT_H
