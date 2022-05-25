#include "uartlayerlibusewindow.h"
#include "ui_uartlayerlibusewindow.h"

UartLayerLibUseWindow::UartLayerLibUseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UartLayerLibUseWindow)
{
    ui->setupUi(this);

    mUartLayerDbus = new UartLayerDbus(this);
    connect(mUartLayerDbus,SIGNAL(SIGNALUartLayerError(mDBusError,QString)),this,SLOT(SLOTDbusError(mDBusError,QString)));
    connect(mUartLayerDbus,SIGNAL(SIGNLASendReturnValue(bool)),this,SLOT(SLOTSendNextData(bool)));
    connect(mUartLayerDbus,SIGNAL(SIGNALReceivedData(QByteArray)),this,SLOT(SLOTReceive(QByteArray)));
    connect(this,SIGNAL(SIGNALSendData(QByteArray)),mUartLayerDbus,SLOT(SLOTaddDataToList(QByteArray)));
}

UartLayerLibUseWindow::~UartLayerLibUseWindow()
{
    delete ui;
}
void UartLayerLibUseWindow::SLOTDbusError(mDBusError error, QString errorMsg)
{
    qDebug()<<error<<":"<<errorMsg;
}
void UartLayerLibUseWindow::SLOTReceive(QByteArray data)
{
    qDebug()<<data;
}
void UartLayerLibUseWindow::sendData()
{
    static int count = 0;
    count ++;
    emit SIGNALSendData((QString::number(count)+":"+ui->lineEditSend->text()).toAscii());
}
void UartLayerLibUseWindow::SLOTSendNextData(bool ok)
{
    sendData();
}
void UartLayerLibUseWindow::on_btnSend_clicked()
{
    sendData();
}
