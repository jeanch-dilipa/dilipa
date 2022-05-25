#include <QCoreApplication>

#include <QDebug>

#include "pattern.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*桥接模式*/

    DeviceA *A = new DeviceA();
    control *c = new control(A);
    qDebug()<<c->control_p();

    controlExpand *ce = new controlExpand(A);
    qDebug()<<ce->control_p();

    return a.exec();
}
