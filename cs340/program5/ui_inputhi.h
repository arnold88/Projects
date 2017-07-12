/********************************************************************************
** Form generated from reading UI file 'inputhi.ui'
**
** Created: Thu Apr 29 19:06:28 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTHI_H
#define UI_INPUTHI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_inputhi
{
public:
    QPlainTextEdit *PlayerName;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *inputhi)
    {
        if (inputhi->objectName().isEmpty())
            inputhi->setObjectName(QString::fromUtf8("inputhi"));
        inputhi->resize(400, 300);
        PlayerName = new QPlainTextEdit(inputhi);
        PlayerName->setObjectName(QString::fromUtf8("PlayerName"));
        PlayerName->setGeometry(QRect(50, 150, 271, 51));
        label = new QLabel(inputhi);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 40, 241, 91));
        pushButton = new QPushButton(inputhi);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(150, 230, 101, 41));

        retranslateUi(inputhi);
        QObject::connect(pushButton, SIGNAL(clicked()), inputhi, SLOT(entry()));

        QMetaObject::connectSlotsByName(inputhi);
    } // setupUi

    void retranslateUi(QDialog *inputhi)
    {
        inputhi->setWindowTitle(QApplication::translate("inputhi", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("inputhi", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600;\">Congratulations!</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">You Are in the high score list!</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Please enter your name below:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("inputhi", "OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class inputhi: public Ui_inputhi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTHI_H
