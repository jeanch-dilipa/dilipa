#include "net.h"

#include <QApplication>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QDebug>
#include <QList>
#include <QHostAddress>
#include <QNetworkAddressEntry>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    net w;
    w.show();
    return a.exec();
//    qDebug()<<QHostInfo::localHostName();   //主机名
//    QHostInfo hi=QHostInfo::fromName(QHostInfo::localHostName());
//    qDebug()<<hi.localDomainName(); //主机mac
//    foreach(QHostAddress ho,hi.addresses())//主机ip列表
//         qDebug()<<ho<<ho.protocol();//协议

//    foreach(QHostAddress ha,QNetworkInterface::allAddresses())//ip列表
//         qDebug()<<"ip："<<ha;

//    foreach(QNetworkInterface nif,QNetworkInterface::allInterfaces())//接口列表
//    {
//        qDebug()<<"接口:"<<nif<<"设备名称:"<<nif.humanReadableName()<<"硬件地址:"<<nif.hardwareAddress();//设备名称，硬件地址
//        foreach(QNetworkAddressEntry nae,nif.addressEntries())
//            qDebug()<<nae.ip().toString()<<"子网掩码："<<nae.netmask().toString()<<nae.broadcast().toString();//ip，子网掩码，广播地址
//    }


}
