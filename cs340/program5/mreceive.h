/*
Arnold Lee
CS 340 Program #5
CS user id: temp563
Server initialization module
Date: 04/29/2010
*/

#ifndef MRECEIVE_H
#define MRECEIVE_H

#include <QDialog>
#include <QTcpServer>
#include <QString>
#include <QMessageBox>

namespace Ui {
    class MReceive;
}

class MReceive : public QDialog {
    Q_OBJECT
public:
    MReceive(QWidget *parent = 0);
    ~MReceive();
    QTcpServer MServer;


public slots:
    void MListen();


protected:
    void changeEvent(QEvent *e);

private:
    Ui::MReceive *ui;
};

#endif // MRECEIVE_H
