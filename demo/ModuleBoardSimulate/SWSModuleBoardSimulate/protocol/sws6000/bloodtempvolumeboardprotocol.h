#ifndef BLOODTEMPVOLUMEMODOULETYPES_H
#define BLOODTEMPVOLUMEMODOULETYPES_H
#include <QtGlobal>

#ifdef Q_OS_WIN
    #pragma pack(1) /*Windows下MinGW编译，__attribute__((packed))没有效果*/
#endif

/***************************************************************************
*   血温血容量模块WR0 (血温传感器校正命令)—3 字节
****************************************************************************/
#define BTVSB_WR0_AS   (1)      //动脉血温传感器
#define BTVSB_WR0_VS   (2)      //静脉血温传感器

struct BTVSB_WR0
{
    unsigned char num;     //1-静脉血温传感器 2-动脉血温传感器
    unsigned short value;   //校正时温度值 放大100倍 精确到0.01℃ 0~5000

}__attribute__((packed));


/***************************************************************************
*   血温血容量模块WR1 (血容量控制命令)—2 字节
****************************************************************************/
#define BTVSB_WR1_SET_BV0    (1 << 2)     //0/1—无/设置当前状态为BV0
#define BTVSB_WR1_LED_ONOFF  (1 << 1)     //0/1—关闭/打开近红外LED
#define BTVSB_WR1_LED_CMD    (1 << 0)     //0/1—模块/主控控制近红外LED

struct BTVSB_WR1
{
    unsigned char cmd;     //血容量控制命令
    unsigned char reserved;  //预留

}__attribute__((packed));


/***************************************************************************
*   血温血容量模块WR2 (血容量校正命令)—3 字节
****************************************************************************/
#define BTVSB_WR2_BV0  (1)     //1: BV0
#define BTVSB_WR2_BV1  (2)     //2: BV1

struct BTVSB_WR2
{
    unsigned char num;     //1: BV0 2: BV1
    unsigned short value;  //校正值 0~65535

}__attribute__((packed));


/***************************************************************************
*   血温血容量模块WR8 (复位重启命令)—0 字节
****************************************************************************/


/***************************************************************************
*   血温血容量模块WR9 (升级命令信息)—1026 字节
****************************************************************************/
struct BTVSB_WR9
{
   unsigned char data_sum;     //APP数据帧总量
    unsigned char data_num;    //当前数据帧编号
    unsigned char data_value[1024];    //数据值，APP程序代码
}__attribute__((packed));



/***************************************************************************
*   血温血容量模块RD0 (血温传感器信息)—5 字节
****************************************************************************/
#define BTVSB_RD0_AS_ERR   (1 << 0)    //0/1—动脉血温传感器正常/异常
#define BTVSB_RD0_VS_ERR   (1 << 1)    //0/1—静脉血温传感器正常/异常

struct BTVSB_RD0
{
    unsigned char  st;    //血温传感器状态 正常/异常
    unsigned short at;    //动脉血温，血液温度 放大100倍 精确到0.01℃ 0~5000
    unsigned short vt;    //静脉血温，放大100倍 精确到0.01℃ 0~5000

}__attribute__((packed));


/***************************************************************************
*   血温血容量模块RD1 (血温传感器校正信息)—5 字节
****************************************************************************/
#define BTVSB_RD1_AS_CR_ERR   (1 << 0)    //0/1—动脉血温传感器正常/异常
#define BTVSB_RD1_VS_CR_ERR   (1 << 1)    //0/1—静脉血温传感器校正正常/异常

struct BTVSB_RD1
{
    unsigned char  err;        //血温传感器校正状态 正常/异常
    short at_ea;    //动脉血温传感器校正点误差，放大100倍，精确到0.01℃ -1000~1000
    short vt_ea;     //静脉血温传感器校正点误差，放大100倍，精确到0.01℃ -1000~1000

}__attribute__((packed));


/***************************************************************************
*   血温血容量模块RD2 (血容量传感器信息)—9 字节
****************************************************************************/
#define BTVSB_RD2_BV_ST     (1 << 3)    //0/1—血容量传感器正常/异常
#define BTVSB_RD2_BD_ST     (1 << 2)    //0/1—未检测到/检测到血液
#define BTVSB_RD2_COVER_ST  (1 << 1)    //0/1—监测盖关闭/打开
#define BTVSB_RD2_LED_ST    (1 << 0)    //0/1—近红外LED关闭/打开

struct BTVSB_RD2
{
    unsigned char  st;      //血温量传感器信息
    unsigned short bv_v;    //受光电压，mV 0~5000
    unsigned short  bv;     //血容量
    unsigned short bv0;     //初始化血容量
    unsigned short rbv;     //以BV0为基点的相对血容量，9012表示90.12% 放大100倍 0~15000 RBV=BV/BV0

}__attribute__((packed));


/***************************************************************************
*   血温血容量模块RD3 (血容量传感器校正信息)—9 字节
****************************************************************************/
#define BTVSB_RD3_BVS_CR_ERR   (1 << 0)    //0/1—血容量传感器校正正常/异常

struct BTVSB_RD3
{
    unsigned char   err;    //血温量传感器信息
    unsigned short  bv0;    //校正BV0的值  0～65535
    unsigned short  bv1;    //校正BV1的值  0～65535
    unsigned short  bv0_v;  //校正BV0时受光电压，mV
    unsigned short  bv1_v;  //校正BV1时受光电压，mV

}__attribute__((packed));


/***************************************************************************
*   血温血容量模块RD7 (软硬件版本信息)—6 字节
****************************************************************************/
struct BTVSB_RD7
{
    unsigned short   id;              //血温传感器模块 部件标识码
    unsigned short   hv;              //血温传感器模块 硬件版本
    unsigned short   sv ;             //血温传感器模块 软件版本

}__attribute__((packed));

/***************************************************************************
*   血温血容量模块RD8（升级状态信息）-3字节
****************************************************************************/
struct BTVSB_RD8
{
    unsigned char next_num;    //发送对应数据帧
    unsigned char write_sum;    //已写入数据量
    unsigned char iap_sv;         //升级程序 软件版本

}__attribute__((packed));

#ifdef Q_OS_WIN
    #pragma pack(0)     //恢复结构体对齐，以免影响到其他地方
#endif

#endif // BLOODTEMPVOLUMEMODOULETYPES_H
