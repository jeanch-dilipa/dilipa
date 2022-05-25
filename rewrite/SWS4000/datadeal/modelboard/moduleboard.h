/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   moduleboard.h
    info:	Module board communication interface
******************************************************************************/

#ifndef MODULEBOARD_H
#define MODULEBOARD_H

#include <QObject>
#include <QMutex>
#include <QPointer>
#include <QMutexLocker>
#include <QMultiMap>

#include "datadeal/common/moduletype.h"
#include "datadeal/modelboard/moduleboardbase.h"

class ModuleBoard : public QObject
{
    Q_OBJECT

public:
    static ModuleBoard& initModuleBoard();

    void registerDataDeliveryQueue(const ModuleBoardAddrType addr, const SystemBusCommandType command);                 //注册数据下发队列
    void unRegisterDataDeliveryQueue(const ModuleBoardAddrType addr, const SystemBusCommandType command);               //注销数据下发队列
    void setModuleBoardDataAttribute(const DataAttributeType attribute);                                                //设置模块板数据属性

    void sync(SyncTag tag);                                                                                             //同步下发

private:
    explicit ModuleBoard();
    ~ModuleBoard();

signals:
    void signal_sendUartData(const DataAttributeType, const QByteArray);                                                //发送数据到Uart

private:
    static QPointer<ModuleBoard>                                s_mb;
    static QMutex                                              *s_mutexLocker;

    QMultiMap<ModuleBoardAddrType, QPointer<ModuleBoardBase>>   m_moduleBoardMap;                                       //模块
};

#endif // MODULEBOARD_H
