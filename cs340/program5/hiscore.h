#ifndef HISCORE_H
#define HISCORE_H




#include <QDialog>
#include <QString>

namespace Ui {
    class hiscore;
}

class hiscore : public QDialog {
    Q_OBJECT
public:
    hiscore(QWidget *parent = 0);
    ~hiscore();
    QString name;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::hiscore *ui;

};

#endif // HISCORE_H
