#include <QCoreApplication>
#include <QDebug>

#include "visitor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Visitor1 *V1 = new Visitor1;
    Visitor2 *V2 = new Visitor2;
    std::array<const Product*,2> pro = {new ProductA,new ProductB};
    foreach(const Product *p,pro)
    {
        qDebug()<<p->Accept(V1);
        qDebug()<<p->Accept(V2);
    }

    return a.exec();
}
