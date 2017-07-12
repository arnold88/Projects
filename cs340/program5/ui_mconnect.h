/********************************************************************************
** Form generated from reading UI file 'mconnect.ui'
**
** Created: Thu Apr 29 23:55:04 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MCONNECT_H
#define UI_MCONNECT_H

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

class Ui_MConnect
{
public:
    QLabel *label;
    QPlainTextEdit *IPAddr;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_2;

    void setupUi(QDialog *MConnect)
    {
        if (MConnect->objectName().isEmpty())
            MConnect->setObjectName(QString::fromUtf8("MConnect"));
        MConnect->resize(400, 300);
        label = new QLabel(MConnect);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, -20, 361, 111));
        IPAddr = new QPlainTextEdit(MConnect);
        IPAddr->setObjectName(QString::fromUtf8("IPAddr"));
        IPAddr->setGeometry(QRect(40, 60, 321, 51));
        pushButton = new QPushButton(MConnect);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(120, 220, 101, 41));
        pushButton_2 = new QPushButton(MConnect);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(250, 220, 101, 41));
        label_2 = new QLabel(MConnect);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 130, 301, 51));

        retranslateUi(MConnect);
        QObject::connect(pushButton_2, SIGNAL(pressed()), MConnect, SLOT(close()));
        QObject::connect(pushButton, SIGNAL(pressed()), MConnect, SLOT(connect_to_server()));

        QMetaObject::connectSlotsByName(MConnect);
    } // setupUi

    void retranslateUi(QDialog *MConnect)
    {
        MConnect->setWindowTitle(QApplication::translate("MConnect", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MConnect", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Please Enter your opponent IP address below:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MConnect", "Connect", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MConnect", "Cancel", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MConnect", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Note: If you have trouble connecting to your opponent, ensure that he has created server and it is in &quot;Listening&quot; mode. If problem still persists, ensure that your firewall or ISP does not block port 31337.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MConnect: public Ui_MConnect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MCONNECT_H
