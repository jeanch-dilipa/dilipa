#include <QCoreApplication>

#include <QDebug>

#include "mediation.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    IncidentA* IA = new IncidentA();
    IncidentB* IB = new IncidentB();
    MediationA* MA = new MediationA(IA,IB);
    Q_UNUSED(MA);

    qDebug()<<IB->DoD();

    return a.exec();
}
