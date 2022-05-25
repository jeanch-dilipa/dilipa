#include "mainqthread.h"
#include "ui_mainqthread.h"
#include "windows.h"
#include "windef.h"

#include <QDebug>
#include <QFile>

MainQthread::MainQthread(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainQthread)
{
    ui->setupUi(this);
    ui->startthread->setEnabled(true);
    ui->stopthread->setEnabled(false);
    ui->start->setEnabled(false);
    ui->pause->setEnabled(false);
    connect(&diceQthread1,&QThread::start,[=](){ui->label->setText("dicethread1 is start");});
    connect(&diceQthread1,&QThread::finished,[=](){ui->label->setText("dicethread1 is finished");});
    connect(&diceQthread1,&dice::newdicecreate,this,&MainQthread::newdicevalue);
    connect(&diceQthread2,&QThread::start,[=](){ui->label->setText("dicethread2 is start");});
    connect(&diceQthread2,&QThread::finished,[=](){ui->label->setText("dicethread2 is finished");});
    connect(&diceQthread2,&dice::newdicecreate,this,&MainQthread::newdicevalue);
}

MainQthread::~MainQthread()
{
    diceQthread1.wait();
    diceQthread2.wait();
    delete ui;
}


void MainQthread::on_startthread_clicked()
{
    ui->startthread->setEnabled(false);
    ui->stopthread->setEnabled(true);
    ui->start->setEnabled(true);
    diceQthread1.start();
//    diceQthread1.init();
    diceQthread2.start();
//    diceQthread2.init();
    ui->textEdit->clear();
}

void MainQthread::on_stopthread_clicked()
{
    ui->startthread->setEnabled(true);
    ui->stopthread->setEnabled(false);
    ui->start->setEnabled(false);
    ui->pause->setEnabled(false);
    ispause=false;
    ui->pause->setText("pause");
    diceQthread1.terminate();
    diceQthread1.wait();
    diceQthread2.terminate();
    diceQthread2.wait();
}

void MainQthread::on_start_clicked()
{
    ui->pause->setEnabled(true);
    ui->start->setEnabled(false);
    diceQthread1.dicestart();
    diceQthread2.dicestart();
}

void MainQthread::on_exit_clicked()
{
    if(diceQthread1.isRunning())
    {
        diceQthread1.quit();
    }
    if(diceQthread2.isRunning())
    {
        diceQthread2.quit();
    }
    this->close();
}

void MainQthread::on_pause_clicked()
{
    if(!ispause)
    {
        ui->pause->setText("goon");
        ispause=true;
        diceQthread1.dicepause();
        diceQthread2.dicepause();
    }
    else
    {
        ui->pause->setText("pause");
        ispause=false;
        diceQthread1.dicestart();
        diceQthread2.dicestart();
    }
}

void MainQthread::on_clear_clicked()
{
    ui->textEdit->clear();
}

void MainQthread::newdicevalue(int dicecount, int diceview,QString Qthreadid)
{
    ui->textEdit->append(QString("第%1次投色字,值是%2").arg(dicecount).arg(diceview));
    if(diceQthread1.threadpk==pk::yes)
    {
        ui->label->setText("diceQthread1 is win");
        emit ui->stopthread->clicked();
    }
    if(diceQthread1.threadpk==pk::yes)
    {
        ui->label->setText("diceQthread2 is win");
        emit ui->stopthread->clicked();
    }
    QFile file("f:/dice.txt");
    file.open(QIODevice::WriteOnly|QIODevice::Append);
    file.write("QThread::currentThreadId()");
    file.write(QString("%1:第%2次投色子,值是%3\n").arg(Qthreadid).arg(dicecount).arg(diceview).toUtf8());
    file.close();
    qDebug()<<Qthreadid<<"read";
}
