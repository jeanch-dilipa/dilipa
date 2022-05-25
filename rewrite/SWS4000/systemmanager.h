/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   systemmanager.h
    info:	System manager, responsible for creating data processing threads,
            network communication threads, serial threads
******************************************************************************/

#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <QObject>
#include <QPointer>
#include <QTimer>

#include "interface/widgetmanager.h"
#include "datadeal/datadeal.h"
#include "network/network.h"
#include "uart/uart.h"
#include "datadeal/common/publicdata.h"

class SystemManager: public QObject
{
    Q_OBJECT

public:
    explicit SystemManager();
    ~SystemManager();

private:
    QPointer<WidgetManager>                         m_mainwidget;               //界面管理
    QPointer<DataDeal>                              m_datadeal;                 //数据处理
    QPointer<Network>                               m_network;                  //网络通信
    QPointer<Uart>                                  m_uart;                     //串口通信
};

#endif // SYSTEMMANAGER_H
