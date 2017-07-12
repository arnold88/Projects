#include "hiscore.h"
#include "ui_hiscore.h"

hiscore::hiscore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hiscore)
{
    ui->setupUi(this);
}

hiscore::~hiscore()
{
    delete ui;
}

void hiscore::changeEvent(QEvent *e)
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
