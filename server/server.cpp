#include "server.h"

Server::Server(quint16 port, QObject *parent) :QTcpServer(parent)
{

  if(!this->listen(QHostAddress::Any, port))
  {
    qDebug() << "Server is not started"<<errorString();
  } else
  {
    qDebug() << "Server is started";
  }
  qDebug() <<"MAXthread count" <<QThread::idealThreadCount();
}

void Server::GetDat(QString str) { qDebug() << str;
}




void Server::incomingConnection(int handle)
{

  SocketTread *thread =
      new SocketTread(handle, this);

  emit sendSocketThread(thread); // send to SQL thread
  qDebug() << QThread::currentThread()<<":: curr thread < serverM call to SQL thread";
  qDebug() << "Server:: incoming conn, Desc->"<<handle;
  //qDebug() << connect(thread, SIGNAL(readyRead()), thread, SLOT(onConnection()));
  qDebug() << connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater())) <<":: connect finfshed-deleteLater";
  connect(thread, SIGNAL(SendS(QString)), this, SLOT(GetDat(QString)), Qt::DirectConnection);
  static unsigned int count = 0;
  count++;
  qDebug() << "Treads started ----> " << count;

  thread->start();


}

