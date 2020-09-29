#include "sockettread.h"

SocketTread::SocketTread(int descriptor, QObject *parent)
    : QThread(parent), socketDescriptor(descriptor)
{
}

SocketTread::~SocketTread() { delete socket;
}

//SocketTread::~SocketTread() { delete socket; }

void SocketTread::run()
{
  socket = new QTcpSocket();
  qDebug() << "SockT:: run, Desc->"<<socketDescriptor;
  socket->setSocketDescriptor(socketDescriptor);
  qDebug() << connect(socket, SIGNAL(readyRead()), this, SLOT(onConnection()),
                      Qt::DirectConnection);
  qDebug() << connect(socket, SIGNAL(disconnected()), this,
                      SLOT(onDisconnected()), Qt::DirectConnection);
  sleep(2);

  exec();
}

void SocketTread::onConnection()
{
  qDebug() << socket->readAll();
  socket->write( "HTTP/1.0 200 Ok\r\n"
                  "Content-Type: text/html; charset=\"utf-8\"\r\n"
                  "\r\n"
                "<h1>Nothing to see here</h1>\n");
  //reply += QTime::currentTime().toString();

  qDebug() << QThread::currentThreadId() << " "<<QTime::currentTime();
  socket->disconnectFromHost();

}

void SocketTread::onDisconnected()
{
  socket->close();
  quit();
}
