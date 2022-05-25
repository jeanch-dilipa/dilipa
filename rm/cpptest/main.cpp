#include "algorithm.h"

#include <QApplication>
#include <QDebug>

QString str(int i);
int aa(QString s);
int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    algorithm w;
//    w.show();
//    return a.exec();
    algorithm a;
    qDebug()<<"11";
    a.add();
    QString str1=str(1);
    qDebug()<<"22";
    return(0);
}

QString str(int i)
{
    return "s";
}
int aa(QString s)
{
    qDebug()<<s;
    if(s!="s")
        return 0;
    else
        return 1;

}
