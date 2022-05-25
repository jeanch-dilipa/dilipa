#include "datalayerdbuswindow.h"
#include "ui_datalayerdbuswindow.h"

DataLayerDbusWindow::DataLayerDbusWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DataLayerDbusWindow)
{
    ui->setupUi(this);

    mDataLayerDbus = new DataLayerDbus(this);
    connect(mDataLayerDbus,SIGNAL(SIGNALDataLayerError(mDBusError,QString)),this,SLOT(SLOTDbusError(mDBusError,QString)));
    connect(mDataLayerDbus,SIGNAL(SIGNALSendRetValue(bool)),this,SLOT(SLOTSendNextData(bool)));
    connect(mDataLayerDbus,SIGNAL(SIGNALReceData(QByteArray)),this,SLOT(SLOTReceive(QByteArray)));
    connect(this,SIGNAL(SIGNALSendData(QByteArray)),mDataLayerDbus,SLOT(SLOTaddSendDataToList(QByteArray)));
}

DataLayerDbusWindow::~DataLayerDbusWindow()
{
    delete ui;
}
void DataLayerDbusWindow::SLOTDbusError(mDBusError error, QString errorMsg)
{
    qDebug()<<error<<":"<<errorMsg;
}
void DataLayerDbusWindow::SLOTReceive(QByteArray data)
{
    qDebug()<<data;
}
void DataLayerDbusWindow::sendData()
{
    static int count = 0;
    count ++;
    emit SIGNALSendData((QString::number(count)+":"+ui->lineEditSend->text()).toAscii());
}
void DataLayerDbusWindow::SLOTSendNextData(bool ok)
{
    sendData();
}
void DataLayerDbusWindow::on_btnSend_clicked()
{
    sendData();
}
