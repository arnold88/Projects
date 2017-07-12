/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Dec 8 22:31:05 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSimulation;
    QAction *actionExit;
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *actionBluetooth;
    QAction *actionSMS;
    QWidget *centralWidget;
    QPushButton *buttonStart;
    QPushButton *buttonStop;
    QPushButton *buttonPause;
    QPushButton *buttonChase;
    QPushButton *buttonZM;
    QPushButton *buttonWing;
    QPushButton *button352;
    QLCDNumber *HomeScore;
    QLCDNumber *AwayScore;
    QProgressBar *posRatio;
    QLabel *colon;
    QLCDNumber *TimerDisplay;
    QLabel *label;
    QFrame *line;
    QLabel *label_2;
    QFrame *line_2;
    QPushButton *button442;
    QPushButton *button433;
    QPushButton *button343;
    QPushButton *button442d;
    QPushButton *button532;
    QPushButton *button4222;
    QPushButton *button4411;
    QPushButton *buttonAllAtt;
    QPushButton *buttonAllDef;
    QLabel *label_3;
    QFrame *line_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QPushButton *buttonSub;
    QPushButton *buttonCounter;
    QPushButton *buttonFlat;
    QPushButton *buttonZP;
    QPushButton *buttonTF;
    QPushButton *buttonDNR;
    QLCDNumber *fouls;
    QLabel *label_10;
    QLCDNumber *YC;
    QLabel *label_11;
    QLCDNumber *offsides;
    QLabel *label_12;
    QLCDNumber *shotCount;
    QProgressBar *onTarget;
    QLabel *label_13;
    QLabel *label_14;
    QMenuBar *menuBar;
    QMenu *menuAction;
    QMenu *menuInput_Mode;
    QMenu *menuChannel_Setup;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(716, 464);
        actionSimulation = new QAction(MainWindow);
        actionSimulation->setObjectName(QString::fromUtf8("actionSimulation"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionBluetooth = new QAction(MainWindow);
        actionBluetooth->setObjectName(QString::fromUtf8("actionBluetooth"));
        actionSMS = new QAction(MainWindow);
        actionSMS->setObjectName(QString::fromUtf8("actionSMS"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        buttonStart = new QPushButton(centralWidget);
        buttonStart->setObjectName(QString::fromUtf8("buttonStart"));
        buttonStart->setGeometry(QRect(10, 70, 91, 41));
        buttonStop = new QPushButton(centralWidget);
        buttonStop->setObjectName(QString::fromUtf8("buttonStop"));
        buttonStop->setGeometry(QRect(110, 70, 91, 41));
        buttonPause = new QPushButton(centralWidget);
        buttonPause->setObjectName(QString::fromUtf8("buttonPause"));
        buttonPause->setGeometry(QRect(210, 70, 91, 41));
        buttonChase = new QPushButton(centralWidget);
        buttonChase->setObjectName(QString::fromUtf8("buttonChase"));
        buttonChase->setGeometry(QRect(0, 320, 81, 41));
        buttonZM = new QPushButton(centralWidget);
        buttonZM->setObjectName(QString::fromUtf8("buttonZM"));
        buttonZM->setGeometry(QRect(90, 320, 71, 41));
        buttonWing = new QPushButton(centralWidget);
        buttonWing->setObjectName(QString::fromUtf8("buttonWing"));
        buttonWing->setGeometry(QRect(170, 320, 81, 41));
        button352 = new QPushButton(centralWidget);
        button352->setObjectName(QString::fromUtf8("button352"));
        button352->setGeometry(QRect(210, 170, 91, 41));
        HomeScore = new QLCDNumber(centralWidget);
        HomeScore->setObjectName(QString::fromUtf8("HomeScore"));
        HomeScore->setGeometry(QRect(470, 70, 51, 51));
        AwayScore = new QLCDNumber(centralWidget);
        AwayScore->setObjectName(QString::fromUtf8("AwayScore"));
        AwayScore->setGeometry(QRect(600, 70, 51, 51));
        posRatio = new QProgressBar(centralWidget);
        posRatio->setObjectName(QString::fromUtf8("posRatio"));
        posRatio->setGeometry(QRect(530, 230, 118, 23));
        posRatio->setValue(24);
        colon = new QLabel(centralWidget);
        colon->setObjectName(QString::fromUtf8("colon"));
        colon->setGeometry(QRect(560, 90, 31, 41));
        TimerDisplay = new QLCDNumber(centralWidget);
        TimerDisplay->setObjectName(QString::fromUtf8("TimerDisplay"));
        TimerDisplay->setGeometry(QRect(480, 150, 171, 51));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 391, 31));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(10, 50, 411, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 110, 391, 31));
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(0, 140, 411, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        button442 = new QPushButton(centralWidget);
        button442->setObjectName(QString::fromUtf8("button442"));
        button442->setGeometry(QRect(10, 170, 91, 41));
        button433 = new QPushButton(centralWidget);
        button433->setObjectName(QString::fromUtf8("button433"));
        button433->setGeometry(QRect(110, 170, 91, 41));
        button343 = new QPushButton(centralWidget);
        button343->setObjectName(QString::fromUtf8("button343"));
        button343->setGeometry(QRect(310, 170, 91, 41));
        button442d = new QPushButton(centralWidget);
        button442d->setObjectName(QString::fromUtf8("button442d"));
        button442d->setGeometry(QRect(10, 220, 91, 41));
        button532 = new QPushButton(centralWidget);
        button532->setObjectName(QString::fromUtf8("button532"));
        button532->setGeometry(QRect(110, 220, 91, 41));
        button4222 = new QPushButton(centralWidget);
        button4222->setObjectName(QString::fromUtf8("button4222"));
        button4222->setGeometry(QRect(210, 220, 91, 41));
        button4411 = new QPushButton(centralWidget);
        button4411->setObjectName(QString::fromUtf8("button4411"));
        button4411->setGeometry(QRect(310, 220, 91, 41));
        buttonAllAtt = new QPushButton(centralWidget);
        buttonAllAtt->setObjectName(QString::fromUtf8("buttonAllAtt"));
        buttonAllAtt->setGeometry(QRect(260, 320, 81, 41));
        buttonAllDef = new QPushButton(centralWidget);
        buttonAllDef->setObjectName(QString::fromUtf8("buttonAllDef"));
        buttonAllDef->setGeometry(QRect(350, 320, 81, 41));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 270, 391, 31));
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(10, 300, 411, 20));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(590, 280, 391, 31));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(460, 200, 221, 31));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(460, 120, 221, 31));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(380, 40, 221, 31));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(510, 40, 221, 31));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(450, 10, 221, 31));
        buttonSub = new QPushButton(centralWidget);
        buttonSub->setObjectName(QString::fromUtf8("buttonSub"));
        buttonSub->setGeometry(QRect(310, 70, 91, 41));
        buttonCounter = new QPushButton(centralWidget);
        buttonCounter->setObjectName(QString::fromUtf8("buttonCounter"));
        buttonCounter->setGeometry(QRect(0, 370, 81, 41));
        buttonFlat = new QPushButton(centralWidget);
        buttonFlat->setObjectName(QString::fromUtf8("buttonFlat"));
        buttonFlat->setGeometry(QRect(90, 370, 71, 41));
        buttonZP = new QPushButton(centralWidget);
        buttonZP->setObjectName(QString::fromUtf8("buttonZP"));
        buttonZP->setGeometry(QRect(170, 370, 81, 41));
        buttonTF = new QPushButton(centralWidget);
        buttonTF->setObjectName(QString::fromUtf8("buttonTF"));
        buttonTF->setGeometry(QRect(260, 370, 81, 41));
        buttonDNR = new QPushButton(centralWidget);
        buttonDNR->setObjectName(QString::fromUtf8("buttonDNR"));
        buttonDNR->setGeometry(QRect(350, 370, 81, 41));
        fouls = new QLCDNumber(centralWidget);
        fouls->setObjectName(QString::fromUtf8("fouls"));
        fouls->setGeometry(QRect(480, 360, 51, 51));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(470, 330, 71, 31));
        YC = new QLCDNumber(centralWidget);
        YC->setObjectName(QString::fromUtf8("YC"));
        YC->setGeometry(QRect(550, 360, 51, 51));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(540, 330, 71, 31));
        offsides = new QLCDNumber(centralWidget);
        offsides->setObjectName(QString::fromUtf8("offsides"));
        offsides->setGeometry(QRect(620, 360, 51, 51));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(610, 330, 71, 31));
        shotCount = new QLCDNumber(centralWidget);
        shotCount->setObjectName(QString::fromUtf8("shotCount"));
        shotCount->setGeometry(QRect(520, 270, 51, 51));
        onTarget = new QProgressBar(centralWidget);
        onTarget->setObjectName(QString::fromUtf8("onTarget"));
        onTarget->setGeometry(QRect(580, 300, 118, 23));
        onTarget->setValue(24);
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(450, 280, 71, 31));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(580, 270, 81, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 716, 21));
        menuAction = new QMenu(menuBar);
        menuAction->setObjectName(QString::fromUtf8("menuAction"));
        menuInput_Mode = new QMenu(menuAction);
        menuInput_Mode->setObjectName(QString::fromUtf8("menuInput_Mode"));
        menuChannel_Setup = new QMenu(menuAction);
        menuChannel_Setup->setObjectName(QString::fromUtf8("menuChannel_Setup"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuAction->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuAction->addAction(menuInput_Mode->menuAction());
        menuAction->addAction(menuChannel_Setup->menuAction());
        menuAction->addSeparator();
        menuAction->addAction(actionExit);
        menuInput_Mode->addAction(actionSimulation);
        menuChannel_Setup->addAction(actionBluetooth);
        menuChannel_Setup->addAction(actionSMS);
        menuHelp->addAction(actionHelp);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);
        QObject::connect(buttonStart, SIGNAL(clicked()), MainWindow, SLOT(program_start()));
        QObject::connect(buttonStop, SIGNAL(clicked()), MainWindow, SLOT(program_stop()));
        QObject::connect(buttonPause, SIGNAL(clicked()), MainWindow, SLOT(program_pause()));
        QObject::connect(buttonSub, SIGNAL(clicked()), MainWindow, SLOT(program_sub()));
        QObject::connect(button442, SIGNAL(clicked()), MainWindow, SLOT(fourfourtwo()));
        QObject::connect(button433, SIGNAL(clicked()), MainWindow, SLOT(fourthreethree()));
        QObject::connect(button352, SIGNAL(clicked()), MainWindow, SLOT(threefivetwo()));
        QObject::connect(button343, SIGNAL(clicked()), MainWindow, SLOT(threefourthree()));
        QObject::connect(button442d, SIGNAL(clicked()), MainWindow, SLOT(fourfourtwodiamond()));
        QObject::connect(button532, SIGNAL(clicked()), MainWindow, SLOT(fivethreetwo()));
        QObject::connect(button4222, SIGNAL(clicked()), MainWindow, SLOT(fourtwotwotwo()));
        QObject::connect(button4411, SIGNAL(clicked()), MainWindow, SLOT(fourfouroneone()));
        QObject::connect(buttonChase, SIGNAL(clicked()), MainWindow, SLOT(ballchase()));
        QObject::connect(buttonZM, SIGNAL(clicked()), MainWindow, SLOT(zonalmark()));
        QObject::connect(buttonWing, SIGNAL(clicked()), MainWindow, SLOT(wingplay()));
        QObject::connect(buttonAllAtt, SIGNAL(clicked()), MainWindow, SLOT(allattack()));
        QObject::connect(buttonAllDef, SIGNAL(clicked()), MainWindow, SLOT(alldefend()));
        QObject::connect(buttonCounter, SIGNAL(clicked()), MainWindow, SLOT(counter()));
        QObject::connect(buttonFlat, SIGNAL(clicked()), MainWindow, SLOT(flatback()));
        QObject::connect(buttonZP, SIGNAL(clicked()), MainWindow, SLOT(zonepress()));
        QObject::connect(buttonTF, SIGNAL(clicked()), MainWindow, SLOT(totalfootball()));
        QObject::connect(buttonDNR, SIGNAL(clicked()), MainWindow, SLOT(dumpnrun()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionSimulation->setText(QApplication::translate("MainWindow", "Simulation", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionHelp->setText(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionBluetooth->setText(QApplication::translate("MainWindow", "Bluetooth", 0, QApplication::UnicodeUTF8));
        actionSMS->setText(QApplication::translate("MainWindow", "SMS", 0, QApplication::UnicodeUTF8));
        buttonStart->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        buttonStop->setText(QApplication::translate("MainWindow", "Stop ", 0, QApplication::UnicodeUTF8));
        buttonPause->setText(QApplication::translate("MainWindow", "Pause", 0, QApplication::UnicodeUTF8));
        buttonChase->setText(QApplication::translate("MainWindow", "Ball Chase", 0, QApplication::UnicodeUTF8));
        buttonZM->setText(QApplication::translate("MainWindow", "Zonal Mark", 0, QApplication::UnicodeUTF8));
        buttonWing->setText(QApplication::translate("MainWindow", "Wing Play", 0, QApplication::UnicodeUTF8));
        button352->setText(QApplication::translate("MainWindow", "3 - 5 - 2", 0, QApplication::UnicodeUTF8));
        colon->setText(QString());
        label->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Basic Control</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Formation</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        button442->setText(QApplication::translate("MainWindow", "4 - 4 - 2", 0, QApplication::UnicodeUTF8));
        button433->setText(QApplication::translate("MainWindow", "4 - 3 - 3", 0, QApplication::UnicodeUTF8));
        button343->setText(QApplication::translate("MainWindow", "3 - 4 - 3", 0, QApplication::UnicodeUTF8));
        button442d->setText(QApplication::translate("MainWindow", "4 -4 -2 Diamond", 0, QApplication::UnicodeUTF8));
        button532->setText(QApplication::translate("MainWindow", "5 - 3 - 2", 0, QApplication::UnicodeUTF8));
        button4222->setText(QApplication::translate("MainWindow", "4 - 2 - 2 - 2", 0, QApplication::UnicodeUTF8));
        button4411->setText(QApplication::translate("MainWindow", "4 - 4 - 1 - 1", 0, QApplication::UnicodeUTF8));
        buttonAllAtt->setText(QApplication::translate("MainWindow", "All Attack", 0, QApplication::UnicodeUTF8));
        buttonAllDef->setText(QApplication::translate("MainWindow", "All Defend", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Special Strategy</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Special Strategy</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Possession Ratio</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Match Timer</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Our Team</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Opp Team</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Goals</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        buttonSub->setText(QApplication::translate("MainWindow", "Subsitute...", 0, QApplication::UnicodeUTF8));
        buttonCounter->setText(QApplication::translate("MainWindow", "Counter", 0, QApplication::UnicodeUTF8));
        buttonFlat->setText(QApplication::translate("MainWindow", "Flat Back", 0, QApplication::UnicodeUTF8));
        buttonZP->setText(QApplication::translate("MainWindow", "Possession", 0, QApplication::UnicodeUTF8));
        buttonTF->setText(QApplication::translate("MainWindow", "Chicken", 0, QApplication::UnicodeUTF8));
        buttonDNR->setText(QApplication::translate("MainWindow", "Dump-n-Run", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Fouls</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">YC</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Offsides</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Shots</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">On Target</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        menuAction->setTitle(QApplication::translate("MainWindow", "Action", 0, QApplication::UnicodeUTF8));
        menuInput_Mode->setTitle(QApplication::translate("MainWindow", "Input Mode...", 0, QApplication::UnicodeUTF8));
        menuChannel_Setup->setTitle(QApplication::translate("MainWindow", "Channel Setup", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
