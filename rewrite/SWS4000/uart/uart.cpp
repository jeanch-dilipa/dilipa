/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   uart.cpp
    info:	Serial communication thread
******************************************************************************/

#include "uart.h"

QPointer<Uart> Uart::s_uart = nullptr;
QMutex *Uart::s_mutexLocker = nullptr;

/****************************************************************************
接口描述: 创建串口通信线程实例
输   入: /
输   出: /
******************************************************************************/
Uart &Uart::initUart()
{
    if(nullptr == s_uart)
    {
        QMutexLocker locker(s_mutexLocker);
        if(nullptr == s_uart)
        {
            s_uart = new Uart();
        }
    }

    return *s_uart;
}

/****************************************************************************
接口描述: 串口通信线程run函数
输   入: /
输   出: /
******************************************************************************/
void Uart::run()
{
    qdebug << QThread::currentThreadId();

    m_uart485 = new Uart485("com3");
}

/****************************************************************************
接口描述: 串口通信线程构造函数
输   入: /
输   出: /
******************************************************************************/
Uart::Uart()
{
    this->moveToThread(new QThread());
    this->start(QThread::NormalPriority);
}

/****************************************************************************
接口描述: 串口通信线程析构函数
输   入: /
输   出: /
******************************************************************************/
Uart::~Uart()
{
    if(nullptr != m_uart485)
    {
        delete m_uart485;
        m_uart485 = nullptr;
    }
}

/****************************************************************************
接口描述: 分拣uart数据
输   入: attribute---数据属性, data---数据
输   出: /
******************************************************************************/
void Uart::slot_sortOutUartData(const DataAttributeType attribute, const QByteArray data)
{
    QByteArray attrData(2, 0);
    attrData[0] = attribute.m_module.m_boardAddr;
    attrData[1] = attribute.m_module.m_command;

    switch(attribute.m_uartType)
    {
        case UART_TYPE_485:
            m_uart485->dealUartSendData(attribute.m_dataType, QByteArray(attrData + data));
            break;
        case UART_TYPE_232:
            break;
        case UART_TYPE_BP:
            break;
        case UART_TYPE_IC:
            break;
        default:
            break;
    }
}
