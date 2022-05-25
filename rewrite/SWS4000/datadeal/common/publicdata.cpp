/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   publicdata.cpp
    info:	Global public data
******************************************************************************/

#include "publicdata.h"

PublicData g_pd;

/****************************************************************************
接口描述: 公共数据类构造函数
输   入: /
输   出: /
******************************************************************************/
PublicData::PublicData()
{
    qdebug << "publicdata构造函数";
    m_mb = &ModuleBoard::initModuleBoard();
}

/****************************************************************************
接口描述: 公共数据类析构函数
输   入: /
输   出: /
******************************************************************************/
PublicData::~PublicData()
{

}

/****************************************************************************
接口描述: 装载功能码
输   入: /
输   出: /
******************************************************************************/
void PublicData::loadingFunctionCode()
{
    m_fcValue.replace(FC_mainProcessSwitch, 0);
    m_fcValue.replace(FC_bloodPumpValueAdd, 0);
    m_fcValue.replace(FC_bloodPumpValueSet, 0);
    m_fcValue.replace(FC_bloodPumpValueMinus, 0);
    m_fcValue.replace(FC_bloodPumpSwitch, 0);
    m_fcValue.replace(FC_sqlDataBaseCheck, 0);
}
