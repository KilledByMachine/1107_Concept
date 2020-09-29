#ifndef SERVER_H
#define SERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QObject
{
  Q_OBJECT
public:
  explicit Server(QObject *parent = nullptr);
  ~Server();
public slots:
  void incomingConnection();
  void onConnection();
  void onDisconnected();

private:
  QTcpServer * mTcpServer;
};

#endif // SERVER_H
