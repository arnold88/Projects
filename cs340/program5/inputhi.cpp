/*
Arnold Lee
CS 340 Program #5
CS user id: temp563
High score input implmentation
Date: 04/20/2010
*/

#include "inputhi.h"
#include "ui_inputhi.h"

inputhi::inputhi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inputhi)
{
    ui->setupUi(this);
    name = ui->PlayerName->toPlainText();


}

inputhi::~inputhi()
{
    delete ui;
}

void inputhi::changeEvent(QEvent *e)
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

void inputhi::entry()
{
    name = ui->PlayerName->toPlainText();
    this->close();

}
