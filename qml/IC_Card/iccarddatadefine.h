#ifndef ICCARDDATADEFINE_H
#define ICCARDDATADEFINE_H

#include <QtGlobal>
#include <QDate>

namespace CARDDATA
{
#pragma pack(1)     //字节对齐方式

//#pragma pack (n)             作用：C编译器将按照n个字节对齐。
//#pragma pack ()               作用：取消自定义字节对齐方式。
//#pragma  pack (push,1)     作用：是指把原来对齐方式设置压栈，并设新的对齐方式设置为一个字节对齐
//#pragma pack(pop)            作用：恢复对齐状态

typedef enum
{
    IC_CARD  = 0,       //ic卡
    CPU_CARD = 1        //cpu卡
}CARD_TYPE_STYLE;

struct RD0_CARD_STYLE
{
    quint8  card_style;
    quint32 UID;
}__attribute__((packed));

/*----------------协议版本：1字节+2字节CRC---------------*/
#define PROTOCOL_ADDRESS    0x0000                  /*协议版本地址*/
#define PROTOCOL_VERSION    1                       /*协议版本*/

/*----------------使用者基本信息：62字节+2字节CRC---------------*/
#define USER_BASIC_INFO_ADDRESS     0x0010          /*使用者基本信息地址*/

typedef enum
{
    unknown = 0,         //未知
    man     = 1,         //男
    woman   = 2          //女
}gender_type;

typedef enum
{
    unopencard = 0x0000,         //未开卡
    patientcard = 0x6170,        //患者卡
    maintenancecard = 0x6e65     //维护卡
}card_type;

struct USER_BASIC_INFO
{
    quint16     card_type;              //卡类型 card_type
    char        name[50];
    quint8      gender;                 //性别 gender_type
    quint32     birthday;
    quint8      stature;
    quint16     uf_before_weight;
    quint16     uf_after_weight;
}__attribute__((packed));

/*--------------治疗方案：78字节+2字节CRC----------------*/
#define THERAPEUTIC_SCHEDULE_ADDRESS    0x0100          /*治疗方案地址*/
struct THERAPEUTIC_SCHEDULE
{
    char        doctorname[50];
    quint32     updatetime;
    quint8      therapeuticmodel;
    quint16     dialystateflow;
    quint8      Naconcentration;
    quint8      HCO3concentration;
    quint16     dialystatetemp;
    quint8      anticoagulationways;
    quint8      anticoagulationdose;
    quint8      anticoagulationstoptime;
    quint16     therapeutictime;
    quint16     uftotal;
    quint16     bloodflow;
    quint8      dilution;
    quint32     substitutiontotal;
    quint8      Ktv;
    quint16     dryweight;
}__attribute__((packed));


struct CardUserInfo                     //IC卡用户信息
{
    CardUserInfo()
    {
        clear();
    }

    void clear()
    {
        type = CARDDATA::unopencard;
        name.clear();
        gender = CARDDATA::unknown;
        birth = QDate();
        height = 0;
        beforeWeight = 0.0f;
        afterWeight = 0.0f;
    }

    CARDDATA::card_type type;         //卡类型
    QString            name;          //姓名
    CARDDATA::gender_type   gender;        //性别
    QDate              birth;         //出生日期
    int                height;        //身高，cm
    float              beforeWeight;  //透析前体重，kg
    float              afterWeight;   //透析后体重，kg
};

/*----------------刷卡记录---9字节（一个记录）--------------*/
#define CREDIT_CARD_RECORDS_START_ADDRESS     0x0400          /*刷卡记录起始地址*/
#define CARDIT_CARD_RECORDS_NUM                 100           /*刷卡记录有效个数*/
#define CARDIT_CARD_RECORDS_ADDR(point)       (CREDIT_CARD_RECORDS_START_ADDRESS+((point)*9+4))   /*point个刷卡记录开始地址*/

/*----------------刷卡记录位置、个数：2字节+2字节CRC---------*/
struct  CREDIT_CARD_RECORDS_ADDR
{
    quint8      currentrecords;
    quint8      recordscount;
}__attribute__((packed));

/*---------------刷卡记录：9字节--------------------------*/
struct CREDIT_CARD_RDCORDS
{
    quint32     chargetime;
    quint8      machineID[5];
}__attribute__((packed));

}

#endif // ICCARDDATADEFINE_H
