#ifndef ALARMCONTROL_H
#define ALARMCONTROL_H

#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QPointer>
#include <QTimer>

#include "common/common.h"
#include "common/systemAlarmCodes.h"
#include "controllayer/sqlbase.h"

#define INITAlarmControl (alarmcontrol::initAlarmControl())

class alarmcontrol : public QThread
{
    Q_OBJECT
public:
    explicit alarmcontrol();
    ~ alarmcontrol();

    static alarmcontrol *initAlarmControl();
    static void deAlarmControl();

protected:
    void run();
    void priorityAlarmListInput();                                                                                                      //分拣报警优先级
    void clearAllAlarm();                                                                                                               //清除所有报警
    int judgeAlarmGrade(const int alarmCode);                                                                                           //获取报警等级

    void slot_disposeAlarm(const int alarmCode,const int alarmInterval,const int alarmEnable = SYSTEM_ALARM_ENABLE);                    //报警处理
    void slot_alarmListCheck();                                                                                                         //报警轮询检测


signals:
    void signal_receivedAlarmData(int alarmCode,int alarmInterval,int alarmEnable);                                                     //报警信号传递
    void signal_clearAllAlarm();                                                                                                        //清除所有报警信号
    void signal_showAlarmToInterface(int alarmCode,int alarmGrade,int alarmEnable = SYSTEM_ALARM_ENABLE);                               //发送报警信息到界面

private:
    static alarmcontrol                                          *s_alarmControl;
    static QMutex                                                 s_mutexLocker;

    QList<int>                                                    m_hightPriorityAlarmList;                                             //高优先级报警列表
    QList<int>                                                    m_mediumPriorityAlarmList;                                            //中优先级报警列表
    QList<int>                                                    m_lowPriorityAlarmList;                                               //低优先级报警列表
    QList<int>                                                    m_hintPriorityAlarmList;                                              //提示性报警列表

    QMultiMap<int,int>                                            m_currentSystemAlarmMap;                                              //当前报警列表
    QPointer<QTimer>                                              m_alarmListCheckTimer;                                                //报警轮询定时器
    int                                                           m_lossOftime;                                                         //已流失时间
};

#endif // ALARMCONTROL_H
