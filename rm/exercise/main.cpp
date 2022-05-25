#include "myexercise.h"

#include<QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myexercise w;
    w.show();
    return a.exec();

//    QString str="a";
//    QString str1="b";
//    QString str2=str+str1;
//    qDebug()<<str2;
//    str.append(str1);
//    qDebug()<<str;
//    qDebug()<<str.sprintf("%s %s","str1","str2");
//    QString str3=QString("%1 welcome %2").arg(str).arg(str1);
//    qDebug()<<str3;
//    QString str="ss";
//    qDebug()<<str.insert(1,"aa");
//    qDebug()<<str.prepend("  ");
//    qDebug()<<str.replace(3,2,"  ");
//    qDebug()<<str.trimmed();
//    qDebug()<<str.simplified();

//    return 0;
}
