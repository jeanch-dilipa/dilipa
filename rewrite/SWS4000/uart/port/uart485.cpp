/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   uart485.cpp
    info:	Serial communication 485
******************************************************************************/

#include "uart485.h"

/****************************************************************************
接口描述: 485通信构造函数
输   入: /
输   出: /
******************************************************************************/
Uart485::Uart485(QString portName)
{
    m_uart = new QSerialPort(portName);                                                 /*多线程定时器异常，后期再做*/
    m_uart->setBaudRate(QSerialPort::Baud115200);
    m_uart->setDataBits(QSerialPort::Data8);
    m_uart->setParity(QSerialPort::NoParity);
    m_uart->setStopBits(QSerialPort::OneStop);
    m_uart->setFlowControl(QSerialPort::NoFlowControl);
    m_uart->open(QIODevice::ReadWrite);

    connect(m_uart, &QSerialPort::readyRead, this, &Uart485::slot_serialPortDataArrived);

    m_brokenFrameTimer = new QTimer();
    m_brokenFrameTimer->setInterval(5);
    connect(m_brokenFrameTimer, &QTimer::timeout, this, &Uart485::slot_serialPortDataInspect);

    m_uartDataSendTimer = new QTimer();
    m_uartDataSendTimer->setInterval(30);
    connect(m_uartDataSendTimer, &QTimer::timeout, this, &Uart485::slot_choiceUartDataSend);
    m_uartDataSendTimer->start(30);

    m_responseTimeout = new QTimer();
    connect(m_responseTimeout, &QTimer::timeout, this, &Uart485::slot_responseTimeOut);

    m_currentCmd = 0;
}

/****************************************************************************
接口描述: 485通信析构函数
输   入: /
输   出: /
******************************************************************************/
Uart485::~Uart485()
{
    if(nullptr != m_uart)
    {
        m_uart->close();
        delete m_uart;
        m_uart = nullptr;
    }
}

/****************************************************************************
接口描述: 处理串口发送数据
输   入: /
输   出: /
******************************************************************************/
void Uart485::dealUartSendData(const DataType dataType, const QByteArray data)
{qDebug()<<123<<m_uartDataSendTimer->isActive()<<m_uartDataSendTimer->remainingTime();
    switch (dataType)
    {
        case REGISTER_TYPE_DATA:
            m_registerQueueList.append(data);
            break;
        case UNREGISTER_TYPE_DATA:
            m_registerQueueList.removeAll(data);
            break;
        case WRITE_TYPE_DATA:
        case READ_TYPE_DATA:
            m_readWriteQueueList.append(data);
        default:
            break;
    }
}

/****************************************************************************
接口描述: 发送数据
输   入: /
输   出: /
******************************************************************************/
void Uart485::sendData()
{
    if(SYSTEM_BUS_READ_COMMAND_8 == m_sendDataBuff[1])
    {
        m_responseTimeout->setInterval(50);
    }
    else
    {
        m_responseTimeout->setInterval(25);
    }

    ushort CRCnum = CRC((unsigned char *)m_sendDataBuff.data(), m_sendDataBuff.length()).Sum();
    m_sendDataBuff[m_sendDataBuff.size()] = CRCnum & 0xff;
    m_sendDataBuff[m_sendDataBuff.size()] = CRCnum >> 8;

    m_uart->write(m_sendDataBuff);
    m_uart->flush();
    m_responseTimeout->start();
}

/****************************************************************************
接口描述: 串口数据到达
输   入: /
输   出: /
******************************************************************************/
void Uart485::slot_serialPortDataArrived()
{qDebug()<<3;
    m_responseTimeout->stop();
    m_arrivedDataBuff.append(m_uart->readAll());
    m_brokenFrameTimer->start();
}

/****************************************************************************
接口描述: 串口数据检测
输   入: /
输   出: /
******************************************************************************/
void Uart485::slot_serialPortDataInspect()
{qDebug()<<4;
    m_brokenFrameTimer->stop();
    qDebug() << m_arrivedDataBuff.toHex();
    m_uartDataSendTimer->start();
}

/****************************************************************************
接口描述: 选择串口数据发送
输   入: /
输   出: /
******************************************************************************/
void Uart485::slot_choiceUartDataSend()
{qDebug()<<1;
    m_uartDataSendTimer->stop();
    m_arrivedDataBuff.clear();
    if(0 != m_readWriteQueueList.size())
    {
        m_sendDataBuff = m_readWriteQueueList[0];
        m_readWriteQueueList.removeFirst();
    }
    else
    {
        m_sendDataBuff = m_registerQueueList[m_currentCmd];
        m_currentCmd++;
        if(m_currentCmd >= m_registerQueueList.size())
        {
            m_currentCmd = 0;
        }
    }

    if(false == m_sendDataBuff.isEmpty())
    {
        sendData();
    }
}

/****************************************************************************
接口描述: 模块响应超时
输   入: /
输   出: /
******************************************************************************/
void Uart485::slot_responseTimeOut()
{qDebug()<<2;
    m_responseTimeout->stop();
    if(1 != m_responseTime)
    {
        m_uart->write(m_sendDataBuff);
        m_uart->flush();
        m_responseTimeout->start();
        m_responseTime--;
    }
    else
    {
        slot_choiceUartDataSend();
    }
}
