#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QThread>
#include <QtSerialPort/QSerialPortInfo>
#include <QMutex>
#include <QMutexLocker>
#include <QtSerialPort/QSerialPort>
#include <QTimer>

#include "crc.h"
#include "iccarddatadefine.h"

#define DEBUG_MODEL 1

#if DEBUG_MODEL
#include <QDebug>
#define qdebug qDebug()<<__FILE__<<__LINE__
#endif

#define CardSerialport (serialport::initserialport())

class serialport : public QThread
{
    Q_OBJECT
public:
    enum connecttype
    {
        HANDSHAKE_CONNECT = 0x21,       //握手
        FORMAT_CONNECT    = 0x23,       //格式化
        WRITE_CONNECT_0   = 0x30,       //wr0
        WRITE_CONNECT_1   = 0x31,       //wr1
        READ_CONNECT_0    = 0x40,       //rd0
        READ_CONNECT_1    = 0x41        //rd1
    };

    serialport();

    static serialport *initserialport();
    static void deinitserialport();

protected:
    void run();

signals:
    void signalconnectresult(bool);                                             /*串口连接结果*/
    void signaldebugserialport(QString);                                        /*连接信息*/
    void signalgetserialport();                                                 /*开始获取串口*/
    void signalICbasicinfo(int,QString);                                        /*IC卡基本信息*/
    void signaluserbasicinfo(int,QString,int,QString,int,float,float);          /*卡基本信息显示*/
    void signalcardrecordsrequst();                                             /*请求获取刷卡记录*/
    void signalcardcordsinfo(int,QString,QString);                              /*刷卡记录信息*/
    void signaltherapeuticschedule();                                           /*请求获取治疗方案数据*/
    void signaltherepeuticscheduleinfo1(QString,QString,int,int,int,int,int,int,int);
    void signaltherepeuticscheduleinfo2(int,int,int,int,int,int,int,int);       /*治疗方案*/
    void signalwriteuserbasicinfo(int,QString,int,QString,int,float,float);     /*写卡基本信息*/

private:
    void slotgetserialportlist();                                       /*获取可用串口列表*/
    void senddatatoserialport(QByteArray senddata,bool addcrc=true);    /*串口数据发送*/
    void readserialportdata();                                          /*读取串口数据*/
    void tryconnectserialport();                                        /*尝试连接串口*/
    void serialportdisconnect(QSerialPort::SerialPortError error);      /*串口连接断开*/
    void analyseserialportdata();                                       /*解析串口数据*/
    void readuserbasicinfo();                                           /*获取卡基本信息*/
    void readcardrecords();                                             /*请求获取刷卡记录num*/
    void readcardrecord();                                              /*获取刷卡记录*/
    void reoperate();                                                   /*出错重试*/
    void readtherapeuticschedule();                                     /*获取治疗方案*/
    void writeuserbasicinfo(int card_type,QString name,int gender,QString birthday,int stature,float uf_before_weight,float uf_after_weight);   /*写卡基本信息*/

private:
    QList<QSerialPortInfo> serialportlist;                              /*串口列表*/
    int currentportindex;                                               /*当前串口序号*/
    bool isTryconnecting;                                               /*尝试连接*/
    QSerialPort *m_serial;                                              /*串口实例*/
    QByteArray serialportdata;                                          /*串口数据缓存*/
    QByteArray serialportsenddata;                                      /*发送数据*/
    QTimer *handshaketimer;                                             /*握手定时器*/
    QTimer *getovertimer;                                               /*数据传输结束定时器*/
    QTimer *replyouttimer;                                              /*连接超时定时器*/
    QTimer *serialporttimer;                                            /*串口监测定时器*/
    quint8 serialportfailnum;                                           /*串口操作失败次数*/
    quint8 cardrecordsnum;                                              /*刷卡记录总数*/
    quint8 currentcardrecordindex;                                      /*当前刷卡记录index*/
    quint8 readcardrecordsnum;                                          /*读取记录数*/


    static serialport *s_initserial;
    static QMutex s_mutex;

};

#endif // SERIALPORT_H
