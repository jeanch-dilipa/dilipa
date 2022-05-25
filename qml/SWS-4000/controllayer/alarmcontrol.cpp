#include "alarmcontrol.h"

alarmcontrol *alarmcontrol::s_alarmControl=nullptr;
QMutex alarmcontrol::s_mutexLocker;

/*
功能描述：alarmcontrol类构造函数
输    入：/
输    出：/
*/
alarmcontrol::alarmcontrol()
{
#if DEBUG_MODEL || DEBUG_MODEL_ALARMCONTROL
    QString debugstr="alarmcontrol::alarmcontrol():构造函数";
    qdebug<<debugstr;
#endif

    priorityAlarmListInput();
    this->start();
}
/*
功能描述：alarmcontrol类析构函数
输    入：/
输    出：/
*/
alarmcontrol::~alarmcontrol()
{
#if DEBUG_MODEL || DEBUG_MODEL_ALARMCONTROL
    QString debugstr="alarmcontrol::~alarmcontrol():析构函数";
    qdebug<<debugstr;
#endif

    if(m_alarmListCheckTimer){delete m_alarmListCheckTimer;m_alarmListCheckTimer = nullptr;}
}
/*
功能描述：创建自身
输    入：/
输    出：/
*/
alarmcontrol *alarmcontrol::initAlarmControl()
{
#if DEBUG_MODEL || DEBUG_MODEL_ALARMCONTROL
    QString debugstr="alarmcontrol *alarmcontrol::initAlarmControl():创建自身";
    qdebug<<debugstr;
#endif

    if(!s_alarmControl)
    {
        QMutexLocker locker(&s_mutexLocker);
        if(!s_alarmControl)
        {
            s_alarmControl = new alarmcontrol();
        }
    }
    return s_alarmControl;
}
/*
功能描述：销毁自身
输    入：/
输    出：/
*/
void alarmcontrol::deAlarmControl()
{
#if DEBUG_MODEL || DEBUG_MODEL_ALARMCONTROL
    QString debugstr="void alarmcontrol::deAlarmControl()：销毁自身";
    qdebug<<debugstr;
#endif

    if(s_alarmControl)
    {
        QMutexLocker locker(&s_mutexLocker);
        if(s_alarmControl)
        {
            s_alarmControl->exit(0);
            s_alarmControl->wait();
            delete s_alarmControl;
            s_alarmControl = nullptr;
        }
    }
}
/*
功能描述：线程run
输    入：/
输    出：/
*/
void alarmcontrol::run()
{
#if DEBUG_MODEL || DEBUG_MODEL_ALARMCONTROL
    QString debugstr="void alarmcontrol::run()：线程";
    qdebug<<debugstr;
#endif

    m_lossOftime = 0;

    connect(this,&alarmcontrol::signal_receivedAlarmData,this,&alarmcontrol::slot_disposeAlarm);

    m_alarmListCheckTimer = new QTimer();
    m_alarmListCheckTimer->setInterval(1000);
    connect(m_alarmListCheckTimer,&QTimer::timeout,this,&alarmcontrol::slot_alarmListCheck);
    m_alarmListCheckTimer->start();

    /*进入事件循环*/
    this->exec();
}
/*
功能描述：设置报警优先级
输    入：/
输    出：/
*/
void alarmcontrol::priorityAlarmListInput()
{
#if DEBUG_MODEL || DEBUG_MODEL_ALARMCONTROL
    QString debugstr="void alarmcontrol::priorityAlarmListInput()：设置报警优先级";
    qdebug<<debugstr;
#endif

    /*高优先级*/
    m_hightPriorityAlarmList << SYSTEM_ERROR_CODE_MODULE_BORD_ERROR;
    /*中优先级*/
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_DATABASE_OPEN_ERROR;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_DATABASE_READ_ERROR;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_LIQUID_A_B_STRAWS_INTO_LIQUID_A_B;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_LIQUID_A_STRAWS_INTO_LIQUID_A;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_LIQUID_B_STRAWS_INTO_LIQUID_B;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_JQ_YJ1_JK_SELF_CHECK;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_FEED_WATER_SELF_CHECK;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_GAS_SELF_CHECK;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_BLOOD_LEAK_SELF_CHECK;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_BLOOD_SELF_CHECK;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_BLOOD_PUMP_SELF_CHECK;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_FLUID_INFUSION_PUMP_SELF_CHECK;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_HEPARIN_PUMP_SELF_CHECK_NOT_BOM;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_HEPARIN_PUMP_SELF_CHECK_NOT_TOP;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_CHOKED_FLOW_MONITOR_SELF_CHECK;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP100;
    m_mediumPriorityAlarmList << SYSTEM_NOTICE_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP100;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP112;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP114;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP101;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP103;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP102;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP105;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP107;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP106;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_PRESSURE_ERR;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP110;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP108;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP113;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP109;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP111;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP116;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_ENDOTOXIN_FILTE_SELF_CHECK_ZN120;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_ENDOTOXIN_FILTE_SELF_CHECK_ZN121;
    m_mediumPriorityAlarmList << SYSTEM_ERROR_CODE_DIALYSATE_TEMPERATURE_SELF_CHECK;

    /*低优先级*/
    m_lowPriorityAlarmList << SYSTEM_ERROR_CODE_DEFAULT;
    /*提示性*/
    //    m_hintPriorityAlarmList << ;
}
/*
功能描述：清除所有报警
输    入：/
输    出：/
*/
void alarmcontrol::clearAllAlarm()
{
#if DEBUG_MODEL || DEBUG_MODEL_ALARMCONTROL
    QString debugstr="void alarmcontrol::clearAllAlarm()：清除所有报警";
    qdebug<<debugstr;
#endif

    m_currentSystemAlarmMap.clear();
    emit signal_clearAllAlarm();
}
/*
功能描述：获取报警等级
输    入：alarmCode:报警号。
输    出：/
*/
int alarmcontrol::judgeAlarmGrade(const int alarmCode)
{
#if DEBUG_MODEL || DEBUG_MODEL_ALARMCONTROL
    QString debugstr="int alarmcontrol::judgeAlarmGrade(const int alarmCode)：获取报警等级";
    qdebug<<debugstr;
#endif

    int alarmGrade;
    if(m_hightPriorityAlarmList.contains(alarmCode))
    {
        alarmGrade = 1;
    }
    else if(m_mediumPriorityAlarmList.contains(alarmCode))
    {
        alarmGrade = 2;
    }
    else if(m_lowPriorityAlarmList.contains(alarmCode))
    {
        alarmGrade = 3;
    }
    else
    {
        alarmGrade = 4;
    }
    return alarmGrade;
}
/*
功能描述：报警处理
输    入：alarmCode:报警内容,alarmInterval:报警间隔,alarmEnable:报警使能。
输    出：/
*/
void alarmcontrol::slot_disposeAlarm(int alarmCode,int alarmInterval,int alarmEnable)
{
#if DEBUG_MODEL || DEBUG_MODEL_ALARMCONTROL
    QString debugstr="void alarmcontrol::slot_disposeAlarm()：报警处理";
    qdebug<<debugstr;
#endif

    if(alarmCode == SYSTEM_ERROR_CODE_DEFAULT)
    {
        clearAllAlarm();
    }
    else
    {
        if(alarmEnable == SYSTEM_ALARM_ENABLE)
        {
            if(!m_currentSystemAlarmMap.contains(alarmCode))
            {
                m_currentSystemAlarmMap.insert(alarmCode,alarmInterval);
            }
        }
        else
        {
            if(m_currentSystemAlarmMap.contains(alarmCode))
            {
                m_currentSystemAlarmMap.erase(m_currentSystemAlarmMap.find(alarmCode));
            }
        }

        int alarmGrade = judgeAlarmGrade(alarmCode);
        emit signal_showAlarmToInterface(alarmCode,alarmGrade,alarmEnable);

        if(alarmEnable == true)
        {
            sqlbase sql;
            QString cmd = QString("insert into historyTest(alarmDateTime,alarmCode,alarmGrade) values('%1',%2,%3)")\
                          .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(alarmCode).arg(alarmGrade);
            sql.Exec(cmd);
        }
    }
}
/*
功能描述：报警轮询检测
输    入：/
输    出：/
*/
void alarmcontrol::slot_alarmListCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_ALARMCONTROL
    QString debugstr="void alarmcontrol::slot_alarmListCheck()：报警轮询检测";
    qdebug<<debugstr;
#endif

    if(m_currentSystemAlarmMap.isEmpty() != true)
    {
        QMap<int,int>::iterator iter = m_currentSystemAlarmMap.begin();
        while (iter != m_currentSystemAlarmMap.end())
        {
            if(m_lossOftime % iter.value() == 0)
            {
                int alarmGrade = judgeAlarmGrade(iter.key());
                emit signal_showAlarmToInterface(iter.key(),alarmGrade);
            }
            iter++;
        }

        m_lossOftime++;
        if(m_lossOftime > 60)
        {
            m_lossOftime = 1;
        }
    }

}
