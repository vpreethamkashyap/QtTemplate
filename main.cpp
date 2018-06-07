#include <QCoreApplication>
#include <QDebug>

#include "mytcpsocket.h"
#include "mytcpserver.h"
#include "mythread.h"


/*This is the start of main thread or GUI thread as referred in Qt applications*/
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    MyThread thread1("A"), thread2("B"), thread3("C");

//    thread1.start();
//    thread1.setObjectName("Thread1");
//    thread2.start();
//    thread2.setObjectName("Thread2");
//    thread3.start();
//    thread3.setObjectName("Thread3");

     MyTcpSocket socket;
     socket.doconnectnoblock();

     MyTcpServer server_a;
     server_a.listentoincommingconnection();

     MyServer server_b;
     server_b.startServer();

    qDebug() << "hello from GUI thread" << a.thread()->currentThreadId();

    return a.exec();
}
