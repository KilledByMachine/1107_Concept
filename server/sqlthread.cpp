#include "sqlthread.h"



SQLThread::SQLThread(QObject *parent) : QThread(parent) {}

void SQLThread::run() { qDebug() << "RUNED"; }

void SQLThread::getSocketThread(SocketTread *thread)
{
  qDebug() <<"SQLTread, connect ::"<<connect(thread, SIGNAL(sendQuery(QString)), this, SLOT(getQuery(QString)),  Qt::DirectConnection);
  qDebug() << QThread::currentThreadId() << "::ID";
}

void SQLThread::getQuery(QString s) { qDebug() << "Query:::" << s;
}
