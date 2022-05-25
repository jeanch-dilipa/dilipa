/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   network.cpp
    info:	Network communication thread
******************************************************************************/

#include "network.h"

QPointer<Network> Network::s_network = nullptr;
QMutex *Network::s_mutexLocker = nullptr;

/****************************************************************************
接口描述: 创建网络通信线程实例
输   入: /
输   出: /
******************************************************************************/
Network &Network::initNetwork()
{
    if(nullptr == s_network)
    {
        QMutexLocker locker(s_mutexLocker);
        if(nullptr == s_network)
        {
            s_network = new Network();
        }
    }

    return *s_network;
}

/****************************************************************************
接口描述: 网络通信线程run函数
输   入: /
输   出: /
******************************************************************************/
void Network::run()
{
    qdebug << QThread::currentThreadId();
}

/****************************************************************************
接口描述: 网络通信线程构造函数
输   入: /
输   出: /
******************************************************************************/
Network::Network()
{
    this->moveToThread(new QThread());
    this->start(QThread::LowPriority);
}

/****************************************************************************
接口描述: 网络通信线程析构函数
输   入: /
输   出: /
******************************************************************************/
Network::~Network()
{

}
