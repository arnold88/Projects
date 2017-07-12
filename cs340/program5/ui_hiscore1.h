/********************************************************************************
** Form generated from reading UI file 'hiscore1.ui'
**
** Created: Thu Apr 29 16:55:43 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISCORE1_H
#define UI_HISCORE1_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_hiscore1
{
public:
    QPushButton *pushButton;
    QLabel *label_6;
    QLabel *label;
    QLCDNumber *lcdNumber5;
    QLCDNumber *lcdNumber1;
    QLabel *label_5;
    QLCDNumber *lcdNumber4;
    QLCDNumber *lcdNumber3;
    QLabel *Namebar2;
    QLCDNumber *lcdNumber2;
    QLabel *label_4;
    QLabel *Namebar5;
    QLabel *Namebar4;
    QLabel *Namebar3;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *Namebar1;

    void setupUi(QDialog *hiscore1)
    {
        if (hiscore1->objectName().isEmpty())
            hiscore1->setObjectName(QString::fromUtf8("hiscore1"));
        hiscore1->resize(500, 476);
        pushButton = new QPushButton(hiscore1);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(210, 350, 91, 41));
        label_6 = new QLabel(hiscore1);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(90, 280, 21, 31));
        label = new QLabel(hiscore1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(140, 30, 231, 41));
        lcdNumber5 = new QLCDNumber(hiscore1);
        lcdNumber5->setObjectName(QString::fromUtf8("lcdNumber5"));
        lcdNumber5->setGeometry(QRect(290, 280, 61, 31));
        lcdNumber1 = new QLCDNumber(hiscore1);
        lcdNumber1->setObjectName(QString::fromUtf8("lcdNumber1"));
        lcdNumber1->setGeometry(QRect(290, 80, 71, 41));
        label_5 = new QLabel(hiscore1);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(90, 230, 21, 31));
        lcdNumber4 = new QLCDNumber(hiscore1);
        lcdNumber4->setObjectName(QString::fromUtf8("lcdNumber4"));
        lcdNumber4->setGeometry(QRect(290, 230, 61, 31));
        lcdNumber3 = new QLCDNumber(hiscore1);
        lcdNumber3->setObjectName(QString::fromUtf8("lcdNumber3"));
        lcdNumber3->setGeometry(QRect(290, 180, 61, 31));
        Namebar2 = new QLabel(hiscore1);
        Namebar2->setObjectName(QString::fromUtf8("Namebar2"));
        Namebar2->setGeometry(QRect(110, 140, 131, 41));
        QFont font;
        font.setPointSize(24);
        Namebar2->setFont(font);
        Namebar2->setTextFormat(Qt::RichText);
        Namebar2->setAlignment(Qt::AlignCenter);
        lcdNumber2 = new QLCDNumber(hiscore1);
        lcdNumber2->setObjectName(QString::fromUtf8("lcdNumber2"));
        lcdNumber2->setGeometry(QRect(290, 130, 61, 41));
        label_4 = new QLabel(hiscore1);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(90, 180, 21, 31));
        Namebar5 = new QLabel(hiscore1);
        Namebar5->setObjectName(QString::fromUtf8("Namebar5"));
        Namebar5->setGeometry(QRect(110, 280, 131, 41));
        Namebar5->setFont(font);
        Namebar5->setTextFormat(Qt::RichText);
        Namebar5->setAlignment(Qt::AlignCenter);
        Namebar4 = new QLabel(hiscore1);
        Namebar4->setObjectName(QString::fromUtf8("Namebar4"));
        Namebar4->setGeometry(QRect(110, 240, 131, 41));
        Namebar4->setFont(font);
        Namebar4->setTextFormat(Qt::RichText);
        Namebar4->setAlignment(Qt::AlignCenter);
        Namebar3 = new QLabel(hiscore1);
        Namebar3->setObjectName(QString::fromUtf8("Namebar3"));
        Namebar3->setGeometry(QRect(110, 190, 131, 41));
        Namebar3->setFont(font);
        Namebar3->setTextFormat(Qt::RichText);
        Namebar3->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(hiscore1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(90, 80, 21, 31));
        label_3 = new QLabel(hiscore1);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(90, 140, 21, 31));
        Namebar1 = new QLabel(hiscore1);
        Namebar1->setObjectName(QString::fromUtf8("Namebar1"));
        Namebar1->setGeometry(QRect(110, 80, 131, 41));
        Namebar1->setFont(font);
        Namebar1->setTextFormat(Qt::RichText);
        Namebar1->setAlignment(Qt::AlignCenter);

        retranslateUi(hiscore1);
        QObject::connect(pushButton, SIGNAL(clicked()), hiscore1, SLOT(close()));

        QMetaObject::connectSlotsByName(hiscore1);
    } // setupUi

    void retranslateUi(QDialog *hiscore1)
    {
        hiscore1->setWindowTitle(QApplication::translate("hiscore1", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("hiscore1", "OK", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("hiscore1", "5.", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("hiscore1", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt;\">HIGH SCORE LIST</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("hiscore1", "4.", 0, QApplication::UnicodeUTF8));
        Namebar2->setText(QApplication::translate("hiscore1", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("hiscore1", "3.", 0, QApplication::UnicodeUTF8));
        Namebar5->setText(QApplication::translate("hiscore1", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        Namebar4->setText(QApplication::translate("hiscore1", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        Namebar3->setText(QApplication::translate("hiscore1", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("hiscore1", "1.", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("hiscore1", "2.", 0, QApplication::UnicodeUTF8));
        Namebar1->setText(QApplication::translate("hiscore1", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class hiscore1: public Ui_hiscore1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISCORE1_H
