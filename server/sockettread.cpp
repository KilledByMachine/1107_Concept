#include "sockettread.h"

SocketTread::SocketTread(int descriptor, QObject *parent)
    : QThread(parent), socketDescriptor(descriptor)
{

}

SocketTread::~SocketTread() { delete socket;
}


void SocketTread::run()
{
  socket = new QTcpSocket();
  qDebug() << "SockT:: run, Desc->"<<socketDescriptor;
  socket->setSocketDescriptor(socketDescriptor);
  qDebug() << connect(socket, SIGNAL(readyRead()), this, SLOT(onConnection()),
                      Qt::DirectConnection);
  qDebug() << connect(socket, SIGNAL(disconnected()), this,
                      SLOT(onDisconnected()), Qt::DirectConnection);
  exec();
}

void SocketTread::onConnection()
{
  QString request = this->socket->readAll();
  qDebug() << request;
  //початок різних провірок, серед них робота з БД, пока лишу
  if (request == "send") {
    qDebug() << "OFF";
    emit SendS(QTime::currentTime().toString()+" -time. Call from other thread");
    socket->disconnectFromHost();
    QThread::currentThread()->quit();
  }
  if (request == "query") {
    emit sendQuery(QTime::currentTime().toString() + " MESS");
    qDebug() << "RESUME query TIME::"<< QTime::currentTime();
    socket->disconnectFromHost();
    return;
  }
  if (request == "wait") {
    int i = 0;
    while (i < 30) {
      i++;
      qDebug() << i << "COunt in other thread";
      sleep(1);
    }
    socket->disconnectFromHost();
    return;
  }
  //різні провірки, кінець


  QJsonParseError sendingError;
  QJsonDocument jsonResponse =
      QJsonDocument::fromJson(request.toLatin1(), &sendingError);
  qDebug() << sendingError.errorString();
  QJsonObject jsonObject = jsonResponse.object();
  if (sendingError.error == QJsonParseError::NoError) {
    if (jsonObject["target"].toString() == "reg") {
      // call func
      registration(jsonObject);
    }
    else if (jsonObject["target"].toString() == "log") {
      loginning(jsonObject);
    }
    else {
      qDebug() << "target is undefined";
      socket->write("Unknown Target, you tarhet is -->");
      socket->write(jsonObject["target"].toString().toLatin1());
      socket->waitForBytesWritten();
      socket->disconnectFromHost();

    }
    return;
  }

  //дефот відповідь
  qDebug()<< jsonResponse.object().value("log");
  socket->write( "HTTP/1.0 200 Ok\r\n"
                  "Content-Type: text/html; charset=\"utf-8\"\r\n"
                  "\r\n"
                "<h1>Nothing to see here</h1>\n");
  socket->disconnectFromHost();

}

void SocketTread::onDisconnected()
{
  socket->close();
  quit();
}


void SocketTread::resume(QString s) { qDebug() << s << " ::: REQUEST ";
                                    }


void SocketTread::registration(QJsonObject jsonObject)
{
  //call DB
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

void SocketTread::loginning(QJsonObject jsonObject)
{
  // call db
  QJsonObject regReply;
  regReply.insert("target", "log");
  bool isGoodLog = false;
  bool isGoodPass = false;
  if (jsonObject["login"].toString() == "admin") {
    regReply.insert("login", "ok");
    isGoodLog = true;
  }

  else
    regReply.insert("login", "bad");

  if (jsonObject["pass"].toString() == "password") {
    regReply.insert("pass", "ok");
    isGoodPass = true;
  }

  else
    regReply.insert("pass", "bad");

  if (isGoodLog && isGoodPass)
    regReply.insert("token", "apugndqhglshqpvsf"); //добавити людський рандом, занести в табл активних юзерів
  else
    regReply.insert("token", "");


  QJsonDocument jsDoc(regReply);
  QString jsString = QString::fromLatin1(jsDoc.toJson());
  socket->write(jsString.toLatin1());
  socket->waitForBytesWritten();
  socket->disconnectFromHost();

}
