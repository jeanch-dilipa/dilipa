/*******************************************************************************
Copyright (c) 2014,重庆山外山科技有限公司技术中心
All rights reserved.
文件：    sqlbase.h
作者：    ccy
版本：    V1.0
日期：    2014-02-12
摘要：    Sqlbase类头文件，定义使用SWS6000中各个数据库的简单方法
********************************************************************************/
#ifndef SQLITE_H
#define SQLITE_H

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QString>
#include <QDateTime>
#include <QVector>
#include <QVariant>
#include <QDebug>

//患者信息数据
struct Patient_info
{
    int id_card;                     //身份证号
    QString name;                    //患者姓名
    QString sex;                     //患者性别
    int height;                      //身高
    int age;                         //年龄
    int tel;                         //患者联系电话
    QString address;                //患者住址
};

//报警的实时信息数据
struct HistoryAlarm
{
    int mode;                      //当前的治疗模式
    int runTime;                  //已运行的时间
    int alarmNum;                 //报警编号
    int A_conductivity;            //A导
    int B_conductivity;            //B导
    int C_conductivity;            //C导
    int APumpSpeed;                //A泵速度
    int BPumpSpeed;                //B泵速度
    int inFluidPre;                 //进液压力
    int outFluidPre;                //废液压力
    int QPSpeed;                    //QP泵速度
    int DPSpeed;                    //DP泵速度
    int YPSpeed;                    //YP泵速度
    int dialyzateFluidPre;          //透析液压
    int dialyzateFluidFlow;          //透析液流量
    int radiotubeStatus;            //电磁阀状态
    int WG1;                         //加热器入口温度
    int WG5;                         //透析液温度
};

//设置参数信息值
struct ParamValue
{
    int name;                                          //参数名称
    int defalutValue;                                   //参数默认值
    int saveValue;                                      //保存的值
    int realValue;                                      //参数当前值
};

/********************************************************************/

#define SQL_DATA_BASE_FILE_NAME            "SWS6000.db"

///////////////////////////////////////////
//数据库表
#define DB_HistoryAlarmTable                     "historyalarm"                //历史报警表
#define DB_SystemParamerTable                    "systemparameter"             //系统参数表
#define DB_CleanDisinfectionParameterTable       "cleandisinfectionparameter"   //清洗消毒参数表
#define DB_BoradParameterTable                   "boardparameter"               //模块参数表
#define DB_CureRealTimeTable                     "cure_realtime"               //治疗实时信息表
#define DB_PatientCureParameterTable             "patient_cure_parameter"      //患者治疗参数表
#define DB_CommonCureParameterTable              "common_cure_parameter"        //公共治疗参数表
#define DB_PatientInfoTable                      "patient_info"                 //患者个人信息表

///////////////////////////////////////////
//数字定义
#define ALARMNUM 10                                  //屏幕所能容纳的最大报警数目

//患者治疗参数
struct CureP
{
    int id_card;    //身份证号
    int UfObj;      //目标超滤量
    int CureTime;   //治疗时间
    int TempHps;    //透析液温度
    int FlowHEP;    //肝素流量
    int TotalSF;    //补液总量
    int TempSF;     //补液温度
    int FlowHDs;    //透析液流量
    int NaRatio;    //na离子浓度
    int HCO3Ratio;  //碳酸氢根离子浓度
    int StopTimHEP; //肝素提前停止时间
    int NoHEP;      //肝素化治疗
    int ModeSF;     //补液方式
    int CurveUF;    //超滤曲线
    int CurveNa;    //Na曲线
    int CurveHCO3;  //碳酸氢根离子曲线
    int CurveCom;   //组合曲线
    int CurveHE;    //肝素曲线
    int CurveTempHd; //透析液温度曲线
    int CurveFlowHds;//透析液流量曲线
    int UfRateMax;  //最大超滤速率
    int FHEP;       //肝素泵快进/快退速率
    int primeTime;   //预冲时间
    int primeTotal;  //预冲总量
    int centralSupply; //是否中央供液
    int useFilter;    //是否使用内毒素滤器
};



class Sqlbase
{
    
public:
    Sqlbase(const QString &db_name=QString(SQL_DATA_BASE_FILE_NAME));

    //执行数据命令
    QSqlQuery Query(const QString &command);
    bool Exec(const QString &command);
    void Exec(const QList<QString> &cmdList);

    //对历史报警表的操作
    QMultiMap<QString,HistoryAlarm>getHistoryAlarmDataFromDBTable(QString alarmdate,const int offset=0);
    void saveHistoryAlarmDataToDB(struct HistoryAlarm alarm);
    void deleteHistoryAlarmData(const int alarmdate);
    void deleteHistoryAlarmData();


    //对系统参数、清洗消毒参数和通用治疗参数表的操作
    void updateParameterDBData(const QString &table_name , const QString name , const int value,bool button);
    QVector <ParamValue> getParameterDataFromDBTable(const QString &table_name,const QString key);

    //对实时参数表的操作
    void saveCureRTDataToDB(const int name,int value);
    QMultiMap<QString,int> getCureRTDataFromDBTable();

    //对患者治疗参数的操作
    void saveCurePDataToDB(struct CureP cure);
    QVector <CureP>getCurePDataFromDBTable(const int id_card);
    void deleteCurePData(const int id_card);
    void deleteCurePData();

    //对患者资料信息的操作
    void savePatientInfoDataToDB(struct Patient_info info);
    void deletePatientInfoData(const int id_card);
    void deletePatientInfoData();
    QVector<Patient_info>getPatientInfoDataFromDBTable(const int id_card);

    virtual ~Sqlbase();

private:
    void createHistoryAlarmDBTable();//创建历史报警表
    void createCureRTDBTable();      //创建实时参数表
    void createPatientInfoDBTable();//创建患者信息表
    void createPatientCureDBTable();//创建患者治疗参数表

private:
   QSqlDatabase db;
   QSqlQuery query;
};

#endif // SQLITE_H


