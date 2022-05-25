#include <QCoreApplication>

#include <QDebug>

#include "command.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*命令模式*/

    Send* s= new Send();
    Reciver* r = new Reciver();
    s->setSimpleCommand(new simpleCommand(new QString("simple")));
    s->setComplexCommand(new ComPlexCommand(r,new QString("ComplexA"),new QString("ComplexB")));

    qDebug()<<s->doSomeSimpleThing();
    qDebug()<<s->doSomeComplexThing();

    return a.exec();
}
