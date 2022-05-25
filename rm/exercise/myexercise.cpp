#include "myexercise.h"
#include "crc.h"

#include <QDebug>

myexercise::myexercise(QWidget *parent)
    : QMainWindow(parent)
{
    QByteArray bt;
    bt.append(0x01);
    bt.append(0x2e);
    bt.append(0x80);
    bt.append(0x3c);
    qDebug()<<CRC((uchar *)bt.data(),bt.length()).Sum();
}

myexercise::~myexercise()
{
}

