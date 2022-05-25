#include "net.h"
#include "ui_net.h"

net::net(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::net)
{
    ui->setupUi(this);
    tcp=new QTcpSocket;
    tcp->connectToHost("127.0.0.1",10000);
    tcp->waitForConnected(2000);
    if(tcp->state()==QAbstractSocket::ConnectedState)
        qDebug()<<"连接成功";
    else
        qDebug()<<"连接失败";
    connect(tcp,&QTcpSocket::readyRead,[=]{qDebug()<<tcp->readAll();});
    tser=new QTcpServer;
    tser->listen(QHostAddress::Any,10000);
    connect(tser,&QTcpServer::newConnection,[=]
                                                {
                                                    if(tser->hasPendingConnections())
                                                    {
                                                        tcp=tser->nextPendingConnection();
                                                        qDebug()<<"new connect";
                                                        connect(tcp,&QTcpSocket::readyRead,[=]{qDebug()<<tcp->readAll();});
                                                    }
                                                });
}

net::~net()
{
    delete ui;
}

