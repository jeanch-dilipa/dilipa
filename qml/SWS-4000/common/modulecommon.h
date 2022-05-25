#ifndef MODULECOMMON_H
#define MODULECOMMON_H

#include <QtGlobal>
#include <shlwapi.h>
//#pragma pack(1)     //字节对齐方式

/*模块地址定义*/
typedef enum
{
    MODULE_BOARD_ADDR_DEFAULT                                       = 0x00,
    BLOOD_PUMP_BOARD_ADDRESS                                        = 0x01,                    //血泵板地址
    FLUID_INFUSION_PUMP_BOARD_ADDRESS                               = 0x02,                    //补液泵板地址
    ULTRAFILTRATION_PUMP_BOARD_ADDRESS                              = 0x03,                    //超滤板地址
    HEPARIN_PUMP_BOARD_ADDRESS                                      = 0x04,                    //肝素板地址
    DRIVER_BOARD_ADDRESS                                            = 0x05,                    //驱动板地址
    BALANCE_CHAMBER_BOARD_ADDRESS                                   = 0x06,                    //平衡腔板地址
    MIXED_BOARD_ADDRESS                                             = 0x07,                    //配液板地址
    CONDUCTANCE_BOARD_AB_ADDRESS                                    = 0x08,                    //电导AB地址
    MONITOR_BOARD_ADDRESS                                           = 0x09 ,                   //监控板地址
    HEATER_BOARD_ADDRESS                                            = 0x0A,                    //加热板地址
    POWER_BOARD_ADDRESS                                             = 0x0C,                    //电源板地址

    CONDUCTANCE_BOARD_C_ADDRESS                                     = 0x25,                    //电导C地址
    BLOOD_PRESSURE_BOARD_ADDRESS                                    = 0x27,                    //血压计模块地址
    ONLINE_KTV_BOARD_ADDRESS                                        = 0x28,                    //实时清除率模块

    KEYPRESS_BOARD_ADDRESS                                          = 0x41,                    //按键地址
    PILOT_LAMP_BOARD_ADDRESS                                        = 0x42,                    //指示灯地址

    MAIN_CONTROL_BOARD_ADDRESS                                      = 0x55                     //主控板地址
}__attribute__((packed)) ModuleBoardAddrType;


/*协议使用读写命令定义*/
typedef enum
{
    SYSTEM_BUS_WRITE_COMMAND_0                                      = 0x30,                    //48
    SYSTEM_BUS_WRITE_COMMAND_1                                      = 0x31,                    //49
    SYSTEM_BUS_WRITE_COMMAND_2                                      = 0x32,                    //50
    SYSTEM_BUS_WRITE_COMMAND_3                                      = 0x33,                    //51
    SYSTEM_BUS_WRITE_COMMAND_4                                      = 0x34,                    //52
    SYSTEM_BUS_WRITE_COMMAND_5                                      = 0x35,                    //53
    SYSTEM_BUS_WRITE_COMMAND_6                                      = 0x36,                    //54
    SYSTEM_BUS_WRITE_COMMAND_7                                      = 0x37,                    //55
    SYSTEM_BUS_WRITE_COMMAND_8                                      = 0x38,                    //56
    SYSTEM_BUS_WRITE_COMMAND_9                                      = 0x39,                    //57

    SYSTEM_BUS_READ_COMMAND_0                                       = 0x40,                    //64
    SYSTEM_BUS_READ_COMMAND_1                                       = 0x41,                    //65
    SYSTEM_BUS_READ_COMMAND_2                                       = 0x42,                    //66
    SYSTEM_BUS_READ_COMMAND_3                                       = 0x43,                    //67
    SYSTEM_BUS_READ_COMMAND_4                                       = 0x44,                    //68
    SYSTEM_BUS_READ_COMMAND_5                                       = 0x45,                    //69
    SYSTEM_BUS_READ_COMMAND_6                                       = 0x46,                    //70
    SYSTEM_BUS_READ_COMMAND_7                                       = 0x48,                    //72

    SYSTEM_BUS_PILOT_LAMP_COMMAND                                   = 0x50,                    //指示灯命令
    SYSTEM_BUS_KEY_PRESSED_COMMAND                                  = 0x51                     //按键指令
}__attribute__((packed)) SystemBusCommandType;

struct __attribute__((packed)) Version
{
    quint16 code;
    quint16 ver_h;
    quint16 ver_s;
};

/*直流电机板*/                                                                                 //0/1
struct DCmotor
{
    const int DCmotor_WR0_SR                                        = 0x08;                    //关机/开机
    const int DCmotor_WR0_FR                                        = 0x04;                    //顺时针/逆时针
    const int DCmotor_WR0_M1                                        = 0x02;                    //运转模式高
    const int DCmotor_WR0_M0                                        = 0x01;                    //运转模式低
    const int DCmotor_WR0_Z                                         = 0x20;                    //流量累计/流量清0
    const int DCmotor_WR0_T                                         = 0x10;                    //泵管系数测试不启动/启动
    struct
    {
        quint8   cmd_1;                                                                        //控制字
        quint8   cmd_2;                                                                        //保留
        quint16  fpr;                                                                          //泵管系数
        quint16  fpm;                                                                          //泵流量min
    }__attribute__((packed))wr0;

    const int DCmotor_RD0_SR                                        = 0x08;                    //关机/开机
    const int DCmotor_RD0_FR                                        = 0x04;                    //顺时针/逆时针
    const int DCmotor_RD0_ND                                        = 0x02;                    //未堵转/堵转
    const int DCmotor_RD0_CO                                        = 0x01;                    //盖闭合/盖开
    const int DCmotor_RD0_ST                                        = 0x10;                    //自检/自检完成
    struct
    {
        quint8   std_1;                                                                        //控制字
        quint8   std_2;                                                                        //保留
        quint16  fpm_set;                                                                      //设置泵流量min
        quint16  fpm_real;                                                                     //实际泵流量min
        quint16  fpr;                                                                          //泵管系数
        quint16  rolls;                                                                        //泵总转速
    }__attribute__((packed))rd0;

    Version rd7;
};

/*超滤板*/
struct UlterFilterPlate
{
    const int UlterFilterPlate_WR0_SR                               = 0x08;                    //关机/开机
    const int UlterFilterPlate_WR0_Z                                = 0x80;                    //流量累计/流量清0
    const int UlterFilterPlate_WR0_ZF                               = 0x40;                    //正传/反转
    const int UlterFilterPlate_WR0_T                                = 0x20;                    //正常/测试模式
    struct
    {
        quint8   cmd_1;                                                                        //控制字
        quint8   cmd_2;                                                                        //保留
        quint16  fpr;                                                                          //泵管系数
        quint16  fph;                                                                          //泵流量h
        quint16  rev;                                                                          //测试模式下超滤泵转数
    }__attribute__((packed))wr0;

    const int UlterFilterPlate_RD0_SR                               = 0x08;                    //关机/开机
    const int UlterFilterPlate_RD0_NP                               = 0x02;                    //正常/缺相
    const int UlterFilterPlate_RD0_NF                               = 0x20;                    //正常/流量故障
    const int UlterFilterPlate_RD0_ND                               = 0x01;                    //未堵转/堵转
    struct
    {
        quint8   std_1;                                                                        //控制字
        quint8   std_2;                                                                        //保留
        quint16  fph_set;                                                                      //设置泵流量h
        quint16  fph_real;                                                                     //实际泵流量h
        quint16  flow;                                                                         //已超滤量
        quint16  rpm;                                                                          //转速
    }__attribute__((packed))rd0;

    Version rd7;
};

/*肝素板*/
struct HeparinPlate
{
    const int HeparinPlate_WR0_SR                               = 0x08;                        //关机/开机
    const int HeparinPlate_WR0_Z                                = 0x80;                        //流量累计/流量清0
    const int HeparinPlate_WR0_M1                               = 0x40;                        //快推高位
    const int HeparinPlate_WR0_M0                               = 0x20;                        //快推低位
    const int HeparinPlate_WR0_T                                = 0x04;                        //正常/测试模式
    struct
    {
        quint8   cmd_1;                                                                        //控制字
        quint8   cmd_2;                                                                        //保留
        quint8   type;                                                                         //注射器型号
        quint16  fph;                                                                          //流量h
    }__attribute__((packed))wr0;

    const int HeparinPlate_RD0_SR                               = 0x08;                        //关机/开机
    const int HeparinPlate_RD0_NP                               = 0x20;                        //正常/缺相
    const int HeparinPlate_RD0_BOM                              = 0x01;                        //到底/未到底
    const int HeparinPlate_RD0_TOP                              = 0x02;                        //到顶/未到顶
    const int HeparinPlate_RD0_ERR                              = 0x40;                        //正常/故障
    const int HeparinPlate_RD0_ND                               = 0x01;                        //未堵转/堵转
    struct
    {
        quint8   std_1;                                                                        //控制字
        quint8   std_2;                                                                        //保留
        quint16  fph_set;                                                                      //目标泵流量h
        quint16  fph_real;                                                                     //实际泵流量h
        quint16  flow;                                                                         //已推注量
    }__attribute__((packed))rd0;

    Version rd7;
};

/*驱动板*/
struct DriveBoard
{
    const int DriveBoard_WR0_BLI                                = 0x01;                        //无/漏血初始化
    const int DriveBoard_WR0_ZLJ                                = 0x02;                        //未通电阻断管路/通电打开阻流夹
    const int DriveBoard_WR0_SV1_L                              = 0x04;                        //SV1强制控制低位
    const int DriveBoard_WR0_SV1_H                              = 0x08;                        //SV1强制控制高位
    const int DriveBoard_WR0_CTRL_SV                            = 0x10;                        //不控制电磁阀/发送新的电磁阀控制状态

    const int DriveBoard_WR0_M1                                 = 0x02;                        //蠕动泵运行模式控制位低位
    const int DriveBoard_WR0_M0                                 = 0x01;                        //蠕动泵运行模式控制位高位

    const int DriveBoard_WR0_SV1                                = 0x01;
    const int DriveBoard_WR0_SV2                                = 0x02;
    const int DriveBoard_WR0_SV3                                = 0x04;
    const int DriveBoard_WR0_SV4                                = 0x08;
    const int DriveBoard_WR0_SV5                                = 0x10;
    const int DriveBoard_WR0_SV6                                = 0x20;
    const int DriveBoard_WR0_SV7                                = 0x40;
    const int DriveBoard_WR0_SV8                                = 0x80;

    const int DriveBoard_WR0_SV9                                = 0x01;
    const int DriveBoard_WR0_SV10                               = 0x02;
    const int DriveBoard_WR0_SV11                               = 0x04;
    const int DriveBoard_WR0_SV12                               = 0x08;
    const int DriveBoard_WR0_SV13                               = 0x10;
    const int DriveBoard_WR0_SV14                               = 0x20;
    const int DriveBoard_WR0_SV15                               = 0x40;
    const int DriveBoard_WR0_SV16                               = 0x80;

    const int DriveBoard_WR0_SV17                               = 0x01;
    const int DriveBoard_WR0_SV18                               = 0x02;
    const int DriveBoard_WR0_SV19                               = 0x04;
    const int DriveBoard_WR0_SV20                               = 0x08;

    struct
    {
        quint8   cmd_1;                                                                        //控制字1
        quint8   cmd_2;                                                                        //控制字2
        quint8   sv1_8;                                                                        //sv1-8
        quint8   sv9_16;                                                                       //sv9-16
        quint8   sv17_24;                                                                      //sv17-24
    }__attribute__((packed))wr0;

    const int DriveBoard_WR1_JMY_0                              = 0x01;                        //无校正/静脉压 0kpa 校正
    const int DriveBoard_WR1_JMY_32                             = 0x02;                        //无校正/静脉压 32kpa 校正
    const int DriveBoard_WR1_DMY_0                              = 0x04;                        //无校正/动脉压 0kpa 校正
    const int DriveBoard_WR1_DMY_32                             = 0x08;                        //无校正/动脉压 32kpa 校正
    const int DriveBoard_WR1_TXY_0                              = 0x10;                        //无校正/透析液压 0kpa 校正
    const int DriveBoard_WR1_TXY_35                             = 0x20;                        //无校正/透析液压 35kpa 校正
    const int DriveBoard_WR1_FY_0                               = 0x40;                        //无校正/负压 0kpa 校正
    const int DriveBoard_WR1_FY_35                              = 0x80;                        //无校正/负压 35kpa 校正

    struct
    {
        quint8  cmd_1;                                                                         //控制字
        quint8  cmd_2;                                                                         //保留
        quint16 cmd_3;                                                                         //保留
    } __attribute__((packed)) wr1;

    const int DriveBoard_RD0_SV13                               = 0x01;                        //SV13处于关闭状态/SV13处于打开状态
    const int DriveBoard_RD0_YJ4                                = 0x02;                        //干粉筒YJ4 干簧管吸合/干粉筒YJ4 干簧管断开
    const int DriveBoard_RD0_GAS                                = 0x04;                        //空气检测无空气/空气检测有空气
    const int DriveBoard_RD0_BLD                                = 0x08;                        //漏血测试不正常/漏血测试正常
    const int DriveBoard_RD0_YK                                 = 0x10;                        //YK 干簧管吸合/YK 干簧管断开
    const int DriveBoard_RD0_WA                                 = 0x20;                        //透析器接头 A 插在机器上/透析器接头 A 不在机器上
    const int DriveBoard_RD0_WB                                 = 0x40;                        //透析器接头 B 插在机器上/透析器接头 B 不在机器上
    const int DriveBoard_RD0_ZLJ                                = 0x80;                        //阻流夹关闭/阻流夹打开

    const int DriveBoard_RD0_CAJ                                = 0x01;                        //A 液吸管插在机器上/A 液吸管不在机器上
    const int DriveBoard_RD0_CBJ                                = 0x02;                        //B 液吸管插在机器上/B 液吸管不在机器上
    const int DriveBoard_RD0_YJ1                                = 0x04;                        //YJ1 干簧管吸合/YJ1 干簧管断开
    const int DriveBoard_RD0_GAS2                               = 0x10;                        //补液无气泡/补液有气泡
    const int DriveBoard_RD0_BLOOD                              = 0x20;                        //有血液/无血液
    const int DriveBoard_RD0_LD                                 = 0x40;                       //底部无漏液/底部漏液

    struct
    {
        quint8  std_1;                                                                         //状态字1
        quint8  std_2;                                                                         //状态字2
        qint16  np;                                                                            //除气负压
        quint16 __unused_1__;                                                                  //保留
    } __attribute__((packed)) rd0;

    struct
    {
        qint16  vp;                                                                            // 静脉压
        qint16  ap;                                                                            // 动脉压
        qint16  dp;                                                                            // 透析液压
    } __attribute__((packed)) rd1;

    const int DriveBoard_RD2_JMY_0                              = 0x01;                        //静脉压 0kp 校正无效/静脉压 0kp 校正正确
    const int DriveBoard_RD2_JMY_32                             = 0x02;                        //静脉压 32kp 校正无效/静脉压 32kp 校正正确
    const int DriveBoard_RD2_DMY_0                              = 0x04;                        //动脉压 0kp 校正无效/动脉压 0kp 校正正确
    const int DriveBoard_RD2_DMY_32                             = 0x08;                        //动脉压 32kp 校正无效/动脉压 32kp 校正正确
    const int DriveBoard_RD2_TXY_0                              = 0x10;                        //透析液压 0kp 校正无效/透析液压 0kp 校正正确
    const int DriveBoard_RD2_TXY_35                             = 0x20;                        //透析液压 32kp 校正无效/透析液压 35kp 校正正确
    const int DriveBoard_RD2_FY_0                               = 0x40;                        //除气负压 0kp 校正无效/除气负压 0kp 校正正确
    const int DriveBoard_RD2_FY_35                              = 0x80;                        //除气负压 32kp 校正无效/除气负压 35kp 校正正确
    struct
    {
        quint8  std_1;                                                                         // 状态字
        quint8  __unused_1__;                                                                  //保留
        quint16 __unused_2__;                                                                  //保留
    } __attribute__((packed)) rd2;

    Version rd7;
};

/*平衡腔板*/
struct Balance
{
    const int Balance_WR0_WORK_MODEL_NORMAL                     = 0x01;                        //正常运行模式
    const int Balance_WR0_WORK_MODEL_STOP                       = 0x02;                        //停止模式
    const int Balance_WR0_WORK_MODEL_PASSBY                     = 0x01;                        //旁路关闭/旁路打开状态
    const int Balance_WR0_WORK_MODEL_SV13                       = 0x02;                        //SV13关闭/SV13打开

    struct
    {
        quint8  cmd_1;                                                                         // 命令字
        quint8  cmd_2;
        quint8  qpv;                                                                           // QP泵电压
        quint16  flow;                                                                         // 透析液流量
    } __attribute__((packed)) wr0;

    const int Balance_WR1_V1                                    = 0x01;
    const int Balance_WR1_V2                                    = 0x02;
    const int Balance_WR1_V3                                    = 0x04;
    const int Balance_WR1_V4                                    = 0x08;
    const int Balance_WR1_V5                                    = 0x10;
    const int Balance_WR1_V6                                    = 0x20;
    const int Balance_WR1_V7                                    = 0x40;
    const int Balance_WR1_V8                                    = 0x80;

    const int Balance_WR1_SV14_T                                = 0x80;                        //由负压罐干簧管状态控制/强制打开

    struct
    {
        quint8  cmd_1;                                                                         // 平衡腔电磁阀
        quint8  cmd_2;                                                                         // 命令字
        quint8  qpv;                                                                           // QP泵电压
        quint8  dpv;                                                                           // DP泵电压
        quint8  ypv;                                                                           // YP泵电压
    } __attribute__((packed)) wr1;

    const int Balance_WR2_JYY_0                                 = 0x01;                        //无校正/进液压 0kpa 校正
    const int Balance_WR2_JYY_35                                = 0x02;                        //无校正/进液压 35kpa 校正
    const int Balance_WR2_FYY_0                                 = 0x04;                        //无校正/废液压 0kpa 校正
    const int Balance_WR2_FYY_35                                = 0x08;                        //无校正/废液压 35kpa 校正

    struct
    {
        quint8  cmd_1;                                                                         // 校正命令
        quint8  cmd_2;
        quint16 cmd_3;
    } __attribute__((packed)) wr2;

    const int Balance_WR3_DP_F                                  = 0x01;                        //齿轮泵 DP 正转/ 齿轮泵 DP 反转
    const int Balance_WR3_YP_F                                  = 0x02;                        //齿轮泵 YP 正转/ 齿轮泵 YP 反转
    const int Balance_WR3_QP_F                                  = 0x04;                        //齿轮泵 QP 正转/ 齿轮泵 QP 反转
    const int Balance_WR3_SV14_T                                = 0x80;                        //由负压罐干簧管状态控制/强制打开

    struct
    {
        quint8  cmd_1;
        quint8  cmd_2;
    }__attribute__((packed)) wr3;

    const int Balance_RD0_CQ2                                   = 0x80;                        //废液出气罐干簧管 1(YJ2)闭合/废液出气罐干簧管 1(YJ2)断开
    const int Balance_RD0_CQ3                                   = 0x40;                        //废液出气罐干簧管 2(YJ3)闭合/废液出气罐干簧管 2(YJ3)断开
    const int Balance_RD0_SV14                                  = 0x20;                        //SV14 电磁阀关闭/SV14 电磁阀打开
    const int Balance_RD0_BK_G                                  = 0x10;                        //表示从机当前处于关机状态/,表示从机当前处于开机状态

    const int Balance_RD0_ERR_GAS_LEAK                          = 0x80;                        //透析液气泡过多
    const int Balance_RD0_ERR_BC1_JAM                           = 0x40;                        //平衡腔异常 I
    const int Balance_RD0_ERR_BC2_JAM                           = 0x20;                        //平衡腔异常 II
    const int Balance_RD0_ERR_BC_V_LEAK                         = 0x10;                        //平衡腔电磁阀泄漏
    const int Balance_RD0_ERR_BC_D_LEAK                         = 0x08;                        //平衡腔膜片泄漏
    const int Balance_RD0_ERR_YG2_ERR                           = 0x04;                        //进液压力异常:传感器 YG2 损坏或平衡腔板坏
    const int Balance_RD0_ERR_YG4_ERR                           = 0x02;                        //废液压力异常:传感器 YG4 损坏或平衡腔板坏
    const int Balance_RD0_ERR_DP_ERR                            = 0x01;                        //进液泵异常:进液泵损坏或测速信号异常

    const int Balance_RD0_ERR_YP_ERR                            = 0x80;                        //废液泵异常:废液泵损坏或测速信号异常
    const int Balance_RD0_ERR_QP_ERR                            = 0x40;                        //除气泵异常:除气泵损坏或测速信号异常
    const int Balance_RD0_ERR_YG2_DATA_ERR                      = 0x20;                        //进液压传感器校正数据错误或未校正
    const int Balance_RD0_ERR_YG4_DATA_ERR                      = 0x10;                        //废液压传感器校正数据错误或未校正
    const int Balance_RD0_ERR_SV14_LEAK                         = 0x08;                        //电磁阀 SV14 泄漏
    const int Balance_RD0_ERR_V4V6_LEAK                         = 0x04;                        //无/平衡腔电磁阀V4V6泄露
    const int Balance_RD0_ERR_M1_LEAK                           = 0x02;                        //无/平衡腔膜片1泄漏
    const int Balance_RD0_ERR_M2_LEAK                           = 0x01;                        //无/平衡腔膜片2泄漏

    struct
    {
        quint8  std_1;                                                                         // 状态字
        quint8  std_2;                                                                         //保留
        quint8  err1;                                                                          // 错误状态1
        quint8  err2;                                                                          // 错误状态2
        quint16 yg2h;                                                                          // 进液高压力
        quint16 yg2l;                                                                          // 进液低压力
        quint16 yg4h;                                                                          // 废液高压力
        quint16 yg4l;                                                                          // 废液低压力
    } __attribute__((packed)) rd0;

    struct
    {
        quint16 dprpm;                                                                         // DP泵转速
        quint16 yprpm;                                                                         // YP泵转速
        quint16 qprpm;                                                                         // QP泵转速
        quint16 dpvol;                                                                         // DP泵电压
        quint16 ypvol;                                                                         // YP泵电压
        quint16 qpvol;                                                                         // QP泵电压
        quint8  dpt;                                                                           // DP推膜时间
        quint8  ypt;                                                                           // YP推膜时间
    } __attribute__((packed)) rd1;

    const int Balance_RD2_JYY_0                                 = 0x01;                        //进液压 0kpa 校正无效/ 进液压 0kpa 校正正确
    const int Balance_RD2_JYY_35                                = 0x02;                        //进液压 32kpa 校正无效/ 进液压 32kpa 校正正确
    const int Balance_RD2_FYY_0                                 = 0x04;                        //废液压 0kpa 校正无效/ 废液压 0kpa 校正正确
    const int Balance_RD2_FYY_35                                = 0x08;                        //废液压 32kpa 校正无效/ 废液压 32kpa 校正正确

    struct
    {
        quint8  std_1;                                                                         // YG2,YG4校正结果
        quint8  std_2;
        quint16 std_3;
    } __attribute__((packed)) rd2;

    const int Balance_RD3_CQ2                                   = 0x80;                        //废液出气罐干簧管 1(YJ2)断开/废液出气罐干簧管 1(YJ2)闭合

    struct
    {
        quint8  std_1;                                                                         // 状态字
        quint8  std_2;
        qint16 rtYG2;                                                                          // 进液压YG2实时压力
        qint16 rtYG4;                                                                          // 废液压YG4实时压力
    } __attribute__((packed)) rd3;

    Version rd7;
};

/*配液板*/
struct Mixture
{
    const int Mixture_WR0_WORK_MOD_STOP                         = 0x00;                        //停止工作
    const int Mixture_WR0_WORK_MOD_CURE                         = 0x01;                        //治疗模式
    const int Mixture_WR0_WORK_MOD_CLEAN                        = 0x02;                        //清洗消毒模式
    const int Mixture_WR0_WORK_MOD_CHECK_A                      = 0x03;                        //自检模式 A
    const int Mixture_WR0_WORK_MOD_CHECK_B                      = 0x04;                        //自检模式 B
    const int Mixture_WR0_WORK_MOD_STORE                        = 0x05;                        //参数暂存

    const int Mixture_WR0_WORK_MOD_FM                           = 0x80;                        //先吸A液/先吸B液
    const int Mixture_WR0_WORK_MOD_BZF                          = 0x40;                        //B泵正转/B泵反转
    const int Mixture_WR0_WORK_MOD_BT                           = 0x20;                        //B泵正常模式/B泵测试模式
    const int Mixture_WR0_WORK_MOD_AZF                          = 0x10;                        //A泵正转/A泵反转
    const int Mixture_WR0_WORK_MOD_AT                           = 0x08;                        //A泵正常模式/A泵测试模式

    const int Mixture_WR0_LIQUID_MOD_DIALYSATE                  = 0x00;                        //浓缩液
    const int Mixture_WR0_LIQUID_MOD_BICAR                      = 0x03;                        //干粉筒

    struct
    {
        quint8  cmd_1;                                                                         //命令字
        quint8  cmd_2;                                                                         //命令字2
        quint16 Afpm;                                                                          //JP1泵流速
        quint16 Bfpm;                                                                          //JP2泵流速
        quint8  Acond;                                                                         //一级电导设定值
        quint8  Bcond;                                                                         //二级电导设定值
        quint16 Afpr;                                                                          //JP1泵系数
        quint16 Bfpr;                                                                          //JP2泵系数
        quint8  range;                                                                         //电导可调节范围
        quint16 flow;                                                                          //透析液流量
    } __attribute__((packed)) wr0;

    struct
    {
        char    AorC;                                                                          //选择标定电导编号
        quint8  cmd_1;                                                                         //1=标定点1;2=标定点2;3=标定温度值
        quint8  Cond_H;                                                                        //电导高8位，放大100倍
        quint8  Cond_L;
        quint8  Tep_H;                                                                         //温度高8位，放大100倍
        quint8  Tep_L;
    } __attribute__((packed)) wr1;

    const int Mixture_RD0_A_SR                                  = 0x01;                        //A泵停机/运行
    const int Mixture_RD0_A_NP                                  = 0x02;                        //A泵正常/缺相
    const int Mixture_RD0_A_ERR                                 = 0x04;                        //A泵正常/流量异常
    const int Mixture_RD0_A_ND                                  = 0x08;                        //A泵正常/堵转
    const int Mixture_RD0_B_SR                                  = 0x10;                        //B泵停机/运行
    const int Mixture_RD0_B_NP                                  = 0x20;                        //B泵正常/缺相
    const int Mixture_RD0_B_ERR                                 = 0x40;                        //B泵正常/流量异常
    const int Mixture_RD0_B_ND                                  = 0x80;                        //B泵正常/堵转

    const int Mixture_RD0_MOD_IDLE                              = 0x00;                        //配液空闲
    const int Mixture_RD0_MOD_TRIAL                             = 0x01;                        //配液试配
    const int Mixture_RD0_MOD_ADJUST                            = 0x02;                        //配液调整
    const int Mixture_RD0_MOD_TRIM                              = 0x03;                        //配液微调
    const int Mixture_RD0_MOD_FINISH                            = 0x04;                        //配液完成
    const int Mixture_RD0_MOD_PAUSE                             = 0x05;                        //配液暂停

    struct
    {
        quint8  std_1;                                                                         // 状态字
        quint8  std_2;
        quint16 Arpm;                                                                          // JP1泵转数设定值
        quint16 Brpm;                                                                          // JP2泵转数设定值
        quint8  Acond;                                                                         // 一级电导设定值
        quint8  Bcond;                                                                         // 二级电导设定值
        quint16 rtArpm;                                                                        // JP1泵实际转速
        quint16 rtBrpm;                                                                        // JP2泵实际转速
        quint8  rtAcond;                                                                       //一级电导实际值
        quint8  rtBcond;                                                                       //二级电导实际值
        quint16 rtAtemp;                                                                       // 一级电导温度实际值
        quint16 rtBtemp;                                                                       // 二级电导温度实际值
    } __attribute__((packed)) rd0;

    struct
    {
        quint16 cond_a(void)    {return m_cond_a>>8 | m_cond_a<<8;}
        quint16 cond_b(void)    {return m_cond_b>>8 | m_cond_b<<8;}
        quint16 temp_a(void)    {return m_temp_a>>8 | m_temp_a<<8;}
        quint16 temp_b(void)    {return m_temp_b>>8 | m_temp_b<<8;}
        quint16 unuser(void)    {return __unused_1__>>8 | __unused_2__<<8;}
    private:
        quint16 m_cond_a;                                                                      // A电导值0.01（大端模式！！！）
        quint16 m_cond_b;                                                                      // B电导值0.01（大端模式！！！）
        quint16 m_temp_a;                                                                      // A温度值0.01（大端模式！！！）
        quint16 m_temp_b;                                                                      // B温度值0.01（大端模式！！！）
        quint8  __unused_1__;
        quint8  __unused_2__;
    } __attribute__((packed)) rd1;

    Version rd7;
};                      // 配液板

/*电导板*/
struct Cond
{
    const int Cond_WR1_POINT1                                   = 0x80;                        // 测试点1
    const int Cond_WR1_POINT2                                   = 0x40;                        // 测试点2
    const int Cond_WR1_POINT3                                   = 0x20;                        // 测试点3
    const int Cond_WR1_TMP_CHK                                  = 0x10;                        // 温度校正点
    const int Cond_WR1_TRY                                      = 0x04;                        // EEPROM 写入测试
    const int Cond_WR1_CHK_SUM                                  = 0x01;                        // 写E2PROM校验和

    struct
    {
        char    AorC;                                                                          //选择标定电导编号
        quint8  CMD;                                                                           //1=标定点1;2=标定点2
        quint8  Cond_H;                                                                        //电导高8位，放大100倍
        quint8  Cond_L;
        quint8  Tep_H;                                                                         //温度高8位，放大100倍
        quint8  Tep_L;
    } __attribute__((packed)) wr0;

    struct
    {
        quint8  __unused_1__;
        quint8  __unused_2__;
        quint8  cond_a;                                                                         // 0.1 A电导值
        quint8  cond_b;                                                                         // 0.1 B电导值
        quint16 temp_a(void)    {return m_temp_a>>8 | m_temp_a<<8;}
        quint16 temp_b(void)    {return m_temp_b>>8 | m_temp_b<<8;}
        quint16 unuser(void)    {return __unused_3__>>8 | __unused_4__<<8;}
    private:
        quint16 m_temp_a;                                                                       // 0.1 A温度值(大端模式！！！)
        quint16 m_temp_b;                                                                       // 0.1 B温度值(大端模式！！！)
        quint8  __unused_3__;
        quint8  __unused_4__;
    } __attribute__((packed)) rd0;

    struct
    {
        quint16 cond_a(void)    {return m_cond_a>>8 | m_cond_a<<8;}
        quint16 cond_b(void)    {return m_cond_b>>8 | m_cond_b<<8;}
        quint16 temp_a(void)    {return m_temp_a>>8 | m_temp_a<<8;}
        quint16 temp_b(void)    {return m_temp_b>>8 | m_temp_b<<8;}
        quint16 unuser(void)    {return __unused_1__>>8 | __unused_2__<<8;}
    private:
        quint16 m_cond_a;                                                                       // c电导值0.01（大端模式！！！）
        quint16 m_cond_b;                                                                       // d电导值0.01（大端模式！！！）
        quint16 m_temp_a;                                                                       // c温度值0.01（大端模式！！！）
        quint16 m_temp_b;                                                                       // d温度值0.01（大端模式！！！）
        quint8  __unused_1__;
        quint8  __unused_2__;
    } __attribute__((packed)) rd1;

    Version rd7;
};

/*加热板*/
struct Heat
{
    const int Heat_WR0_SR                                       = 0x01;                        //关机/开机
    const int Heat_WR0_WG1_REF                                  = 0x10;                        //无校正/WG1温度校正
    const int Heat_WR0_WG6_REF                                  = 0x20;                        //无校正/WG6温度校正
    struct
    {
        quint8  cmd_1;                                                                         // 命令字
        quint8  cmd_2;
        quint16 temp;                                                                          // 加热设置温度
        quint16 alarm_h;                                                                       // 报警上限温度
        quint16 alarm_l;                                                                       // 报警下限温度
        quint16 flow;                                                                          // 透析液流量
    } __attribute__((packed)) wr0;

    struct
    {
        quint8  __unused_1__;
        quint8  __unused_2__;
        qint16  adjust;                                                                        // 温度补偿
    } __attribute__((packed)) wr1;

    const int Heat_RD0_ALARM_H                                  = 0x01;                        //无/温度高限报警
    const int Heat_RD0_YJ1                                      = 0x02;                        //进水正常/进水水位长时间无变化
    const int Heat_RD0_ST                                       = 0x20;                        //加热器没有加热/加热器加热
    const int Heat_RD0_NE1                                      = 0x80;                        //正常/透析液温度传感器异常
    const int Heat_RD0_NE0                                      = 0x40;                        //正常/加热器温度传感器异常

    struct
    {
        quint8  std_1;                                                                         // 加热板状态字
        quint8  std_2;
        quint16 rtTemp_o;                                                                      // 实际加热后温度（透析液温度）
        quint16 rtTemp_i;                                                                      // 实际加热前温度（进水温度）
        quint16 temp_s;                                                                        // 设定加热温度
    } __attribute__((packed)) rd0;

    Version rd7;
};

/*称重板*/
//struct Weight
//{
//    const int Weight_WR0_CORR_OTHER                             = 0x00;                        //校正任意
//    const int Weight_WR0_CORR_LOW                               = 0x01;                        //低端校正
//    const int Weight_WR0_CORR_HIGH                              = 0x02;                        //高端校正

//    struct
//    {
//        quint8  cmd_1;                                                                         // 校正命令字
//        quint8  cmd_2;
//        quint32 VAL;                                                                           // 校准基准重量
//        quint16 REV;
//    } __attribute__((packed)) wr0;

//    const int Weight_RO0_OV0                                    = 0x01;                        //正常/称重 1 溢出
//    const int Weight_RO0_OV1                                    = 0x02;                        //正常/称重 2 溢出
//    const int Weight_RO0_VL0                                    = 0x04;                        //正常/称重 1 超载
//    const int Weight_RO0_VL1                                    = 0x08;                        //正常/称重 2 超载
//    const int Weight_RO0_ST0                                    = 0x10;                        //正常/传感器 1 坏
//    const int Weight_RO0_ST1                                    = 0x20;                        //正常/传感器 2 坏
//    const int Weight_RO0_PAR0                                   = 0x40;                        //正常/称重 1 参数异常
//    const int Weight_RO0_PAR1                                   = 0x80;                        //正常/称重 2 参数异常

//    struct
//    {
//        quint8  std_1;                                                                         // 状态字
//        quint8  std_2;
//        quint16 adc1;                                                                          // 1#秤ADC值
//        quint16 adc2;                                                                          // 2#秤ADC值
//        quint16 weight1;                                                                       // 1#秤重量
//        quint16 weight2;                                                                       // 2#秤重量
//        quint16 __unused_2__;
//    } __attribute__((packed)) rd0;

//    Version rd7;
//};

/*电源板*/
struct Power
{
    const int Power_WR0_ON_OFF                                  = 0x01;                        //电源维持/关机
    const int Power_WR0_AUTO_ON_OFF                             = 0x02;                        //定时开机功能失能/使能
    const int Power_WR0_WORKDAY_ON_OFF                          = 0x04;                        //轮休功能失能/使能
    const int Power_WR0_AUTOTIME_ON_OFF                         = 0x08;                        //定时开机字节数失能/使能

    const int Power_WR0_MON                                     = 0x01;                        //星期一轮休/使用
    const int Power_WR0_TUES                                    = 0x02;                        //星期二轮休/使用
    const int Power_WR0_WED                                     = 0x04;                        //星期三轮休/使用
    const int Power_WR0_THUR                                    = 0x08;                        //星期四轮休/使用
    const int Power_WR0_FRI                                     = 0x10;                        //星期五轮休/使用
    const int Power_WR0_SAT                                     = 0x20;                        //星期六轮休/使用
    const int Power_WR0_SUN                                     = 0x40;                        //星期日轮休/使用
    const int Power_WR0_ONCE_PERIOD                             = 0x80;                        //一次/周期

    struct
    {
        quint8  cmd_1;                                                                         // 命令字;
        quint8  cmd_2;
        quint8  workDay;                                                                       // 工作日期
        quint8  autoStart_hour_Monday;                                                         //周一自动开机小时数
        quint8  autoStart_min_Monday;                                                          //周一自动开机分钟数
        quint8  autoStart_hour_Tuesday;                                                        //周二自动开机小时数
        quint8  autoStart_min_Tuesday;                                                         //周二自动开机分钟数
        quint8  autoStart_hour_Wednesday;                                                      //周三自动开机小时数
        quint8  autoStart_min_Wednesday;                                                       //周三自动开机分钟数
        quint8  autoStart_hour_Thursday;                                                       //周四自动开机小时数
        quint8  autoStart_min_Thursday;                                                        //周四自动开机分钟数
        quint8  autoStart_hour_Friday;                                                         //周五自动开机小时数
        quint8  autoStart_min_Friday;                                                          //周五自动开机分钟数
        quint8  autoStart_hour_Saturday;                                                       //周六自动开机小时数
        quint8  autoStart_min_Saturday;                                                        //周六自动开机分钟数
        quint8  autoStart_hour_Sunday;                                                         //周日自动开机小时数
        quint8  autoStart_min_Sunday;                                                          //周日自动开机分钟数
    } __attribute__((packed)) wr0;

    struct
    {
        quint8  cmd_1;
        quint8  cmd_2;
        quint8  year;                                                                          //年
        quint8  month;                                                                         //月
        quint8  day;                                                                           //日
        quint8  hour;                                                                          //时
        quint8  minute;                                                                        //分
        quint8  second;                                                                        //秒
    }__attribute__((packed)) wr1;

    const int Power_RD0_VHVL_NOR                                = 0x00;                        //市电正常
    const int Power_RD0_VHVL_LOW                                = 0x01;                        //市电过低
    const int Power_RD0_VHVL_HIGH                               = 0x02;                        //市电过高
    const int Power_RD0_VHVL_DOWN                               = 0x03;                        //市电断电

    const int Power_RD0_BHBL_NOR                                = 0x00;                        //电池正常
    const int Power_RD0_BHBL_LOW                                = 0x04;                        //电池未充电
    const int Power_RD0_BHBL_HIGH                               = 0x08;                        //电池充电
    const int Power_RD0_BHBL_ERR                                = 0x0C;                        //电池异常

    const int Power_RD0_POWER_SUPPY_FAILURE                     = 0x10;                        //电源输出故障
    const int Power_RD0_NORMAL_PSF                              = 0x10;                        //正常/电源故障（9V、15V、24V电源输出异常）
    const int Power_RD0_NORMAL_OFF                              = 0x80;                        //正常关机/异常关机

    struct
    {
        quint8  std_1;                                                                         // 状态字
        quint8  std_2;
        quint16 s_vol;                                                                         // 市电电压
        quint8  rate;                                                                          // 电池电量
        quint16 b_vol;                                                                         // 电池电压
        quint8  std_3;
    } __attribute__((packed)) rd0;

    Version rd7;
};

/*监控板*/
struct  Monitor
{
#define MONITOR_WR0_MUTE_OFF        (0x00000000 << 0)                                          //静音灯灭
#define MONITOR_WR0_MUTE_ON         (0x00000001 << 0)                                          //静音灯亮
#define MONITOR_WR0_MUTE_FLASH      (0x00000002 << 0)                                          //静音灯闪
#define MONITOR_WR0_MUTE_UNUSE      (0x00000003 << 0)                                          //保留

#define MONITOR_WR0_BLP_OFF         (0x00000000 << 2)                                          //血泵灯灭
#define MONITOR_WR0_BLP_ON          (0x00000001 << 2)                                          //血泵灯亮
#define MONITOR_WR0_BLP_FLASH       (0x00000002 << 2)                                          //血泵灯闪
#define MONITOR_WR0_BLP_UNUSE       (0x00000003 << 2)                                          //保留

#define MONITOR_WR0_GREEN_OFF       (0x00000000 << 4)                                          //工作(绿) 灯灭
#define MONITOR_WR0_GREEN_ON        (0x00000001 << 4)                                          //工作(绿) 灯亮
#define MONITOR_WR0_GREEN_FLASH     (0x00000002 << 4)                                          //工作(绿) 灯闪
#define MONITOR_WR0_GREEN_UNUSE     (0x00000003 << 4)                                          //保留

#define MONITOR_WR0_RED_OFF         (0x00000000 << 6)                                          //工作(红) 灯灭
#define MONITOR_WR0_RED_ON          (0x00000001 << 6)                                          //工作(红) 灯亮
#define MONITOR_WR0_RED_FLASH       (0x00000002 << 6)                                          //工作(红) 灯闪
#define MONITOR_WR0_RED_UNUSE       (0x00000003 << 6)                                          //保留

#define MONITOR_WR0_YELLOW_OFF      (0x00000000 << 8)                                          //工作(黄) 灯灭
#define MONITOR_WR0_YELLOW_ON       (0x00000001 << 8)                                          //工作(黄) 灯亮
#define MONITOR_WR0_YELLOW_FLASH    (0x00000002 << 8)                                          //工作(黄) 灯闪
#define MONITOR_WR0_YELLOW_UNUSE    (0x00000003 << 8)                                          //保留

    struct WR0
    {
        quint8  cmd;                                                                           // 命令字 0x42;
        quint32 lamb_bits;                                                                     // 指示灯位

        WR0()
        {
            cmd = 0x42;
        }
    } __attribute__((packed)) wr0;

    struct
    {
        quint8  cmd;
        quint8  key;                                                                           // 按键码
    } __attribute__((packed)) rd0;

     Version rd7;
};

/*血压板*/
struct BloodPressure
{
    quint8 rd0_s;                                                                              //rd0 数据有效状态位
    quint8 rd1_s;                                                                              //rd1 数据有效状态位
    quint8 rd2_s;                                                                              //rd2 数据有效状态位
    struct
    {
        quint8 startByte;
        quint8 startCmd;
        quint8 chkSum;
    }__attribute__((packed)) wr0;

    struct
    {
        quint8 startByte;
        quint8 Cmd;
        quint8 data_l;
        quint8 data_h;
        quint8 chkSum;
    }__attribute__((packed))wr1;

    struct                                                                                     //模块命令返回值
    {
        quint8 startByte;                                                                      //开始字节
        quint8 length;                                                                         //返回值长度
        quint8 data;                                                                           //返回值数据
        quint8 chkSum;                                                                         //校验和
    } __attribute__((packed)) rd0;

    struct                                                                                     //袖袋压返回值
    {
        quint8 startByte;                                                                      //开始字节
        quint8 length;                                                                         //返回值长度
        quint8 data_l;                                                                         //袖袋压低字节
        quint8 data_h;                                                                         //袖袋压高字节
        quint8 chkSum;                                                                         //校验和
    } __attribute__((packed)) rd1;

    struct                                                                                     //血压值返回数据
    {
        quint8 startByte;                                                                      //开始字节
        quint8 length;                                                                         //返回值长度
        quint8 systolic_l;                                                                     //收缩压低字节
        quint8 systolic_h;                                                                     //收缩压高字节
        quint8 diastolic_l;                                                                    //舒张压低字节
        quint8 diastolic_h;                                                                    //舒张压高字节
        quint8  __unused_1__;
        quint8 bps;                                                                            //BP Status
        quint8  __unused_2__;
        quint8  __unused_3__;
        quint8  __unused_4__;
        quint8  __unused_5__;
        quint8  __unused_6__;
        quint8  __unused_7__;
        quint8  __unused_8__;
        quint8  __unused_9__;
        quint8 rate_l;                                                                         //心率低字节
        quint8 rate_h;                                                                         //心率高字节
        quint8 map_l;                                                                          //平均动脉压低字节
        quint8 map_h;                                                                          //平均动脉压高字节
        quint8  __unused_10__;
        quint8  __unused_11__;
        quint8  __unused_12__;
        quint8 chkSum;                                                                         //校验和
    } __attribute__((packed)) rd2;
};

/*在线KTV板*/
struct OnlineKtv
{
    const int Power_RD0_NORMAL_OFF                              = 0x80;                        //正常关机/异常关机
    const int OnlineKtv_WR0_UPDATE                              = 0x01;                        //停止检测/开始检测
    const int OnlineKtv_WR0_CALI                                = 0x02;                        //无校正/ 零点校正

    struct
    {
        quint8  cmd_1;                                                                         // 命令字
        quint8  cmd_2;
        quint16 interval;                                                                      //检测间隔
        quint16 cmd_3;
    } __attribute__((packed)) wr0;

    const int OnlineKtv_RD0_UPDATE                              = 0x01;                        //停止检测/正在检测
    const int OnlineKtv_RD0_CALI                                = 0x02;                        //校正正常/ 校正异常

    struct
    {
        quint8  std_1;
        quint8  std_2;
        quint16 bun;                                                                           // 尿素浓度，放大100倍
        qint16 std_3;
        quint32 in_AD;                                                                         // 辐照光强度接收传感器AD值
        quint32 out_AD;                                                                        // 通过液体后光强度接收传感器AD值
        quint32  std_4;
    } __attribute__((packed)) rd0;

    Version rd7;
};

#endif // MODULECOMMON_H
