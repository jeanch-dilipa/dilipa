#ifndef BLOODTRAILBOARDPROTOCOL_H
#define BLOODTRAILBOARDPROTOCOL_H
#include <QtGlobal>

/***************************
*        血路板协议定义       *
***************************/

#ifdef Q_OS_WIN
    #pragma pack(1) /*Windows下MinGW编译，__attribute__((packed))没有效果*/
#endif

//----------------WR0--自检命令--3Byte-------------------------<
// st1
#define TDB_WR0_BP         (1 << 7)     //  0/1—血泵不自检/自检
#define TDB_WR0_FB         (1 << 6)     //  0/1—补液泵不自检/自检
#define TDB_WR0_CC         (1 << 5)     //  0/1—阻流夹不自检/自检
#define TDB_WR0_LLC        (1 << 4)     //  0/1—液面调节组件不自检/自检
#define TDB_WR0_AM         (1 << 3)     //  0/1—空气监测不自检/自检
#define TDB_WR0_BR         (1 << 2)     //  0/1—血液识别不自检/自检
#define TDB_WR0_VPL        (1 << 1)     //  0/1—静脉壶液面不自检/自检

// st2
#define TDB_WR0_PV         (1 << 7)     //  0/1—静脉压不自检/自检
#define TDB_WR0_PA         (1 << 6)     //  0/1—动脉压不自检/自检
struct TDB_WR0
{
    quint8   st1;    //self test 1
    quint8   st2;    //selt test 2
    quint8   ret;    //预留
}__attribute__((packed));

//----------------WR1--血泵控制命令--8Byte----------------------<
#define TDB_WR1_MM_NR       (0)         //正常运转模式
#define TDB_WR1_MM_PI       (1)         //管路安装缓动模式（点动）
#define TDB_WR1_MM_CPT      (2)         //泵管系数测试模式
#define TDB_WR1_MM_RET      (3)         //预留

#define TDB_WR1_CWR         (1 << 2)    //0/1-正转/反转
#define TDB_WR1_BP          (1 << 3)    //0/1-血泵关机/开机
#define TDB_WR1_FLOW        (1 << 4)    //0/1-流量累计/流量清零
#define TDB_WR1_SN          (1 << 5)    //0/1-预留/单针模式，单针模式时，主控可自由控制阻流夹

struct TDB_WR1
{
    quint8   cmd;
    quint8   ret1;   //预留
    quint16  rpm;    //目标转速比，放大10倍
    quint32  ret2;   //预留
}__attribute__((packed));

//----------------WR2--补液泵控制命令--8Byte---------------------<
#define TDB_WR2_MM_NR       0           //正常运转模式
#define TDB_WR2_MM_PI       1           //管路安装缓动模式（点动）
#define TDB_WR2_MM_CPT      2           //泵管系数测试模式
#define TDB_WR2_MM_RET      3           //预留

#define TDB_WR2_CWR         (1 << 2)    //0/1-顺时针/反时针旋转
#define TDB_WR2_BP          (1 << 3)    //0/1-补液泵关机/开机
#define TDB_WR2_FLOW        (1 << 4)    //0/1-流量累计/流量清零
struct TDB_WR2
{
    quint8   cmd;
    quint8   ret1;   //预留
    quint16  rpm;    //流量转速比，放大10倍
    quint32  ret2;   //预留
}__attribute__((packed));

//--------------WR3--阻流夹及静脉壶控制命令--4Byte-----------------<
#define TDB_WR3_OFF     (0)     //阻流夹关
#define TDB_WR3_ON      (1)     //阻流夹开

#define TDB_WR3_STOP    (0)     //静脉壶液面调节模块不动作
#define TDB_WR3_UP      (1)     //液面上升
#define TDB_WR3_DOWN    (2)     //液面下降
struct TDB_WR3
{
    quint8   cmd;
    quint8   point;
    quint16  ret;    //预留
}__attribute__((packed));

//------------------WR4--动静脉压力校正--4Byte-------------------<
#define TDB_WR4_AP      (1)     //动脉压传感器
#define TDB_WR4_VP      (2)     //静脉压传感器
#define TDB_WR4_SVP     (3)     //监控静脉压传感器

#define TDB_WR4_ZERO    (0)     //零点
#define TDB_WR4_NP      (1)     //负压
#define TDB_WR4_PP      (2)     //正压
struct TDB_WR4
{
    quint8   num;
    quint8   point;
    qint16   pressure;   //mmHg
}__attribute__((packed));

//------------------WR8--复位重启命令--0Byte--------------------<

//------------------WR9--升级命令--1026Byte--------------------<
struct TDB_WR9
{
    quint8   data_sum;         //APP数据帧总量
    quint8   data_num;         //当前数据帧编号
    quint8   data_value[1024]; //数据值，APP程序
}__attribute__((packed));

//-------------------RD0--自检信息--4Byte----------------------<
// st0
#define TDB_RD0_NOR     (0)         //正常状态 没在自检
#define TDB_RD0_RUN     (1)         //正在自检
#define TDB_RD0_FINISH  (2)         //自检完成 可能正常 可能异常

// st1
#define  TDB_RD0_BP     (1 << 7)    //0/1-血泵自检正常/自检异常
#define  TDB_RD0_FB     (1 << 6)    //0/1-补液泵自检正常/自检异常
#define  TDB_RD0_CC     (1 << 5)    //0/1-阻流夹自检正常/自检异常
#define  TDB_RD0_LLC    (1 << 4)    //0/1-液位调节组件自检正常/自检异常
#define  TDB_RD0_AM     (1 << 3)    //0/1-空气监测自检正常/自检异常
#define  TDB_RD0_BR     (1 << 2)    //0/1-血液识别自检正常/自检异常
#define  TDB_RD0_VPL    (1 << 1)    //0/1-静脉壶液面监测自检正常/自检异常

// st2
#define  TDB_RD0_PV     (1 << 7)    //0/1-静脉压自检正常/自检异常
#define  TDB_RD0_PA     (1 << 6)    //0/1-动脉压自检正常/自检异常
struct TDB_RD0
{
    quint8  st0;
    quint8  st1;
    quint8  st2;
    quint8  ret;  //预留
}__attribute__((packed));

//------------------RD1--血泵运行参数--14Byte-------------------<
#define TDB_RD1_ON_CLOSED   (1 << 0)   //0/1-盖闭合/盖开
#define TDB_RD1_STALL       (1 << 1)   //0/1-未堵转/堵转
#define TDB_RD1_CW          (1 << 2)   //0/1-正转/反转
#define TDB_RD1_ON_OFF      (1 << 3)   //0/1-泵关机/泵开机
struct TDB_RD1
{
    quint8   st1;      //血泵状态
    quint8   st2;      //状态字1,保留
    quint16  rpm_tt;   //目标转速，放大10倍
    quint16  rpm_rt;   //实时转速，放大10倍
    quint32  tr;       //累计转数(r),放大100倍
    quint32  ret;      //预留
}__attribute__((packed));

//------------------RD2--补液泵运行参数--14Byte------------------<
#define TDB_RD2_ON_CLOSED   (1 << 0)   //0/1-盖闭合/盖开
#define TDB_RD2_STALL       (1 << 1)   //0/1-未堵转/堵转
#define TDB_RD2_CW          (1 << 2)   //0/1-顺时针/反时针
#define TDB_RD2_ON_OFF      (1 << 3)   //0/1-泵关机/泵开机

struct TDB_RD2
{
    quint8   st1;      //补液泵状态
    quint8   st2;      //状态字1,保留
    quint16  rpm_tt;   //目标转速，放大10倍
    quint16  rpm_rt;   //实时转速，放大10倍
    quint32  tr;       //累计转数(r),放大100倍
    quint32  ret;      //预留
}__attribute__((packed));

//-----------------RD3--传感器及阻流夹状态--7Byte-----------------<
#define TDB_RD3_AM          (1 << 7)   //1-空气监测报警；0-未报警
#define TDB_RD3_BC          (1 << 6)   //1-血液回路有血液；0-无血液
#define TDB_RD3_VPL         (1 << 5)   //1-静脉壶液面低；0-静脉壶液面高
#define TDB_RD3_CC          (1 << 4)   //1-阻流夹关闭；0-阻流夹打开
#define TDB_RD3_BLM         (1 << 3)   //1-动静脉压模块通信异常；0-正常
struct TDB_RD3
{
    quint8   st;
    qint16   ap;   //动脉压，mmHg
    qint16   vp;   //静脉压，mmHg
    qint16   svp;  //监控静脉压，mmHg
}__attribute__((packed));

//-----------------RD4--动静脉压传感器信息--21Byte----------------<
#define TDB_RD4_APS         (1 << 7)   //0/1动脉压传感器校正值正常/异常
#define TDB_RD4_VPS         (1 << 6)   //0/1静脉压传感器校正值正常/异常
struct TDB_RD4
{
    quint8    st;      //校正状态
    qint32    pa_ad;   //动脉压传感器实时AD值
    qint32    pa_ad0;  //动脉压传感器零点AD值
    quint16   pa_k;    //动脉压传感器斜率值
    qint32    pv_ad;   //静脉压传感器实时AD值
    qint32    pv_ad0;  //静脉压传感器零点AD值
    quint16   pv_k;    //静脉压传感器斜率值
}__attribute__((packed));

//-----------------RD5--监控静脉压信息--11Byte-------------------<
#define TDB_RD5_SVP    (1 << 7) //0/1监控静脉压校正值正常/异常
struct TDB_RD5
{
    quint8   st;        //校正状态
    qint32   pvs_ad;    //监控静脉压传感器实时AD值
    qint32   pvs_ad0;   //监控静脉压传感器零点AD值
    quint16  pvs_k;     //监控静脉压传感器斜率值
}__attribute__((packed));

//-----------------RD7--软硬件版本信息--12Byte-------------------<
struct TDB_RD7
{
    quint16  id_p;      //动静脉压传感器模块部件标识码
    quint16  hv_p;      //动静脉压传感器硬件版本
    quint16  sv_p;      //动静脉压传感器软件版本
    quint16  id;        //部件标识码
    quint16  hv;        //硬件版本
    quint16  sv;        //软件版本
}__attribute__((packed));

//------------------RD8--IAP升级信息--6Byte--------------------<
struct TDB_RD8
{
    quint8   next_num;  //发送对应数据帧
    quint8   write_sum; //已写入数据量
    quint8   iap_sv;    //升级程序 软件版本
}__attribute__((packed));

#ifdef Q_OS_WIN
    #pragma pack(0)     /*恢复结构体对齐，以免影响到其他地方*/
#endif

#endif // BLOODTRAILBOARDPROTOCOL_H
