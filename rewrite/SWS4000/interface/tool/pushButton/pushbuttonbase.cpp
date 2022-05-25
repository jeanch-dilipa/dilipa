/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   pushbuttonbase.cpp
    info:	Button base class, unified button event handling interface
******************************************************************************/

#include "pushbuttonbase.h"

/****************************************************************************
接口描述: 按钮基类构造函数
输   入: parent---父类
输   出: /
******************************************************************************/
PushButtonBase::PushButtonBase(QWidget *parent) : QPushButton(parent)
{

}

/****************************************************************************
接口描述: 设置按钮功能码
输   入: code---功能码
输   出: /
******************************************************************************/
void PushButtonBase::setButtonFunctionCode(const FunctionCode code)
{
    m_fctCode = code;
}
