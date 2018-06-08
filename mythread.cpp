#include "mythread.h"
#include "mytimer.h"
#include <QDebug>

MyThread::MyThread(QString s) : name(s)
{

}


MyThread::MyThread(qintptr ID, QObject* parent):
    QThread(parent)
{
    socketDescriptor = ID;
}
/* We override the QThread's run() method here run() will be called
   when a thread starts the code. This will be shared by all the threads*/

void MyThread::run()
{
    //for(int i = 0; i<= 100; i++ )
    //{
    //    qDebug() << this->name << " " << i << MyThread::currentThreadId();
    //}

    // thread starts here
    qDebug() << " Thread started";

    socket = new QTcpSocket();

    // set the ID
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        // something's wrong, we just emit a signal
        emit error(socket->error());
        return;
    }

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    // We'll have multiple clients, we want to know which is which
    qDebug() << socketDescriptor << " Client connected";


    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies
    /* To keep the thread's alive */
    exec();
}

void MyThread::readyRead()
{
    // get the information
    QByteArray Data = socket->readAll();

    /* Some hints on converting QByteArray to QString*/
    //QString data = QString::fromAscii_helper(Data.data());
    //QString DataAsString = QTextCodec::codecForMib(1015)->toUnicode(Data);

    QString stringData(Data);

    if(stringData == "EM alive !"){
        qDebug() << "***************************energy-manager signaled**********************************";
    }
    else if(stringData == "OM alive !"){
        qDebug() << "***************************outback-module signaled**********************************";
    }
    else if(stringData == "SM alive !"){
        qDebug() << "***************************serial-module signaled**********************************";
    }

    // will write on server side window
    qDebug() << socketDescriptor << " Data in: " << Data;

    //QTimer::singleShot(5000, this, SLOT(singleshotslot()));

    socket->flush();
    socket->write("Thanks signal received !");
}

void MyThread::singleshotslot()
{
    qDebug() << "Single shot timed out";
}

void MyThread::disconnected()
{
    QMutex mutex;
    mutex.lock();
    stoptimerthread = true;
    mutex.unlock();

    qDebug() << socketDescriptor << " Disconnected";
    socket->deleteLater();
    exit(0);
}
