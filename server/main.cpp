#include <QCoreApplication>
#include <iostream>

#include <server.h>
int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  Server s;
  return a.exec();
}
