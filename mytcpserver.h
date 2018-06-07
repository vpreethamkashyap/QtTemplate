#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);

    void listentoincommingconnection();

signals:

public slots:

    /*The void QTcpServer::newConnection() signal is emitted
     * every time a new connection is available.*/
    void newConnection();

private:
    QTcpServer* server;
};



class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = nullptr);

    void startServer();

signals:

public slots:

protected:

    void incomingConnection(qintptr socketDescriptor);

};

#endif // MYTCPSERVER_H
