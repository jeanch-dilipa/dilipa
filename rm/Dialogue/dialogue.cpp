#include "dialogue.h"
#include "ui_dialogue.h"
#include <QTcpSocket>

#include <QDebug>
#include <QFile>
#include <QFileDialog>

    QString jfilename="";
    qint64 jfilesize=0;
    QString jfilepath="";
    qint64 jsendsize=0;

    QString ffilename="";
    qint64 ffilesize=0;
    QString ffilepath="";
    qint64 fsendsize=0;

Dialogue::Dialogue(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Dialogue)
{
    ui->setupUi(this);
    socket =new QTcpSocket(this);
//    socketfile =new QTcpSocket(this);
    ui->lineEdit_2->setText("192.168.10.35");
    connect(socket,SIGNAL(readyRead()),this,SLOT(slot_readreturn()));
    connect(socket,&QTcpSocket::readyRead,[=](){qDebug()<<"time1.currentTime()";});
}

Dialogue::~Dialogue()
{
    delete ui;
}


void Dialogue::on_lineEdit_returnPressed()
{
    QString msg = ui->lineEdit->text();
    ui->listWidget->addItem("i:    "+msg);
    socket->write(ui->lineEdit->text().toUtf8());
}

void Dialogue::on_pushButton_clicked()
{
    if(ui->lineEdit_2->text().size()!=0 && ui->lineEdit_3->text().size()!=0)
    {
        QString str=ui->lineEdit_2->text();
        int port=ui->lineEdit_3->text().toInt();
        socket->connectToHost(str,port);
        socket->waitForConnected(3000);
        if(socket->state()==QAbstractSocket::ConnectedState)
            ui->listWidget->addItem("sys:    connection successful");
        else
            ui->listWidget->addItem("sys:    connection fail");
    }
    else
    {
        ui->listWidget->addItem("sys:   请输入正确的ip*port");
    }
}

void Dialogue::slot_readreturn()
{
    QByteArray bt = socket->readAll();
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
        ui->lineEdit->setEnabled(false);
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
    }
    if(!jfilename.isEmpty())
    {
        if(jfilepath.isEmpty())
            jfilepath=QDir::currentPath()+"/"+jfilename;
        QFile file(jfilepath);
        bool isopen=file.open(QIODevice::WriteOnly|QIODevice::Append);
        if(isopen)
        {
            file.write(bt);
            file.close();
        }
        QFileInfo info(jfilepath);
        double sd=info.size()/jfilesize*100;
        ui->lineEdit->setText("已完成："+(QString::number(sd))+"%");
        if(info.size()==jfilesize)
        {
            jfilename="";
            jfilesize=0;
            jfilepath="";
            ui->listWidget->addItem("i:    read over    解锁输入");
            ui->lineEdit->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
            ui->pushButton_3->setEnabled(true);
        }
        return;
    }
    ui->listWidget->addItem(msg);
}

void Dialogue::on_pushButton_2_clicked()
{
    ffilepath=QFileDialog::getOpenFileName(this,tr("choces file"),"e:/",tr("*.*"));
    QFileInfo info(ffilepath);
    ffilename=info.fileName();
    ffilesize=info.size();
    ui->lineEdit->setText(ffilename);
}

void Dialogue::on_pushButton_3_clicked()
{
    QString info=QString("%1%2%3%4%5").arg("[tcpfile]#").arg(ffilename).arg("#").arg(ffilesize).arg("#");
    socket->write(info.toUtf8());
    char buff[4*1024]={0};
    qint64 count=0;
    QFile file(ffilepath);
    file.open(QIODevice::ReadOnly);
    while(fsendsize!=ffilesize)
    {
        count=file.read(buff,sizeof(buff));
        socket->write(buff,count);
        fsendsize+=count;
    }
    fsendsize=0;
    ui->listWidget->addItem("s:    send over");
}
