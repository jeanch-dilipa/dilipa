#include <QCoreApplication>

#include <QDebug>

#include "state.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    State1 *state1 = new State1(new QString("state1"));
    Context *con = new Context(state1);
    qDebug()<<con->SetState1();
    con->SetState2();
    qDebug()<<con->SetState1();
    con->SetState2();
    qDebug()<<con->SetState1();
    con->SetState2();
    qDebug()<<con->SetState1();
    con->SetState2();
    qDebug()<<con->SetState1();
    con->SetState2();
    qDebug()<<con->SetState1();


    return a.exec();
}
