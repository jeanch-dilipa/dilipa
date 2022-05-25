/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   debuginterface.cpp
    info:	The main debugging interface is used by engineers only for
            system upgrade and engineer maintenance
******************************************************************************/

#include "debuginterface.h"
#include "ui_debuginterface.h"

QPointer<DebugInterface> DebugInterface::s_debug = nullptr;
QMutex *DebugInterface::s_mutexLocker = nullptr;

/****************************************************************************
接口描述: 创建工程师界面实例
输   入: /
输   出: /
******************************************************************************/
DebugInterface &DebugInterface::initDebugInterface()
{
    if(nullptr == s_debug)
    {
        QMutexLocker locker(s_mutexLocker);
        if(nullptr == s_debug)
        {
            s_debug = new DebugInterface();
            s_debug->show();
        }
    }

    return *s_debug;
}

/****************************************************************************
接口描述: 工程师界面类构造函数
输   入: /
输   出: /
******************************************************************************/
DebugInterface::DebugInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebugInterface)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
}

/****************************************************************************
接口描述: 工程师界面类析构函数
输   入: /
输   出: /
******************************************************************************/
DebugInterface::~DebugInterface()
{
    delete ui;
}
