#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <testthread.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<"threadidmain"<<QThread::currentThread();
    testthread t1;
    testthread t2;
    t1.start();
    t2.start();
    QObject::connect(&t1,&testthread::pubdata,&t2,&testthread::fun);
    QObject::connect(&t2,&testthread::pubdata,&t1,&testthread::fun);


    return 0;
//    return a.exec();
}
