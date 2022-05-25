/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   datadeal.cpp
    info:	Data processing
******************************************************************************/

#include "datadeal.h"

QPointer<DataDeal> DataDeal::s_datadeal = nullptr;
QMutex *DataDeal::s_mutexLocker = nullptr;

/****************************************************************************
接口描述: 创建数据处理线程实例
输   入: /
输   出: /
******************************************************************************/
DataDeal &DataDeal::initDataDeal()
{
    if(nullptr == s_datadeal)
    {
        QMutexLocker locker(s_mutexLocker);
        if(nullptr == s_datadeal)
        {
            s_datadeal = new DataDeal();
        }
    }

    return *s_datadeal;
}

/****************************************************************************
接口描述: 数据处理线程run函数
输   入: /
输   出: /
******************************************************************************/
void DataDeal::run()
{
    qdebug << QThread::currentThreadId();
    m_sql = &SqlBase::initSqlBase("");
}

/****************************************************************************
接口描述: 数据处理线程构造函数
输   入: /
输   出: /
******************************************************************************/
DataDeal::DataDeal()
{
    this->moveToThread(new QThread());
    this->start(QThread::NormalPriority);
}

/****************************************************************************
接口描述: 数据处理线程析构函数
输   入: /
输   出: /
******************************************************************************/
DataDeal::~DataDeal()
{

}
