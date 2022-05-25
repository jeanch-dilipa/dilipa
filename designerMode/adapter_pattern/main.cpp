#include <QCoreApplication>

#include <QDebug>

#include "adapter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Target *t = new Target();
    qDebug()<<t->show_target();

    adapted *ada = new adapted();
    qDebug()<<ada->show_adapted();

    adapter *adap = new adapter(ada);
    qDebug()<<adap->show_target();

    superAdapter *adb = new superAdapter();
    qDebug()<<adb->show_superaddapter();

    return a.exec();
}
