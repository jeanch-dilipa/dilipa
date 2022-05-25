/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   network.h
    info:	Network communication thread
******************************************************************************/

#ifndef NETWORK_H
#define NETWORK_H

#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QPointer>

#include "common/common.h"

class Network: public QThread
{
    Q_OBJECT

public:
    static Network& initNetwork();

protected:
    void run();

private:
    explicit Network();
    ~Network();

private:
    static QPointer<Network>            s_network;
    static QMutex                      *s_mutexLocker;
};

#endif // NETWORK_H
