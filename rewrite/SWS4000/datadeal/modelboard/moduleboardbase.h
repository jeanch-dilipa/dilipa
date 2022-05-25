/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   moduleboardbase.h
    info:	Module board communication interface
******************************************************************************/

#ifndef MODULEBOARDBASE_H
#define MODULEBOARDBASE_H

#include <QObject>
#include <QMutex>
#include <QMultiMap>

#include "datadeal/common/moduletype.h"

class ModuleBoardBase : public QObject
{
    Q_OBJECT

public:
    explicit ModuleBoardBase(const QMultiMap<SystemBusCommandType, void*> dataMap);
    ~ModuleBoardBase();

    void setAttribute(const DataAttributeType attribute);                                           //设置数据属性
    DataAttributeType getAttribute(const SystemBusCommandType command);                             //获取数据属性

private:
    QMultiMap<SystemBusCommandType, void*>                      m_dataMap;                          //协议中读/写命令
    QMultiMap<SystemBusCommandType, QMutex*>                    m_lockMap;                          //保护m_dataMap中的数据
    QMultiMap<SystemBusCommandType, DataAttributeType>          m_dataAttrMap;                      //数据属性列表
    QMultiMap<SystemBusCommandType, bool>                       m_dataUpdateFlagMap;                //数据是否更新
};

#endif // MODULEBOARDBASE_H
