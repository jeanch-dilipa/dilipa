#include "uartlayerdbuswindow.h"
#include "ui_uartlayerdbuswindow.h"

UartLayerDbusWindow::UartLayerDbusWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UartLayerDbusWindow)
{
    ui->setupUi(this);

    m_uartLayerDbus = new UartLayerDbus(this);
    connect(m_uartLayerDbus,SIGNAL(SIGNALReceivedData(QByteArray)),this,SLOT(SLOTReceData(QByteArray)));
    connect(this,SIGNAL(SIGNALSendData(QByteArray)),m_uartLayerDbus,SLOT(SLOTaddDataToList(QByteArray)));
    connect(m_uartLayerDbus,SIGNAL(SIGNLASendReturnValue(bool)),this,SLOT(SLOTSendNextData(bool)));
    connect(m_uartLayerDbus,SIGNAL(SIGNALUartLayerError(mDBusError,QString)),this,SLOT(SLOTDbusError(mDBusError,QString)));
}

UartLayerDbusWindow::~UartLayerDbusWindow()
{
    delete ui;
}

void UartLayerDbusWindow::on_btnSend_clicked()
{
    sendData();
}

void UartLayerDbusWindow::SLOTReceData(QByteArray data)
{
    qDebug()<<data;
}
void UartLayerDbusWindow::SLOTSendNextData(bool ok)
{
    sendData();
}
void UartLayerDbusWindow::sendData()
{
    static int count = 0;
    count ++;
    emit SIGNALSendData((QString::number(count)+":"+ui->lineEditSend->text()).toAscii());
}
void UartLayerDbusWindow::SLOTDbusError(mDBusError error, QString errorMsg)
{
    qDebug()<<error<<":"<<errorMsg;
}
