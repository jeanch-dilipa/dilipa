#include <QCoreApplication>

#include <QDebug>

#include "chain.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DecisionA* A = new DecisionA();
    DecisionB* B = new DecisionB();
    DecisionC* C = new DecisionC();

    A->next_decision(B)->next_decision(C);

    qDebug()<<A->dec(QString("C"));
    qDebug()<<B->dec(QString("B"));
    qDebug()<<C->dec(QString("A"));

    return a.exec();
}
