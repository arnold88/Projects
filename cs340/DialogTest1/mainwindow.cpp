#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::aboutClicked()
{
    statusBar()->showMessage(tr("About was pressed"), 2000);
    QMessageBox::about (this, tr("About Author"),
                        tr("Here is some text.\nEven more."));
       // qApp->aboutQt();
}

void MainWindow::quitClicked()
{
    qApp->quit();
}

void MainWindow::createActions()
 {
     newAct = new QAction(tr("&New"), this);
     newAct->setShortcut(tr("Ctrl+N"));
     newAct->setStatusTip(tr("Create a new file"));
     connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

     quitAct = new QAction(tr("&Quit"), this);
     quitAct->setShortcut(tr("Ctrl+Q"));
     quitAct->setStatusTip(tr("Quit the program"));
     connect(quitAct, SIGNAL(triggered()), qApp, SLOT(quit()));

     aboutAct = new QAction(tr("&About"), this);
     aboutAct->setShortcut(tr("Ctrl+A"));
     aboutAct->setStatusTip(tr("See who wrote the code"));
     connect(aboutAct, SIGNAL(triggered()), this, SLOT(aboutClicked()));
 }

void MainWindow::createMenus()
 {
     fileMenu = menuBar()->addMenu(tr("&File"));
     fileMenu->addAction(newAct);
     fileMenu->addSeparator();
     fileMenu->addAction(quitAct);

     aboutMenu = menuBar()->addMenu(tr("&About"));
     aboutMenu->addAction(aboutAct);

 }

void MainWindow::newFile()
{
    statusBar()->showMessage(tr("New File was pressed"));

    int r = QMessageBox::question(
            this, tr("Ask a Question"),
            tr("Do you want a new File?"),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No);

    if (r == QMessageBox::Yes)
    {
        QString fileName = QFileDialog::getOpenFileName (this,
                          tr("Open File"), ".",
                          tr("Header Files (*.h)"));

        statusBar()->showMessage(tr("File Selected: ")+fileName);

    }
}
