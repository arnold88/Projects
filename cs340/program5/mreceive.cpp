/*
Arnold Lee
CS 340 Program #5
CS user id: temp563
Server initialization module
Date: 04/29/2010
*/

#include "mreceive.h"
#include "ui_mreceive.h"

MReceive::MReceive(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MReceive)
{
    ui->setupUi(this);
    ui->label->setWordWrap(true);


}

MReceive::~MReceive()
{
    delete ui;
}

void MReceive::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MReceive::MListen()
{
    MServer.listen(QHostAddress::Any,31337);
    QString ListenMessage;
    ListenMessage = "New connections are being listened. Your IP address is: ";
    ListenMessage = ListenMessage + MServer.serverAddress().toString();
    QMessageBox Listening;
    Listening.about(this,tr("Waiting for New Connection"),ListenMessage);
}
