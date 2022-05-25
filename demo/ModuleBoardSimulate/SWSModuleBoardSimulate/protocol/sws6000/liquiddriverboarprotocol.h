/*******************************************************************************
Copyright (c) 2014,重庆山外山科技有限公司技术中心
All rights reserved.
文件：    liquiddriverboardtypes.h
作者：    Wjl
版本：    V1.0
日期：    2014-02-10
摘要：    定义485协议中定义水路驱动板模块数据结构********************************************************************************/
#ifndef LIQUIDDRIVERBOARDPROTOCOL_H
#define LIQUIDDRIVERBOARDPROTOCOL_H
#include <QtGlobal>

#ifdef Q_OS_WIN
    #pragma pack(1) /*Windows下MinGW编译，__attribute__((packed))没有效果*/
#endif

/***************************************************************************
*   水路驱动模块WR0 (水路控制命令)—21 字节
****************************************************************************/
//Mode//////////////////////////////////////
#define LDB_WR0_BLA_STOP  0    //平衡系统停止
#define LDB_WR0_BLA_NOMCH 1    //平衡系统正常切换
#define LDB_WR0_BLA_CTLED 2    //平衡系统由主控控制
#define LDB_WR0_RUN_CLSCH 3    //治疗过程中密闭检测
#define LDB_WR0_LST_SLFCH 4    //水路系统自检
#define LDB_WR0_LST_EXH   5    //填充排气

//CMD/////////////////////////////////////////
#define LDB_WR0_BLOOD_LEAK_INITE   (1 << 0)       //0/1—漏血不初始化/初始化

//GP_CMD/////////////////////////////////////
#define LDB_WR0_DP_CTLED          (1 << 0)     //  0/1—DP 由模块/主控控制
#define LDB_WR0_YP_CTLED          (1 << 1)     //  0/1—YP 由模块/主控控制
#define LDB_WR0_QP_CTLED          (1 << 2)     //  0/1—QP 由模块/主控控制
#define LDB_WR0_DP_CTL_PN         (1 << 4)     //  0/1—DP  正/反转
#define LDB_WR0_YP_CTL_PN         (1 << 5)     //  0/1—YP  正/反转
#define LDB_WR0_QP_CTL_PN         (1 << 6)     //  0/1—QP  正/反转

//V_C1、V_C2、 SV_C1、SV_C2、SV_C3、SV_C4、SV_C5////////////////////////////////
/// V1、V5、SV1、SV5、SV9、SV13、SV17、SV21、SV25、SV29、SV33
#define LDB_WR0_ON_MSB      (3)         //00000011B 开启
#define LDB_WR0_OFF_MSB     (2)         //00000010B 关闭
#define LDB_WR0_SET_MSB     (1)         //00000001B 预留
#define LDB_WR0_SLF_MSB     (0)         //00000000B 模块控制

///V2、V6、SV2、SV6、SV10、SV14、SV18、SV22、SV26、SV30、SV34
#define LDB_WR0_ON_MSB_S    (3 << 2)    //00001100B 开启
#define LDB_WR0_OFF_MSB_S   (2 << 2)    //00001000B 关闭
#define LDB_WR0_SET_MSB_S   (1 << 2)    //00000100B 预留
#define LDB_WR0_SLF_MSB_S   (0 << 2)    //00000000B 模块控制

///V3、V7、SV3、SV7、SV11、SV15、SV19、SV23、SV27、SV31、SV35
#define LDB_WR0_ON_LSB_S    (3 << 4)    //00110000B 开启
#define LDB_WR0_OFF_LSB_S   (2 << 4)    //00100000B 关闭
#define LDB_WR0_SET_LSB_S   (1 << 4)    //00010000B 预留
#define LDB_WR0_SLF_LSB_S   (0 << 4)    //00000000B 模块控制

///V4、V8、SV4、SV8、SV12、SV16、SV20、SV24、SV28、SV32、SV36
#define LDB_WR0_ON_LSB      (3 << 6)    //11000000B 开启
#define LDB_WR0_OFF_LSB     (2 << 6)    //10000000B 关闭
#define LDB_WR0_SET_LSB     (1 << 6)    //01000000B 预留
#define LDB_WR0_SLF_LSB     (0 << 6)    //00000000B 模块控制
struct LDB_WR0
{
    unsigned char   mode;                //平衡系统模式 （上诉define 对应hp_cmd的各bit）
    unsigned short  flow;                //透析液设置流量(ml/min)
    unsigned short  volume;              //平衡腔容积,放大 10 倍,精确到 0.1ml
    unsigned char   cmd;                 //漏血初始化 0不初始化
    unsigned char   GP_cmd;              // QP，YP，DP泵控制字
    unsigned short  DP_targetSpeed;      //齿轮泵 DP 目标速度(rpm)  0 表示泵停止
    unsigned short  YP_targetSpeed;      //齿轮泵 YP 目标速度(rpm)  0 表示泵停止
    unsigned short  QP_targetSpeed;      //齿轮泵 QP 目标速度(rpm)  0 表示泵停止
    unsigned char   v_c1;                //V1--V4阀控制
    unsigned char   v_c2;                //V5--V8阀控制
    unsigned char   sv_c1;               //SV1--SV4阀控制
    unsigned char   sv_c2;               //SV5--SV8阀控制
    unsigned char   sv_c3;               //SV9--SV12阀控制
    unsigned char   sv_c4;               //SV13--SV16阀控制
    unsigned char   sv_c5;               //SV17--SV20阀控制
    unsigned char   sv_c6;               //SV21--SV24阀控制
    unsigned char   sv_c7;               //SV25--SV28阀控制
    unsigned char   sv_c8;               //SV29--SV32阀控制
    unsigned char   sv_c9;               //SV33--SV36阀控制
}__attribute__((packed));

/***************************************************************************
*   水路驱动模块WR1 (加热控制命令)—9 字节
****************************************************************************/
//H_CMD//////////////////////////////////
#define LDB_WR1_HEATER_ON   (1 << 0)        // 1/0—加热/停止加热
#define LDB_WR1_MODE        (1 << 1)        //0/1—正常进水模式/消毒循环模式
struct LDB_WR1
{
    unsigned char   cmd;            //加热控制
    unsigned short  temp;           //透析液设置温度，放大 100 倍，精确到 0.01
    unsigned short  temp_Low;       //透析液温度下限，放大 100 倍
    unsigned short  temp_High;      //透析液温度上限，放大 100 倍
    unsigned short  temp_Offset;    //透析液温度补偿值，放大 100 倍
}__attribute__((packed));

/***************************************************************************
*   水路驱动模块WR2 （温度校正命令）—6 字节
****************************************************************************/
#define LDB_WR2_S_WG1   (1)     //加热器入口温度 WG1
#define LDB_WR2_S_WG5   (2)     //加热器出口温度 WG5
#define LDB_WR2_S_WG6   (3)     //透析液温度 WG6

#define LDB_WR2_CMD          (0)   //温度校正
#define LDB_WR2_OFFSET      (1)  //温度补偿值


struct LDB_WR2
{
    unsigned char   num;        //传感器编号
    unsigned char   cmd;        //温度校正类型
    unsigned short  value;      //校正时的压力值或温度值，放大 100 倍，精确到 0.01℃
    short temp_offset;            //温度补偿值    放大 100 倍，精确到 0.01
}__attribute__((packed));

/***************************************************************************
*   下行命令 WR3（液压传感器校正命令）—4 字节
****************************************************************************/
#define LDB_WR3_SYG1    (1)        //液压传感器 YG1
#define LDB_WR3_SYG2    (2)        //液压传感器 YG2
#define LDB_WR3_SYG3    (3)        //液压传感器 YG3
#define LDB_WR3_SYG4    (4)        //液压传感器 YG4
struct LDB_WR3
{
    unsigned char   num;            //传感器编号
    unsigned char   point;          //校正点：0-零点；1-负压；2-正压
    short  value;                   //校正时的压力值，放大 10 倍，精确到 0.1kpa
}__attribute__((packed));


/***************************************************************************
*   水路驱动模块WR8 (复位重启命令)—0 字节
****************************************************************************/


/***************************************************************************
*   水路驱动模块WR9 (升级命令信息)—1026 字节
****************************************************************************/
struct LDB_WR9
{
    unsigned char data_sum;     //APP数据帧总量
    unsigned char data_num;    //当前数据帧编号
    unsigned char data_value[1024];    //数据值，APP程序代码
}__attribute__((packed));

/***************************************************************************
*   上行信息 RD0（报警标志及传感器信息）—25 字节
****************************************************************************/
//W_ST1//////////////////////////////////////////////////////////////
#define LDB_RD0_BS_RS   (1<<7)              //0/1—平衡系统停止/运行
#define LDB_RD0_HT_RS   (1<<6)              //0/1—加热停止/运行
#define LDB_RD0_FH      (1<<5)              //0/1—未强制关断加热/强制关断加热
#define LDB_RD0_WS      (1<<4)              //0/1—正常/供水不足
#define LDB_RD0_WL      (1<<3)             //0/1—正常/进水水位长时间无变化
#define LDB_RD0_DA      (1<<2)              //0/1—正常/透析液空气过多
#define LDB_RD0_LH_YG4  (1<<1)              //0/1—正常/废液压低压高
#define LDB_RD0_LH_YG2  (1<<0)              //0/1—正常/进液压低压高



//W_ST2
#define LDB_RD0_OTL_SV1  (1<<7)             //0/1—正常/SV1打开时间过长可能溢水
#define LDB_RD0_DM_YJ1YK (1<<6)             //0/1—正常/YJ1或YK检测元件坏
#define LDB_RD0_OL_YG2   (1<<5)             //0/1—正常/进液压力超限
#define LDB_RD0_OL_YG4   (1<<4)             //0/1—正常/废液压力超限
#define LDB_RD0_SA_DP    (1<<3)             //0/1—正常/齿轮泵 DP 转速异常
#define LDB_RD0_SA_YP    (1<<2)             //0/1—正常/齿轮泵 YP 转速异常
#define LDB_RD0_SA_QP    (1<<1)             //0/1—正常/齿轮泵 QP 转速异常
#define LDB_RD0_CE_HPB   (1<<0)             //0/1-正常/压力板通信错误

//W_ST3
#define LDB_RD0_LK_M1      (1 << 7)         //0/1—正常/平衡腔膜片M1泄漏
#define LDB_RD0_LK_M2      (1 << 6)         //0/1—正常/平衡腔膜片M2泄漏
#define LDB_RD0_LK_V1V7   (1 << 5)         //0/1—正常/电磁阀V1V7泄漏
#define LDB_RD0_LK_V2V8   (1 << 4)         //0/1—正常/电磁阀V2V8泄漏
#define LDB_RD0_LK_V3V5   (1 << 3)         //0/1—正常/电磁阀V3V5泄漏
#define LDB_RD0_LK_V4V6   (1 << 2)         //0/1—正常/电磁阀V4V6泄漏
#define LDB_RD0_LK_SV13   (1 << 1)         //0/1—正常/电磁阀SV13泄漏
#define LDB_RD0_LK_SV14   (1 << 0)         //0/1—正常/电磁阀SV14泄漏



//H_ST1/////////////////////////////////////////////////////////////
#define  LDB_RD0_YK_RD    (1 << 7)           //进水罐 YK:1-断开；0-闭合
#define  LDB_RD0_YJ1_RD   (1 << 6)           //进水罐 YJ1:1-断开；0-闭合
#define  LDB_RD0_YJ2_RD   (1 << 5)           //负压罐 YJ2:1-断开；0-闭合
#define  LDB_RD0_YJ3_RD   (1 << 4)           //负压罐 YJ3:1-断开；0-闭合
#define  LDB_RD0_YJ5_RD   (1 << 3)           //AB液除气 YJ5:1-断开；0-闭合
#define  LDB_RD0_A_RD     (1 << 2)           //浓缩液接头 A:1-断开；0-闭合
#define  LDB_RD0_B_RD     (1 << 1)           //浓缩液接头 B:1-断开；0-闭合
#define  LDB_RD0_DCA_RD   (1 << 0)           //透析器接头 DCA:1-断开；0-闭合

//H_ST2//////////////////////////////////////////////////////////////
#define  LDB_RD0_DCB_RD   (1 << 7)           //透析器接头 DCB:1-断开；0-闭合
#define  LDB_RD0_GF_RD      (1 << 6)           //干粉筒 GF:1-断开;0-闭合
#define  LDB_RD0_SBA_RD    (1 << 5)           //补液接头 SBA:1-断开；0-闭合
#define  LDB_RD0_SBB_RD    (1 << 4)           //补液接头 SBB:1-断开；0-闭合
#define  LDB_RD0_BL_RD       (1 << 3)           //漏血传感器 BL:1-漏血监测报警；0-未报警
#define  LDB_RD0_LL1_RD     (1 << 2)           //漏液传感器LL1:1-漏液报警；0-未报警
#define  LDB_RD0_LL2_RD     (1 << 1)           //漏液传感器 LL2:1-漏液报警；0-未报警

struct LDB_RD0
{
    unsigned char   w_st1;
    unsigned char   w_st2;

    unsigned char   w_st3;               //预留未使用
    unsigned short  ret_2;

    unsigned char   st1;               //水路霍尔元件状态1
    unsigned char   st2;               //水路霍尔元件状态2

    unsigned short  WG1_temperature;     //加热器入口温度，放大 100 倍，精确到0.01
    unsigned short  WG5_temperature;     //透析液设置温度，放大 100 倍，精确到0.01
    unsigned short  WG6_temperature;     //透析液设置温度，放大 100 倍，精确到0.01

    short  YG1_pressure;        //除气负压，放大 10 倍，精确到 0.1kpa
    short  YG2_pressure;        //进液压，放大 10 倍，精确到 0.1kpa
    short  YG3_pressure;        //透析液压，放大 10 倍，精确到 0.1kpa
    short  YG4_pressure;        //废液压，放大 10 倍，精确到 0.1kpa

    unsigned short  heatcycle;           //加热占空比，放大10倍
}__attribute__((packed));

/***************************************************************************
*  上行信息 RD1（水路运行状态参数）—28 字节
****************************************************************************/
//Mode//////////////////////////////////////
#define LDB_RD1_BLA_STOP  (0)    //平衡系统停止
#define LDB_RD1_BLA_NOMCH (1)    //平衡系统正常切换
#define LDB_RD1_BLA_CTLED (2)    //平衡系统由主控控制
#define LDB_RD1_RUN_CLSCH (3)    //治疗过程中密闭检测
#define LDB_RD1_LST_SLFCH (4)    //水路系统自检
#define LDB_RD1_LST_EXH   (5)    //填充排气

//GP_ST/////////////////////////////////////
#define LDB_RD1_DP_CTLED          (1 << 0)     //  0/1—DP 由模块/主控控制
#define LDB_RD1_YP_CTLED          (1 << 1)     //  0/1—YP 由模块/主控控制
#define LDB_RD1_QP_CTLED          (1 << 2)     //  0/1—QP 由模块/主控控制
#define LDB_RD1_DP_CTL_PN         (1 << 4)     //  0/1—DP  正/反转
#define LDB_RD1_YP_CTL_PN         (1 << 5)     //  0/1—YP  正/反转
#define LDB_RD1_QP_CTL_PN         (1 << 6)     //  0/1—QP  正/反转

//V_S///////////////////////////////////////
#define LDB_RD1_VS_V1                 (1 << 0)  //V1状态：1-开启；0-关闭
#define LDB_RD1_VS_V2                 (1 << 1)  //V2状态：1-开启；0-关闭
#define LDB_RD1_VS_V3                 (1 << 2)  //V3状态：1-开启；0-关闭
#define LDB_RD1_VS_V4                 (1 << 3)  //V4状态：1-开启；0-关闭
#define LDB_RD1_VS_V5                 (1 << 4)  //V5状态：1-开启；0-关闭
#define LDB_RD1_VS_V6                 (1 << 5)  //V6状态：1-开启；0-关闭
#define LDB_RD1_VS_V7                 (1 << 6)  //V7状态：1-开启；0-关闭
#define LDB_RD1_VS_V8                 (1 << 7)  //V8状态：1-开启；0-关闭

//SV_S1///////////////////////////////////////
#define LDB_RD1_SVS1_SV1                 (1 << 0)  //SV1状态：1-开启；0-关闭
#define LDB_RD1_SVS1_SV2                 (1 << 1)  //SV2状态：1-开启；0-关闭
#define LDB_RD1_SVS1_SV3                 (1 << 2)  //SV3状态：1-开启；0-关闭
#define LDB_RD1_SVS1_SV4                 (1 << 3)  //SV4状态：1-开启；0-关闭
#define LDB_RD1_SVS1_SV5                 (1 << 4)  //SV5状态：1-开启；0-关闭
#define LDB_RD1_SVS1_SV6                 (1 << 5)  //SV6状态：1-开启；0-关闭
#define LDB_RD1_SVS1_SV7                 (1 << 6)  //SV7状态：1-开启；0-关闭
#define LDB_RD1_SVS1_SV8                 (1 << 7)  //SV8状态：1-开启；0-关闭

//SV_S2///////////////////////////////////////
#define LDB_RD1_SVS2_SV9                  (1 << 0)  //SV9状态：1-开启；0-关闭
#define LDB_RD1_SVS2_SV10                 (1 << 1)  //SV10状态：1-开启；0-关闭
#define LDB_RD1_SVS2_SV11                 (1 << 2)  //SV11状态：1-开启；0-关闭
#define LDB_RD1_SVS2_SV12                 (1 << 3)  //SV12状态：1-开启；0-关闭
#define LDB_RD1_SVS2_SV13                 (1 << 4)  //SV13状态：1-开启；0-关闭
#define LDB_RD1_SVS2_SV14                 (1 << 5)  //SV14状态：1-开启；0-关闭
#define LDB_RD1_SVS2_SV15                 (1 << 6)  //SV15状态：1-开启；0-关闭
#define LDB_RD1_SVS2_SV16                 (1 << 7)  //SV16状态：1-开启；0-关闭

//SV_S3///////////////////////////////////////
#define LDB_RD1_SVS3_SV17                 (1 << 0)  //SV17状态：1-开启；0-关闭
#define LDB_RD1_SVS3_SV18                 (1 << 1)  //SV18状态：1-开启；0-关闭
#define LDB_RD1_SVS3_SV19                 (1 << 2)  //SV19状态：1-开启；0-关闭
#define LDB_RD1_SVS3_SV20                 (1 << 3)  //SV20状态：1-开启；0-关闭
#define LDB_RD1_SVS3_SV21                 (1 << 4)  //SV21状态：1-开启；0-关闭
#define LDB_RD1_SVS3_SV22                 (1 << 5)  //SV22状态：1-开启；0-关闭
#define LDB_RD1_SVS3_SV23                 (1 << 6)  //SV23状态：1-开启；0-关闭
#define LDB_RD1_SVS3_SV24                 (1 << 7)  //SV24状态：1-开启；0-关闭

//SV_S4///////////////////////////////////////
#define LDB_RD1_SVS4_SV25                 (1 << 0)  //SV25状态：1-开启；0-关闭
#define LDB_RD1_SVS4_SV26                 (1 << 1)  //SV26状态：1-开启；0-关闭
#define LDB_RD1_SVS4_SV27                 (1 << 2)  //SV27状态：1-开启；0-关闭
#define LDB_RD1_SVS4_SV28                 (1 << 3)  //SV28状态：1-开启；0-关闭
#define LDB_RD1_SVS4_SV29                 (1 << 4)  //SV29状态：1-开启；0-关闭
#define LDB_RD1_SVS4_SV30                 (1 << 5)  //SV30状态：1-开启；0-关闭
#define LDB_RD1_SVS4_SV31                 (1 << 6)  //SV31状态：1-开启；0-关闭
#define LDB_RD1_SVS4_SV32                 (1 << 7)  //SV32状态：1-开启；0-关闭

//SV_S5//////////////////////////////////////
#define LDB_RD1_SVS5_SV33                 (1 << 0)  //SV33状态：1-开启；0-关闭
#define LDB_RD1_SVS5_SV34                 (1 << 1)  //SV34状态：1-开启；0-关闭
#define LDB_RD1_SVS5_SV35                 (1 << 2)  //SV35状态：1-开启；0-关闭
#define LDB_RD1_SVS5_SV36                 (1 << 3)  //SV36状态：1-开启；0-关闭

struct LDB_RD1
{
    unsigned char  mode;
    unsigned short flow;        //透析液设置流量(ml/min)
    unsigned char  gp_st;

    unsigned short  DP_LiveSpeed;       //齿轮泵 DP 实时速度(rpm)
    unsigned short  YP_LiveSpeed;       //齿轮泵 YP 实时速度(rpm)
    unsigned short  QP_LiveSpeed;       //齿轮泵 QP 实时速度(rpm)

    short  YG2_MP;  //进液压传感器在一个平衡腔切换周期内的最大压力，放大 10 倍，精确到 0.1kpa
    short  YG2_AP;  //进液压传感器在一个平衡腔切换周期内的平均压力，放大 10 倍，精确到 0.1kpa
    short  YG4_MP;  //废液压传感器在一个平衡腔切换周期内的最大压力，放大 10 倍，精确到 0.1kpa
    short  YG4_AP;  //废液压传感器在一个平衡腔切换周期内的平均压力，放大 10 倍，精确到 0.1kpa
    unsigned short  DP_time;    //齿轮泵 DP 推膜片时间，放大 10 倍，精确到 0.1S
    unsigned short  YP_time;    //齿轮泵 YP 推膜片时间，放大 10 倍，精确到 0.1S

    unsigned char   V_S;                //V1---V8电磁阀状态字
    unsigned char   SV_S1;              //SV1---SV8电磁阀状态字
    unsigned char   SV_S2;              //SV9---SV16电磁阀状态字
    unsigned char   SV_S3;              //SV17---SV24电磁阀状态字
    unsigned char   SV_S4;              //SV25---SV32电磁阀状态字
    unsigned char   SV_S5;              //SV33---SV40电磁阀状态字
}__attribute__((packed));

/***************************************************************************
*  上行信息 RD2（温度传感器 WG1/WG5/WG6 信息）—19 字节
****************************************************************************/
#define LDB_RD2_CO_WG1  (1<<7)              //0/1—传感器WG1校正值正常/异常
#define LDB_RD2_CO_WG5  (1<<6)              //0/1—传感器WG5校正值正常/异常
#define LDB_RD2_CO_WG6  (1<<5)              //0/1—传感器WG6校正值正常/异常
struct LDB_RD2
{
    unsigned char   st;
    unsigned int    WG1_AD;     //传感器 WG1 实时 AD 值
    short  WG1_Offset;      //传感器 WG1 温度补偿值(放大100 倍,精确到 0.01)

    unsigned int    WG5_AD;     //传感器 WG5 实时 AD 值
    short  WG5_Offset;      //传感器 WG5 温度补偿值(放大100 倍,精确到 0.01)

    unsigned int    WG6_AD;     //传感器 WG6 实时 AD 值
    short  WG6_Offset;      //传感器 WG6 温度补偿值(放大100 倍,精确到 0.01)
}__attribute__((packed));

/***************************************************************************
*  上行信息 RD3（液压传感器 YG1/YG3 信息）—21 字节
****************************************************************************/
#define LDB_RD3_CO_YG1  (1<<7)              //0/1—传感器YG1校正值正常/异常
#define LDB_RD3_CO_YG3  (1<<6)              //0/1—传感器YG3校正值正常/异常
struct LDB_RD3
{
    unsigned char   st;
    int    S1_AD;              //传感器 YG1 实时 AD 值
    int    S1_AD0;             //传感器 YG1 零点 AD 值
    unsigned short  S1_K;               //传感器 YG1 斜率值

    int    S2_AD;              //传感器 YG3 实时 AD 值
    int    S2_AD0;             //传感器 YG3 零点 AD 值
    unsigned short  S2_K;               //传感器 YG3 斜率值
}__attribute__((packed));

/***************************************************************************
*  上行信息 RD4（液压传感器 YG2/YG4 信息）—21 字节
****************************************************************************/
#define LDB_RD4_CO_YG2  (1<<7)              //0/1—传感器YG2校正值正常/异常
#define LDB_RD4_CO_YG4  (1<<6)              //0/1—传感器YG4校正值正常/异常
struct LDB_RD4
{
    unsigned char   st;
    int    S1_AD;              //传感器 YG2 实时 AD 值
    int    S1_AD0;             //传感器 YG2 零点 AD 值
    unsigned short  S1_K;               //传感器 YG2 斜率值

    int    S2_AD;              //传感器 YG4 实时 AD 值
    int    S2_AD0;             //传感器 YG4 零点 AD 值
    unsigned short  S2_K;               //传感器 YG4 斜率值
}__attribute__((packed));

/***************************************************************************
*  上行信息 RD7（软硬件版本信息）—18 字节
****************************************************************************/
struct LDB_RD7
{
    unsigned short   YG13_id;              //液压传感器 YG1/3 模块部件标识码
    unsigned short   YG13_hv;              //液压传感器 YG1/3 模块硬件版本
    unsigned short   YG13_sv ;             //液压传感器 YG1/3 模块软件版本

    unsigned short   YG24_id;              //液压传感器 YG2/4 模块部件标识码
    unsigned short   YG24_hv;              //液压传感器 YG2/4 模块硬件版本
    unsigned short   YG24_sv;              //液压传感器 YG2/4 模块软件版本

    unsigned short   id;                   //水路板部件标识码
    unsigned short   hv;                   //水路板硬件版本
    unsigned short   sv;                   //水路板软件版本
}__attribute__((packed));


/***************************************************************************
*   水路驱动模块RD8（软硬件版本信息）-2字节
****************************************************************************/
struct LDB_RD8
{
    unsigned char next_num;    //发送对应数据帧
    unsigned char write_sum;    //已写入数据量
    unsigned char iap_sv;         //升级程序 软件版本
}__attribute__((packed));

#ifdef Q_OS_WIN
    #pragma pack(0) /*恢复结构体对齐，以免影响到其他地方*/
#endif

#endif // LIQUIDDRIVERBOARDPROTOCOL_H
