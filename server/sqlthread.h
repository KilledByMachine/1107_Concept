#ifndef SQLTHREAD_H
#define SQLTHREAD_H

#include <QThread>
#include <QObject>
#include <QDebug>

#include <sockettread.h>

class SQLThread : public QThread
{
  Q_OBJECT
public:
  explicit SQLThread(QObject *parent = nullptr);
  void run() override;
signals:
  void request(QString);
public slots:
  void getSocketThread(SocketTread *thread);
  void getQuery(QString );
};

#endif // SQLTHREAD_H
