#ifndef SOCKETTREAD_H
#define SOCKETTREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QTime>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>


class SocketTread : public QThread
{
  Q_OBJECT
public:
  explicit SocketTread(int descriptor, QObject *parent = nullptr);
  ~SocketTread();
  void run();
signals:
  void SendS(QString);
  void sendQuery(QString);

public slots:
  void onConnection();
  void onDisconnected();


private:
  int socketDescriptor;
  QTcpSocket * socket;
};

#endif // SOCKETTREAD_H
