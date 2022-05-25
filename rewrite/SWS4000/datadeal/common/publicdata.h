/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   publicdata.h
    info:	Global public data
******************************************************************************/

#ifndef PUBLICDATA_H
#define PUBLICDATA_H

#include <QObject>
#include <QPointer>

#include "datadeal/common/modulestruct.h"
#include "datadeal/modelboard/moduleboard.h"
#include "datadeal/common/functioncode.h"
#include "common/common.h"

class PublicData : public QObject
{
    Q_OBJECT

public:
    explicit PublicData();
    virtual ~PublicData();

    void loadingFunctionCode();                                 //装载功能码

public:
    MDB                                 m_mdb;                  //模块板
    QPointer<ModuleBoard>               m_mb;                   //模块通信管理
    QMultiMap<FunctionCode, int>        m_fcValue;              //功能值
};

extern PublicData g_pd;

#endif // PUBLICDATA_H
