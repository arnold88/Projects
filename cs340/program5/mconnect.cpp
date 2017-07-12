/*
Arnold Lee
CS 340 Program #5
CS user id: temp563
Connection initialization module
Date: 04/29/2010
*/

#include "mconnect.h"
#include "ui_mconnect.h"
#include <QMessageBox>

MConnect::MConnect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MConnect)
{
    ui->setupUi(this);
    ui->label_2->setWordWrap(true);
}

MConnect::~MConnect()
{
    delete ui;
}

void MConnect::changeEvent(QEvent *e)
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

bool MConnect::connect_to_server()
{
    QString ServerAddr;
    ServerAddr = ui->IPAddr->toPlainText();
    QHostAddress HA(ServerAddr);

    QTcpSocket Socket;

    QMessageBox::about(this,tr("Connecting to opponent"),tr("Connecting to opponent... Please wait..."));
    return true;

}
