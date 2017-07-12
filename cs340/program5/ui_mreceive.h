/********************************************************************************
** Form generated from reading UI file 'mreceive.ui'
**
** Created: Thu Apr 29 23:55:04 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MRECEIVE_H
#define UI_MRECEIVE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_MReceive
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;

    void setupUi(QDialog *MReceive)
    {
        if (MReceive->objectName().isEmpty())
            MReceive->setObjectName(QString::fromUtf8("MReceive"));
        MReceive->resize(571, 496);
        pushButton = new QPushButton(MReceive);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(320, 440, 101, 31));
        pushButton_2 = new QPushButton(MReceive);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(440, 440, 101, 31));
        label = new QLabel(MReceive);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 60, 391, 281));

        retranslateUi(MReceive);
        QObject::connect(pushButton_2, SIGNAL(clicked()), MReceive, SLOT(close()));
        QObject::connect(pushButton, SIGNAL(pressed()), MReceive, SLOT(MListen()));

        QMetaObject::connectSlotsByName(MReceive);
    } // setupUi

    void retranslateUi(QDialog *MReceive)
    {
        MReceive->setWindowTitle(QApplication::translate("MReceive", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MReceive", "Listen", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MReceive", "Cancel", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MReceive", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Note:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">As a server, you will need to give your IP address to connect, after you hit the &quot;Listen&quot; button. This program will by default use port number </span><span style=\" font-size:12pt; font-weight:600; text-decoration: underline;\">31337</span><span style=\" font-size:12pt;\"> to communicate. Please ensure to open up this port from your firewal"
                        "l software.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">To know your current IP address, go to www.whatismyip.com</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px"
                        "; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MReceive: public Ui_MReceive {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MRECEIVE_H
