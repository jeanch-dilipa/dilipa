#include <QCoreApplication>

#include <QDebug>

#include "builder.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*生成器*/

    manager *ma = new manager();
    BuildeCreate *creat = new BuildeCreate();
    ma->setCreater(creat);
    ma->createMax();

    Product *pmin = creat->getPrduct();
    qDebug()<<pmin->_productItem;

    return a.exec();
}
