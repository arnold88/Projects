#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private slots:
        void aboutClicked();
        void quitClicked();
        void newFile();

private:
    void createActions();
    void createMenus();

    Ui::MainWindow *ui;
    QAction *newAct;
    QAction *quitAct;
    QAction *aboutAct;
    QMenu *fileMenu;
    QMenu *aboutMenu;

};

#endif // MAINWINDOW_H
