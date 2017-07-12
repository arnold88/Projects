
#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QtNetwork\QTcpSocket>

class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTcpSocket;
class QTextEdit;

class Client : public QDialog
{
    Q_OBJECT

public:
    Client(QWidget *parent = 0);

private slots:
    void makeConnection();
    void endConnection();
    void sendMessage();
    void readMessage();
    void displayError(QAbstractSocket::SocketError socketError);
    void enableMakeConnectionButton();

private:
    QLabel *hostLabel;
    QLabel *portLabel;
    QLabel *messageLabel;
    QLineEdit *hostLineEdit;
    QLineEdit *portLineEdit;
    QLineEdit *messageLineEdit;
    QLabel *statusLabel;
    QLabel *statusLabel2;
    QTextEdit *history;
    QPushButton *endConnectionButton;
    QPushButton *makeConnectionButton;
    QPushButton *sendMessageButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;

    QTcpSocket *tcpSocket;
    QString currentFortune;
    quint16 blockSize;
};

#endif
