#ifndef MODELBOARD_H
#define MODELBOARD_H

#include <QObject>
#include <QMutex>
#include <QMutexLocker>
#include <QTimer>
#include <QMultiMap>
#include <QPointer>

#include "controllayer/crc.h"
#include "common/common.h"
#include "common/modulecommon.h"
#include "controllayer/serialportcontrol.h"
#include "controllayer/alarmcontrol.h"

#define TAG_BLOOD_WR0                                                              0x00000001                                                                //血泵
#define TAG_FLUID_WR0                                                              0x00000002                                                                //补液泵
#define TAG_UFPUMP_WR0                                                             0x00000004                                                                //超滤泵
#define TAG_HEPUMP_WR0                                                             0x00000008                                                                //肝素泵
#define TAG_DRIVE_WR0                                                              0x00000010                                                                //驱动板
#define TAG_DRIVE_WR1                                                              0x00000020
#define TAG_MONITORBOOD_WR0                                                        0x00000040                                                                //监控板
#define TAG_BALANCE_WR0                                                            0x00000100                                                                //平衡腔
#define TAG_BALANCE_WR1                                                            0x00000200
#define TAG_BALANCE_WR2                                                            0x00000400
#define TAG_BALANCE_WR3                                                            0x00000800
#define TAG_MIXTURE_WR0                                                            0x00001000                                                                //配液板
#define TAG_MIXTURE_WR1                                                            0x00004000                                                                //标定电导
#define TAG_COND_WR0                                                               0x00002000                                                                //电导板
#define TAG_HEAT_WR0                                                               0x00010000                                                                //加热板
#define TAG_HEAT_WR1                                                               0x00020000
#define TAG_POWER_WR0                                                              0x00200000                                                                //电源板
#define TAG_POWER_WR1                                                              0x00400000
#define TAG_PILOT_WR0                                                              0x00800000                                                                //监控板
#define TAG_BLOODPRESSURE_WR0                                                      0x01000000                                                                //血压计
#define TAG_BLOODPRESSURE_WR1                                                      0x02000000
#define TAG_ONLINEKTV_WR0                                                          0x04000000                                                                //Ktv

#define INITModelBoard                                                             (modelboard::initmodelBoard())

class modelboard : public QObject
{
    Q_OBJECT
public:
    explicit modelboard(QObject *parent = nullptr);
    ~modelboard();

    static modelboard *initmodelBoard();
    static void demodelboard();
    void loadInitModel(const int addr,const int funType);                                                                                                    //装载初始化模块
    void Sync(int tags);                                                                                                                                     //同步模块数据

protected:
    void slot_analySerialportDataArrived(const QByteArray arriveData);                                                                                       //解析串口数据
    void serialportDataToModel(const int addr,const int funType,const QByteArray modelData);                                                                 //转发串口数据到相应模块
    void modelBoardDataLoading(const int addr,const int funType);                                                                                            //发送模块数据
    void slot_moduleCheckingSend();                                                                                                                          //模块数据自动检测

signals:
    void signal_modelBoardDataLoading(QByteArray);                                                                                                           //转发模块数据到相应串口

public:
    DCmotor                                                                           bloodPump;
    DCmotor                                                                           fuildPump;
    UlterFilterPlate                                                                  ufPump;
    HeparinPlate                                                                      hePump;
    DriveBoard                                                                        drive;
    Balance                                                                           balance;
    Mixture                                                                           mixture;
    Cond                                                                              cond;
    Heat                                                                              heat;
//    Weight                                                                            weight;
    Power                                                                             power;
    Monitor                                                                           monitor;
    BloodPressure                                                                     bloodPressure;
    OnlineKtv                                                                         onlineKtv;

private:
    static modelboard                                                                *s_modelboard;
    static QMutex                                                                     s_mutexLocker;

    QMultiMap<int,int>                                                                m_moduleCheckingMap;                                                   //巡检模块列表
    int                                                                               m_currentCheckNum;                                                     //当前检测
    QTimer                                                                           *m_moduleCheckingTimer;                                                 //巡检定时器

    QPointer<serialportControl>                                                       m_serialport;                                                          //串口类对象
};

#endif // MODELBOARD_H
