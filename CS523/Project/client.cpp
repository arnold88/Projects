
#include <QtGui>
#include <QtNetwork/QtNetwork>

#include "client.h"

Client::Client(QWidget *parent)
    : QDialog(parent)
{
    hostLabel = new QLabel(tr("&Server name:"));
    portLabel = new QLabel(tr("S&erver port:"));
    messageLabel = new QLabel(tr("&Message:"));

    hostLineEdit = new QLineEdit("Localhost");
    portLineEdit = new QLineEdit;
    portLineEdit->setValidator(new QIntValidator(1, 65535, this));
    messageLineEdit = new QLineEdit("Type Message Here");

    hostLabel->setBuddy(hostLineEdit);
    portLabel->setBuddy(portLineEdit);
    messageLabel->setBuddy(messageLineEdit);

    statusLabel = new QLabel(tr("This examples requires that you run the "
                                "Fortune Server example as well."));
    statusLabel2 = new QLabel(tr("Last Local Port: never connected"));
    history = new QTextEdit;

    makeConnectionButton = new QPushButton(tr("Make Connection"));
    makeConnectionButton->setDefault(true);
    makeConnectionButton->setEnabled(false);

    sendMessageButton = new QPushButton(tr("Send Message"));
    sendMessageButton->setEnabled(false);

    endConnectionButton = new QPushButton(tr("End Connection"));
    endConnectionButton->setEnabled(false);

    quitButton = new QPushButton(tr("Quit"));

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton (sendMessageButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(endConnectionButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(makeConnectionButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    tcpSocket = new QTcpSocket(this);

    connect(hostLineEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(enableMakeConnectionButton()));
    connect(portLineEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(enableMakeConnectionButton()));
    connect(endConnectionButton, SIGNAL(clicked()),
            this, SLOT(endConnection()));
    connect(makeConnectionButton, SIGNAL(clicked()),
            this, SLOT(makeConnection()));

    connect(sendMessageButton, SIGNAL(clicked()),
            this, SLOT(sendMessage()));
    //connect(messageLineEdit, SIGNAL(returnPressed()),
    //        this, SLOT(sendMessage()));

    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(hostLabel, 0, 0);
    mainLayout->addWidget(hostLineEdit, 0, 1);
    mainLayout->addWidget(portLabel, 1, 0);
    mainLayout->addWidget(portLineEdit, 1, 1);
    mainLayout->addWidget(messageLabel, 2, 0);
    mainLayout->addWidget(messageLineEdit, 2, 1);
    mainLayout->addWidget(statusLabel, 3, 0, 1, 2);
    mainLayout->addWidget(statusLabel2, 4, 0, 1, 2);
    mainLayout->addWidget(history, 5, 0, 4, 2);
    mainLayout->addWidget(buttonBox, 9, 0, 1, 2);
    setLayout(mainLayout);

    setWindowTitle(tr("Echo Client"));
    portLineEdit->setFocus();
}

void Client::makeConnection()
{
    makeConnectionButton->setEnabled(false);
    endConnectionButton->setEnabled(true);
    sendMessageButton->setEnabled(true);
    blockSize = 0;
    tcpSocket->abort();
    tcpSocket->connectToHost(hostLineEdit->text(),
                             portLineEdit->text().toInt());
}

void Client::endConnection()
{
    makeConnectionButton->setEnabled(true);
    endConnectionButton->setEnabled(false);
    sendMessageButton->setEnabled(false);
    tcpSocket->abort();
}

void Client::sendMessage()
{
    //sendMessageButton->setEnabled(false);

    blockSize = 0;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << messageLineEdit->text();
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    tcpSocket->write(block);
    history->append(tr("Sending message to %1").arg(tcpSocket->peerPort()));


}

void Client::readMessage()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    history->append(tr("in readMessage, blockSize %1, bytesAvailable %2")
                        .arg(blockSize).arg(tcpSocket->bytesAvailable()));
    if (blockSize == 0) {
        if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;

        in >> blockSize;
    }

    if (tcpSocket->bytesAvailable() < blockSize)
        return;

    QString nextFortune;
    in >> nextFortune;

    //if (nextFortune == currentFortune) {
    //    QTimer::singleShot(0, this, SLOT(requestNewFortune()));
    //    return;
    //}

    currentFortune = nextFortune;
    statusLabel->setText(currentFortune);
    statusLabel2->setText(tr("Last Local Port: %1").arg(tcpSocket->localPort()));
    history->append(currentFortune);
    //makeConnectionButton->setEnabled(true);
    sendMessageButton->setEnabled(true);
    blockSize = 0;
}

void Client::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Echo Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Echo Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Echo Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(tcpSocket->errorString()));
    }

    makeConnectionButton->setEnabled(true);
}

void Client::enableMakeConnectionButton()
{
    makeConnectionButton->setEnabled(!hostLineEdit->text().isEmpty()
                                 && !portLineEdit->text().isEmpty());
}
