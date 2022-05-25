/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   functioninterface.cpp
    info:	Function module setting interface
******************************************************************************/

#include "functioninterface.h"
#include "ui_functioninterface.h"

/****************************************************************************
接口描述: 功能模块界面构造函数
输   入: parent---父窗口
输   出: /
******************************************************************************/
FunctionInterface::FunctionInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FunctionInterface)
{
    ui->setupUi(this);
}

/****************************************************************************
接口描述: 功能模块界面析构函数
输   入: /
输   出: /
******************************************************************************/
FunctionInterface::~FunctionInterface()
{
    delete ui;
}
