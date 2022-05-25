/*******************************************************************************
Copyright (c) 2014,重庆山外山科技有限公司技术中心
All rights reserved.
文件：    ceramicpumpboardtypes.h
作者：    ccy
版本：    V1.0
日期：    2014-02-11
摘要：    定义485协议中定义陶瓷泵驱动模块数据结构********************************************************************************/
#ifndef MIXULTRABOARDPROTOCOL_H
#define MIXULTRABOARDPROTOCOL_H
#include <QtGlobal>

#ifdef Q_OS_WIN
    #pragma pack(1) /*Windows下MinGW编译，__attribute__((packed))没有效果*/
#endif

/***************************************************************************
*   陶瓷泵驱动模块WR0（配液控制命令）-13字节
****************************************************************************/
/// mode
#define CPB_WR0_STOP    (0)    //配液系统停止工作
#define CPB_WR0_LQR     (1)    //配液模式
#define CPB_WR0_FSR     (2)    //系数测试模式
#define CPB_WR0_CAD     (3)    //清洗消毒模式,Cleaning and disinfection


/// P_CMD
#define CPB_WR0_A       (1 << 0)    //0/1-A泵正转/反转
#define CPB_WR0_B       (1 << 1)    //0/1-B泵正转/反转
#define CPB_WR0_AF      (1 << 2)    //A 泵转数累计不清零/清零
#define CPB_WR0_BF      (1 << 3)    //B 泵转数累计不清零/清零
struct CPB_WR0
{
    unsigned char mode;     //配液模式选择
    unsigned char p_cmd;    //A、B、NA泵控制命令
    unsigned short flow;    //透析液设置流量（ml/min)

    unsigned short cond_B;  //B电导目标值，放大1000倍，精确到0.001
    unsigned short cond_A;  //A电导目标值，放大1000倍，精确到0.001

    unsigned short rpm_A;   //A 泵目标转速，放大十倍
    unsigned short rpm_B;   //B 泵目标转速，放大十倍

    unsigned char limits;   //配液调整范围,20 表示 A、B 泵可以在参考转速±20%范围内调节
}__attribute__((packed));


/***************************************************************************
*  陶瓷泵驱动模块WR1（超滤泵控制命令）-6字节
****************************************************************************/
#define CPB_WR1_RUN     (0)    //正常运转模式
#define CPB_WR1_CPTM    (2)    //泵管系数测试模式
#define CPB_WR1_SC      (3)    //自检模式

#define CPB_WR1_CWR     (1 << 2)    //0/1-顺时针/反时针旋转
#define CPB_WR1_OFF_ON  (1 << 3)    //0/1-关机/开机
#define CPB_WR1_FLOW    (1 << 4)    //0/1—转数累计/转数清0
struct CPB_WR1
{
    unsigned char cmd;

    unsigned char ret1;     //预留

    unsigned short rpm;     //目标转速，放大十倍

    unsigned short ret2;    //预留
}__attribute__((packed));



/***************************************************************************
*   陶瓷泵驱动模块WR2（电导校正控制命令）-10字节
****************************************************************************/
#define CPB_WR2_COND_B  (1)     //电导传感器 B
#define CPB_WR2_COND_A  (2)     //电导传感器 A
#define CPB_WR2_COND_C  (3)     //电导传感器 C
#define CPB_WR2_COND_D  (4)     //电导传感器 D

#define CPB_WR2_CORRECT_COND   (0)  //校正电导
#define CPB_WR2_CORRECT_TEMP    (1)   //校正温度
#define CPB_WR2_CORRECT_PARAMETER  (2)   //校正电导特性参数
#define CPB_WR2_CORRECT_TEMP_OFFSET   (3)  //校正电导温度补偿值


struct CPB_WR2
{
    unsigned char   num;
    unsigned char   cmd;      //预留
    unsigned short  cond;     //校正时的电导值，放大1000倍，精确到0.001
    unsigned short  temp;     //校正时的温度值，放大100倍，精确到0.01
    unsigned short  parameter;  //传感器特性参数
    short temp_offset;       //校正温度补偿值  可以正负 放大100倍 ，精确到0.01
}__attribute__((packed));



/***************************************************************************
*  陶瓷泵驱动模块WR8（复位重启命令）-0字节
****************************************************************************/

/***************************************************************************
*  陶瓷泵驱动模块WR9（升级命令信息）-1026字节
****************************************************************************/
struct CPB_WR9
{
    unsigned char data_sum;     //APP数据帧总量
    unsigned char data_num;    //当前数据帧编号
    unsigned char data_value[1024];    //数据值，APP程序代码
}__attribute__((packed));


/***************************************************************************
*   陶瓷泵驱动模块RD0（配液运行参数）-21字节
****************************************************************************/
struct CPB_RD0
{
    unsigned char mode;             //0-停止工作，1-配液模式，2-系数测试模式(转100转后自动停止)，3-固定转速模式

    unsigned char st1;              //0-停止，1-试配，2-调整，3-微调，4-完成
    unsigned char st2;
   // unsigned short ret1;
    unsigned char ret;              //预留

    unsigned short cond_B;          //B电导实时值，放大1000倍，精确到0.001
    unsigned short temp_B;          //B电导实时温度值，放大100倍，精确到0.01

    unsigned short cond_A;          //A电导实时值，放大1000倍，精确到0.001
    unsigned short temp_A;          //A电导实时温度值，放大100倍，精确到0.01

    unsigned short cond_C;          //C电导实时值，放大1000倍，精确到0.001
    unsigned short temp_C;          //C电导实时温度值，放大100倍，精确到0.01

    unsigned short cond_D;          //D电导实时值，放大1000倍，精确到0.001
    unsigned short temp_D;          //D电导实时温度值，放大100倍，精确到0.01

    unsigned char limits;         //配液调整范围
}__attribute__((packed));


/***************************************************************************
*   陶瓷泵驱动模块RD1（A B泵运行参数）-20字节
****************************************************************************/
//AP_ST1/////////////////////////////////////////////////
#define CPB_RD1_AP_MOTOR         (1 << 0)    //0/1-正常/转速异常
#define CPB_RD1_AP_DRIVE         (1 << 1)    //0/1-正常/驱动过流或过热
#define CPB_RD1_AP_CWR           (1 << 2)    //0/1-正转/反转
#define CPB_RD1_AP_OFF_ON        (1 << 3)    //0/1-关机/开机

//BP_ST1//////////////////////////////////////////////////
#define CPB_RD1_BP_MOTOR         (1 << 0)    //0/1-正常/转速异常
#define CPB_RD1_BP_DRIVE         (1 << 1)    //0/1-正常/驱动过流或过热
#define CPB_RD1_BP_CWR           (1 << 2)    //0/1-正转/反转
#define CPB_RD1_BP_OFF_ON        (1 << 3)    //0/1-关机/开机

struct CPB_RD1
{
    unsigned char  a_st1;       //A状态字1
    unsigned char  a_st2;       //预留
    unsigned short a_rpm_tt;    //A 泵目标转速，放大10倍
    unsigned short a_rpm_rt;    //A 泵实时转速，放大10倍
    unsigned int a_tr;          //A 泵累计圈数，放大100倍

    unsigned char  b_st1;       //B状态字1
    unsigned char  b_st2;       //预留
    unsigned short b_rpm_tt;    //B 泵目标转速，放大10倍
    unsigned short b_rpm_rt;    //B 泵实时转速，放大10倍
    unsigned int b_tr;          //B 泵累计圈数，放大100倍
}__attribute__((packed));


/***************************************************************************
*   陶瓷泵驱动模块RD2（超滤泵运行参数）-10字节
****************************************************************************/
#define CPB_RD2_UF_MOTOR       (1 << 0)    //0/1-正常/转速异常
#define CPB_RD2_UF_DRIVE       (1 << 1)    //0/1-正常/驱动过流或过热
#define CPB_RD2_UF_CWR         (1 << 2)    //0/1-顺时针/反时针
#define CPB_RD2_UF_OFF_ON      (1 << 3)    //0/1-关机/开机

struct CPB_RD2
{
    unsigned char  st1;
    unsigned char  st2;         //预留
    unsigned short rpm_tt;      //超滤泵目标转速，放大10倍
    unsigned short rpm_rt;      //超滤泵实时转速，放大10倍
    unsigned int tr;            //超滤泵累计圈数，放大100倍
}__attribute__((packed));

/***************************************************************************
*   陶瓷泵驱动模块RD3（B电导信息）-13字节
****************************************************************************/
#define CPB_RD3_CO_COND_B        (1<<7)  //0/1-B电导校正数据正常/异常
#define CPB_RD3_TEMP_CO_COND_B   (1<<6)  //0/1-B电导温度校正数据正常/异常
struct CPB_RD3
{
    unsigned char st;
    unsigned int cond_ad;       //B 电导实时AD
    unsigned int  wg2_ad;      //WG2温度实时AD
    unsigned short condB_parameter;    //B 电导参数
     short wg2_offset;     // WG2温度补偿值  放大 100 倍 精确到0.01
}__attribute__((packed));

/***************************************************************************
*   陶瓷泵驱动模块RD4（B电导信息）-13字节
****************************************************************************/
#define CPB_RD4_CO_COND_A        (1<<7)  //0/1-A电导校正数据正常/异常
#define CPB_RD4_TEMP_CO_COND_A   (1<<6)  //0/1-A电导温度校正数据正常/异常
struct CPB_RD4
{
    unsigned char st;
    unsigned int cond_ad;       //A 电导实时AD
    unsigned int  wg3_ad;      //WG3温度实时AD
    unsigned short condA_parameter;    //A电导参数
     short wg3_offset;     // WG3温度补偿值  放大 100 倍 精确到0.01
}__attribute__((packed));



/***************************************************************************
*   陶瓷泵驱动模块RD5（C电导信息）-13字节
****************************************************************************/
#define CPB_RD5_CO_COND_C        (1<<7)  //0/1-C电导校正数据正常/异常
#define CPB_RD5_TEMP_CO_COND_C   (1<<6)  //0/1-C电导温度校正数据正常/异常
struct CPB_RD5
{
    unsigned char st;
    unsigned int cond_ad;       //C 电导实时AD
    unsigned int  wg4_ad;      //WG4温度实时AD
    unsigned short condC_parameter;    //C电导参数
     short wg4_offset;     // WG4温度补偿值  放大 100 倍 精确到0.01
}__attribute__((packed));


/***************************************************************************
*   陶瓷泵驱动模块RD6（D电导信息）-13字节
****************************************************************************/
#define CPB_RD6_CO_COND_D        (1<<7)  //0/1-D电导校正数据正常/异常
#define CPB_RD6_TEMP_CO_COND_D   (1<<6)  //0/1-D电导温度校正数据正常/异常
struct CPB_RD6
{
    unsigned char st;
    unsigned int cond_ad;       //D 电导实时AD
    unsigned int  wg7_ad;      //WG7温度实时AD
    unsigned short condD_parameter;    //D电导参数
     short wg7_offset;     // WG7温度补偿值  放大 100 倍 精确到0.01
}__attribute__((packed));


/***************************************************************************
*   陶瓷泵驱动模块RD7（软硬件版本信息）-6字节
****************************************************************************/
struct CPB_RD7
{
    unsigned short  id;     //部件标识码
    unsigned short  hv;     //硬件版本
    unsigned short  sv;     //软件版本
}__attribute__((packed));


/***************************************************************************
*   陶瓷泵驱动模块RD8（软硬件版本信息）-6字节
****************************************************************************/
struct CPB_RD8
{
    unsigned char next_num;    //发送对应数据帧
    unsigned char write_sum;    //已写入数据量
    unsigned char iap_sv;         //升级程序 软件版本
}__attribute__((packed));

#ifdef Q_OS_WIN
    #pragma pack(0) /*恢复结构体对齐，以免影响到其他地方*/
#endif

#endif // MIXULTRABOARDPROTOCOL_H
