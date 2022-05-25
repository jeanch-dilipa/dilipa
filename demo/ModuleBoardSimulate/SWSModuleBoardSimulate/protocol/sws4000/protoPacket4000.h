#ifndef PROTOPACKET_H
#define PROTOPACKET_H

#include <QtGlobal>

/**
 *  ProtoPacket 结构体的结构将严格按照《sws4000_v4.8型产品平台总线接口协议.doc》定义
 *  如有争议，以上述文档为准。
 */

#ifdef Q_OS_WIN
    #pragma pack(1) /*Windows下MinGW编译，__attribute__((packed))没有效果*/
#endif

struct __attribute__((packed)) version{
    quint16 code;   // 部件标识码
    quint16 ver_h;  // 硬件版本（压缩BCD码）
    quint16 ver_s;  // 软件版本（压缩BCD码）
};

//IAP升级命令 add zf 181226
struct __attribute__((packed)) IAP_WR9{
    quint8 Data_Sum;                 // APP数据帧总量
    quint8 Data_Num;                // 当前帧数据编号
    quint8 Data_Value[1024];  // 数据值，APP 程序代码
};

struct __attribute__((packed)) IAP_RD8{
    quint8 Next_Num;         //准备发送的数据编号
    quint8 Writed_Sum;      //已写入数据量
    quint8 IAP_Ver;              //IAP软件版本
};
//add zf end

/**
 * 直流电机板
 */
struct DirectPump {
#define DIRECTPUMP_WR0_SR   0x08    //关机/开机
#define DIRECTPUMP_WR0_FR   0x04    //顺时针/逆时针旋转(若硬件固定方向,则此位无效)
#define DIRECTPUMP_WR0_M1   0x02    //运转模式高位
#define DIRECTPUMP_WR0_M0   0x01    //运转模式低位
#define DIRECTPUMP_WR0_Z    0x20    //流量累计/流量清零
#define DIRECTPUMP_WR0_T    0x10    //泵管系数测试不启动/启动
    struct {
        quint8  cmd;        // 控制命令字
        quint8  __unused_1__;
        quint8  fpr;        // 每转流量/泵管系数（放大10倍）
        quint16 fpm;        // 每分钟流量（放大10倍）
    }__attribute__((packed)) wr0;

    IAP_WR9 wr9; //add zf 190114

    ////////////////////////////////////////////////////////////////////
#define DIRECTPUMP_RD0_SR   0x08    //关机/开机
#define DIRECTPUMP_RD0_FR   0x04    //顺时针/逆时针旋转
#define DIRECTPUMP_RD0_ND   0x02    //泵未堵转/堵转
#define DIRECTPUMP_RD0_CO   0x01    //盖闭合/盖开
#define DIRECTPUMP_RD0_ST   0x10    //状态
    struct {
        quint8  status;     // 状态字
        quint8  __unused_2__;
        quint16 fpm_set;    // 设置的流速（放大10倍）
        quint16 fpm_real;   // 实际的流速（放大10倍）
        quint8  fpr;        // 泵管系数（放大10倍）
        quint32 rolls;      // 泵总转数（放大60倍）
    }__attribute__((packed)) rd0;

    /////////////////////////////////////////////////////////////////////
    version rd7;

    IAP_RD8 rd8; //add zf 190114
};

/**
 * 超滤泵
 */
struct UFPump{
#define UFPUMP_WR0_SR   0x08    //关/开
#define UFPUMP_WR0_T    0x20    //正常/测试模式
#define UFPUMP_WR0_ZF   0x40    //反转/正传
#define UFPUMP_WR0_Z    0x80    //流量累计/流量清 0
    struct {
        quint8  cmd;        // 命令字
        quint8  __unused_1__;
        quint16 fpr;        // 超滤泵系数
        quint16 fph;        // 每小时流量
        quint16 rev;        // 测试模式下，超滤泵需要转多少转
    }__attribute__((packed)) wr0;

    IAP_WR9 wr9; //add zf 190116

    ////////////////////////////////////////////////////////////////////
#define UFPUMP_RD0_SR   0x08    //停机/运行
#define UFPUMP_RD0_NP   0x02    //正常/缺相
#define UFPUMP_RD0_ND   0x01    //未堵转/堵转
#define UFPUMP_RD0_NF   0x20    //正常/流量故障
    struct {
        quint8  status;     // 状态字
        quint8  __unused_1__;
        quint16 fpm_set;    // 目标流速
        quint16 fpm_real;   // 实际流速
        quint32 flow;       // 已超滤量
        quint16 rpm;        // 超滤泵转数
    } __attribute__((packed)) rd0;

    //////////////////////////////////////////////////////////////////////
    version rd7;

    IAP_RD8 rd8; //add zf 190116
};                   // 超滤泵

/**
 * 肝素泵
 */
struct HePump{
#define HEPUMP_WR0_SR   0x08    //关/开
#define HEPUMP_WR0_T    0x04    //正常/测试模式
#define HEPUMP_WR0_Z    0x80    //流量累计/流量清 0
#define HEPUMP_WR0_M1   0x40    //工作模式高位
#define HEPUMP_WR0_M0   0x20    //工作模式低位
    struct {
        quint8  cmd;        // 命令字
        quint8  __unused_1__;
        quint8  type;       // 注射器类型
        quint16  fph;        // 肝素泵目标流速
    } __attribute__((packed)) wr0;

    IAP_WR9 wr9; //add zf 190116

    //////////////////////////////////////////////////////////////////
#define HEPUMP_RD0_SR    0x08   //停机/运行
#define HEPUMP_RD0_ERR   0x04   //正常/故障
#define HEPUMP_RD0_TOP   0x02   //未到顶/到达顶端
#define HEPUMP_RD0_BOM   0x01   //未到底/ 到达底端
#define HEPUMP_RD0_ND    0x10   //未堵转/泵堵转
#define HEPUMP_RD0_NF    0x20   //正常/泵缺相
    struct {
        quint8   status;     // 状态字
        quint8   __unused_1__;
        quint16  fph_set;    // 设置流速
        quint16  fph_real;   // 当前流速
        quint16  flow;       // 已推注量
    } __attribute__((packed)) rd0;

    ////////////////////////////////////////////////////////////////////
    version rd7;

    IAP_RD8 rd8; //add zf 190116
};                  // 肝素泵

/**
 * 驱动板
 */
struct DriveBroad{
#define DRIVERBOARD_WR0_BLI     0x01    //无/漏血初始化
#define DRIVERBOARD_WR0_ZLJ     0x02    //未通电阻断管路/通电打开阻流夹
#define DRIVERBOARD_WR0_SV1_L   0x04    //SV1强制控制低位
#define DRIVERBOARD_WR0_SV1_H   0x08    //SV1强制控制高位
#define DRIVERBOARD_WR0_CTRL_SV 0x10    //不控制电磁阀/发送新的电磁阀控制状态

#define DRIVERBOARD_WR0_M_L          0x00000001       //蠕动泵运行模式控制位低位
#define DRIVERBOARD_WR0_M_H         0x00000002       //蠕动泵运行模式控制位高位

#define DRIVERBOARD_WR0_SV1    0x00000100
#define DRIVERBOARD_WR0_SV2    0x00000200
#define DRIVERBOARD_WR0_SV3    0x00000400
#define DRIVERBOARD_WR0_SV4    0x00000800

#define DRIVERBOARD_WR0_SV5    0x00001000
#define DRIVERBOARD_WR0_SV6    0x00002000
#define DRIVERBOARD_WR0_SV7    0x00004000
#define DRIVERBOARD_WR0_SV8    0x00008000

#define DRIVERBOARD_WR0_SV9     0x00010000
#define DRIVERBOARD_WR0_SV10    0x00020000
#define DRIVERBOARD_WR0_SV11    0x00040000
#define DRIVERBOARD_WR0_SV12    0x00080000

#define DRIVERBOARD_WR0_SV13    0x00100000
#define DRIVERBOARD_WR0_SV14    0x00200000
#define DRIVERBOARD_WR0_SV15    0x00400000
#define DRIVERBOARD_WR0_SV16    0x00800000

#define DRIVERBOARD_WR0_SV17    0x01000000
#define DRIVERBOARD_WR0_SV18    0x02000000
#define DRIVERBOARD_WR0_SV19    0x04000000 //add xy 2013.9.24
#define DRIVERBOARD_WR0_SV20    0x08000000 //add xy 2015.7.22

    struct {
        quint8  cmd;        // 命令字
        quint32 sv;         //共4个字节，但SV只使用后面3个字节，第一个字节保留
    } __attribute__((packed)) wr0;

    /////////////////////////////////////////////////////////////////
#define DRIVERBOARD_WR1_JMY_0       0x01    //无校正/静脉压 0kpa 校正
#define DRIVERBOARD_WR1_JMY_32      0x02    //无校正/静脉压 32kpa 校正
#define DRIVERBOARD_WR1_DMY_0       0x04    //无校正/动脉压 0kpa 校正
#define DRIVERBOARD_WR1_DMY_32      0x08    //无校正/动脉压 32kpa 校正
#define DRIVERBOARD_WR1_TXY_0       0x10    //无校正/透析液压 0kpa 校正
#define DRIVERBOARD_WR1_TXY_35      0x20    //无校正/透析液压 35kpa 校正
#define DRIVERBOARD_WR1_FY_0        0x40    //无校正/负压 0kpa 校正
#define DRIVERBOARD_WR1_FY_35       0x80    //无校正/负压 35kpa 校正
    struct {
        quint8  cmd;        // 命令字
        quint8  __unused_1__;
        quint16 __unused_2__;
    } __attribute__((packed)) wr1;

    IAP_WR9 wr9; //add zf 190116

    //////////////////////////////////////////////////////////////////
#define DRIVERBOARD_RD0_SV13  0x01     //SV13处于关闭状态/SV13处于打开状态
#define DRIVERBOARD_RD0_YJ4     0x02    //干粉筒YJ4 干簧管吸合/干粉筒YJ4 干簧管断开
#define DRIVERBOARD_RD0_GAS     0x04    //空气检测无空气/空气检测有空气
#define DRIVERBOARD_RD0_BLD     0x08    //漏血测试不正常/漏血测试正常
#define DRIVERBOARD_RD0_YK      0x10    //YK 干簧管吸合/YK 干簧管断开
#define DRIVERBOARD_RD0_WA      0x20    //透析器接头 A 插在机器上/透析器接头 A 不在机器上
#define DRIVERBOARD_RD0_WB      0x40    //透析器接头 B 插在机器上/透析器接头 B 不在机器上
#define DRIVERBOARD_RD0_ZLJ     0x80    //阻流夹关闭/阻流夹打开

#define DRIVERBOARD_RD0_CAJ     0x01    //A 液吸管插在机器上/A 液吸管不在机器上
#define DRIVERBOARD_RD0_CBJ     0x02    //B 液吸管插在机器上/B 液吸管不在机器上
#define DRIVERBOARD_RD0_YJ1     0x04    //YJ1 干簧管吸合/YJ1 干簧管断开
#define DRIVERBOARD_RD0_GAS2    0x10    //补液无气泡/补液有气泡
#define DRIVERBOARD_RD0_BLOOD   0x20    //有血液/无血液
#define DRIVERBOARD_RD0_LD      0x40    //底部无漏液/底部有漏液
    struct {
        quint8  status1;    // 状态字1
        quint8  status2;    // 状态字2
        qint16  np;         // 除气负压（0.1Kpa）
        quint16 __unused_1__;
    } __attribute__((packed)) rd0;

    /////////////////////////////////////////////////////////////////////
    struct {
        qint16  vp;         // 静脉压（放大10倍）
        qint16  ap;         // 动脉压（放大10倍）
        qint16  dp;         // 透析液压（放大10倍）
    } __attribute__((packed)) rd1;

    /////////////////////////////////////////////////////////////////////
#define DRIVERBOARD_RD2_JMY_0       0x01    //静脉压 0kp 校正无效/静脉压 0kp 校正正确
#define DRIVERBOARD_RD2_JMY_32      0x02    //静脉压 32kp 校正无效/静脉压 32kp 校正正确
#define DRIVERBOARD_RD2_DMY_0       0x04    //动脉压 0kp 校正无效/动脉压 0kp 校正正确
#define DRIVERBOARD_RD2_DMY_32      0x08    //动脉压 32kp 校正无效/动脉压 32kp 校正正确
#define DRIVERBOARD_RD2_TXY_0       0x10    //透析液压 0kp 校正无效/透析液压 0kp 校正正确
#define DRIVERBOARD_RD2_TXY_35      0x20    //透析液压 32kp 校正无效/透析液压 35kp 校正正确
#define DRIVERBOARD_RD2_FY_0        0x40    //除气负压 0kp 校正无效/除气负压 0kp 校正正确
#define DRIVERBOARD_RD2_FY_35       0x80    //除气负压 32kp 校正无效/除气负压 35kp 校正正确
    struct {
        quint8  status;     // 状态字
        quint8  __unused_1__;
        quint16 __unused_2__;
    } __attribute__((packed)) rd2;

    //////////////////////////////////////////////////////////////////////
    version rd7;

    IAP_RD8 rd8; //add zf 190116
};                    // 驱动板

/**
 * 平衡腔
 */
struct Balance{
#define BALANCE_WR0_WORK_MODEL_NORMAL   0x01    //正常运行模式
#define BALANCE_WR0_WORK_MODEL_STOP     0x02    //停止模式
#define BALANCE_WR0_WORK_MODEL_PASSBY   0x01    //旁路关闭/旁路打开状态
#define BALANCE_WR0_WORK_MODEL_SV13        0x02    //SV13关闭/SV13打开

    struct {
        quint8  cmd;         // 命令字
        quint8  cmd_2;
        quint8  qpv;         // QP泵电压
        quint16  flow;       // 平衡腔流量
    } __attribute__((packed)) wr0;

    ////////////////////////////////////////////////////////////////////////
#define BALANCE_WR1_V1  0x01
#define BALANCE_WR1_V2  0x02
#define BALANCE_WR1_V3  0x04
#define BALANCE_WR1_V4  0x08
#define BALANCE_WR1_V5  0x10
#define BALANCE_WR1_V6  0x20
#define BALANCE_WR1_V7  0x40
#define BALANCE_WR1_V8  0x80

#define BALANCE_WR1_SV14_T      0x80    //由负压罐干簧管状态控制/强制打开
    struct {
        quint8  vv;         // 平衡腔电磁阀
        quint8  cmd;        // 命令字
        quint8  qpv;        // QP泵电压
        quint8  dpv;        // DP泵电压
        quint8  ypv;        // YP泵电压
    } __attribute__((packed)) wr1;

    ///////////////////////////////////////////////////////////////////////////
#define BALANCE_WR2_JYY_0       0x01    //无校正/进液压 0kpa 校正
#define BALANCE_WR2_JYY_35      0x02    //无校正/进液压 35kpa 校正
#define BALANCE_WR2_FYY_0       0x04    //无校正/废液压 0kpa 校正
#define BALANCE_WR2_FYY_35      0x08    //无校正/废液压 35kpa 校正
    struct {
        quint8  cmd;        // 校正命令
        quint8  __unused_1__;
        quint16 __unused_2__;
    } __attribute__((packed)) wr2;

    ///////////////////////////////////////////////////////////////////////////
#define BALANCE_WR3_DP_F        0x01    //齿轮泵 DP 正转/ 齿轮泵 DP 反转
#define BALANCE_WR3_YP_F        0x02    //齿轮泵 YP 正转/ 齿轮泵 YP 反转
#define BALANCE_WR3_QP_F        0x04    //齿轮泵 QP 正转/ 齿轮泵 QP 反转
#define BALANCE_WR3_SV14_T      0x80    //由负压罐干簧管状态控制/强制打开
    struct
    {
        quint8  cmd;
        quint8  __unused_1__;
    }__attribute__((packed)) wr3;

    IAP_WR9 wr9; //add zf 190116

    /////////////////////////////////////////////////////////////////////////////
#define BALANCE_RD0_CQ2     0x80    //废液出气罐干簧管 1(YJ2)闭合/废液出气罐干簧管 1(YJ2)断开
#define BALANCE_RD0_CQ3     0x40    //废液出气罐干簧管 2(YJ3)闭合/废液出气罐干簧管 2(YJ3)断开
#define BALANCE_RD0_SV14    0x20    //SV14 电磁阀关闭/SV14 电磁阀打开
#define BALANCE_RD0_BK_G    0x10    //表示从机当前处于关机状态/,表示从机当前处于开机状态

#define BALANCE_RD0_ERR_GAS_LEAK    0x80    //透析液气泡过多
#define BALANCE_RD0_ERR_BC1_JAM     0x40    //平衡腔异常 I
#define BALANCE_RD0_ERR_BC2_JAM     0x20    //平衡腔异常 II
#define BALANCE_RD0_ERR_BC_V_LEAK    0x10    //平衡腔电磁阀泄漏
#define BALANCE_RD0_ERR_BC_D_LEAK    0x08    //平衡腔膜片泄漏
#define BALANCE_RD0_ERR_YG2_ERR     0x04    //进液压力异常:传感器 YG2 损坏或平衡腔板坏
#define BALANCE_RD0_ERR_YG4_ERR     0x02    //废液压力异常:传感器 YG4 损坏或平衡腔板坏
#define BALANCE_RD0_ERR_DP_ERR      0x01    //进液泵异常:进液泵损坏或测速信号异常

#define BALANCE_RD0_ERR_YP_ERR          0x80    //废液泵异常:废液泵损坏或测速信号异常
#define BALANCE_RD0_ERR_QP_ERR          0x40    //除气泵异常:除气泵损坏或测速信号异常
#define BALANCE_RD0_ERR_YG2_DATA_ERR    0x20    //进液压传感器校正数据错误或未校正
#define BALANCE_RD0_ERR_YG4_DATA_ERR    0x10    //废液压传感器校正数据错误或未校正
#define BALANCE_RD0_ERR_SV14_LEAK       0x08    //电磁阀 SV14 泄漏
    struct {
        quint8  status;     // 状态字
        quint8  __unused_1__;
        quint8  err1;       // 错误状态1
        quint8  err2;       // 错误状态2
        quint16 yg2h;       // 进液高压力
        quint16 yg2l;       // 进液低压力
        quint16 yg4h;       // 废液高压力
        quint16 yg4l;       // 废液低压力
    } __attribute__((packed)) rd0;

    /////////////////////////////////////////////////////////////////////////
    struct {
        quint16 dprpm;      // DP泵转速
        quint16 yprpm;      // YP泵转速
        quint16 qprpm;      // QP泵转速
        quint16 dpvol;      // DP泵电压
        quint16 ypvol;      // YP泵电压
        quint16 qpvol;      // QP泵电压
        quint8  dpt;        // DP推膜时间
        quint8  ypt;        // YP推膜时间
    } __attribute__((packed)) rd1;

    /////////////////////////////////////////////////////////////////////////////
#define BALANCE_RD2_JYY_0       0x01    //进液压 0kpa 校正无效/ 进液压 0kpa 校正正确
#define BALANCE_RD2_JYY_35      0x02    //进液压 32kpa 校正无效/ 进液压 32kpa 校正正确
#define BALANCE_RD2_FYY_0       0x04    //废液压 0kpa 校正无效/ 废液压 0kpa 校正正确
#define BALANCE_RD2_FYY_35      0x08    //废液压 32kpa 校正无效/ 废液压 32kpa 校正正确
    struct {
        quint8  status;     // YG2,YG4校正结果
        quint8  __unused_1__;
        quint16 __unused_2__;
    } __attribute__((packed)) rd2;

    //////////////////////////////////////////////////////////////////////////////
#define BALANCE_RD3_CQ2     0x80    //废液出气罐干簧管 1(YJ2)断开/废液出气罐干簧管 1(YJ2)闭合
    struct {
        quint8  status;     // 状态字
        quint8  __unused_1__;
        qint16 rtYG2;      // 进液压YG2实时压力
        qint16 rtYG4;      // 废液压YG4实时压力
    } __attribute__((packed)) rd3;

    /////////////////////////////////////////////////////////////////////////////
    version rd7;

    IAP_RD8 rd8; //add zf 190116
};                  // 平衡腔

/**
 * 配液板
 */
struct Mixture {
#define MIXTURE_WR0_WORK_MOD_STOP       0x00    //停止工作
#define MIXTURE_WR0_WORK_MOD_CURE       0x01    //治疗模式
#define MIXTURE_WR0_WORK_MOD_CLEAN      0x02    //清洗消毒模式
#define MIXTURE_WR0_WORK_MOD_CHECK_A    0x03    //自检模式 A
#define MIXTURE_WR0_WORK_MOD_CHECK_B    0x04    //自检模式 B
#define MIXTURE_WR0_WORK_MOD_STORE      0x05    //参数暂存

    struct {
        quint8  cmd;        // 命令字
        quint8  __unused_1__;
        quint16 Afpm;       // A泵流速
        quint16 Bfpm;       // B泵流速
        quint8  Acond;      // A电导设定值
        quint8  Bcond;      // B电导设定值
        quint16 Afpr;       // A泵系数
        quint16 Bfpr;       // B泵系数
        quint8  range;      // 电导可调节范围
        quint16 flow;       // 透析液流量
    } __attribute__((packed)) wr0;

    ///////////////////////////////////////////////////////////////////
    struct {
        char    AorC;//选择标定电导编号
        quint8  CMD;//1=标定点1;2=标定点2;3=标定温度值
        quint8  Cond_H;//电导高8位，放大100倍
        quint8  Cond_L;
        quint8  Tep_H;//温度高8位，放大100倍
        quint8  Tep_L;
    } __attribute__((packed)) wr1;

    IAP_WR9 wr9; //add zf 190114

    //////////////////////////////////////
#define MIXTURE_RD0_A_SR      0x01    //A泵停机/运行
#define MIXTURE_RD0_A_NP      0x02    //A泵正常/缺相
#define MIXTURE_RD0_A_ERR     0x04    //A泵正常/流量异常
#define MIXTURE_RD0_A_ND      0x08    //A泵正常/堵转
#define MIXTURE_RD0_B_SR      0x10    //B泵停机/运行
#define MIXTURE_RD0_B_NP      0x20    //B泵正常/缺相
#define MIXTURE_RD0_B_ERR     0x40    //B泵正常/流量异常
#define MIXTURE_RD0_B_ND      0x80    //B泵正常/堵转

    struct {
        quint8  status;     // 状态字
        quint8  __unused_1__;
        quint16 Arpm;       // A泵转数设定值
        quint16 Brpm;       // B泵转数设定值
        quint8  Acond;      // A电导设定值
        quint8  Bcond;      // B电导设定值
        quint16 rtArpm;     // A泵实际转速
        quint16 rtBrpm;     // B泵实际转速
        quint8  rtAcond;    // A电导实际值
        quint8  rtBcond;    // B电导实际值
        quint16 rtAtemp;    // A电导温度实际值
        quint16 rtBtemp;    // B电导温度实际值
    } __attribute__((packed)) rd0;

    struct {
        quint16 cond_a(void)    {return m_cond_a>>8 | m_cond_a<<8;}
        quint16 cond_b(void)    {return m_cond_b>>8 | m_cond_b<<8;}
        quint16 temp_a(void)    {return m_temp_a>>8 | m_temp_a<<8;}
        quint16 temp_b(void)    {return m_temp_b>>8 | m_temp_b<<8;}
    private:
        quint16 m_cond_a;   // A电导值0.01（大端模式！！！）
        quint16 m_cond_b;   // B电导值0.01（大端模式！！！）
        quint16 m_temp_a;   // A温度值0.01（大端模式！！！）
        quint16 m_temp_b;   // B温度值0.01（大端模式！！！）
        quint8  __unused_1__;
        quint8  __unused_2__;
    } __attribute__((packed)) rd1;//add wl 200224

    /////////////////////////////////////////////////////////////////////
    version rd7;

    IAP_RD8 rd8;  //add zf 190114
};                      // 配液板

/**
 * 电导板
 */
struct Cond{
#define COND_WR1_POINT1     0x80    // 测试点1
#define COND_WR1_POINT2     0x40    // 测试点2
#define COND_WR1_POINT3     0x20    // 测试点3
#define COND_WR1_TMP_CHK    0x10    // 温度校正点
#define COND_WR1_TRY        0x04    // EEPROM 写入测试
#define COND_WR1_CHK_SUM    0x01    // 写E2PROM校验和
    struct {
        char    AorC;//选择标定电导编号
        quint8  CMD;//1=标定点1;2=标定点2
        quint8  Cond_H;//电导高8位，放大100倍
        quint8  Cond_L;
        quint8  Tep_H;//温度高8位，放大100倍
        quint8  Tep_L;
    } __attribute__((packed)) wr1;

    struct {
        quint8  __unused_1__;
        quint8  __unused_2__;
        quint8  cond_a;     // 0.1 A电导值
        quint8  cond_b;     // 0.1 B电导值
        quint16 temp_a(void)    {return m_temp_a>>8 | m_temp_a<<8;}
        quint16 temp_b(void)    {return m_temp_b>>8 | m_temp_b<<8;}
        quint16 m_temp_a;     // 0.1 A温度值(大端模式！！！)
        quint16 m_temp_b;     // 0.1 B温度值(大端模式！！！)
        quint8  __unused_3__;
        quint8  __unused_4__;
    } __attribute__((packed)) rd0;

    struct {
        quint16 cond_a(void)    {return m_cond_a>>8 | m_cond_a<<8;}
        quint16 cond_b(void)    {return m_cond_b>>8 | m_cond_b<<8;}
        quint16 temp_a(void)    {return m_temp_a>>8 | m_temp_a<<8;}
        quint16 temp_b(void)    {return m_temp_b>>8 | m_temp_b<<8;}
    private:
        quint16 m_cond_a;   // c电导值0.01（大端模式！！！）
        quint16 m_cond_b;   // d电导值0.01（大端模式！！！）
        quint16 m_temp_a;   // c温度值0.01（大端模式！！！）
        quint16 m_temp_b;   // d温度值0.01（大端模式！！！）
        quint8  __unused_1__;
        quint8  __unused_2__;
    } __attribute__((packed)) rd1;

    //////////////////////////////////////////////////////////////
    version rd7;
};

/**
 * 加热板
 */
struct Heat{
#define HEAT_WR0_SR 0x01    //关机/开机
    struct {
        quint8  cmd;        // 命令字
        quint8  __unused_1__;
        quint16 temp;       // 加热设置温度
        quint16 alarm_h;    // 报警上限温度
        quint16 alarm_l;    // 报警下限温度
        quint16 flow;       // 透析液流量
    } __attribute__((packed)) wr0;

    //////////////////////////////////////////////////
    struct {
        quint8  __unused_1__;
        quint8  __unused_2__;
        qint16  adjust;     // 温度补偿
    } __attribute__((packed)) wr1;

    IAP_WR9 wr9; //add zf 190116

    //////////////////////////////////////////////////////////////
#define HEAT_RD0_ALARM_H    0x01    //无/温度高限报警
#define HEAT_RD0_YJ1        0x02    //进水正常/进水水位长时间无变化
#define HEAT_RD0_ST         0x20    //加热器没有加热/加热器加热
#define HEAT_RD0_NE1        0x80    //正常/透析液温度传感器异常
#define HEAT_RD0_NE0        0x40    //正常/加热器温度传感器异常
    struct {
        quint8  status;     // 加热板状态字
        quint8  __unused_1__;
        quint16 rtTemp_o;   // 实际加热后温度（透析液温度）
        quint16 rtTemp_i;   // 实际加热前温度（进水温度）
        quint16 temp_s;     // 设定加热温度
    } __attribute__((packed)) rd0;

    /////////////////////////////////////////////////////////////////////////
    version rd7;

    IAP_RD8 rd8; //add zf 190116
} ;                    // 加热板

/**
 * 称重板
 */
struct Weight{  // 称重板
#define WEIGHT_WR0_CORR_OTHER   0x00    //校正任意
#define WEIGHT_WR0_CORR_LOW     0x01    //低端校正
#define WEIGHT_WR0_CORR_HIGH    0x02    //高端校正
    struct {
        quint8  cmd;        // 校正命令字
        quint8  __unused_1__;
        quint32 stdWeight;  // 校准基准重量
        quint16 __unused_2__;
    } __attribute__((packed)) wr0;

    //////////////////////////////////////////////////////////////////////////
#define WEIGHT_RO0_OV0      0x01    //正常/称重 1 溢出
#define WEIGHT_RO0_OV1      0x02    //正常/称重 2 溢出
#define WEIGHT_RO0_VL0      0x04    //正常/称重 1 超载
#define WEIGHT_RO0_VL1      0x08    //正常/称重 2 超载
#define WEIGHT_RO0_ST0      0x10    //正常/传感器 1 坏
#define WEIGHT_RO0_ST1      0x20    //正常/传感器 2 坏
#define WEIGHT_RO0_PAR0     0x40    //正常/称重 1 参数异常
#define WEIGHT_RO0_PAR1     0x80    //正常/称重 2 参数异常
    struct {
        quint8  status;     // 状态字
        quint8  __unused_1__;
        quint16 adc1;       // 1#秤ADC值
        quint16 adc2;       // 2#秤ADC值
        quint16 weight1;    // 1#秤重量
        quint16 weight2;    // 2#秤重量
        quint16 __unused_2__;
    } __attribute__((packed)) rd0;

    ////////////////////////////////////////////////////////////////////////
    version rd7;
};

/**
 * 电源板
 */
struct Power {
#define POWER_WR0_ON_OFF            0x01   //电源维持/关机
#define POWER_WR0_AUTO_ON_OFF       0x02   //定时开机功能失能/使能
#define POWER_WR0_WORKDAY_ON_OFF    0x04   //轮休功能失能/使能
#define POWER_WR0_AUTOTIME_ON_OFF   0x08   //定时开机字节数失能/使能

#define POWER_WR0_MON               0x01   //星期一轮休/使用
#define POWER_WR0_TUES              0x02   //星期二轮休/使用
#define POWER_WR0_WED               0x04   //星期三轮休/使用
#define POWER_WR0_THUR              0x08   //星期四轮休/使用
#define POWER_WR0_FRI               0x10   //星期五轮休/使用
#define POWER_WR0_SAT               0x20   //星期六轮休/使用
#define POWER_WR0_SUN               0x40   //星期日轮休/使用
#define POWER_WR0_ONCE_PERIOD       0x80   //一次/周期
    struct {
        quint8  cmd;                       // 命令字;
        quint8  __unused_1__;
        quint8  workDay;                   // 工作日期
        quint8  autoStart_hour_Monday;     //周一自动开机小时数
        quint8  autoStart_min_Monday;      //周一自动开机分钟数
        quint8  autoStart_hour_Tuesday;    //周二自动开机小时数
        quint8  autoStart_min_Tuesday;     //周二自动开机分钟数
        quint8  autoStart_hour_Wednesday;  //周三自动开机小时数
        quint8  autoStart_min_Wednesday;   //周三自动开机分钟数
        quint8  autoStart_hour_Thursday;   //周四自动开机小时数
        quint8  autoStart_min_Thursday;    //周四自动开机分钟数
        quint8  autoStart_hour_Friday;     //周五自动开机小时数
        quint8  autoStart_min_Friday;      //周五自动开机分钟数
        quint8  autoStart_hour_Saturday;   //周六自动开机小时数
        quint8  autoStart_min_Saturday;    //周六自动开机分钟数
        quint8  autoStart_hour_Sunday;     //周日自动开机小时数
        quint8  autoStart_min_Sunday;      //周日自动开机分钟数
    } __attribute__((packed)) wr0;

    struct
    {
        quint8  __unused_1__;
        quint8  __unused_2__;
        quint8  year;                //年
        quint8  month;               //月
        quint8  day;                 //日
        quint8  hour;                //时
        quint8  minute;              //分
        quint8  second;              //秒
    }__attribute__((packed)) wr1;

    IAP_WR9 wr9; //add zf 190116

    ////////////////////////////////////////////////////////////////////////
#define POWER_RD0_VHVL_NOR       0x00   //市电正常
#define POWER_RD0_VHVL_LOW       0x01   //市电过低
#define POWER_RD0_VHVL_HIGH      0x02   //市电过高
#define POWER_RD0_VHVL_DOWN      0x03   //市电断电

#define POWER_RD0_BHBL_LOW          0x04
#define POWER_RD0_BHBL_HIGH          0x08

#define POWER_RD0_POWER_SUPPY_FAILURE        0x10    //电源输出故障

#define POWER_RD0_NORMAL_OFF    0x80    //正常关机/异常关机
    struct {
        quint8  status;     // 状态字
        quint8  __unused_1__;
        quint16 s_vol;      // 市电电压
        quint8  rate;       // 电池电量
        quint16 b_vol;      // 电池电压
        quint8  __unused_2__;
    } __attribute__((packed)) rd0;

    //////////////////////////////////////////////////////////////////////////////
    version rd7;

    IAP_RD8 rd8; //add zf 190116
};

/**
 * 监控板
 */
struct  Monitor {  // 监控板
#define MONITOR_WR0_MUTE_OFF        (0x00000000 << 0)   //静音灯灭
#define MONITOR_WR0_MUTE_ON         (0x00000001 << 0)   //静音灯亮
#define MONITOR_WR0_MUTE_FLASH      (0x00000002 << 0)   //静音灯闪
#define MONITOR_WR0_MUTE_UNUSE      (0x00000003 << 0)   //保留

#define MONITOR_WR0_BLP_OFF        (0x00000000 << 2)   //血泵灯灭
#define MONITOR_WR0_BLP_ON         (0x00000001 << 2)   //血泵灯亮
#define MONITOR_WR0_BLP_FLASH      (0x00000002 << 2)   //血泵灯闪
#define MONITOR_WR0_BLP_UNUSE      (0x00000003 << 2)   //保留

#define MONITOR_WR0_GREEN_OFF        (0x00000000 << 4)   //工作(绿) 灯灭
#define MONITOR_WR0_GREEN_ON         (0x00000001 << 4)   //工作(绿) 灯亮
#define MONITOR_WR0_GREEN_FLASH      (0x00000002 << 4)   //工作(绿) 灯闪
#define MONITOR_WR0_GREEN_UNUSE      (0x00000003 << 4)   //保留

#define MONITOR_WR0_RED_OFF        (0x00000000 << 6)   //工作(红) 灯灭
#define MONITOR_WR0_RED_ON         (0x00000001 << 6)   //工作(红) 灯亮
#define MONITOR_WR0_RED_FLASH      (0x00000002 << 6)   //工作(红) 灯闪
#define MONITOR_WR0_RED_UNUSE      (0x00000003 << 6)   //保留

#define MONITOR_WR0_YELLOW_OFF        (0x00000000 << 8)   //工作(黄) 灯灭
#define MONITOR_WR0_YELLOW_ON         (0x00000001 << 8)   //工作(黄) 灯亮
#define MONITOR_WR0_YELLOW_FLASH      (0x00000002 << 8)   //工作(黄) 灯闪
#define MONITOR_WR0_YELLOW_UNUSE      (0x00000003 << 8)   //保留

//#define MONITOR_WR0_DIALYER_OFF        (0x00000000 << 4)   //透析灯灭
//#define MONITOR_WR0_DIALYER_ON         (0x00000001 << 4)   //透析灯亮
//#define MONITOR_WR0_DIALYER_FLASH      (0x00000002 << 4)   //透析灯闪
//#define MONITOR_WR0_DIALYER_UNUSE      (0x00000003 << 4)   //保留

//#define MONITOR_WR0_PRESHOOT_OFF        (0x00000000 << 6)   //预充灯灭
//#define MONITOR_WR0_PRESHOOT_ON         (0x00000001 << 6)   //预充灯亮
//#define MONITOR_WR0_PRESHOOT_FLASH      (0x00000002 << 6)   //预充灯闪
//#define MONITOR_WR0_PRESHOOT_UNUSE      (0x00000003 << 6)   //保留

//#define MONITOR_WR0_ULF_OFF        (0x00000000 << 8)   //超滤灯灭
//#define MONITOR_WR0_ULF_ON         (0x00000001 << 8)   //超滤灯亮
//#define MONITOR_WR0_ULF_FLASH      (0x00000002 << 8)   //超滤灯闪
//#define MONITOR_WR0_ULF_UNUSE      (0x00000003 << 8)   //保留

//#define MONITOR_WR0_PASSBY_OFF        (0x00000000 << 10)   //旁通灯灭
//#define MONITOR_WR0_PASSBY_ON         (0x00000001 << 10)   //旁通灯亮
//#define MONITOR_WR0_PASSBY_FLASH      (0x00000002 << 10)   //旁通灯闪
//#define MONITOR_WR0_PASSBY_UNUSE      (0x00000003 << 10)   //保留

//#define MONITOR_WR0_ALARM_OFF        (0x00000000 << 12)   //报警灯灭
//#define MONITOR_WR0_ALARM_ON         (0x00000001 << 12)   //报警灯亮
//#define MONITOR_WR0_ALARM_FLASH      (0x00000002 << 12)   //报警灯闪
//#define MONITOR_WR0_ALARM_UNUSE      (0x00000003 << 12)   //保留
    struct WR0{     // 指示灯
        quint8  cmd;        // 命令字 0x42;
        quint32 lamb_bits;  // 指示灯位

        WR0(){ cmd = 0x42; }
    } __attribute__((packed)) wr0;

     IAP_WR9 wr9; //add wl 190729

    //////////////////////////////////////////////////////////////////////////////
    struct      // 按键
    {
        quint8  cmd;
        quint8  key;        // 按键码
    } __attribute__((packed)) rd0;

     version rd7;       //add wl 190729
     IAP_RD8 rd8; //add wl 190729
};

/**
 * 血压板
 */

struct BloodPressure        //血压计模块     //jian.huang
{
    //quint8  wr0[5];     //= {0x3A,0x17,0xA0,0x00,0x0F};     //设定初始充气压命令
   // quint8  wr1[3];     //= {0x3A,0x20,0xA6};                          //启动血压测量命令
    //quint8  wr2[5];     //= {0x3A,0x79,0x01,0x00,0x4C};          //停止血压测量命令
    //quint8  wr3[5];     //= {0x3A,0x79,0x05,0x00,0x48};          //获取袖袋压值命令
    //quint8  wr4[5];     //= {0x3A,0x79,0x03,0x00,0x4A};          //获取血压值命令
    quint8 rd0_s; //rd0 数据有效状态位
    quint8 rd1_s; //rd1 数据有效状态位
    quint8 rd2_s; //rd2 数据有效状态位
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

    struct                                //模块命令返回值
    {
        quint8 startByte;           //开始字节
        quint8 length;               //返回值长度
        quint8 data;                  //返回值数据
        quint8 chkSum;            //校验和
    } __attribute__((packed)) rd0;

    struct                                  //袖袋压返回值
    {
        quint8 startByte;           //开始字节
        quint8 length;                //返回值长度
        quint8 data_l;                //袖袋压低字节
        quint8 data_h;               //袖袋压高字节
        quint8 chkSum;             //校验和
    } __attribute__((packed)) rd1;

    struct                                    //血压值返回数据
    {
        quint8 startByte;              //开始字节
        quint8 length;                  //返回值长度
        quint8 systolic_l;              //收缩压低字节
        quint8 systolic_h;             //收缩压高字节
        quint8 diastolic_l;             //舒张压低字节
        quint8 diastolic_h;            //舒张压高字节
        quint8  __unused_1__;
        quint8 bps;                         //BP Status
        quint8  __unused_2__;
        quint8  __unused_3__;
        quint8  __unused_4__;
        quint8  __unused_5__;
        quint8  __unused_6__;
        quint8  __unused_7__;
        quint8  __unused_8__;
        quint8  __unused_9__;
        quint8 rate_l;                      //心率低字节
        quint8 rate_h;                     //心率高字节
        quint8 map_l;                     //平均动脉压低字节
        quint8 map_h;                    //平均动脉压高字节
        quint8  __unused_10__;
        quint8  __unused_11__;
        quint8  __unused_12__;
        quint8 chkSum;                  //校验和
    } __attribute__((packed)) rd2;
};

/* 在线KTV板，通用模块，见"ureasensorboardprotocol.h" */

#ifdef Q_OS_WIN
    #pragma pack(0)     //下面的恢复结构体对齐
#endif

/*4000型模块板数据*/
struct ModuleData4000
{
    DirectPump     blood;          //血泵板
    DirectPump     sub;            //置换液泵板
    UFPump         uf;             //超滤板
    HePump         hep;            //肝素板
    DriveBroad     drive;          //驱动板
    Balance        balance;        //平衡腔板
    Mixture        mix;            //配液板
    Cond           cond;           //电导板
    Heat           heat;           //加热板
    Weight         weight;         //称重板
    Power          power;          //电源板
    Monitor        monitor;        //监控板
    BloodPressure  bloodPre;       //血压计板
};

#endif // PROTOPACKET_H
