#include "server.h"

Server::Server(QObject *parent) :QTcpServer(parent)
{

  if(!this->listen(QHostAddress::Any, 80))
  {
    qDebug() << "Server is not started"<<errorString();
  } else
  {
    qDebug() << "Server is started";
  }



}



void Server::incomingConnection(int handle)
{

  SocketTread *thread =
      new SocketTread(handle);
  qDebug() << "Server:: incoming conn, Desc->"<<handle;
  //qDebug() << connect(socket, SIGNAL(readyRead()), thread, SLOT(onConnection()));
  //qDebug() << connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
  thread->start();


}

