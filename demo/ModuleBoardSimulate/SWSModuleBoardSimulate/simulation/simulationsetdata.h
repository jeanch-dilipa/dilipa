#ifndef SIMULATIONSETDATA_H
#define SIMULATIONSETDATA_H

#include <QtGlobal>
#include "common/simulationdatacode.h"

enum ValueSimModeType
{
    FixSimMode,    //固定值
    RandomSimMode, //随机值
    AutoSimMode,   //自动或跟随主控
};

enum ValueType
{
    BinaryValue = 0,           //二值的
    BinaryValueWithAuto,       //二值的，同时可以自动模拟的
    NumericValue,              //数值的
    NumericValueWithAuto,      //数值的，同时可以自动模拟的
    NumericValueWithAutoRange, //数值的，可自动模拟的，跟随主控时有波动范围的
    EnumValue,                 //枚举的
    EnumValueWithAuto          //枚举的，同时可以自动模拟的
};

struct DataSimModeSt
{
    ValueSimModeType mode = FixSimMode; //模拟模式
    ValueType valueType = BinaryValue;  //数值类型
    float     fixValue = 0;             //固定值
    float     randomMinValue = 0;       //随机最小值
    float     randomMaxValue = 0;       //随机最大值
    float     autoSubValue = 0;         //自动下偏移
    float     autoAddValue = 0;         //自动上偏移
    quint8    decimals = 0;             //精度（小数后多少位）
    bool      changed = true;           //设置被改变（标记需要重新载入，默认为true保证至少加载1次）
};

struct SimDataSt
{
    SimDataCode code = C_Invalid;       //编号
    float value = 0;                    //生成的模拟值
    float fluctValue = 0;               //当模拟模式为跟随主控时，随机生成的偏移量
    DataSimModeSt set;                  //模拟方式设置
};

//血路系统数据模拟设置
struct BloodSystemSimDataSetSt
{
    bool      bloodBoardComSW = false;        //血路板通讯开关
    bool      bloodPumpBoardComSW = false;    //血泵板通讯开关
    bool      subPumpBoardComSW = false;      //补液泵板通讯开关

    ushort    bloodBoardSoftVer = 0;          //血路板软件版本
    ushort    bloodBoardHardVer = 0;          //血路板硬件版本
    ushort    vapBoardSoftVer = 0;            //动静脉压板软件版本
    ushort    vapBoardHardVer = 0;            //动静脉压板硬件版本
    ushort    bloodPumpBoardSoftVer = 0;      //血泵板软件版本
    ushort    bloodPumpBoardHardVer = 0;      //血泵板硬件版本
    ushort    subPumpBoardSoftVer = 0;        //补液泵板软件版本
    ushort    subPumpBoardHardVer = 0;        //补液泵板硬件版本

    SimDataSt bloodPumpSW;                    //血泵开关
    SimDataSt bloodPumpTargetSpeed;           //血泵目标转速 r/min
    SimDataSt bloodPumpRealSpeed;             //血泵实时转速 r/min
    SimDataSt bloodPumpRolls;                 //血泵累计转数 r
    SimDataSt bloodPumpDirec;                 //血泵方向 0-正转，1-反转
    SimDataSt bloodPumpBlock;                 //血泵堵转 0-未堵转，1-堵转
    SimDataSt bloodPumpCover;                 //血泵盖 0-关，1-开
    SimDataSt bloodPumpFpr;                   //血泵泵管系数 mL/r
    SimDataSt subPumpSwitch;                  //置换液泵开关
    SimDataSt subPumpTargetSpeed;             //置换液泵目标转速 r/min
    SimDataSt subPumpRealSpeed;               //置换液泵实时转速 r/min
    SimDataSt subPumpRolls;                   //置换液泵累计转数 r
    SimDataSt subPumpDirec;                   //置换液泵方向 0-正转，1-反转
    SimDataSt subPumpBlock;                   //置换液泵堵转 0-未堵转，1-堵转
    SimDataSt subPumpCover;                   //置换液泵盖 0-关，1-开
    SimDataSt subPumpFpr;                     //置换液泵泵管系数 mL/r
    SimDataSt vp;                             //静脉压
    SimDataSt ap;                             //动脉压
    SimDataSt airMonitor;                     //空气监测
    SimDataSt bloodId;                        //血液识别
    SimDataSt chokeClamp;                     //阻流夹
    SimDataSt vpAD;                           //静脉压实时AD值
    SimDataSt vpZeroAD;                       //静脉压零点AD值
    SimDataSt vpSlopeAD;                      //静脉压AD斜率值
    SimDataSt apAD;                           //动脉压实时AD值
    SimDataSt apZeroAD;                       //动脉压零点AD值
    SimDataSt apSlopeAD;                      //动脉压AD斜率值
    SimDataSt PAVCom;                         //动静脉压板通信
};

//水路系统数据模拟设置
struct LiquidSystemSimDataSetSt
{
    bool      liquidBoardComSW = false;       //水路板通讯开关
    bool      driveBoardComSW = false;        //驱动板通讯开关
    bool      balanceBoardComSW = false;      //平衡腔板通讯开关
    bool      heatBoardComSW = false;         //加热板通讯开关

    ushort    liquidBoardSoftVer = 0;         //水路板软件版本
    ushort    liquidBoardHardVer = 0;         //水路板硬件版本
    ushort    liquidPreBoardSoftVer = 0;      //水路压力板软件版本
    ushort    liquidPreBoardHardVer = 0;      //水路压力板硬件版本
    ushort    driveBoardSoftVer = 0;          //驱动板软件版本
    ushort    driveBoardHardVer = 0;          //驱动板硬件版本
    ushort    balanceBoardSoftVer = 0;        //平衡腔板软件版本
    ushort    balanceBoardHardVer = 0;        //平衡腔板硬件版本
    ushort    heatBoardSoftVer = 0;           //加热板软件版本
    ushort    heatBoardHardVer = 0;           //加热板硬件版本

    SimDataSt WG1;                            //WG1值，精确0.01
    SimDataSt WG5;                            //WG5值，精确0.01
    SimDataSt WG6;                            //WG6值，精确0.01
    SimDataSt YG1;                            //YG1
    SimDataSt YG2;                            //YG2
    SimDataSt YG3;                            //YG3
    SimDataSt YG4;                            //YG4
    SimDataSt diaFlow;                        //透析液流量
    SimDataSt DPSpeed;                        //DP转速
    SimDataSt YPSpeed;                        //YP转速
    SimDataSt QPSpeed;                        //QP转速
    SimDataSt DPTime;                         //DP推膜时间
    SimDataSt YPTime;                         //YP推膜时间
    SimDataSt YG2High;                        //进液高压
    SimDataSt YG2Low;                         //进液低压
    SimDataSt YG4High;                        //废液高压
    SimDataSt YG4Low;                         //废液低压

    SimDataSt balanceSW;                      //平衡腔开关
    SimDataSt heatSW;                         //加热开关
    SimDataSt heatForceOff;                   //加热强关
    SimDataSt heatDutyFactor;                 //加热占空比
    SimDataSt YK;                             //YK
    SimDataSt YJ1;                            //YJ1
    SimDataSt YJ2;                            //YJ2
    SimDataSt YJ3;                            //YJ3
    SimDataSt YJ4;                            //YJ4
    SimDataSt YJ5;                            //YJ5
    SimDataSt leftSubJoint;                   //左补液接头
    SimDataSt rightSubJoint;                  //右补液接头
    SimDataSt AStraw;                         //A液吸管
    SimDataSt BStraw;                         //B液吸管
    SimDataSt diaJointRed;                    //红色透析器接头
    SimDataSt diaJointBlue;                   //蓝色透析器接头
    SimDataSt V[9];                           //平衡腔电磁阀V，取值1~8，第0个不要
    SimDataSt SV[25];                         //电磁阀SV，取值1~24，第0个不要

    SimDataSt waterSupply;                    //供水不足
    SimDataSt inletWaterLevel;                //进水位长时间无变化
    SimDataSt air;                            //透析液空气过多
    SimDataSt diaphBlock;                     //平衡腔膜片受阻
    SimDataSt YG4LowPreTooHigh;               //废液压低压高
    SimDataSt YG2LowPreTooHigh;               //进液压低压高
    SimDataSt bloodLeak;                      //漏血
    SimDataSt fluidLeak1;                     //漏液传感器1
    SimDataSt fluidLeak2;                     //漏液传感器2
    SimDataSt yg1OutLimit;                    //进液压超限
    SimDataSt yg4OutLimit;                    //废液压超限
    SimDataSt QPSpeedError;                   //QP转速异常
    SimDataSt DPSpeedError;                   //DP转速异常
    SimDataSt YPSpeedError;                   //YP转速异常
    SimDataSt M1Leak;                         //膜片M1泄漏
    SimDataSt M2Leak;                         //膜片M2泄漏
    SimDataSt V1V7Leak;                       //V1/V7泄漏
    SimDataSt V2V8Leak;                       //V2/V8泄漏
    SimDataSt V3V5Leak;                       //V3/V5泄漏
    SimDataSt V4V6Leak;                       //V4/V6泄漏
    SimDataSt SV13Leak;                       //SV13泄漏
    SimDataSt SV14Leak;                       //SV14泄漏
    SimDataSt YG2DataError;                   //YG2数据异常（仅4000）
    SimDataSt YG4DataError;                   //YG4数据异常（仅4000）
    SimDataSt YG13Com;                        //YG1/3通信异常
    SimDataSt YG24Com;                        //YG2/4通信异常
    SimDataSt diaTempSensor;                  //透析液温度传感器异常（仅4000）
    SimDataSt heatTempSensor;                 //加热温度传感器异常（仅4000）
};

//配液超滤系统
struct MixUltraSystemSimDataSetSt
{
    bool      mixUfBoardComSW = false;        //配液超滤板通讯开关
    bool      mixBoardComSW = false;          //配液板通讯开关
    bool      ufBoardComSW = false;           //超滤板通讯开关
    bool      condBoardComSW = false;         //电导板通讯开关

    ushort    mixUfBoardSoftVer = 0;          //配液超滤板软件版本
    ushort    mixUfBoardHardVer = 0;          //配液超滤板硬件版本
    ushort    mixBoardSoftVer = 0;            //配液板软件版本
    ushort    mixBoardHardVer = 0;            //配液板硬件版本
    ushort    ufBoardSoftVer = 0;             //超滤板软件版本
    ushort    ufBoardHardVer = 0;             //超滤板硬件版本
    ushort    condBoardSoftVer = 0;           //电导板软件版本
    ushort    condBoardHardVer = 0;           //电导板硬件版本

    SimDataSt mixSW;                          //配液开关
    SimDataSt BCond;                          //B电导，精确0.001
    SimDataSt ACond;                          //A电导，精确0.001
    SimDataSt CCond;                          //C电导，精确0.001
    SimDataSt adjustRange;                    //配液调整范围
    SimDataSt WG2;                            //WG2值，精确0.01
    SimDataSt WG3;                            //WG3值，精确0.01
    SimDataSt WG4;                            //WG4值，精确0.01

    SimDataSt APumpSW;                        //A泵开关
    SimDataSt APumpDirec;                     //A泵方向（仅6000）
    SimDataSt APumpBlock;                     //A泵堵转
    SimDataSt APumpPhaseLoss;                 //A泵缺相（仅4000）
    SimDataSt APumpTargetSpeed;               //A泵目标转速 精确0.1
    SimDataSt APumpRealSpeed;                 //A泵实际转速 精确0.1
    SimDataSt APumpRolls;                     //A泵累计转数 精确0.01（仅6000）

    SimDataSt BPumpSW;                        //B泵开关
    SimDataSt BPumpDirec;                     //B泵方向（仅6000）
    SimDataSt BPumpBlock;                     //B泵堵转
    SimDataSt BPumpPhaseLoss;                 //B泵缺相（仅4000）
    SimDataSt BPumpTargetSpeed;               //B泵目标转速，精确0.1
    SimDataSt BPumpRealSpeed;                 //B泵实际转速，精确0.1
    SimDataSt BPumpRolls;                     //B泵累计转数，精确0.01（仅6000）

    SimDataSt ufPumpSW;                       //超滤泵开关
    SimDataSt ufPumpDirec;                    //超滤泵方向（仅6000）
    SimDataSt ufPumpBlock;                    //超滤泵堵转
    SimDataSt ufPumpPhaseLoss;                //超滤泵缺相（仅4000）
    SimDataSt ufPumpTargetSpeed;              //超滤泵目标转速，精确0.1
    SimDataSt ufPumpRealSpeed;                //超滤泵实际转速，精确0.1
    SimDataSt ufPumpRolls;                    //超滤泵累计转数，精确0.01（仅6000）
};

//抗凝系统
struct AntiSystemSimDataSetSt
{
    bool      hepBoardComSW = false;          //肝素板通讯开关

    ushort    hepBoardSoftVer = 0;            //肝素板软件版本
    ushort    hepBoardHardVer = 0;            //肝素板硬件版本

    SimDataSt hepPumpSW;                      //肝素泵开关
    SimDataSt hepPumpDirec;                   //肝素泵方向（仅6000）
    SimDataSt hepPumpBlock;                   //肝素泵堵转
    SimDataSt injectorSpeci;                  //注射器规格（仅6000）
    SimDataSt arriveBottom;                   //肝素到底
    SimDataSt arriveTop;                      //肝素到顶（仅4000）
    SimDataSt hepPlateMove;                   //肝素推板被移动（仅6000）
    SimDataSt hepLight;                       //光电开关被遮挡（仅6000）
    SimDataSt hepPumpError;                   //肝素泵故障（仅4000）
    SimDataSt hepTargetFlow;                  //目标流量（精确0.1mL/h 仅4000）
    SimDataSt hepRealFlow;                    //实际流量，精确0.1mL/h
    SimDataSt hepTotalFlow;                   //累计流量，精确0.001mL
};

//电源系统
struct PowerSystemSimDataSetSt
{
    bool      powerBoardComSW = false;        //电源板通讯开关

    ushort    powerBoardSoftVer = 0;          //电源板软件版本
    ushort    powerBoardHardVer = 0;          //电源板硬件版本

    SimDataSt powerError;                     //电源故障
    SimDataSt chargeStatus;                   //充电状态
    SimDataSt batteryStatus;                  //电池状态
    SimDataSt cityPower;                      //市电状态
    SimDataSt powerSupply;                    //供电状态
    SimDataSt cityVol;                        //市电电压
    SimDataSt battery;                        //电池电量
    SimDataSt vol12V;                         //12V电压（仅6000）
    SimDataSt vol24V;                         //24V电压（仅6000）
    SimDataSt batteryVol;                     //电池电压（仅6000）
};

//按键指示灯
struct KeyLampSimDataSetSt
{
    bool      monitorBoardComSW = false;        //监控板通讯开关

    ushort    monitorBoardSoftVer = 0;          //监控板软件版本
    ushort    monitorBoardHardVer = 0;          //监控板硬件版本

};

//BTV/RCM
struct BtvRcmDataSetSt
{
    bool      btvBoardComSW = false;            //血温血容量板通讯开关
    bool      rcmBoardComSW = false;            //实时清除率监测通讯开关

    ushort    btvBoardSoftVer = 0;              //血温血容量板软件版本
    ushort    btvBoardHardVer = 0;              //血温血容量板硬件版本
    ushort    rcmBoardSoftVer = 0;              //实时清除率监测板软件版本
    ushort    rcmBoardHardVer = 0;              //实时清除率监测板硬件版本

    SimDataSt VTStatus;                         //静脉血温传感器状态
    SimDataSt ATStatus;                         //动脉血温传感器状态
    SimDataSt VT;                               //静脉血温 精确0.01 °C
    SimDataSt AT;                               //动脉血温 精确0.01 °C
    SimDataSt BVStatus;                         //血容量传感器状态
    SimDataSt bloodDetect;                      //是否检测到血液
    SimDataSt BVCover;                          //血容量监测盖
    SimDataSt LEDSW;                            //近红外LED状态
    SimDataSt BV_V;                             //受光电压 mV
    SimDataSt BV;                               //血容量
    SimDataSt BV0;                              //初始血容量
    SimDataSt RBV;                              //相对血容量 精确0.01 %

    SimDataSt RCMCorrect;                       //实时清除率监测传感器校正
    SimDataSt RCMStatus;                        //实时清除率监测传感器状态
    SimDataSt RCMDetect;                        //实时清除率监测检测状态
    SimDataSt abs;                              //吸光度 精确0.01
};

//模块板模拟数据设置
struct ModuleSimDataSetSt
{
    BloodSystemSimDataSetSt    bloodSys;      //血路系统模拟数据
    LiquidSystemSimDataSetSt   liquidSys;     //水路系统模拟数据
    MixUltraSystemSimDataSetSt mixUltraSys;   //配液超滤系统
    AntiSystemSimDataSetSt     antiSys;       //抗凝系统
    PowerSystemSimDataSetSt    powerSys;      //电源系统
    KeyLampSimDataSetSt        keyLamp;       //按键指示灯
    BtvRcmDataSetSt            btvRcm;        //血温血容与实时清除率监测
};

#endif // SIMULATIONSETDATA_H
