#include "mainthread.h"

#include "ui_mainthread.h"
#include "readwritethread.h"

mainthread::mainthread(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::mainthread)
{
    connect(&readthread,&readthread::readbuffsignal,this,&mainthread::showtext);
    ui->setupUi(this);
}

mainthread::~mainthread()
{
    if(readthread.isRunning())
    {
        readthread.quit();
        readthread.wait();
    }
    if(writethread.isRunning())
    {
        writethread.quit();
        writethread.wait();
    }
    delete ui;
}


void mainthread::on_start_clicked()
{
    writethread.start();
    writethread.over=false;
    readthread.start();
    readthread.over=false;

}

void mainthread::on_stop_clicked()
{
    readthread.threadstop();
    writethread.threadstop();
}

void mainthread::showtext(int *data, int size, int num)
{
    if(readthread.isRunning()&&writethread.isRunning())
    {
        QString str;
        str.append(QString("缓冲区%1:").arg(num));
        for(int i=0;i<size;i++)
        {
            str.append(QString(" ,%1").arg(*data));
            data++;
        }
        ui->textEdit->append(str);
    }
    if(num==1000)
    {
        readthread.threadstop();
        writethread.threadstop();
    }
}


