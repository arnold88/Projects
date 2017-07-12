/*
Arnold Lee
CS 340 Program #5
CS user id: temp563
Hi-Score List Window class declaration
Date: 04/20/2010
*/


#ifndef HISCORE1_H
#define HISCORE1_H

#include <QDialog>
#include <QString>

namespace Ui {
    class hiscore1;
}

class hiscore1 : public QDialog {
    Q_OBJECT
public:
    hiscore1(QWidget *parent = 0);
    ~hiscore1();
    void name_score_entry(QString,int,int);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::hiscore1 *ui;
};

#endif // HISCORE1_H
