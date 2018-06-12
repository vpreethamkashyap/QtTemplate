#ifndef MYUDP_H
#define MYUDP_H
#include <QObject>
#include <QUdpSocket>
#include <QDebug>
#include <QDateTime>
#include <QLineEdit>
#include <QTimer>
#include <QMutexLocker>
#include <QMutex>
#include <QProcess>

#define PORT 5678
#define ADDRESS "127.0.0.4"
#define TIMEOUT_mS 5000

class MyUdp : public QObject
{
    Q_OBJECT
public:
    explicit MyUdp(QObject *parent = nullptr);
    ~MyUdp();

    void initsocket();

private:
    QUdpSocket* socketServer;
    QTimer* timer;
    QTime em_newtime;
    QTime em_oldtime;
    QTime sm_newtime;
    QTime sm_oldtime;
    QTime om_newtime;
    QTime om_oldtime;

    QString module;
    QMutex mutex;

signals:

public slots:
    void readPendingDatagrams();
    void readtimestamp();
};

#endif // MYUDP_H
