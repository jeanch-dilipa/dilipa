#include <QCoreApplication>

#include <QDebug>

#include "prototype.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    /*原型模式*/
    prototype *pro = new prototype(new QString("原型"));
    qDebug()<<pro->getM_name();

    prototype *pro1 = pro->clone();
    qDebug()<<pro1->getM_name();

    return a.exec();
}
