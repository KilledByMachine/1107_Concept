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
  ~SocketTread() override;
  void run() override;
signals:
  void SendS(QString);
  void sendQuery(QString);

public slots:
  void onConnection();
  void onDisconnected();
  void resume(QString);

private:
  void registration (QJsonObject);
  void loginning    (QJsonObject);

private:
  int socketDescriptor;
  QTcpSocket * socket;


};

#endif // SOCKETTREAD_H
