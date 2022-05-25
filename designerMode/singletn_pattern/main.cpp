#include <QCoreApplication>

#include <QDebug>

#include "testclass.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    /*单例模式*/
    TestClass *test1 = TestClass::initTestClass(new QString("test1"));
    qDebug()<<test1->getM_name();
    TestClass *test2 = TestClass::initTestClass(new QString("test2"));
    qDebug()<<test2->getM_name();

    return a.exec();
}
