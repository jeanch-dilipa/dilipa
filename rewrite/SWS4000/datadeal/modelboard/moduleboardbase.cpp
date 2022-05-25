/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   moduleboardbase.cpp
    info:	Module board communication interface
******************************************************************************/

#include "moduleboardbase.h"

/****************************************************************************
接口描述: 模块板通信基类构造函数
输   入: dataMap---
输   出: /
******************************************************************************/
ModuleBoardBase::ModuleBoardBase(const QMultiMap<SystemBusCommandType, void *> dataMap)
{
    m_dataMap = dataMap;
}

/****************************************************************************
接口描述: 模块板通信基类析构函数
输   入: /
输   出: /
******************************************************************************/
ModuleBoardBase::~ModuleBoardBase()
{

}

/****************************************************************************
接口描述: 设置数据属性
输   入: attribute---数据属性
输   出: /
******************************************************************************/
void ModuleBoardBase::setAttribute(const DataAttributeType attribute)
{
    m_dataAttrMap.insert(attribute.m_module.m_command, attribute);
}

/****************************************************************************
接口描述: 获取数据属性
输   入: command---指令
输   出: 数据属性
******************************************************************************/
DataAttributeType ModuleBoardBase::getAttribute(const SystemBusCommandType command)
{
    return m_dataAttrMap.value(command);
}
