/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   modulestruct.h
    info:	Module board data structure
******************************************************************************/

#ifndef MODULESTRUCT_H
#define MODULESTRUCT_H

#include "modulecommon.h"

struct MDB
{
    DCmotor                         bp;                             //血泵
    DCmotor                         fp;                             //补液泵
    UlterFilterPlate                ufp;                            //超滤泵
    HeparinPlate                    hp;                             //肝素泵
    DriveBoard                      drive;                          //驱动板
    Balance                         balance;                        //平衡腔
    Mixture                         mixture;                        //配液板
    Monitor                         monitor;                        //监控板
    Heat                            heat;                           //加热板
    Power                           power;                          //电源板
    Cond                            cond;                           //电导板
    BloodPressure                   bpm;                            //血压计
    OnlineKtv                       rcm;                            //实时清除率
    BTBV                            btbv;                           //血温血容
};

#endif // MODULESTRUCT_H
