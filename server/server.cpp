#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
  mTcpServer = new QTcpServer(this);
  if(!mTcpServer->listen(QHostAddress::Any, 80))
  {
    qDebug() << "Server is not started";
  } else
  {
    qDebug() << "Server is started";
  }
  connect(mTcpServer, &QTcpServer::newConnection, this, &Server::incomingConnection);

}

Server::~Server() { delete mTcpServer;
}

void Server::incomingConnection()
{
  QTcpSocket *nSocket = mTcpServer->nextPendingConnection();
  connect(nSocket, SIGNAL(readyRead()), this, SLOT(onConnection()));
  connect(nSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

}

void Server::onConnection()
{
  QTcpSocket *rSocket = static_cast<QTcpSocket *>(sender());
  qDebug() << rSocket->readAll();
  rSocket->write("HTTP/1.0 200 Ok\r\n"
                 "Content-Type: text/html; charset=\"utf-8\"\r\n"
                 "\r\n"
                 "<h1>Nothing to see here</h1>\n");
  rSocket->disconnectFromHost();
    //reply
}

void Server::onDisconnected()
{
  QTcpSocket *dSocket = static_cast<QTcpSocket *>(sender());
  dSocket->close();
  dSocket->deleteLater();
  //destroy
}
