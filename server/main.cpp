#include <QCoreApplication>
#include <iostream>

#include <sockettread.h>
#include <sqlthread.h>

#include <server.h>
int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  Server s;
  SQLThread queryThread;
  qDebug()<<"Main - connect"<<QObject::connect(&s, SIGNAL(sendSocketThread(SocketTread*)), &queryThread,
                   SLOT(getSocketThread(SocketTread*)));

  queryThread.start();
  return a.exec();
}
