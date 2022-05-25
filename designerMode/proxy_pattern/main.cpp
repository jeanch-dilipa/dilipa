#include <QCoreApplication>

#include <QDebug>

#include "proxy.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RealServer* real = new RealServer();
    qDebug()<<real->show();

    Proxy* pro = new Proxy(real);
    qDebug()<<pro->show();

    return a.exec();
}
