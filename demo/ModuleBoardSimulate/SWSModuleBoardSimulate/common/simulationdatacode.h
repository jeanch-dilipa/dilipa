#ifndef SIMULATIONDATACODE_H
#define SIMULATIONDATACODE_H

enum SimDataCode
{
    C_Invalid = 0,                  //无效

    //-----------------血路系统--------------------<
    C_BloodPumpSW = 1,              //血泵开关
    C_BloodPumpTargetSpeed = 2,     //血泵目标转速
    C_BloodPumpRealSpeed = 3,       //血泵实时转速
    C_BloodPumpRolls = 4,           //血泵累计转数
    C_BloodPumpDirec = 5,           //血泵方向
    C_BloodPumpBlock = 6,           //血泵堵转
    C_BloodPumpCover = 7,           //血泵盖
    C_BloodPumpFpr = 8,             //血泵泵管系数
    C_SubPumpSwitch = 9,            //置换液泵开关
    C_SubPumpTargetSpeed = 10,      //置换液泵目标转速
    C_SubPumpRealSpeed = 11,        //置换液泵实时转速
    C_SubPumpRolls = 12,            //置换液泵累计转数
    C_SubPumpDirec = 13,            //置换液泵方向
    C_SubPumpBlock = 14,            //置换液泵堵转
    C_SubPumpCover = 15,            //置换液泵盖
    C_SubPumpFpr = 16,              //置换液泵泵管系数
    C_Vp = 17,                      //静脉压
    C_Ap = 18,                      //动脉压
    C_AirMonitor = 19,              //空气监测
    C_BloodId = 20,                 //血液识别
    C_ChokeClamp = 21,              //阻流夹
    C_VpAD = 22,                    //静脉压实时AD值
    C_VpZeroAD = 23,                //静脉压零点AD值
    C_VpSlopeAD = 24,               //静脉压AD斜率值
    C_ApAD = 25,                    //动脉压实时AD值
    C_ApZeroAD = 26,                //动脉压零点AD值
    C_ApSlopeAD = 27,               //动脉压AD斜率值
    C_PAVCom = 28,                  //动静脉压板通信

    C_BloodSysBoardVersion = 50,    //血路系统各板子版本

    //-----------------水路系统--------------------<
    C_WG1 = 100,                    //WG1
    C_WG5 = 101,                    //WG5
    C_WG6 = 102,                    //WG6
    C_YG1 = 103,                    //YG1
    C_YG2 = 104,                    //YG2
    C_YG3 = 105,                    //YG3
    C_YG4 = 106,                    //YG4
    C_DiaFlow = 107,                //透析液流量
    C_DPSpeed = 108,                //DP转速
    C_YPSpeed = 109,                //YP转速
    C_QPSpeed = 110,                //QP转速
    C_DPTime = 111,                 //DP推膜时间
    C_YPTime = 112,                 //YP推膜时间
    C_YG2High = 113,                //进液高压
    C_YG2Low = 114,                 //进液低压
    C_YG4High = 115,                //废液高压
    C_YG4Low = 116,                 //废液低压
    C_BalanceSW = 117,              //平衡腔开关
    C_HeatSW = 118,                 //加热开关
    C_HeatForceOff = 119,           //加热强关
    C_HeatDutyFactor = 120,         //加热占空比
    C_YK = 121,                     //YK
    C_YJ1 = 122,                    //YJ1
    C_YJ2 = 123,                    //YJ2
    C_YJ3 = 124,                    //YJ3
    C_YJ4 = 125,                    //YJ4
    C_YJ5 = 126,                    //YJ5
    C_LeftSubJoint = 127,           //左补液接头
    C_RightSubJoint = 128,          //右补液接头
    C_AStraw = 129,                 //A液吸管
    C_BStraw = 130,                 //B液吸管
    C_DiaJointRed = 131,            //红色透析器接头
    C_DiaJointBlue = 132,           //蓝色透析器接头
    C_V1 = 133,                     //V1，注意：V1~V8一定要保持连续
    C_V2 = 134,                     //V2
    C_V3 = 135,                     //V3
    C_V4 = 136,                     //V4
    C_V5 = 137,                     //V5
    C_V6 = 138,                     //V6
    C_V7 = 139,                     //V7
    C_V8 = 140,                     //V8
    C_SV1 = 141,                    //SV1，注意：SV1~SV24一定要保持连续
    C_SV2 = 142,                    //SV2
    C_SV3 = 143,                    //SV3
    C_SV4 = 144,                    //SV4
    C_SV5 = 145,                    //SV5
    C_SV6 = 146,                    //SV6
    C_SV7 = 147,                    //SV7
    C_SV8 = 148,                    //SV8
    C_SV9 = 149,                    //SV9
    C_SV10 = 150,                   //SV10
    C_SV11 = 151,                   //SV11
    C_SV12 = 152,                   //SV12
    C_SV13 = 153,                   //SV13
    C_SV14 = 154,                   //SV14
    C_SV15 = 155,                   //SV15
    C_SV16 = 156,                   //SV16
    C_SV17 = 157,                   //SV17
    C_SV18 = 158,                   //SV18
    C_SV19 = 159,                   //SV19
    C_SV20 = 160,                   //SV20
    C_SV21 = 161,                   //SV21
    C_SV22 = 162,                   //SV22
    C_SV23 = 163,                   //SV23
    C_SV24 = 164,                   //SV24
    C_WaterSupply = 165,            //供水不足
    C_InletWaterLevel = 166,        //进水位长时间无变化
    C_DiaAir = 167,                 //透析液空气过多
    C_DiaphBlock = 168,             //平衡腔膜片受阻
    C_BloodLeak = 169,              //漏血
    C_FluidLeak1 = 170,             //漏液传感器1
    C_FluidLeak2 = 171,             //漏液传感器2
    C_YG1OutLimit = 172,            //进液压超限
    C_YG4OutLimit = 173,            //废液压超限
    C_QPSpeedError = 174,           //QP转速异常
    C_DPSpeedError = 175,           //DP转速异常
    C_YPSpeedError = 176,           //YP转速异常
    C_M1Leak = 177,                 //膜片M1泄漏
    C_M2Leak = 178,                 //膜片M2泄漏
    C_V1V7Leak = 179,               //V1/V7泄漏
    C_V2V8Leak = 180,               //V2/V8泄漏
    C_V3V5Leak = 181,               //V3/V5泄漏
    C_V4V6Leak = 182,               //V4/V6泄漏
    C_SV13Leak = 183,               //SV13泄漏
    C_SV14Leak = 184,               //SV14泄漏
    C_YG2DataError = 185,           //YG2数据异常
    C_YG4DataError = 186,           //YG4数据异常
    C_YG13Com = 187,                //YG1/3通信异常
    C_YG24Com = 188,                //YG2/4通信异常
    C_DiaTempSensor = 189,          //透析液温度传感器异常
    C_HeatTempSensor = 190,         //加热温度传感器异常
    C_YG4LowPre = 191,              //废液压低压高
    C_YG2LowPre = 192,              //进液压低压高

    C_LiquidSysBoardVersion = 250,  //水路系统各板子版本

    //---------------配液超滤系统-------------------<
    C_MixSW = 300,                  //配液开关
    C_BCond = 301,                  //B电导
    C_ACond = 302,                  //A电导
    C_CCond = 303,                  //C电导
    C_AdjustRange = 304,            //配液调整范围
    C_WG2 = 305,                    //WG2
    C_WG3 = 306,                    //WG3
    C_WG4 = 307,                    //WG4
    C_APumpSW = 308,                //A泵开关
    C_APumpDirec = 309,             //A泵方向
    C_APumpBlock = 310,             //A泵堵转
    C_APumpPhaseLoss = 311,         //A泵缺相
    C_APumpTargetSpeed = 312,       //A泵目标转速
    C_APumpRealSpeed = 313,         //A泵实际转速
    C_APumpRolls = 314,             //A泵累计转数
    C_BPumpSW = 315,                //B泵开关
    C_BPumpDirec = 316,             //B泵方向
    C_BPumpBlock = 317,             //B泵堵转
    C_BPumpPhaseLoss = 318,         //B泵缺相
    C_BPumpTargetSpeed = 319,       //B泵目标转速
    C_BPumpRealSpeed = 320,         //B泵实际转速
    C_BPumpRolls = 321,             //B泵累计转数
    C_UfPumpSW = 322,               //超滤泵开关
    C_UfPumpDirec = 323,            //超滤泵方向
    C_UfPumpBlock = 324,            //超滤泵堵转
    C_UfPumpPhaseLoss = 325,        //超滤泵缺相
    C_UfPumpTargetSpeed = 326,      //超滤泵目标转速
    C_UfPumpRealSpeed = 327,        //超滤泵实际转速
    C_UfPumpRolls = 328,            //超滤泵累计转数

    C_MixUfSysBoardVersion = 350,   //配液超滤系统各板子版本

    //-----------------抗凝系统--------------------<
    C_HepPumpSW = 400,              //肝素泵开关
    C_HepPumpDirec = 401,           //肝素泵方向
    C_HepPumpBlock = 402,           //肝素泵堵转
    C_InjectorSpeci = 403,          //注射器规格
    C_ArriveBottom = 404,           //肝素到底
    C_ArriveTop = 405,              //肝素到顶
    C_HepPlateMove = 406,           //肝素推板被移动
    C_HepLight = 407,               //光电开关被遮挡
    C_HepPumpError = 408,           //肝素泵故障
    C_HepTargetFlow = 409,          //目标流量
    C_HepRealFlow = 410,            //实际流量
    C_HepTotalFlow = 411,           //累计流量

    C_AntiSysBoardVersion = 450,    //抗凝系统各板子版本

    //-----------------电源系统--------------------<
    C_PowerError = 500,             //电源故障
    C_ChargeStatus = 501,           //充电状态
    C_BatteryStatus = 502,          //电池状态
    C_CityPower = 503,              //市电状态
    C_PowerSupply = 504,            //供电状态
    C_CityVol = 505,                //市电电压
    C_PowerVol = 506,               //电源电压
    C_Battery = 507,                //电池电量
    C_Vol12V = 508,                 //12V电压
    C_Vol24V = 509,                 //24V电压
    C_BatteryVol = 510,             //电池电压

    C_PowerSysBoardVersion = 550,   //电源系统各板子版本

    //----------------按键指示灯-------------------<

    C_MonitorBoardVersion = 650,    //监控板版本

    //----------血温血容与实时清除率监测-------------<
    C_VTStatus = 700,                //静脉血温传感器状态
    C_ATStatus = 701,                //动脉血温传感器状态
    C_VT = 702,                      //静脉血温
    C_AT = 703,                      //动脉血温
    C_BVStatus = 704,                //血容量传感器状态
    C_bloodDetect = 705,             //是否检测到血液
    C_BVCover = 706,                 //血容量监测盖
    C_LEDSW = 707,                   //近红外LED状态
    C_BV_V = 708,                    //受光电压
    C_BV = 709,                      //血容量
    C_BV0 = 710,                     //初始血容量
    C_RBV = 711,                     //相对血容量
    C_RCMCorrect = 712,              //实时清除率监测传感器校正
    C_RCMStatus = 713,               //实时清除率监测传感器状态
    C_RCMDetect = 714,               //实时清除率监测检测状态
    C_abs = 715,                     //吸光度

    C_BtvRcmBoardVersion = 750,     //血温血容与实时清除率板版本

    //------------------其他----------------------<
    C_MachineSetType = 1000,        //机器类型设置
};

#endif // SIMULATIONDATACODE_H
