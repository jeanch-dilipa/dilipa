#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->com->clear();
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        QSerialPort se;
        se.setPort(info);
        if(se.open(QIODevice::ReadWrite))
        {
            ui->com->addItem(se.portName());
        }
    }
    ser=new QSerialPort();
    ser->setPortName(ui->com->currentText());
    if(ser->open(QIODevice::ReadWrite))
    ser->setBaudRate(QSerialPort::Baud9600);
    ser->setDataBits(QSerialPort::Data8);
    ser->setStopBits(QSerialPort::OneStop);
    ser->setParity(QSerialPort::EvenParity);
    ser->setFlowControl(QSerialPort::NoFlowControl);

    ser1=new QSerialPort();
    ser1->setPortName(ui->com->itemText(1));
    if(ser1->open(QIODevice::ReadWrite))
    ser1->setBaudRate(QSerialPort::Baud9600);
    ser1->setDataBits(QSerialPort::Data8);
    ser1->setStopBits(QSerialPort::OneStop);
    ser1->setParity(QSerialPort::EvenParity);
    ser1->setFlowControl(QSerialPort::NoFlowControl);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_send_clicked()
{
    ser->write(ui->write->toPlainText().toUtf8(),ui->write->toPlainText().toUtf8().length());
    ser->flush();
    ui->read->setText(ser1->readAll());
}
