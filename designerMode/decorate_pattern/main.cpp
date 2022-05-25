#include <QCoreApplication>

#include <QDebug>

#include "decorate.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ProductA  *pro = new ProductA();
    qDebug()<<pro->show();

    DecorateA *da = new DecorateA(pro);
    qDebug()<<da->show();

    DecorateB *db = new DecorateB(da);
    qDebug()<<db->show();

    return a.exec();
}
