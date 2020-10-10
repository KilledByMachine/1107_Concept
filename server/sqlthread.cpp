#include "sqlthread.h"



SQLThread::SQLThread(QObject *parent) : QThread(parent) {}

void SQLThread::run() { qDebug() << "RUNED"; }

void SQLThread::getSocketThread(SocketTread *thread)
{
  // BlockingQueuedConnection ==? DirectConnection
  connect(thread, SIGNAL(sendQuery(QString)), this, SLOT(getQuery(QString)),
          Qt::BlockingQueuedConnection);
  connect(this, SIGNAL(request(QString)), thread, SLOT(resume(QString)),
          Qt::DirectConnection);
}

void SQLThread::getQuery(QString s)
{

  qDebug() << "Query:::" << s;
  //sleep(5);
  emit request("IT`S WORKS!");
  //sleep(2);

}
