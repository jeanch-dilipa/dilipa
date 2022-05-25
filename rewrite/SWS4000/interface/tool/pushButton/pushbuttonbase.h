/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   pushbuttonbase.cpp
    info:	Button base class, unified button event handling interface
******************************************************************************/

#ifndef PUSHBUTTONBASE_H
#define PUSHBUTTONBASE_H

#include <QPushButton>

#include "datadeal/common/functioncode.h"

class PushButtonBase :public QPushButton
{
    Q_OBJECT

public:
    explicit PushButtonBase(QWidget *parent = nullptr);

    void setButtonFunctionCode(const FunctionCode code = FC_default);

private:
    FunctionCode                    m_fctCode;                      //按键功能码
};

#endif // PUSHBUTTONBASE_H
