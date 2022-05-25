#include <QCoreApplication>
#include <QDebug>

#include "strategy.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Context *con = new Context(new Strategy1());
    qDebug()<<con->DoSomeThing();
    con->SetStrategy(new Strategy2);
    qDebug()<<con->DoSomeThing();
    con->SetStrategy(new Strategy3);
    qDebug()<<con->DoSomeThing();

    return a.exec();
}
