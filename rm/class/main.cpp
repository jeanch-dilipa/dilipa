#include "aclass.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    aclass a;
    int resurt=a.Add(-1,0);
    if(resurt!=8)
        qDebug()<<resurt;
    else
        qDebug()<<"no";
}
