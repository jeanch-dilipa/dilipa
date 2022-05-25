#include <QCoreApplication>

#include <QDebug>

#include "organization.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*组合模式*/

    Organization *simple = new Leaf(new QString("simple"));
    if(simple->isLeaf())
    {
        qDebug()<<simple->Operation();
    }

    Organization *tree = new Continer();
    Organization *continer = new Continer();
    Organization *leaf1 = new Leaf(new QString("leaf1"));
    Organization *leaf2 = new Leaf(new QString("leaf2"));
    Organization *Leaf3 = new Leaf(new QString("leaf3"));
    Organization *leaf4 = new Leaf(new QString("leaf4"));

    tree->addItem(continer);
    tree->addItem(leaf1);
    continer->addItem(leaf2);
    continer->addItem(Leaf3);
    continer->addItem(leaf4);
    qDebug()<<tree->Operation();

    tree->addItem(simple);
    tree->removeItem(leaf2);
    qDebug()<<tree->Operation();

    return a.exec();
}
