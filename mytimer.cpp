#include "mytimer.h"

bool stoptimerthread = false;

MyTimer::MyTimer(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    worker = new QThread();
    worker->setObjectName("TIMER THREAD");
    this->moveToThread(worker);

    connect(worker , SIGNAL(started()), this, SLOT(handletimerthread()));
    connect(this, SIGNAL(finished()), worker, SLOT(quit()));
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(timer, SIGNAL(timeout()), this, SLOT(activeslot()));
}

MyTimer* MyTimer::pInstance = NULL;

MyTimer* MyTimer::getInstance()
{
    if(pInstance == NULL)
    {
        pInstance = new MyTimer();
    }
    return pInstance;
}

void MyTimer::start()
{
    worker->start();
}

void MyTimer::startactive()
{
    timer->start();
}

void MyTimer::startsingleslot()
{
    QTimer::singleShot(5000, this, SLOT(singleshotslot()));
}

void MyTimer::stopactive()
{
    timer->stop();
}

void MyTimer::activeslot()
{
    qDebug() << "Active timer timedout" ;
}

void MyTimer::singleshotslot()
{
    qDebug() << " single shot timer timed out ";
}

void MyTimer::MyTimerSlot()
{
    qDebug() << "My Timer slot timerd out";
}

void MyTimer::handletimerthread()
{
    QEventLoop eventloop;

    connect(this, SIGNAL(loopevent()), this, SLOT(handleloopeventslot()));
    emit this->loopevent();

    eventloop.exec();
}

void MyTimer::handleloopeventslot()
{
    while(!(stoptimerthread))
    {
         qDebug() << " Connection either still not connected or its present";
    }
    qDebug() << "One of the connections droped out please stop and reset";
    emit worker->quit();
    return;

}
