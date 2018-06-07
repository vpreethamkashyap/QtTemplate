#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>

class MyTcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = nullptr);

    /* Member prototype*/
    void doConnectblock();

    void doconnectnoblock();

signals:

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void error(QAbstractSocket::SocketError);

private:
    QTcpSocket* socket;
};

#endif // MYTCPSOCKET_H
