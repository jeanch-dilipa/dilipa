#include <QCoreApplication>
#include <QDebug>

#include "facade.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Interface1* i1 = new Interface1();
    Interface2* i2 = new Interface2();
    Facade* fa = new Facade(i1,i2);
    qDebug()<<fa->show();

    return a.exec();
}
