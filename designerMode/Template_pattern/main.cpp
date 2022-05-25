#include <QCoreApplication>
#include <QDebug>

#include "template.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TemplateT *tempT = new TemplateT();
    qDebug()<<tempT->TemplateMothd();
    TemplateK *tempK = new TemplateK();
    qDebug()<<tempK->TemplateMothd();


    return a.exec();
}
