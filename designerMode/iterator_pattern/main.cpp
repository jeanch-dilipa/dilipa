#include <QCoreApplication>

#include <QDebug>

#include "iterator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Container<int> con;
    for(int i = 0; i < 10; i++)
    {
        con.add(i);
    }

    Iterator<int,Container<int>>* iter = con.createIterator();
    for(iter->first(); !iter->isend(); iter->next())
    {
        qDebug()<<*iter->current();
    }

    return a.exec();
}
