#include "fileidalogue.h"
#include <QFile>
#include <QFileDialog>
#include <QDebug>

    QString filestr;
    QByteArray bt;

fileidalogue::fileidalogue(QWidget *parent)
    : QWidget(parent)
{
    filestr=QFileDialog::getOpenFileName(this,tr("OPen file") , "e:/" ,tr("*.*"));
    if(!filestr.isEmpty())
    {
        qDebug()<<filestr;
        read(filestr);
        write(filestr);
        read(filestr);
    }
}

fileidalogue::~fileidalogue()
{
}

void fileidalogue::read(QString str)
{
    QFile file(str);
    file.open(QIODevice::ReadOnly);
    for(;;)
    {
        if(!file.atEnd())
        {
            bt+=file.readLine();
        }
        else
        {
            break;
        }
    }

    qDebug()<<QString(bt);
    file.close();
}

void fileidalogue::write(QString str)
{
    QString sstr=str.mid(0,str.indexOf("."));
    QString gc=str.mid(str.indexOf("."));
    QFile file(sstr+"复制"+gc);
    file.open(QIODevice::WriteOnly|QIODevice::Append);
    file.write(bt);
    file.close();

}

