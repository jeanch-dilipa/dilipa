/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   functioncode.cpp
    info:	Interface module tool function code
******************************************************************************/

#ifndef FUNCTIONCODE_H
#define FUNCTIONCODE_H

typedef enum
{
    FC_default                                  = 0,

    /*主界面*/
    FC_mainProcessSwitch                        = 1,                        //主界面流程切换按钮

    FC_bloodPumpValueAdd                        = 2,                        //血泵值增加
    FC_bloodPumpValueSet                           ,                        //设置血泵值
    FC_bloodPumpValueMinus                         ,                        //血泵值减少
    FC_bloodPumpSwitch                             ,                        //血泵开关

    FC_sqlDataBaseCheck                         = 15,                       //数据库检测
}FunctionCode;

#endif // FUNCTIONCODE_H
