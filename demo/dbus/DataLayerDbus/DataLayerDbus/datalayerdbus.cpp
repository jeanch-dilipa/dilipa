#include "datalayerdbus.h"

DataLayerDbus::DataLayerDbus(QObject *parent) :
    QObject(parent)
{

    //接收线程
    m_ReceiveThread = new QThread(this);
    m_DataLayerDbusReceive = new DataLayerDbusReceive();
    m_DataLayerDbusReceive->moveToThread(m_ReceiveThread);
    connect(m_DataLayerDbusReceive,SIGNAL(SIGNALReceivedData(QByteArray)),this,SIGNAL(SIGNALReceData(QByteArray)));
    connect(m_DataLayerDbusReceive,SIGNAL(SIGNALDataLayerError(mDBusError,QString)),this,SIGNAL(SIGNALDataLayerError(mDBusError,QString)));
    m_ReceiveThread->start();

    //发送线程
    m_SendThread = new QThread(this);
    m_DataLayerDbusSend = new DataLayerDbusSend();
    m_DataLayerDbusSend->moveToThread(m_SendThread);
    connect(this,SIGNAL(SIGNALSendData(QByteArray)),m_DataLayerDbusSend,SLOT(SLOTDataSend(QByteArray)));
    connect(m_DataLayerDbusSend,SIGNAL(SIGNALReturnValue(bool)),this,SIGNAL(SIGNALSendRetValue(bool)));
    connect(m_DataLayerDbusSend,SIGNAL(SIGNALDataLayerError(mDBusError,QString)),this,SIGNAL(SIGNALDataLayerError(mDBusError,QString)));
    m_SendThread->start();


    //发送间隔控制定时器
    m_sendTimer = new QTimer(this);
    connect(m_sendTimer,SIGNAL(timeout()),this,SLOT(SLOTSendDataTimerFun()));
    m_sendTimer->start(20);
}
void DataLayerDbus::SLOTaddSendDataToList(QByteArray data)
{
    sendDataList.append(data);
}
void DataLayerDbus::SLOTSendDataTimerFun()
{
    if(!sendDataList.isEmpty())
    {
        emit SIGNALSendData(sendDataList.first());
        sendDataList.remove(0);
    }
}
