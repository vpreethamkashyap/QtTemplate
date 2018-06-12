#include "myudp.h"

MyUdp::MyUdp(QObject *parent) :
    QObject(parent)
{
    em_newtime = QTime::fromString("00:00:00", "hh:mm:ss");
    em_oldtime = QTime::fromString("00:00:00", "hh:mm:ss");
    sm_newtime = QTime::fromString("00:00:00", "hh:mm:ss");
    sm_oldtime = QTime::fromString("00:00:00", "hh:mm:ss");
    om_newtime = QTime::fromString("00:00:00", "hh:mm:ss");
    om_oldtime = QTime::fromString("00:00:00", "hh:mm:ss");

    module = " ";
}

void MyUdp::initsocket()
{
    socketServer = new QUdpSocket(this);
    timer = new QTimer(this);
    socketServer->bind(QHostAddress::Any, PORT);
    connect(socketServer, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    connect(timer, SIGNAL(timeout()), this, SLOT(readtimestamp()));
}


MyUdp::~MyUdp()
{
    delete socketServer;
}

void MyUdp::readPendingDatagrams()
{

    if(!timer->isActive()){
        timer->start(TIMEOUT_mS);
    }

    // Create a local QByteArray to capture UDP packets
    QByteArray datagram;

    do{
        datagram.resize(socketServer->pendingDatagramSize());
        socketServer->readDatagram(datagram.data(), datagram.size());
    }while(socketServer->hasPendingDatagrams());

    // Create a local QString to convert ByteArray to QString
    QString moduledata(datagram);

    //To split the string received from other modules
    QStringList list1 = moduledata.split(' ', QString::SkipEmptyParts);

    if(list1[0] == "EM"){
        //Lock the mutex to capture newtime
        QMutexLocker lock(&mutex);
        module = list1[0];
        em_newtime = QTime::fromString(list1[1], "hh:mm:ss");
        qDebug() << " Module name & New time : " << list1[0] << list1[1] ;
    } else if(list1[0] == "SM"){
        //Lock the mutex to capture newtime
        QMutexLocker lock(&mutex);
        module = list1[0];
        sm_newtime = QTime::fromString(list1[1], "hh:mm:ss");
        qDebug() << " Module name & New time : " << list1[0] << list1[1] ;
    } else if(list1[0] == "OM"){
        //Lock the mutex to capture newtime
        QMutexLocker lock(&mutex);
        module = list1[0];
        om_newtime = QTime::fromString(list1[1], "hh:mm:ss");
        qDebug() << " Module name & New time : " << list1[0] << list1[1] ;
    }
}


// Slot based on the timeout() stimulus from QTimer
void MyUdp::readtimestamp()
{
    // Lock the mutex so that newtime & oldtime is safe
    QMutexLocker lock(&mutex);

    if(module == "EM"){
        if(em_newtime != em_oldtime){
            em_oldtime = em_newtime;
            qDebug() << " Updated EM oldtime : " << em_oldtime.toString("hh:mm:ss");
        }
    } else if(module == "SM"){
        if(sm_newtime != sm_oldtime){
            sm_oldtime = sm_newtime;
            qDebug() << "Updated SM oldtime : " << sm_oldtime.toString("hh:mm:ss");
        }
    } else if(module == "OM"){
        if(om_newtime != om_oldtime){
            om_oldtime = om_newtime;
            qDebug() << "Updated OM oldtime : " << om_oldtime.toString("hh:mm:ss");
        }
    } else{       // Take necessary action

        /*QProcess process;
        process.start("bash", QStringList() << "-c" << "service hc-daemon restart");
        process.waitForFinished();*/
        qDebug() << "********* restart *************";
    }
}
