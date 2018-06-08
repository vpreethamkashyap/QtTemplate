#ifndef MYTIMER_H
#define MYTIMER_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QDebug>
#include <QEventLoop>

extern bool stoptimerthread;

class MyTimer : public QObject
{
    Q_OBJECT
private:
    static MyTimer* pInstance;

public:
    explicit MyTimer(QObject *parent = nullptr);
    QTimer* timer;
    QThread* worker;

    void startactive();
    void startsingleslot();
    void stopactive();
    void start();

    static MyTimer* getInstance();

signals:
    void loopevent();

public slots:
    void MyTimerSlot();
    void activeslot();
    void singleshotslot();
    void handletimerthread();
    void handleloopeventslot();
};

#endif // MYTIMER_H
