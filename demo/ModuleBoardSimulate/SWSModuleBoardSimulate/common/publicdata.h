#ifndef PUBLICDATA_H
#define PUBLICDATA_H

#include "common.h"
#include "protocol/protocol.h"
#include "simulation/simulationsetdata.h"
#include <QDebug> ///zf_debug #include <QDebug>

//声明类型
struct SystemSettingsType;

extern ModuleBoardData    g_mbd;   //模块板数据
extern SystemSettingsType g_ss;    //系统设定
extern ModuleSimDataSetSt g_simDa; //模拟设置数据

//系统设置类型
struct SystemSettingsType
{
    MachineType    machineSetType = AutoDetectMachine;  //机器类型设置
    MachineType    machineType = NoneMachine;           //当前机器类型（自动检测）
};

#endif // PUBLICDATA_H
