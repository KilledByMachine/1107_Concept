#ifndef SOCKETTREAD_H
#define SOCKETTREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QTime>



class SocketTread : public QThread
{
  Q_OBJECT
public:
  explicit SocketTread(int descriptor, QObject *parent = nullptr);
  ~SocketTread();
  void run() ;
public slots:
  void onConnection();
  void onDisconnected();

private:
  int socketDescriptor;
  QTcpSocket * socket;
};

#endif // SOCKETTREAD_H
