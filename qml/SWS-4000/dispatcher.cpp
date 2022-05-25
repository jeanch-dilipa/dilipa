#include "dispatcher.h"

/*
功能描述：Dispatcher类构造函数（中央调度）
输    入：/
输    出：/
*/
Dispatcher::Dispatcher(QObject *parent) : QObject(parent)
{
#if DEBUG_MODEL || DEBUG_MODEL_DISPATCHER
    QString debugstr="Dispatcher::Dispatcher(QObject *parent) : QObject(parent):构造函数";
    qdebug<<debugstr;
#endif

    /*alarmcontrol*/
    m_alarmControl = INITAlarmControl;
    connect(m_alarmControl,&alarmcontrol::signal_clearAllAlarm,this,&Dispatcher::signal_clearAllAlarm);
    connect(m_alarmControl,&alarmcontrol::signal_showAlarmToInterface,this,&Dispatcher::signal_showAlarmToInterface);

    /*dataDealThread*/
    createDataDealThread();

    /*startInterface*/
    m_startInterface = INITStartInterface;
    connect(m_startInterface,&startInterface::signal_createStartInterface,this,&Dispatcher::signal_createStartInterface);

    /*systemSelfCheck*/
    connect(this,&Dispatcher::signal_createSystemSelfCheck,this,&Dispatcher::createSystemSelfCheck);
    connect(this,&Dispatcher::signal_destroySystemSelfCheck,this,&Dispatcher::destroySystemSelfCheck);

    /*schema*/
    connect(this,&Dispatcher::signal_createSchema,this,&Dispatcher::createSchema);
    connect(this,&Dispatcher::signal_destroySchema,this,&Dispatcher::destroySchema);

    /*correct*/
    connect(this,&Dispatcher::signal_createCorrectInterface,this,&Dispatcher::createCorrectInterface);
    connect(this,&Dispatcher::signal_destroyCorrectInterface,this,&Dispatcher::destroyCorrectInterface);

    /*detect*/
    connect(this,&Dispatcher::signal_createDetectInterface,this,&Dispatcher::createDetectInterface);
    connect(this,&Dispatcher::signal_destroyDetectInterface,this,&Dispatcher::destroyDetectInterface);
}
/*
功能描述：Dispatcher类析构函数
输    入：/
输    出：/
*/
Dispatcher::~Dispatcher()
{
#if DEBUG_MODEL || DEBUG_MODEL_DISPATCHER
    QString debugstr="Dispatcher::~Dispatcher():析构函数";
    qdebug<<debugstr;
#endif

    if(m_startInterface)delete m_startInterface;
    if(m_systemSelfCheck)delete m_systemSelfCheck;
    if(m_detectInterface)delete m_detectInterface;
    if(m_correctInterface)delete m_correctInterface;
    g_data.~publicData();
    m_alarmControl->deAlarmControl();
    m_dataDealThread->deDataDealThread();
}
/*
功能描述：创建自检
输    入：/
输    出：/
*/
void Dispatcher::createSystemSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_DISPATCHER
    QString debugstr="Dispatcher::createSystemSelfCheck():创建自检";
    qdebug<<debugstr;
#endif
    m_systemSelfCheck = INITSystemSelfCheck;

    connect(this,&Dispatcher::signal_reSelfCheck,m_systemSelfCheck,&systemSelfCheck::signal_reSelfCheck);

    connect(m_systemSelfCheck,&systemSelfCheck::signal_SelfCheckStart,this,&Dispatcher::signal_SelfCheckStart);
    connect(m_systemSelfCheck,&systemSelfCheck::signal_SelfCheckResult,this,&Dispatcher::signal_SelfCheckResult);
}
/*
功能描述：销毁自检
输    入：/
输    出：/
*/
void Dispatcher::destroySystemSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_DISPATCHER
    QString debugstr="Dispatcher::destroySystemSelfCheck():销毁自检";
    qdebug<<debugstr;
#endif

    m_systemSelfCheck->deSystemSelfCheck();
}
/*
功能描述：创建模式
输    入：/
输    出：/
*/
void Dispatcher::createSchema()
{
#if DEBUG_MODEL || DEBUG_MODEL_DISPATCHER
    QString debugstr="Dispatcher::createSchema():创建模式";
    qdebug<<debugstr;
#endif
}
/*
功能描述：销毁模式
输    入：/
输    出：/
*/
void Dispatcher::destroySchema()
{
#if DEBUG_MODEL || DEBUG_MODEL_DISPATCHER
    QString debugstr="Dispatcher::destroySchema():销毁模式";
    qdebug<<debugstr;
#endif
}
/*
功能描述：创建校正
输    入：/
输    出：/
*/
void Dispatcher::createCorrectInterface()
{
#if DEBUG_MODEL || DEBUG_MODEL_DISPATCHER
    QString debugstr="Dispatcher::createCorrectInterface():创建校正";
    qdebug<<debugstr;
#endif
}
/*
功能描述：销毁校正
输    入：/
输    出：/
*/
void Dispatcher::destroyCorrectInterface()
{
#if DEBUG_MODEL || DEBUG_MODEL_DISPATCHER
    QString debugstr="Dispatcher::destroyCorrectInterface():销毁校正";
    qdebug<<debugstr;
#endif
}
/*
功能描述：创建检测
输    入：/
输    出：/
*/
void Dispatcher::createDetectInterface()
{
#if DEBUG_MODEL || DEBUG_MODEL_DISPATCHER
    QString debugstr="Dispatcher::createDetectInterface():创建检测";
    qdebug<<debugstr;
#endif
}
/*
功能描述：销毁检测
输    入：/
输    出：/
*/
void Dispatcher::destroyDetectInterface()
{
#if DEBUG_MODEL || DEBUG_MODEL_DISPATCHER
    QString debugstr="Dispatcher::destroyDetectInterface():销毁检测";
    qdebug<<debugstr;
#endif
}
/*
功能描述：创建数据处理线程
输    入：/
输    出：/
*/
void Dispatcher::createDataDealThread()
{
#if DEBUG_MODEL || DEBUG_MODEL_DISPATCHER
    QString debugstr="void Dispatcher::createDataDealThread():创建数据处理线程";
    qdebug<<debugstr;
#endif

    m_dataDealThread = INITDataDealThread;

//    connect(this,)
}
/*
功能描述：销毁数据处理线程
输    入：/
输    出：/
*/
void Dispatcher::destroyDataDealThread()
{
#if DEBUG_MODEL || DEBUG_MODEL_DISPATCHER
    QString debugstr="void Dispatcher::destroyDataDealThread():销毁数据处理线程";
    qdebug<<debugstr;
#endif

    m_dataDealThread->deDataDealThread();
}
