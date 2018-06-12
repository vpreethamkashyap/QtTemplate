#include "myudp.h"

MyUdp::MyUdp(QObject *parent) :
    QObject(parent)
{
    newtime = QTime::fromString("00:00:00", "hh:mm:ss");
    oldtime = QTime::fromString("00:00:00", "hh:mm:ss");
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

    if(!timer->isActive())
    {
        timer->start(TIMEOUT_mS);
    }
//    while(socketServer->hasPendingDatagrams())
//    {
//        QByteArray buffer;
//        buffer.resize(socketServer->pendingDatagramSize());

//        QHostAddress sender;
//        quint16 senderPort;
//        socketServer->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

//        qDebug() << "received signal : " << buffer;
//    }

    QByteArray datagram;


    do
    {
        datagram.resize(socketServer->pendingDatagramSize());
        socketServer->readDatagram(datagram.data(), datagram.size());
    }while(socketServer->hasPendingDatagrams());

//    QDateTime datetime;
//    QDataStream in(&datagram, QIODevice::ReadOnly);
//    in.setVersion(QDataStream::Qt_5_3);
//    in >> datetime ;

    QString datetimestring(datagram);

    //Perform this in a QTimer
    QMutexLocker lock(&mutex);
    newtime = QTime::fromString(datetimestring, "hh:mm:ss");
//    static QTime oldtime = QTime::fromString("00:00:00", "hh:mm:ss");

//    if(newtime != oldtime)
//    {
//        oldtime = newtime;
//    }
//    else
//    {

//    }

//    qDebug() << " ******* Converted Time ******** "<< newtime;
//    QLineEdit dateLineEdit;
//    dateLineEdit.setText(datetime.date().toString());
//    QLineEdit timeLineEdit;
//    timeLineEdit.setText(datetime.time().toString());

//    QString date = dateLineEdit.text();
//    QString time = timeLineEdit.text();

    qDebug() << " Time in hh:mm:ss : " << datetimestring ;
}

void MyUdp::readtimestamp()
{
    QMutexLocker lock(&mutex);
    if(newtime != oldtime)
    {
        oldtime = newtime;
        qDebug() << "The updated oldtime : " << oldtime ;
    }
    else
    {
//        QProcess process;
//        process.start("bash", QStringList() << "-c" << "service hc-daemon restart");
//        process.waitForFinished();
        qDebug() << "********* restart *************";
    }

}
