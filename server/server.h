#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "sockettread.h"

class Server :  public QTcpServer
{
  Q_OBJECT
public:
  explicit Server(QObject *parent = nullptr);
  //~Server();
  void incomingConnection(qintptr handle) override;
public slots:


private:
  QTcpServer * mTcpServer;
};

#endif // SERVER_H
