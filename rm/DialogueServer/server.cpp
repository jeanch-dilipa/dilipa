#include "server.h"
#include "ui_server.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QThread>
#include <QTimer>
#include <windows.h>
#include <QTranslator>
#include <QDir>

    QTcpServer *ts;
    QTcpSocket *tc;
//    QTcpSocket *tcf;

    QString ffilename="";
    QString ffilepath;
    qint64 ffilesize=0;
    qint64 fsendsize=0;
    QByteArray fbt;

    QString jfilename="";
    QString jfilepath;
    qint64 jfilesize=0;
    qint64 jsendsize=0;
    QByteArray jbt;

Server::Server(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    ts=new QTcpServer;
//    timer=new QTimer(this);
    ts->listen(QHostAddress::Any,10000);
    connect(ts,&QTcpServer::newConnection,this,&Server::slot_connect);
}

Server::~Server()
{
    delete ui;
}

void Server::slot_connect()
{
    if(ts->hasPendingConnections())
    {
        tc=ts->nextPendingConnection();
//        tcf=ts->nextPendingConnection();
        ui->listWidget->addItem("new connect..");
        connect(tc,&QTcpSocket::readyRead,this,&Server::slot_read);
//        connect(tcf,&QTcpSocket::readyRead,this,&Server::slot_read);
//        connect(tc,&QTcpSocket::disconnected,this,&Server::slot_disconnect);
    }
}

void Server::slot_read()
{
    QByteArray bt = tc->readAll();
    QString msg=bt;
    int isfile=msg.mid(0,9).compare("[tcpfile]",Qt::CaseInsensitive);
    if(isfile==0 && jfilename.isEmpty())
    {
        jfilename=msg.section("#",1,1);
        jfilesize=msg.section("#",2,2).toInt();
        QString str="[tcpfile]#"+msg.section("#",1,2)+"#";
        msg=msg.section("#",1,1);
        bt=bt.mid(str.toUtf8().size());
        ui->listWidget->addItem("i:    接收文件: "+msg+" 锁定输入");
        ui->lineEdit_3->setEnabled(false);
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
    }
    if(!jfilename.isEmpty())
    {
        if(jfilepath.isEmpty())
            jfilepath="F:/"+jfilename;
        QFile file(jfilepath);
        bool isopen=file.open(QIODevice::WriteOnly|QIODevice::Append);
        if(isopen)
        {
            file.write(bt);
            file.close();
        }
        QFileInfo info(jfilepath);
        double sd=info.size()/jfilesize*100;
        ui->lineEdit_3->setText(tr("已完成：")+(QString::number(sd))+"%");
        if(info.size()==jfilesize)
        {
            jfilename="";
            jfilesize=0;
            jfilepath="";
            ui->listWidget->addItem("i:    read over    解锁输入");
            ui->lineEdit_3->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
        }
        return;
    }
    ui->listWidget->addItem(msg);
}

//void Server::slot_disconnect()
//{
//    ui->listWidget->addItem("close");
//    ts->close();
//}

void Server::on_lineEdit_3_returnPressed()
{
    tc->write(ui->lineEdit_3->text().toUtf8());
    ui->listWidget->addItem("i:    "+ui->lineEdit_3->text().toUtf8());
}

void Server::on_pushButton_clicked()
{
    ffilepath=QFileDialog::getOpenFileName(this,tr("choces file"),"e:/",tr("*.*"));
    QFileInfo info(ffilepath);
    ffilename=info.fileName();
    ffilesize=info.size();
    ui->lineEdit_3->setText(ffilename);
}

void Server::on_pushButton_2_clicked()
{
    QString info=QString("%1%2%3%4%5").arg("[tcpfile]#").arg(ffilename).arg("#").arg(ffilesize).arg("#");
    tc->write(info.toUtf8());
    char buff[4*1024]={0};
    qint64 count=0;
    QFile file(ffilepath);
    file.open(QIODevice::ReadOnly);
    while(fsendsize!=ffilesize)
    {
        count=file.read(buff,sizeof(buff));
        tc->write(buff,count);
        fsendsize+=count;
    }
    fsendsize=0;
    ui->listWidget->addItem("s:    send over");
}


void Server::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1=="english")
    {
        qtranslator.load(dir.absolutePath()+"/english.qm");     //qApp指向自己的宏
        qApp->installTranslator(&qtranslator);
        ui->retranslateUi(this);
    }
    else
    {
        qApp->removeTranslator(&qtranslator);
        ui->retranslateUi(this);
    }
}
