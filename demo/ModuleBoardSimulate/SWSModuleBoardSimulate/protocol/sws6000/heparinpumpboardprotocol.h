/*******************************************************************************
Copyright (c) 2014,重庆山外山科技有限公司技术中心
All rights reserved.
文件：    HeparinPumpBoardTypes.h
作者：    Wjl
版本：    V1.0
日期：    2014-02-10
摘要：    定义485协议中定义肝素泵模块数据结构********************************************************************************/
#ifndef HEPARINPUMPBOARDPROTOCOL_H
#define HEPARINPUMPBOARDPROTOCOL_H
#include <QtGlobal>

#ifdef Q_OS_WIN
    #pragma pack(1) /*Windows下MinGW编译，__attribute__((packed))没有效果*/
#endif

/***************************************************************************
*   肝素泵WR0定义，控制肝素泵  4 byte
****************************************************************************/
#define HPB_WR0_RUN      (0)    //运行          00000000b
#define HPB_WR0_ADJ      (1)    //注射器校正    00000001b
#define HPB_WR0_SLC      (2)    //自检          00000010b
#define HPB_WR0_RET      (3)    //预留          00000011b

#define HPB_WR0_BCK      (1 << 2)    //注射器前进/后退  0——前进、1——后退
#define HPB_WR0_ON_OFF   (1 << 3)    //肝素泵OFF/ON  0——OFF、1——ON
#define HPB_WR0_CLN      (1 << 4)    //注射器流量累计/清零  0——累计、1——清零
struct HPB_WR0
{
    unsigned char cmd;    //控制命令 （上诉define 对应hp_cmd的各bit）
    unsigned char syringe_type;  //注射器型号
    unsigned short flow;         //推注速率，毫升/h（分辨率0.1,放大十倍）
}__attribute__((packed));

/***************************************************************************
*   肝素泵WR1定义，控制肝素追加  4 byte
****************************************************************************/
struct HPB_WR1
{
    unsigned short rate;    //追加速率，毫升/h（分辨率0.1,放大十倍）
    unsigned short volume;  //追加量，毫升（分辨率0.1,放大十倍）
}__attribute__((packed));


/***************************************************************************
*   肝素泵驱动模块WR8 (复位重启命令)—0 字节
****************************************************************************/


/***************************************************************************
*   肝素泵驱动模块WR9 (升级命令信息)—1026 字节
****************************************************************************/
struct HPB_WR9
{
    unsigned char data_sum;     //APP数据帧总量
    unsigned char data_num;    //当前数据帧编号
    unsigned char data_value[1024];    //数据值，APP程序代码
}__attribute__((packed));


/***************************************************************************
*   肝素泵RD0定义，肝素泵运行参数 8 byte
****************************************************************************/
//hp_st1//////////////////////////////
#define HPB_RD0_RUN_RD      (0)    //正常          00000000b
#define HPB_RD0_SLC_RD      (1)    //正在自检      00000001b
#define HPB_RD0_SLCD_RD     (2)    //完成自检      00000010b
#define HPB_RD0_UUL_RD      (3)    //异常          00000011b

#define HPB_RD0_BCK_RD     (1 << 2)   //注射器前进/后退  0——前进、1——后退
#define HPB_RD0_OFF_RD     (1 << 3)    //注射器开机/关机  0——关机、1——开机
#define HPB_RD0_SLT_RD     (1 << 4)   //  0/1—底端光电开关未遮挡/遮挡
#define HPB_RD0_FRE_RD     (1 << 5)   //  0/1—未堵转/堵转
#define HPB_RD0_ARB_RD     (1 << 6)   //  0/1—未到底/到底
#define HPB_RD0_PPM_RD     (1 << 7)   //0/1—正常状态/肝素泵推杆被移动

//Syringe_type///////////////////////////////////////////////
#define HPB_RD0_TYPE_0ML       (0)    //  0ml注射器
#define HPB_RD0_TYPE_10ML      (10)   // 10ml注射器
#define HPB_RD0_TYPE_20ML      (20)   // 20ml注射器
#define HPB_RD0_TYPE_30ML      (30)   // 30ml注射器
#define HPB_RD0_TYPE_40ML      (50)   // 50ml注射器
struct HPB_RD0
{
    unsigned char hp_st1;           //肝素泵状态 （上诉define 对应hp_st1的各bit）
    unsigned char Syringe_type;     //S注射器型号 0ml,10ml,20ml,30ml,50ml
    unsigned int  HP_SF;            //累计流量，（分辨率0.001ml,放大1000倍）
    unsigned short HP_LF;           //实时流量，（分辨率0.1ml,放大十倍）
}__attribute__((packed));


/***************************************************************************
*   肝素泵RD1定义，肝素泵校正信息 10 byte
****************************************************************************/
#define HPB_RD1_CO_NO    (0)    //10ml 注射器未校正
#define HPB_RD1_CO_CO    (1)    //10ml 注射器正在校正
#define HPB_RD1_CO_OK    (2)    //10ml 注射器校正完成
#define HPB_RD1_CO_ERR   (3)    //10ml 注射器校正异常
struct HPB_RD1
{
    unsigned char st;
    unsigned char type; //当前校正注射器规格(ml):0-注射器 未 安 装 ; 10-10ml ; 20-20ml ;30-30ml;50-50ml
    unsigned short R_10ML;  //推注 10ml 注射器步进电机转数,放大 100 倍,精确到 0.01 转
    unsigned short R_20ML;  //推注 20ml 注射器步进电机转数,放大 100 倍,精确到 0.01 转
    unsigned short R_30ML;  //推注 30ml 注射器步进电机转数,放大 100 倍,精确到 0.01 转
    unsigned short R_50ML;  //推注 40ml 注射器步进电机转数,放大 100 倍,精确到 0.01 转
}__attribute__((packed));


/***************************************************************************
*   肝素泵RD7定义，软硬件版本信息
****************************************************************************/
struct HPB_RD7
{
    unsigned short  id;     //部件标识码
    unsigned short  hv;     //硬件版本
    unsigned short  sv;     //软件版本
}__attribute__((packed));


/***************************************************************************
*   陶瓷泵驱动模块RD8（软硬件版本信息）-6字节
****************************************************************************/
struct HPB_RD8
{
    unsigned char next_num;    //发送对应数据帧
    unsigned char write_sum;    //已写入数据量
    unsigned char iap_sv;         //升级程序 软件版本
}__attribute__((packed));

#ifdef Q_OS_WIN
    #pragma pack(0)     /*恢复结构体对齐，以免影响到其他地方*/
#endif

#endif // HEPARINPUMPBOARDPROTOCOL_H
