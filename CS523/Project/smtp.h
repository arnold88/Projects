#ifndef SMTP_H
#define SMTP_H

#include <qobject.h>
#include <qstring.h>
#include <qtextstream.h>
#include <qsocket.h>
#include <qdns.h>
#include <qtimer.h>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qregexp.h>

class QSocket;
class QTextStream;
class QDns;

class Smtp : public QObject
{
    Q_OBJECT

public:
    Smtp( const QString &from, const QString &to,
          const QString &subject, const QString &body );
    ~Smtp();

signals:
    void status( const QString & );

private slots:
    void dnsLookupHelper();
    void readyRead();
    void connected();

private:
    enum State {
        Init,
        Mail,
        Rcpt,
        Data,
        Body,
        Quit,
        Close
    };

    QString message;
    QString from;
    QString rcpt;
    QSocket *socket;
    QTextStream * t;
    int state;
    QString response;
    QDns * mxLookup;
};

#endif // SMTP_H
