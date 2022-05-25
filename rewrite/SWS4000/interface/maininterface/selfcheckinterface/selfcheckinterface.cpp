/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   selfcheckinterface.cpp
    info:	System self-check control interface
******************************************************************************/

#include "selfcheckinterface.h"
#include "ui_selfcheckinterface.h"

QPointer<SelfCheckInterface> SelfCheckInterface::s_selfCheck = nullptr;
QMutex *SelfCheckInterface::s_mutexLocker = nullptr;

/****************************************************************************
接口描述: 创建自检界面实例
输   入: /
输   出: /
******************************************************************************/
SelfCheckInterface &SelfCheckInterface::initSelfCheckInterface()
{
    if(nullptr == s_selfCheck)
    {
        QMutexLocker locker(s_mutexLocker);
        if(nullptr == s_selfCheck)
        {
            s_selfCheck = new SelfCheckInterface();
        }
    }

    return *s_selfCheck;
}

/****************************************************************************
接口描述: 启动界面构造函数
输   入: parent---父窗口
输   出: /
******************************************************************************/
SelfCheckInterface::SelfCheckInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelfCheckInterface)
{
    ui->setupUi(this);
}

/****************************************************************************
接口描述: 启动界面析构函数
输   入: /
输   出: /
******************************************************************************/
SelfCheckInterface::~SelfCheckInterface()
{
    delete ui;
}
