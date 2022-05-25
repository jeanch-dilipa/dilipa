#include <QCoreApplication>

#include <QDebug>

#include <observer.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Subject *sub = new Subject();
    Observer *obser1 = new Observer(sub);
    Observer *obser2 = new Observer(sub);
    Observer *obser3 = new Observer(sub);

    sub->newMessage(QString("newmesssage"));
    qDebug()<<sub->issue();


    return a.exec();
}
