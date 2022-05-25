#include <QCoreApplication>

#include <factory.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*工厂方法*/ //-->抽象工厂

    Factory1 *factory1 = new Factory1();
    qDebug()<<factory1->createrA()->show();
    qDebug()<<factory1->createrB()->show();

    Factory2 *factory2 = new Factory2();
    qDebug()<<factory2->createrA()->show();
    qDebug()<<factory2->createrB()->show();

    return a.exec();
}
