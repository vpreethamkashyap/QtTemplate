#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QString>
#include <QTcpSocket>
#include <QTimer>
#include <QMutexLocker>
#include <QMutex>

class MyThread : public QThread
{
    Q_OBJECT
public:

    // constructor
    // set name using initializer
    explicit MyThread(QString s);
    explicit MyThread(qintptr ID, QObject* parent = nullptr);

    // overriding the QThread's run() method
    void run();

private:
    QString name;

signals:

    void error(QTcpSocket::SocketError socketerror);


public slots:

    void readyRead();
    void disconnected();
    void singleshotslot();

private:
    QTcpSocket* socket;
    qintptr socketDescriptor;

};



#endif // MYTHREAD_H
