#include "datalaywindow.h"
#include "ui_datalaywindow.h"

DataLayWindow::DataLayWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DataLayWindow)
{
    ui->setupUi(this);

    m_dataLayer = new  DataLayerDbus(this);
    connect(this,SIGNAL(SIGNALSendData(QByteArray)),m_dataLayer,SLOT(SLOTaddSendDataToList(QByteArray)));
    connect(m_dataLayer,SIGNAL(SIGNALReceData(QByteArray)),this,SLOT(SLOTReceData(QByteArray)));
    connect(m_dataLayer,SIGNAL(SIGNALSendRetValue(bool)),this,SLOT(SLOTSendNextData(bool)));
    connect(m_dataLayer,SIGNAL(SIGNALDataLayerError(mDBusError,QString)),this,SLOT(SLOTDbusError(mDBusError,QString)));
}

DataLayWindow::~DataLayWindow()
{
    delete ui;
}

void DataLayWindow::on_btnSend_clicked()
{
    sendData();
}
void DataLayWindow::SLOTReceData(QByteArray data)
{
    qDebug()<<data;
}
void DataLayWindow::SLOTSendNextData(bool ok)
{
    sendData();
}
void DataLayWindow::sendData()
{
    static int count = 0;
    count ++;
    emit SIGNALSendData((QString::number(count)+":"+ui->lineEditSend->text()).toAscii());
}
void DataLayWindow::SLOTDbusError(mDBusError error, QString errorMsg)
{
    qDebug()<<error<<":"<<errorMsg;
}
