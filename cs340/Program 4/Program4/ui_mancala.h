/********************************************************************************
** Form generated from reading UI file 'mancala.ui'
**
** Created: Sat Mar 27 00:15:22 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANCALA_H
#define UI_MANCALA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mancala
{
public:
    QWidget *centralWidget;
    QLCDNumber *lcdNumber26;
    QLCDNumber *lcdNumber24;
    QLCDNumber *lcdNumber21;
    QLCDNumber *lcdNumber25;
    QLCDNumber *lcdNumber22;
    QLCDNumber *lcdNumber23;
    QLCDNumber *lcdNumberM1;
    QLCDNumber *lcdNumberM2;
    QPushButton *pushButton_13;
    QLabel *statusbar;
    QLabel *player2label;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_4;
    QPushButton *pushButton;
    QLabel *player2label_2;
    QLabel *title;
    QLCDNumber *lcdNumber14;
    QLCDNumber *lcdNumber16;
    QPushButton *pushButton_9;
    QPushButton *pushButton_12;
    QLCDNumber *lcdNumber12;
    QPushButton *pushButton_10;
    QPushButton *pushButton_8;
    QLCDNumber *lcdNumber11;
    QLabel *player1label;
    QPushButton *pushButton_11;
    QPushButton *pushButton_7;
    QLCDNumber *lcdNumber13;
    QLCDNumber *lcdNumber15;
    QLabel *player1label_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *mancala)
    {
        if (mancala->objectName().isEmpty())
            mancala->setObjectName(QString::fromUtf8("mancala"));
        mancala->resize(880, 649);
        centralWidget = new QWidget(mancala);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lcdNumber26 = new QLCDNumber(centralWidget);
        lcdNumber26->setObjectName(QString::fromUtf8("lcdNumber26"));
        lcdNumber26->setGeometry(QRect(690, 130, 51, 51));
        lcdNumber24 = new QLCDNumber(centralWidget);
        lcdNumber24->setObjectName(QString::fromUtf8("lcdNumber24"));
        lcdNumber24->setGeometry(QRect(530, 130, 51, 51));
        lcdNumber21 = new QLCDNumber(centralWidget);
        lcdNumber21->setObjectName(QString::fromUtf8("lcdNumber21"));
        lcdNumber21->setGeometry(QRect(290, 130, 51, 51));
        lcdNumber25 = new QLCDNumber(centralWidget);
        lcdNumber25->setObjectName(QString::fromUtf8("lcdNumber25"));
        lcdNumber25->setGeometry(QRect(610, 130, 51, 51));
        lcdNumber22 = new QLCDNumber(centralWidget);
        lcdNumber22->setObjectName(QString::fromUtf8("lcdNumber22"));
        lcdNumber22->setGeometry(QRect(370, 130, 51, 51));
        lcdNumber23 = new QLCDNumber(centralWidget);
        lcdNumber23->setObjectName(QString::fromUtf8("lcdNumber23"));
        lcdNumber23->setGeometry(QRect(450, 130, 51, 51));
        lcdNumberM1 = new QLCDNumber(centralWidget);
        lcdNumberM1->setObjectName(QString::fromUtf8("lcdNumberM1"));
        lcdNumberM1->setGeometry(QRect(750, 240, 91, 131));
        lcdNumberM2 = new QLCDNumber(centralWidget);
        lcdNumberM2->setObjectName(QString::fromUtf8("lcdNumberM2"));
        lcdNumberM2->setGeometry(QRect(180, 240, 91, 131));
        pushButton_13 = new QPushButton(centralWidget);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));
        pushButton_13->setGeometry(QRect(430, 540, 181, 51));
        statusbar = new QLabel(centralWidget);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setGeometry(QRect(280, 250, 461, 101));
        QFont font;
        font.setPointSize(24);
        statusbar->setFont(font);
        statusbar->setTextFormat(Qt::RichText);
        statusbar->setAlignment(Qt::AlignCenter);
        player2label = new QLabel(centralWidget);
        player2label->setObjectName(QString::fromUtf8("player2label"));
        player2label->setGeometry(QRect(450, 50, 131, 51));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(370, 200, 51, 51));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(450, 200, 51, 51));
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(610, 200, 51, 51));
        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(690, 200, 51, 51));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(530, 200, 51, 51));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(290, 200, 51, 51));
        player2label_2 = new QLabel(centralWidget);
        player2label_2->setObjectName(QString::fromUtf8("player2label_2"));
        player2label_2->setGeometry(QRect(160, 190, 131, 51));
        title = new QLabel(centralWidget);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(80, 0, 861, 51));
        lcdNumber14 = new QLCDNumber(centralWidget);
        lcdNumber14->setObjectName(QString::fromUtf8("lcdNumber14"));
        lcdNumber14->setGeometry(QRect(450, 430, 51, 51));
        lcdNumber16 = new QLCDNumber(centralWidget);
        lcdNumber16->setObjectName(QString::fromUtf8("lcdNumber16"));
        lcdNumber16->setGeometry(QRect(290, 430, 51, 51));
        pushButton_9 = new QPushButton(centralWidget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(450, 360, 51, 51));
        pushButton_12 = new QPushButton(centralWidget);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setGeometry(QRect(690, 360, 51, 51));
        lcdNumber12 = new QLCDNumber(centralWidget);
        lcdNumber12->setObjectName(QString::fromUtf8("lcdNumber12"));
        lcdNumber12->setGeometry(QRect(610, 430, 51, 51));
        pushButton_10 = new QPushButton(centralWidget);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(530, 360, 51, 51));
        pushButton_8 = new QPushButton(centralWidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(370, 360, 51, 51));
        lcdNumber11 = new QLCDNumber(centralWidget);
        lcdNumber11->setObjectName(QString::fromUtf8("lcdNumber11"));
        lcdNumber11->setGeometry(QRect(690, 430, 51, 51));
        player1label = new QLabel(centralWidget);
        player1label->setObjectName(QString::fromUtf8("player1label"));
        player1label->setGeometry(QRect(450, 500, 131, 51));
        pushButton_11 = new QPushButton(centralWidget);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(610, 360, 51, 51));
        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(290, 360, 51, 51));
        lcdNumber13 = new QLCDNumber(centralWidget);
        lcdNumber13->setObjectName(QString::fromUtf8("lcdNumber13"));
        lcdNumber13->setGeometry(QRect(530, 430, 51, 51));
        lcdNumber15 = new QLCDNumber(centralWidget);
        lcdNumber15->setObjectName(QString::fromUtf8("lcdNumber15"));
        lcdNumber15->setGeometry(QRect(370, 430, 51, 51));
        player1label_2 = new QLabel(centralWidget);
        player1label_2->setObjectName(QString::fromUtf8("player1label_2"));
        player1label_2->setGeometry(QRect(730, 380, 131, 51));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(280, 30, 481, 41));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(290, 110, 51, 20));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(370, 110, 51, 20));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(450, 110, 51, 20));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(530, 110, 51, 20));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(610, 110, 51, 20));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(690, 110, 51, 20));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(240, 110, 46, 21));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(450, 480, 51, 20));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(370, 480, 51, 20));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(690, 480, 51, 20));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(530, 480, 51, 20));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(290, 480, 51, 20));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(240, 480, 46, 21));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(610, 480, 51, 20));
        mancala->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(mancala);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 880, 21));
        mancala->setMenuBar(menuBar);
        mainToolBar = new QToolBar(mancala);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mancala->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(mancala);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        mancala->setStatusBar(statusBar);

        retranslateUi(mancala);
        QObject::connect(pushButton_13, SIGNAL(clicked()), mancala, SLOT(resetbutton()));
        QObject::connect(pushButton, SIGNAL(clicked()), mancala, SLOT(button1pressed()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), mancala, SLOT(button2pressed()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), mancala, SLOT(button3pressed()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), mancala, SLOT(button4pressed()));
        QObject::connect(pushButton_5, SIGNAL(clicked()), mancala, SLOT(button5pressed()));
        QObject::connect(pushButton_6, SIGNAL(clicked()), mancala, SLOT(button6pressed()));
        QObject::connect(pushButton_7, SIGNAL(clicked()), mancala, SLOT(button7pressed()));
        QObject::connect(pushButton_8, SIGNAL(clicked()), mancala, SLOT(button8pressed()));
        QObject::connect(pushButton_9, SIGNAL(clicked()), mancala, SLOT(button9pressed()));
        QObject::connect(pushButton_10, SIGNAL(clicked()), mancala, SLOT(button10pressed()));
        QObject::connect(pushButton_11, SIGNAL(clicked()), mancala, SLOT(button11pressed()));
        QObject::connect(pushButton_12, SIGNAL(clicked()), mancala, SLOT(button12pressed()));

        QMetaObject::connectSlotsByName(mancala);
    } // setupUi

    void retranslateUi(QMainWindow *mancala)
    {
        mancala->setWindowTitle(QApplication::translate("mancala", "mancala", 0, QApplication::UnicodeUTF8));
        pushButton_13->setText(QApplication::translate("mancala", "RESET", 0, QApplication::UnicodeUTF8));
        statusbar->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        player2label->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Player 2</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("mancala", "NUDGE", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("mancala", "NUDGE", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("mancala", "NUDGE", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("mancala", "NUDGE", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("mancala", "NUDGE", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("mancala", "NUDGE", 0, QApplication::UnicodeUTF8));
        player2label_2->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Player 2</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Mancala</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt;\"></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px"
                        "; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        title->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600;\">Arnold Lee's LCD Mancala </span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600;\">Version 1.0</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt; font-weight:600;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        pushButton_9->setText(QApplication::translate("mancala", "NUDGE", 0, QApplication::UnicodeUTF8));
        pushButton_12->setText(QApplication::translate("mancala", "NUDGE", 0, QApplication::UnicodeUTF8));
        pushButton_10->setText(QApplication::translate("mancala", "NUDGE", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("mancala", "NUDGE", 0, QApplication::UnicodeUTF8));
        player1label->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Player 1</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        pushButton_11->setText(QApplication::translate("mancala", "NUDGE", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("mancala", "NUDGE", 0, QApplication::UnicodeUTF8));
        player1label_2->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Player 1</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Mancala</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Note: Please read readme.txt to learn the game rules</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">1</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">2</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">3</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">4</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">5</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">6</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">CUP</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">4</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">5</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">1</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">3</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">6</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">CUP</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("mancala", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">2</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mancala: public Ui_mancala {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANCALA_H
