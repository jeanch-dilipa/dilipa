#include "uartlayerdbus.h"

UartLayerDbus::UartLayerDbus(QObject *parent) :
    QObject(parent)
{
    m_UartLayerDbusSend = new UartLayerDbusSend();
    m_SendThread = new QThread(this);
    m_UartLayerDbusSend->moveToThread(m_SendThread);
    connect(this,SIGNAL(SIGNALSendData(QByteArray)),m_UartLayerDbusSend,SLOT(SLOTDataSend(QByteArray)));
    connect(m_UartLayerDbusSend,SIGNAL(SIGNALSendReturnValue(bool)),this,SIGNAL(SIGNLASendReturnValue(bool)));
    connect(m_UartLayerDbusSend,SIGNAL(SIGNALUartLayerError(mDBusError,QString)),this,SIGNAL(SIGNALUartLayerError(mDBusError,QString)));
    m_SendThread->start();

    m_UartLayerDbusReceice = new UartLayerDbusReceive();
    m_receiceThread = new QThread(this);
    m_UartLayerDbusReceice->moveToThread(m_receiceThread);
    connect(m_UartLayerDbusReceice,SIGNAL(SIGNALReceivedData(QByteArray)),this,SIGNAL(SIGNALReceivedData(QByteArray)));
    connect(m_UartLayerDbusSend,SIGNAL(SIGNALUartLayerError(mDBusError,QString)),this,SIGNAL(SIGNALUartLayerError(mDBusError,QString)));
    m_receiceThread->start();

    m_sendDataTimer = new QTimer(this);
    connect(m_sendDataTimer,SIGNAL(timeout()),this,SLOT(SLOTSendDataTimerFun()));
    m_sendDataTimer->start(20);
}
void UartLayerDbus::SLOTaddDataToList(QByteArray data)
{
    sendDataList.append(data);
}
void UartLayerDbus::SLOTSendDataTimerFun()
{
    if(!sendDataList.isEmpty())
    {
        emit SIGNALSendData(sendDataList.first());
        sendDataList.remove(0);
    }
}
