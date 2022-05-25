/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   uart485.h
    info:	Serial communication 485
******************************************************************************/

#ifndef UART485_H
#define UART485_H

#include <QObject>
#include <QSerialPort>
#include <QPointer>
#include <QTimer>
#include <qDebug>

#include "datadeal/common/moduletype.h"
#include "uart/crc/crc.h"

class Uart485 : public QObject
{
    Q_OBJECT

public:
    explicit Uart485(QString portName);
    virtual ~Uart485();

    void dealUartSendData(const DataType dataType, const QByteArray data);              //处理串口发送数据

private:
    void sendData();                                                                    //发送数据

private slots:
    void slot_serialPortDataArrived();                                                  //串口数据到达
    void slot_serialPortDataInspect();                                                  //串口数据检测
    void slot_choiceUartDataSend();                                                     //选择串口数据发送
    void slot_responseTimeOut();                                                        //模块响应超时

private:
    QPointer<QSerialPort>                       m_uart;
    QList<QByteArray>                           m_readWriteQueueList;                   //读写命令队列
    QList<QByteArray>                           m_registerQueueList;                    //注册队列

    QByteArray                                  m_arrivedDataBuff;                      //接收到的串口数据
    QByteArray                                  m_sendDataBuff;                         //发送到串口的数据

    QPointer<QTimer>                            m_brokenFrameTimer;                     //断帧定时器
    QPointer<QTimer>                            m_uartDataSendTimer;                    //串口数据发送定时器
    QPointer<QTimer>                            m_responseTimeout;                      //模块板响应超时定时器
    quint8                                      m_currentCmd;                           //当前注册命令
    quint8                                      m_responseTime;                         //回复超时次数
};

#endif // UART485_H
