#include "dialogs.h"

#include <QApplication>
#include <QDebug>
#include <QDateTime>
#include <QByteArray>
#include <QTextStream>
#include "string.h"
#include <QDate>
#include <QDataStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dialogs w;
    w.show();

//    unsigned char p=0;
//    p&=(1<<0);
//    qDebug()<<p;

    return a.exec();
}

