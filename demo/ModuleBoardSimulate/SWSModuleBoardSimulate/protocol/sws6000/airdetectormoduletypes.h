/*****************************************************************************
 *  Copyright (c) 2014,重庆山外山科技有限公司技术中心 All rights reserved.
 *  摘要：空气探测器模块通信数据定义
 *  版本：V1.0
 *  作者：wzx
 *  日期：2021-04-23
 * **************************************************************************/
#ifndef AIRDETECTORMODULETYPES_H
#define AIRDETECTORMODULETYPES_H
#include <QtGlobal>

#ifdef Q_OS_WIN
    #pragma pack(1) /*Windows下MinGW编译，__attribute__((packed))没有效果*/
#endif

/***************************************************************************
*   空气探测器模块WR0 — 11 字节
****************************************************************************/
#define AIR_DETECTOR_WRO_CAL    (1 << 7) // 0/1 未开始/开始压电陶瓷谐振频率校正
#define AIR_DETECTOR_WRO_SWITCH (1 << 0) // 0/1 关闭/打开气泡累计功能
struct AIR_DETECTOR_WR0
{
    unsigned char st;                       //空气探测器校正、开关、报警等命令
    unsigned char mode ;                   //模式
    unsigned char bigBubbleLimit;          //单个大气泡报警限 0～100
    unsigned short microBubbltLimit;        //小气泡累计量报警限 0～5000
    unsigned char bloodVoltageConnect;     //引血血液识别信号报警限，放大10倍 0～50
    unsigned char bloodVoltageDisconnect;  //回血血液识别信号报警限，放大10倍 0～50
    unsigned short reserved1; //预留1
    unsigned short reserved2; //预留2
}__attribute__((packed));


/***************************************************************************
*   空气探测器模块WR7 — 6 字节
****************************************************************************/
struct AIR_DETECTOR_WR7
{
    unsigned short code;        //部件标识码
    unsigned short hVer ;       //硬件版本
    unsigned short reserved;    //预留
}__attribute__((packed));

/***************************************************************************
*   空气探测器模块RD0 — 12字节
****************************************************************************/
#define AIR_DETECTOR_RD0_CAL        (1 << 7) // 0/1 压电陶瓷谐振频率校正成功/失败
#define AIR_DETECTOR_RD0_SWITCH     (1 << 6) // 0/1 气泡累计功能关闭/打开
#define AIR_DETECTOR_RD0_BLOOD      (1 << 2) // 0/1 无血液/有血液
#define AIR_DETECTOR_RD0_MBALERM    (1 << 1) // 0/1 累计小气泡未报警/报警
#define AIR_DETECTOR_RD0_BBALERM    (1 << 0) // 0/1 大气泡未报警/报警

struct AIR_DETECTOR_RD0
{
    unsigned char st;                  //空气探测器校正、开关、报警等状态
    unsigned short bubbleSum ;          //每分钟内小气泡累计量
    unsigned char airVoltage;          //空气探测信号电压值，放大10倍 0～50
    unsigned char bloodVoltage;        //血液识别信号电压值，放大10倍 0～50
    unsigned char bigBubbleLimit;      //单个大气泡报警限 0～100
    unsigned short microBubbleLimit;    //小气泡累计量报警限 0～5000
    unsigned int   reserved; //预留
}__attribute__((packed));

/***************************************************************************
*   空气探测器模块RD0 — 6字节
****************************************************************************/
struct AIR_DETECTOR_RD7
{
    unsigned short code;        //部件标识码
    unsigned short hVer ;       //硬件版本
    unsigned short sVer;        //软件版本
}__attribute__((packed));

#ifdef Q_OS_WIN
    #pragma pack(0)     //恢复结构体对齐，以免影响到其他地方
#endif

#endif // AIRDETECTORMODULETYPES_H
