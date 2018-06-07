#include "mytcpsocket.h"

MyTcpSocket::MyTcpSocket(QObject *parent) :
    QObject(parent),
    socket(new QTcpSocket())
{
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
}

void
MyTcpSocket::doConnectblock()
{

    qDebug() << "connecting...";

    // this is not blocking call
    socket->connectToHost("google.com", 80);

    if(socket->waitForConnected(5000)){
        qDebug() << "Connected!";

        //send
        socket->write("Hello server \r\n\r\n");
        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(3000);

        qDebug() << "Reading: " << socket->bytesAvailable();

        // get the data
        qDebug() << socket->readAll();

        // close the connection
        socket->close();
    } else {
        qDebug() << "Not connected!";
    }
}

void
MyTcpSocket::doconnectnoblock()
{
    qDebug() << "connecting...";

    // this is not blocking call
    // attempts to make a connection to hostName on the given port
    socket->connectToHost("google.com", 80);

    // we need to wait...
    if(!socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << socket->errorString();
    }
}


/*The socket is opened in the given openMode and first enters HostLookupState,
 * then performs a host name lookup of hostName. If the lookup succeeds,
 * hostFound() is emitted and QAbstractSocket enters ConnectingState.
 * It then attempts to connect to the address or addresses returned by the lookup.
 * Finally, if a connection is established, QAbstractSocket enters ConnectedState and emits connected().*/
void MyTcpSocket::connected()
{
    qDebug() << "connected...";

    // Hey server, tell me about you.
    socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");
}

/*At any point, the socket can emit error() to signal that an error occurred.*/
void MyTcpSocket::error(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Error in connection...." << socketError;
}

void MyTcpSocket::disconnected()
{
    qDebug() << "disconnected...";
}

/*For buffered devices, the bool QIODevice::waitForBytesWritten(int msecs) function waits until a
 * payload of buffered written data has been written to the device and the bytesWritten() signal has
 * been emitted, or until msecs milliseconds have passed. If msecs is -1, this function will not time out.
 * For unbuffered devices, it returns immediately.*/
void MyTcpSocket::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

/*This function blocks until new data is available for reading and the readyRead() signal has been emitted.
 * The function will timeout after msecs milliseconds; the default timeout is 30000 milliseconds.*/
void MyTcpSocket::readyRead()
{
    qDebug() << "reading...";

    qDebug() << "Reading: " << socket->bytesAvailable();
    // read the data from the socket
    qDebug() << socket->readAll();
}

