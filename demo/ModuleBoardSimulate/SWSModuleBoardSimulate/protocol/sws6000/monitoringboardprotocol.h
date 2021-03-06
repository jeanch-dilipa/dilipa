
/*******************************************************************************
Copyright (c) 2014,重庆山外山科技有限公司技术中心
All rights reserved.
文件：    monitoringboardtypes.h
作者：    lp
版本：    V1.0
日期：    2014-02-06
摘要：    定义485协议中定义监控板模块数据结构等********************************************************************************/

#ifndef MONITORINGBOARDPROTOCOL_H
#define MONITORINGBOARDPROTOCOL_H
#include <QtGlobal>

#ifdef Q_OS_WIN
    #pragma pack(1) /*Windows下MinGW编译，__attribute__((packed))没有效果*/
#endif

/***************************************************************************
*   监控板WR0定义，控制
****************************************************************************/
#define MB_WR0_OO       (1 << 7)     //0/1-“正常关机”/ “异常关机”
struct MB_WR0
{
    unsigned char   cmd;      //控制命令1

    unsigned int    ret;        //预留
}__attribute__((packed));

/***************************************************************************
*  监控板驱动模块WR8（复位重启命令）-0字节
****************************************************************************/

/***************************************************************************
*  监控板驱动模块WR9（升级命令信息）-1026字节
****************************************************************************/
struct MB_WR9
{
    unsigned char data_sum;         //APP数据帧总量
    unsigned char data_num;         //当前数据帧编号
    unsigned char data_value[1024]; //数据值，APP程序代码
}__attribute__((packed));

/***************************************************************************
*   监控板RD7定义，软硬件版本信息
****************************************************************************/
struct MB_RD7
{
    unsigned short  id;     //部件标识码
    unsigned short  hv;     //硬件版本
    unsigned short  sv;     //软件版本
}__attribute__((packed));

/***************************************************************************
*   监控板驱动模块RD8（软硬件版本信息）-6字节
****************************************************************************/
struct MB_RD8
{
    unsigned char next_num;    //发送对应数据帧
    unsigned char write_sum;   //已写入数据量
    unsigned char iap_sv;      //升级程序 软件版本
}__attribute__((packed));

#ifdef Q_OS_WIN
    #pragma pack(0) /*恢复结构体对齐，以免影响到其他地方*/
#endif

#endif // MONITORINGBOARDPROTOCOL_H
