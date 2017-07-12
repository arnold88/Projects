/*
Arnold Lee
CS 340 Program #5
CS user id: temp563
Hi-Score List Window class implmentation
Date: 04/20/2010
*/

#include "hiscore1.h"
#include "ui_hiscore1.h"

hiscore1::hiscore1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hiscore1)
{
    ui->setupUi(this);
}

hiscore1::~hiscore1()
{
    delete ui;
}

void hiscore1::changeEvent(QEvent *e)
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

void hiscore1::name_score_entry(QString name, int score, int slot)
{
    switch (slot)
    {
    case 1:
        ui->Namebar1->setText(name);
        ui->lcdNumber1->display(score);
        break;
    case 2:
        ui->Namebar2->setText(name);
        ui->lcdNumber2->display(score);
        break;
    case 3:
        ui->Namebar3->setText(name);
        ui->lcdNumber3->display(score);
        break;
    case 4:
        ui->Namebar4->setText(name);
        ui->lcdNumber4->display(score);
        break;
    case 5:
        ui->Namebar5->setText(name);
        ui->lcdNumber5->display(score);
        break;
    default:
        break;
    }

}


