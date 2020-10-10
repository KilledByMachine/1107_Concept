#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTime>
#include <QThread>

#include "sockettread.h"

class Server :  public QTcpServer
{
  Q_OBJECT
public:
  explicit Server(quint16 port =80, QObject *parent = nullptr);
  //~Server();
  void incomingConnection(qintptr handle) override;

signals:
  void sendSocketThread(SocketTread * thread);
public slots:
  void GetDat(QString str);


private:
  QTcpServer * mTcpServer;

  //active user table+token, map?
};

#endif // SERVER_H
