/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   systemmanager.cpp
    info:	System manager, responsible for creating data processing threads,
            network communication threads, serial threads
******************************************************************************/

#include "systemmanager.h"

#include "datadeal/modelboard/moduleboard.h"

/****************************************************************************
接口描述: 系统管理器构造函数
输   入: /
输   出: /
******************************************************************************/
SystemManager::SystemManager()
{
    qdebug << QThread::currentThreadId();
    m_datadeal = &DataDeal::initDataDeal();
    m_uart = &Uart::initUart();
    m_mainwidget = &WidgetManager::initWidgetManager();
    m_network = &Network::initNetwork();

    connect(g_pd.m_mb, &ModuleBoard::signal_sendUartData, m_uart, &Uart::slot_sortOutUartData, Qt::DirectConnection);
}

/****************************************************************************
接口描述: 系统管理器析构函数
输   入: /
输   出: /
******************************************************************************/
SystemManager::~SystemManager()
{
    if(nullptr != m_uart)
    {
        m_uart->deleteLater();
        m_uart->wait();
    }

    if(nullptr != m_network)
    {
        m_network->deleteLater();
        m_network->wait();
    }

    if(nullptr != m_datadeal)
    {
        m_datadeal->deleteLater();
        m_datadeal->wait();
    }

    if(nullptr != m_mainwidget)
    {
        m_mainwidget->deleteLater();
    }
}
