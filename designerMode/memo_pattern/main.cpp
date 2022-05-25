#include <QCoreApplication>

#include <QDebug>

#include "memo.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Send<BaseMemo>* send = new Send<BaseMemo>(new QString("old"));
    Manager<Send<BaseMemo>,BaseMemo>* manger = new Manager<Send<BaseMemo>,BaseMemo>(send);
    qDebug()<<send->showSate();
    manger->backUp();
    send->doSomeThing();
    qDebug()<<send->showSate();
    manger->backUp();
    send->doSomeThing();
    qDebug()<<send->showSate();
    manger->backUp();

    qDebug()<<manger->history();

    manger->unDo();
    qDebug()<<send->showSate();
    manger->unDo();
    qDebug()<<send->showSate();
    manger->unDo();
    qDebug()<<send->showSate();


    return a.exec();
}
