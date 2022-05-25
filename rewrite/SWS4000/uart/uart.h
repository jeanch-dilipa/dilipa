/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   uart.h
    info:	Serial communication thread
******************************************************************************/

#ifndef UART_H
#define UART_H

#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QPointer>

#include "common/common.h"
#include "uart/port/uart485.h"
#include "datadeal/common/moduletype.h"

class Uart: public QThread
{
    Q_OBJECT

public:
    static Uart& initUart();

protected:
    void run();

private:
    explicit Uart();
    virtual ~Uart();

public slots:
    void slot_sortOutUartData(const DataAttributeType attribute, const QByteArray data);        //分拣uart数据

private:
    static QPointer<Uart>           s_uart;
    static QMutex                  *s_mutexLocker;

    QPointer<Uart485>               m_uart485;                      //485通信
};

#endif // UART_H
