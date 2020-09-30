#include "sockettread.h"

SocketTread::SocketTread(int descriptor, QObject *parent)
    : QThread(parent), socketDescriptor(descriptor)
{
}

SocketTread::~SocketTread() { delete socket;
}

//SocketTread::~SocketTread() { delete socket; }

void SocketTread::run()
{
  socket = new QTcpSocket();
  qDebug() << "SockT:: run, Desc->"<<socketDescriptor;
  socket->setSocketDescriptor(socketDescriptor);
  qDebug() << connect(socket, SIGNAL(readyRead()), this, SLOT(onConnection()),
                      Qt::DirectConnection);
  qDebug() << connect(socket, SIGNAL(disconnected()), this,
                      SLOT(onDisconnected()), Qt::DirectConnection);
  //sleep(2);

  exec();
}

void SocketTread::onConnection()
{
  //qDebug() << socket->readAll();

  QString str = this->socket->readAll();
  qDebug() << str;
  QJsonParseError sendingError;
  QJsonDocument jsonResponse =
      QJsonDocument::fromJson(str.toLatin1(), &sendingError);
  qDebug() << sendingError.errorString();
  QJsonObject jsonObject = jsonResponse.object();
  if (sendingError.error == QJsonParseError::NoError) {
    if (jsonObject["target"].toString() == "reg") {
      // call func
      QJsonObject regReply;
      regReply.insert("target", "reg");

      if (jsonObject["login"].toString() == "admin")
        regReply.insert("login", "bad");
      else
        regReply.insert("login", "ok");

      if (jsonObject["email"].toString() == "admin@gmail.com")
        regReply.insert("email", "bad");
      else
        regReply.insert("email", "ok");

      QJsonDocument jsDoc(regReply);
      QString jsString = QString::fromLatin1(jsDoc.toJson());
      socket->write(jsString.toLatin1());
      socket->waitForBytesWritten();
      socket->disconnectFromHost();
    }
    else {
      qDebug() << "target is not reg";
    }
    return;
  }


  QJsonObject obj22{
      {"log", "Login"},
      {"pass", "Password"},
  };
  qDebug() << obj22;
  if (obj22["log"].toString() == "Login")
    qDebug() << "log == Login";
  else
    qDebug() << "log != Login";
  QStringList list = obj22.keys();
  qDebug() << list;
  QStringList list2;
  qDebug()<< jsonResponse.object().value("log");
  socket->write( "HTTP/1.0 200 Ok\r\n"
                  "Content-Type: text/html; charset=\"utf-8\"\r\n"
                  "\r\n"
                "<h1>Nothing to see here</h1>\n");

  QJsonObject obj{
      {"log", "Login"},
      {"pass", "Password"},
  };
  qDebug() << obj.value("log");
   qDebug() << obj.value("pass");
  QJsonArray jsarray {obj};
  QJsonDocument jsDoc(jsarray);
  QString jsString = QString::fromLatin1(jsDoc.toJson());

  socket->write(jsString.toLatin1());


  qDebug() << QThread::currentThreadId() << " "<<QTime::currentTime();
  socket->disconnectFromHost();

}

void SocketTread::onDisconnected()
{
  socket->close();
  quit();
}
