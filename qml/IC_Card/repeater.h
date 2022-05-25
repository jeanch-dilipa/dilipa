#ifndef REPEATER_H
#define REPEATER_H

#include <QObject>
#include <QTimer>

#include "serialport.h"

class repeater : public QObject
{
    Q_OBJECT
public:
    explicit repeater(QObject *parent = nullptr);
    ~repeater();

signals:
    void signalconnectbtnclick(bool isclick);                                         /*自动连接信号*/
    void signalstartconnect();                                                        /*开始连接*/
    void signalconnectresult(bool isconnect);                                         /*串口连接结果*/
    void signaldebugserialport(QString debugmessage);                                 /*连接信息*/
    void signalICbasicinfo(int card_style,QString UID);                               /*IC卡基本信息*/
    void signaluserbasicinfo(int card_type,QString name,int gender,QString birthday,int stature,float uf_before_weight,float uf_after_weight);    /*卡基本信息显示*/
    void signalcardrecordsrequst();                                                   /*请求获取刷卡记录*/
    void signalcardcordsinfo(int currentindex,QString chargetime,QString machineID);  /*刷卡记录信息*/
    void signaltherapeuticschedule();                                                 /*请求获取治疗方案数据*/
    void signaltherepeuticscheduleinfo1(QString doctorName,QString updateTime,int therapeuticModel,int dialystateFlow,int naConcentration,
                                       int hco3Concentration,int dialystateTemp,int anticoagulationWays,int anticoagulationDose);
    void signaltherepeuticscheduleinfo2(int anticoagulationStoptime,int therapeuticTime,int ufTotal,int bloodFlow,int diluTion,int substitutionTotal,int kTv,int dryWeight);         /*治疗方案*/
    void signalwriteuserbasicinfo(int card_type,QString name,int gender,QString birthday,int stature,float uf_before_weight,float uf_after_weight);    /*写卡基本信息*/


private:


};

#endif // REPEATER_H
