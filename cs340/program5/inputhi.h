/*
Arnold Lee
CS 340 Program #5
CS user id: temp563
High score input declaration
Date: 04/20/2010
*/


#ifndef INPUTHI_H
#define INPUTHI_H

#include <QDialog>
#include <QString>

namespace Ui {
    class inputhi;
}

class inputhi : public QDialog {
    Q_OBJECT
public:
    inputhi(QWidget *parent = 0);
    ~inputhi();
    QString name;

public slots:
    void entry();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::inputhi *ui;

};

#endif // INPUTHI_H
