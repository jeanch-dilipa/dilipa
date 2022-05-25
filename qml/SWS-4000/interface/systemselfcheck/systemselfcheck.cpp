#include "systemselfcheck.h"

systemSelfCheck *systemSelfCheck::s_systemSelfCheck=nullptr;
QMutex systemSelfCheck::s_mutexLocker;

/*
功能描述：systemSelfCheck类构造函数
输    入：/
输    出：/
*/
systemSelfCheck::systemSelfCheck(QObject *parent) : QObject(parent)
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="systemSelfCheck::systemSelfCheck(QObject *parent) : QObject(parent):构造函数";
    qdebug<<debugstr;
#endif

    /*自检过程量*/
    m_feedWaterSelfCheckTimes = 0;
    m_countSustionYG2YG4Times = 0;
    m_YG3moreThan110kpaTimes = 0;
    m_YG3ChangeValue = 0;
    m_preValue = 0;
    m_YG3Above90KpaTimes = 0;
    m_endotoxinCheckTimes = 0;
    m_TempChangeValue = 0;
    m_preTempValue = 0;

    /*是否开始过自检*/
    m_checkItem_monitor = false;
    m_checkItem_bloodPump = false;
    m_checkItem_fluidPump = false;
    m_checkItem_heparPump = false;
    m_checkItem_choke = false;
    m_checkItem_balance = false;
    m_checkItem_endotoxin = false;
    m_checkItem_temp = false;
    m_checkItem_liquor = false;

    /*重复检测界定*/
    m_isHeparinPumpFirstCheck = true;
    m_isChokeFirstCheck = true;
    m_isCheckYG3Reveal = true;
    m_isCheckTempReveal = true;
    m_reCheckEndotoxin15 = true;

    /*装载欲自检项*/
    m_selfCheckItemList << CHECK_ITEM_OF_WATER_SYSTEM;
    m_selfCheckItemList << CHECK_ITEM_OF_BALANCE_SYSTEM;
    m_selfCheckItemList << CHECK_ITEM_OF_HEAT_SYSTEM;
    m_selfCheckItemList << CHECK_ITEM_OF_MIXED_SYSTEM;
    m_selfCheckItemList << CHECK_ITEM_OF_SUBPRESSURE_SYSTEM;
    m_selfCheckItemList << CHECK_ITEM_OF_ULTRATILTRATION_SYSTEM;
//    m_selfCheckItemList << CHECK_ITEM_OF_WEIGHT_SYSTEM;
    m_selfCheckItemList << CHECK_ITEM_OF_BLOOD_SYSTEM;
    m_selfCheckItemList << CHECK_ITEM_OF_HEPARIN_SYSTEM;
    m_selfCheckItemList << CHECK_ITEM_OF_MONITOR_SYSTEM;
    m_selfCheckItemList << CHECK_ITEM_OF_CHOKED_FLOW_SYSTEM;
    m_selfCheckItemList << CHECK_ITEM_OF_FLUID_INFUSION_SYSTEM;
    m_selfCheckItemList << CHECK_ITEM_OF_ENDOTOXIN_SYSTEM;

    m_alarmcontrol = INITAlarmControl;
    connect(this,&systemSelfCheck::signal_sendAlarmData,m_alarmcontrol,&alarmcontrol::signal_receivedAlarmData);

    connect(this,&systemSelfCheck::signal_reSelfCheck,this,&systemSelfCheck::slot_judgeReSelfCheck);

    /*通信注册*/
    connectOutSignal();
    /*开始自检*/
    QTimer::singleShot(0,this,SLOT(slot_systemSelfChekStart()));

    /*AB液管检测定时器*/
    m_ABSuctionTubeStatus = new QTimer();
    m_ABSuctionTubeStatus->setInterval(SYSTEM_SELF_CHECK_ABSTATUS_CHECK_TIME*1000);

    m_balanceJudgeTimer = new QTimer();
    m_balanceSustionTimer = new QTimer();
}
/*
功能描述：systemSelfCheck类析构函数
输    入：/
输    出：/
*/
systemSelfCheck::~systemSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="systemSelfCheck::~systemSelfCheck():析构函数";
    qdebug<<debugstr;
#endif
    m_alarmcontrol = nullptr;
    if(m_ABSuctionTubeStatus){delete m_ABSuctionTubeStatus;m_ABSuctionTubeStatus = nullptr;}
    if(m_balanceJudgeTimer){delete m_balanceJudgeTimer;m_balanceJudgeTimer = nullptr;}
    if(m_balanceSustionTimer){delete m_balanceSustionTimer;m_balanceSustionTimer = nullptr;}
}
/*
功能描述：创建自身
输    入：/
输    出：/
*/
systemSelfCheck *systemSelfCheck::initSystemSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="systemSelfCheck *systemSelfCheck::systemSelfCheck():创建自身";
    qdebug<<debugstr;
#endif

    if(!s_systemSelfCheck)
    {
        QMutexLocker locker(&s_mutexLocker);
        if(!s_systemSelfCheck)
        {
            s_systemSelfCheck = new systemSelfCheck();
        }
    }
    return s_systemSelfCheck;
}
/*
功能描述：销毁自身
输    入：/
输    出：/
*/
void systemSelfCheck::deSystemSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::deSystemSelfCheck()：销毁自身";
    qdebug<<debugstr;
#endif

    if(nullptr != s_systemSelfCheck)
    {
        QMutexLocker locker(&s_mutexLocker);
        if(nullptr != s_systemSelfCheck)
        {
            delete s_systemSelfCheck;
            s_systemSelfCheck = nullptr;
        }
    }
}
/*
功能描述：连接外部信号
输    入：/
输    出：/
*/
void systemSelfCheck::connectOutSignal()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::connectOutSignal()：连接外部信号";
    qdebug<<debugstr;
#endif

    //注册消息队列  注意：在构造函数中注册消息队列（21个），在析构函数中取消队列注册（21个）
    g_data.module->loadInitModel(BLOOD_PUMP_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);

    g_data.module->loadInitModel(FLUID_INFUSION_PUMP_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);

    g_data.module->loadInitModel(ULTRAFILTRATION_PUMP_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);

    g_data.module->loadInitModel(HEPARIN_PUMP_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_0);

    g_data.module->loadInitModel(DRIVER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_0);
    g_data.module->loadInitModel(DRIVER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_1);
    g_data.module->loadInitModel(DRIVER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_2);

    g_data.module->loadInitModel(BALANCE_CHAMBER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_0);
    g_data.module->loadInitModel(BALANCE_CHAMBER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_1);
    g_data.module->loadInitModel(BALANCE_CHAMBER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_2);
    g_data.module->loadInitModel(BALANCE_CHAMBER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_3);

    g_data.module->loadInitModel(MIXED_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);
    g_data.module->loadInitModel(MIXED_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_1);

    g_data.module->loadInitModel(CONDUCTANCE_BOARD_C_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);
    g_data.module->loadInitModel(CONDUCTANCE_BOARD_C_ADDRESS,SYSTEM_BUS_READ_COMMAND_1);

    g_data.module->loadInitModel(KEYPRESS_BOARD_ADDRESS,SYSTEM_BUS_KEY_PRESSED_COMMAND);

    g_data.module->loadInitModel(HEATER_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);

    g_data.module->loadInitModel(POWER_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);

    g_data.module->loadInitModel(BLOOD_PRESSURE_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);
    g_data.module->loadInitModel(BLOOD_PRESSURE_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_1);

    g_data.module->loadInitModel(ONLINE_KTV_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);

}
/*
功能描述：开始自检
输    入：/
输    出：/
*/
void systemSelfCheck::slot_systemSelfChekStart()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_systemSelfChekStart()：开始自检";
    qdebug<<debugstr;
#endif

    memset(&g_data.module->drive.wr0,0,sizeof(g_data.module->drive.wr0));
    /*关闭平衡、配液、超滤、加热*/
    g_data.module->balance.wr0.cmd_1 = g_data.module->balance.Balance_WR0_WORK_MODEL_STOP;
    g_data.module->mixture.wr0.cmd_1 &= 0xF0;
    g_data.module->mixture.wr0.cmd_1 |= g_data.module->mixture.Mixture_WR0_WORK_MOD_STOP;
    g_data.module->ufPump.wr0.cmd_1 &= ~g_data.module->ufPump.UlterFilterPlate_WR0_SR;
    g_data.module->heat.wr0.cmd_1 &= ~g_data.module->heat.Heat_WR0_SR;

    g_data.module->Sync(TAG_BALANCE_WR0 | TAG_MIXTURE_WR0 | TAG_UFPUMP_WR0 | TAG_HEAT_WR0);

    /*启动供水系统检测*/
    feedWaterSelfCheck();

    /*巡检A\B吸管位置*/
    connect(m_ABSuctionTubeStatus,&QTimer::timeout,this,&systemSelfCheck::slot_judgeABSutionTubeStatus);
    m_ABSuctionTubeStatus->start();
}
/*
功能描述：判断重新自检项
输    入：chenckItem:自检项
输    出：/
*/
void systemSelfCheck::slot_judgeReSelfCheck(const int checkItem)
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeReSelfCheck(const int checkItem)：判断重新自检项";
    qdebug<<debugstr;
#endif

    switch (checkItem)
    {
    case CHECK_ITEM_OF_WATER_SYSTEM:
        feedWaterSelfCheck();
        break;
    case CHECK_ITEM_OF_BALANCE_SYSTEM:
        balanceSelfCheck();
        break;
    case CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_11:
    case CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_21_1:
    case CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_21_2:
        slot_judgeBalanceSelfCheck_11();
        break;
    case CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_22_1:
    case CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_22_2:
        slot_balanceSelfCheck_22_1();
        break;
    case CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_2:
    case CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_3:
    case CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_4:
    case CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_5:
    case CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_6:
        slot_balanceSelfCheck_32_1();
        break;
    case CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_2:
    case CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_3:
    case CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_4:
    case CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_5:
    case CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_6:
        slot_balanceSelfCheck_33_1();
        break;
    case CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_36:
    case CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_36_1:
    case CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_36_2:
        slot_balanceSelfCheck_36();
        break;
    case CHECK_ITEM_OF_HEAT_SYSTEM:
        dialystateTempSelfCheck();
        break;
    case CHECK_ITEM_OF_MIXED_SYSTEM:
        break;
    case CHECK_ITEM_OF_SUBPRESSURE_SYSTEM:
        balanceSelfCheck();
        break;
    case CHECK_ITEM_OF_ULTRATILTRATION_SYSTEM:
        slot_balanceSelfCheck_36();
        break;
//    case CHECK_ITEM_OF_WEIGHT_SYSTEM:
//        break;
    case CHECK_ITEM_OF_BLOOD_SYSTEM:
        bloodPumpSelfCheck();
        break;
    case CHECK_ITEM_OF_HEPARIN_SYSTEM:
        heparinPumpSelfCheck();
        break;
    case CHECK_ITEM_OF_MONITOR_SYSTEM:
        monitorSelfCheck();
        break;
    case CHECK_ITEM_OF_CHOKED_FLOW_SYSTEM:
        chokedFlowMonitorSelfCheck();
        break;
    case CHECK_ITEM_OF_FLUID_INFUSION_SYSTEM:
        fluidinfusionPumpSelfCheck();
        break;
    case CHECK_ITEM_OF_ENDOTOXIN_SYSTEM:
    case CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_11:
    case CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_1:
    case CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_2:
    case CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_3:
    case CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_4:
    case CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_5:
    case CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_13:
    case CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_14:
    case CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_15_1:
    case CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_15_2:
        endotoxinSelfCheck();
        break;
    }
}
/*
功能描述：供水检测
输    入：/
输    出：/
*/
void systemSelfCheck::feedWaterSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::systemSelfChekStart()：供水检测";
    qdebug<<debugstr;
#endif

    /*清除供水自检相关报警*/
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_JQ_YJ1_JK_SELF_CHECK,INTERVAL_10,SYSTEM_ALARM_DISABLE);
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_FEED_WATER_SELF_CHECK,INTERVAL_10,SYSTEM_ALARM_DISABLE);

    m_feedWaterSelfCheckTimes = FEED_WATER_SELF_CHECK_TIMES;

    emit signal_SelfCheckStart(CHECK_ITEM_OF_WATER_SYSTEM,SYSTEM_SELF_CHECK_WATER_CHECK_MAX_TIME*1000);
    g_data.module->drive.wr0.cmd_1 |= g_data.module->drive.DriveBoard_WR0_CTRL_SV | g_data.module->drive.DriveBoard_WR0_SV1_L;
    g_data.module->drive.wr0.cmd_1 &= g_data.module->drive.DriveBoard_WR0_SV1_H;
    g_data.module->Sync(TAG_DRIVE_WR0);

    QTimer::singleShot(SYSTEM_SELF_CHECK_WATER_CHECK_MAX_TIME/2*1000,this,SLOT(slot_judgeFeedWaterSelfCheck()));
}
/*
功能描述：供水自检判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeFeedWaterSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeFeedWaterSelfCheck()：供水自检判断";
    qdebug<<debugstr;
#endif

    bool status_YK = (bool)(g_data.module->drive.rd0.std_1 & g_data.module->drive.DriveBoard_RD0_YK);
    bool status_YJ1 = (bool)(g_data.module->drive.rd0.std_1 & g_data.module->drive.DriveBoard_RD0_YJ1);

    if(status_YK == true && status_YJ1 == false)
    {
        emit signal_SelfCheckResult(CHECK_ITEM_OF_WATER_SYSTEM,SELF_CHECK_CORRECT);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_WATER_SYSTEM) == true)
        {
            m_selfCheckItemList.removeOne(CHECK_ITEM_OF_WATER_SYSTEM);
        }

        if(m_checkItem_monitor == false)
        {
            /*启动监控系统检测*/
            monitorSelfCheck();
        }
        if(m_checkItem_bloodPump == false)
        {
            /*启动血路系统检测*/
            bloodPumpSelfCheck();
        }
        if(m_checkItem_fluidPump == false)
        {
            /*补液系统检测*/
            fluidinfusionPumpSelfCheck();
        }
        if(m_checkItem_heparPump == false)
        {
            /*抗凝系统检测*/
            heparinPumpSelfCheck();
        }
        /*启动内毒素自检*/
        if(m_checkItem_temp == false)
        {
            dialystateTempSelfCheck();
        }
    }
    else
    {
        m_feedWaterSelfCheckTimes--;
        if(m_feedWaterSelfCheckTimes < 0)
        {
            emit signal_SelfCheckResult(CHECK_ITEM_OF_WATER_SYSTEM,SELF_CHECK_ERROR);
            if(m_selfCheckItemList.contains(CHECK_ITEM_OF_WATER_SYSTEM) == false)
            {
                m_selfCheckItemList << CHECK_ITEM_OF_WATER_SYSTEM;
            }

            if(status_YK == false && status_YJ1 == false)
            {
                emit signal_sendAlarmData(SYSTEM_ERROR_CODE_JQ_YJ1_JK_SELF_CHECK,INTERVAL_10,SYSTEM_ALARM_ENABLE);
            }
            else
            {
                emit signal_sendAlarmData(SYSTEM_ERROR_CODE_FEED_WATER_SELF_CHECK,INTERVAL_10,SYSTEM_ALARM_ENABLE);
            }
        }
        else
        {
            QTimer::singleShot(1000,this,SLOT(slot_judgeFeedWaterSelfCheck()));
        }
    }
}

void systemSelfCheck::slot_judgeBloodPumpSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeBloodPumpSelfCheck()：血路系统自检判断";
    qdebug<<debugstr;
#endif

    bool status_ST = (bool)(g_data.module->bloodPump.rd0.std_1 & g_data.module->bloodPump.DCmotor_RD0_ST);

    if(status_ST == true)
    {
        emit signal_SelfCheckResult(CHECK_ITEM_OF_BLOOD_SYSTEM,SELF_CHECK_CORRECT);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_BLOOD_SYSTEM) == true)
        {
            m_selfCheckItemList.removeOne(CHECK_ITEM_OF_BLOOD_SYSTEM);
        }
    }
    else
    {
        emit signal_SelfCheckResult(CHECK_ITEM_OF_BLOOD_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_BLOOD_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_BLOOD_SYSTEM;
        }
        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BLOOD_PUMP_SELF_CHECK,INTERVAL_10,SYSTEM_ALARM_ENABLE);
    }

    /*正常模式关闭血泵*/
    g_data.module->bloodPump.wr0.cmd_1 &= ~g_data.module->bloodPump.DCmotor_WR0_M1 & ~g_data.module->bloodPump.DCmotor_WR0_M0 & ~g_data.module->bloodPump.DCmotor_WR0_SR;
    g_data.module->Sync(TAG_BLOOD_WR0);
}
/*
功能描述：补液系统自检判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeFluidinfusionPumpSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeFluidinfusionPumpSelfCheck()：补液系统自检判断";
    qdebug<<debugstr;
#endif

    bool status_ST = (bool)(g_data.module->fuildPump.rd0.std_1 & g_data.module->fuildPump.DCmotor_RD0_ST);

    if(status_ST == true)
    {
        emit signal_SelfCheckResult(CHECK_ITEM_OF_FLUID_INFUSION_SYSTEM,SELF_CHECK_CORRECT);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_FLUID_INFUSION_SYSTEM) == true)
        {
            m_selfCheckItemList.removeOne(CHECK_ITEM_OF_FLUID_INFUSION_SYSTEM);
        }
    }
    else
    {
        emit signal_SelfCheckResult(CHECK_ITEM_OF_FLUID_INFUSION_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_FLUID_INFUSION_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_FLUID_INFUSION_SYSTEM;
        }
        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_FLUID_INFUSION_PUMP_SELF_CHECK,INTERVAL_10,SYSTEM_ALARM_ENABLE);
    }

    /*正常模式关闭补液泵*/
    g_data.module->fuildPump.wr0.cmd_1 &= ~g_data.module->fuildPump.DCmotor_WR0_M1 & ~g_data.module->fuildPump.DCmotor_WR0_M0 & ~g_data.module->fuildPump.DCmotor_WR0_SR;
    g_data.module->Sync(TAG_FLUID_WR0);
}
/*
功能描述：抗凝系统自检判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeHeparinPumpSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeHeparinPumpSelfCheck()：抗凝系统自检判断";
    qdebug<<debugstr;
#endif

    bool status_BOM = (bool)(g_data.module->hePump.rd0.std_1 & g_data.module->hePump.HeparinPlate_RD0_BOM);
    bool status_TOP = (bool)(g_data.module->hePump.rd0.std_1 & g_data.module->hePump.HeparinPlate_RD0_TOP);

    if(m_isHeparinPumpFirstCheck == true)
    {
        if(status_BOM == true && status_TOP == false)
        {
            m_isHeparinPumpFirstCheck = false;
            heparinPumpSelfCheck();
        }
        else
        {
            emit signal_SelfCheckResult(CHECK_ITEM_OF_HEPARIN_SYSTEM,SELF_CHECK_ERROR);
            if(m_selfCheckItemList.contains(CHECK_ITEM_OF_HEPARIN_SYSTEM) == false)
            {
                m_selfCheckItemList << CHECK_ITEM_OF_HEPARIN_SYSTEM;
            }
            emit signal_sendAlarmData(SYSTEM_ERROR_CODE_HEPARIN_PUMP_SELF_CHECK_NOT_BOM,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        }
    }
    else
    {
        if(status_BOM == false && status_TOP == true)
        {
            m_isHeparinPumpFirstCheck = true;
            emit signal_SelfCheckResult(CHECK_ITEM_OF_HEPARIN_SYSTEM,SELF_CHECK_CORRECT);
            if(m_selfCheckItemList.contains(CHECK_ITEM_OF_HEPARIN_SYSTEM) == true)
            {
                m_selfCheckItemList.removeOne(CHECK_ITEM_OF_HEPARIN_SYSTEM);
            }
        }
        else
        {
            emit signal_SelfCheckResult(CHECK_ITEM_OF_HEPARIN_SYSTEM,SELF_CHECK_ERROR);
            if(m_selfCheckItemList.contains(CHECK_ITEM_OF_HEPARIN_SYSTEM) == false)
            {
                m_selfCheckItemList << CHECK_ITEM_OF_HEPARIN_SYSTEM;
            }
            emit signal_sendAlarmData(SYSTEM_ERROR_CODE_HEPARIN_PUMP_SELF_CHECK_NOT_TOP,INTERVAL_10,SYSTEM_ALARM_ENABLE);
            /*肝素泵自检失败后从头开始*/
            m_isHeparinPumpFirstCheck = true;
        }
    }
}
/*
功能描述：阻流夹自检判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeChokedFlowMonitorSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeChokedFlowMonitorSelfCheck()：阻流夹自检判断";
    qdebug<<debugstr;
#endif

    bool status_ZLJ = (bool)(g_data.module->drive.rd0.std_1 & g_data.module->drive.DriveBoard_RD0_ZLJ);

    if(m_isChokeFirstCheck == true)
    {
        if(status_ZLJ == true)
        {
            m_isChokeFirstCheck = false;
            chokedFlowMonitorSelfCheck();
        }
        else
        {
            emit signal_SelfCheckResult(CHECK_ITEM_OF_CHOKED_FLOW_SYSTEM,SELF_CHECK_ERROR);
            if(m_selfCheckItemList.contains(CHECK_ITEM_OF_CHOKED_FLOW_SYSTEM) == false)
            {
                m_selfCheckItemList << CHECK_ITEM_OF_CHOKED_FLOW_SYSTEM;
            }
            emit signal_sendAlarmData(SYSTEM_ERROR_CODE_CHOKED_FLOW_MONITOR_SELF_CHECK,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        }
    }
    else
    {
        if(status_ZLJ == false)
        {
            m_isChokeFirstCheck = true;
            emit signal_SelfCheckResult(CHECK_ITEM_OF_CHOKED_FLOW_SYSTEM,SELF_CHECK_CORRECT);
            if(m_selfCheckItemList.contains(CHECK_ITEM_OF_CHOKED_FLOW_SYSTEM) == true)
            {
                m_selfCheckItemList.removeOne(CHECK_ITEM_OF_CHOKED_FLOW_SYSTEM);
            }

            if(m_checkItem_balance == false)
            {
                /*启动平衡腔自检*/
                balanceSelfCheck();
            }
        }
        else
        {
            emit signal_SelfCheckResult(CHECK_ITEM_OF_CHOKED_FLOW_SYSTEM,SELF_CHECK_ERROR);
            if(m_selfCheckItemList.contains(CHECK_ITEM_OF_CHOKED_FLOW_SYSTEM) == false)
            {
                m_selfCheckItemList << CHECK_ITEM_OF_CHOKED_FLOW_SYSTEM;
            }
            emit signal_sendAlarmData(SYSTEM_ERROR_CODE_CHOKED_FLOW_MONITOR_SELF_CHECK,INTERVAL_10,SYSTEM_ALARM_ENABLE);
            /*阻流夹自检失败后从头开始*/
//            m_isChokeFirstCheck = true;
        }
    }
}
/*
功能描述：负压罐状态检测
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeSubpressureSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeSubpressureSelfCheck()：功能描述：负压罐状态检测";
    qdebug<<debugstr;
#endif

    bool status_YJ2 = (bool)(g_data.module->balance.rd0.std_1 & g_data.module->balance.Balance_RD0_CQ2);
    bool status_YJ3 = (bool)(g_data.module->balance.rd0.std_1 & g_data.module->balance.Balance_RD0_CQ3);

    if(status_YJ2 == false && status_YJ3 == false)
    {
        emit signal_SelfCheckResult(CHECK_ITEM_OF_BALANCE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_BALANCE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_BALANCE_SYSTEM;
        }
        emit signal_SelfCheckResult(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_SUBPRESSURE_SYSTEM;
        }

        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP100,INTERVAL_10,SYSTEM_ALARM_ENABLE);
    }
    else
    {
        QTimer::singleShot(0,this,SLOT(slot_judgeBalanceSelfCheck_11()));
    }
}
/*
功能描述：平衡腔自检11判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeBalanceSelfCheck_11()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeBalanceSelfCheck_11()：平衡腔自检11判断";
    qdebug<<debugstr;
#endif

    /*消除平衡腔自检21_*相关报警*/
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP112,INTERVAL_10,SYSTEM_ALARM_DISABLE);
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP114,INTERVAL_10,SYSTEM_ALARM_DISABLE);
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP101,INTERVAL_10,SYSTEM_ALARM_DISABLE);
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP103,INTERVAL_10,SYSTEM_ALARM_DISABLE);
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP102,INTERVAL_10,SYSTEM_ALARM_DISABLE);

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_11);

    bool status_WA = (bool)(g_data.module->drive.rd0.std_1 & g_data.module->drive.DriveBoard_RD0_WA);
    bool status_WB = (bool)(g_data.module->drive.rd0.std_1 & g_data.module->drive.DriveBoard_RD0_WB);

    if(status_WA == false && status_WB == false)
    {
        emit signal_sendAlarmData(SYSTEM_NOTICE_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP100,INTERVAL_10,SYSTEM_ALARM_DISABLE);
        /*释放压力*/
        releasePressureOfTheSystem();
        QTimer::singleShot(SYSTEM_SELF_CHECK_RELEASE_PRESSURE_MAX_RUN_TIME*1000,this,SLOT(slot_balanceSelfCheck_21_1()));
    }
    else
    {
        emit signal_sendAlarmData(SYSTEM_NOTICE_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP100,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        emit signal_SelfCheckResult(CHECK_ITEM_OF_BALANCE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_BALANCE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_BALANCE_SYSTEM;
        }
        emit signal_SelfCheckResult(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_SUBPRESSURE_SYSTEM;
        }
    }
}
/*
功能描述：平衡腔自检21_1
输    入：/
输    出：/
*/
void systemSelfCheck::slot_balanceSelfCheck_21_1()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_balanceSelfCheck_21_1()：平衡腔自检21_1";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_21_1);

    g_data.module->balance.wr1.cmd_2 &= ~g_data.module->balance.Balance_WR1_SV14_T;
    g_data.module->balance.wr1.qpv = 0;
    g_data.module->balance.wr1.dpv = 0;
    g_data.module->balance.wr1.ypv = 0;

    /*关V1-V8*/
    g_data.module->balance.wr1.cmd_1 = 0x00;

    /*YJ1控制SV1*/
    g_data.module->drive.wr0.cmd_1 |= g_data.module->drive.DriveBoard_WR0_CTRL_SV | g_data.module->drive.DriveBoard_WR0_SV1_L;
    g_data.module->drive.wr0.cmd_1 &= ~g_data.module->drive.DriveBoard_WR0_SV1_H;

    /*开SV5、10、11、13，其余关*/
    g_data.module->drive.wr0.sv1_8 |= g_data.module->drive.DriveBoard_WR0_SV5;
    g_data.module->drive.wr0.sv1_8 &= ~g_data.module->drive.DriveBoard_WR0_SV2 & ~g_data.module->drive.DriveBoard_WR0_SV3 & ~g_data.module->drive.DriveBoard_WR0_SV4\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV6 & ~g_data.module->drive.DriveBoard_WR0_SV7 & ~g_data.module->drive.DriveBoard_WR0_SV8;

    g_data.module->drive.wr0.sv9_16 |= g_data.module->drive.DriveBoard_WR0_SV10 | g_data.module->drive.DriveBoard_WR0_SV11 | g_data.module->drive.DriveBoard_WR0_SV13;
    g_data.module->drive.wr0.sv9_16 &= ~g_data.module->drive.DriveBoard_WR0_SV9 & ~g_data.module->drive.DriveBoard_WR0_SV12 & ~g_data.module->drive.DriveBoard_WR0_SV14\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV15 & ~g_data.module->drive.DriveBoard_WR0_SV16;

    g_data.module->drive.wr0.sv17_24 &= ~g_data.module->drive.DriveBoard_WR0_SV17 & ~g_data.module->drive.DriveBoard_WR0_SV18 & ~g_data.module->drive.DriveBoard_WR0_SV19\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV20;

    g_data.module->heat.wr0.cmd_1 &= ~g_data.module->heat.Heat_WR0_SR;

    g_data.module->mixture.wr0.cmd_1 &= 0xf0;
    g_data.module->mixture.wr0.cmd_1 |= g_data.module->mixture.Mixture_WR0_WORK_MOD_STOP;

    g_data.module->ufPump.wr0.cmd_1 &= ~g_data.module->ufPump.UlterFilterPlate_WR0_SR;

    g_data.module->Sync(TAG_BALANCE_WR1 | TAG_DRIVE_WR0 | TAG_HEAT_WR0 | TAG_MIXTURE_WR0 | TAG_UFPUMP_WR0);

    m_balanceJudgeTimer->setInterval(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME*1000);
    connect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_21_1);
    m_balanceJudgeTimer->start();

    m_balanceSustionTimer->setInterval(SYSTEM_SELF_CHECK_SUSTION_TIME_21_1*1000);
    connect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_21_1);
    m_balanceSustionTimer->start();
}
/*
功能描述：平衡腔自检21_1判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeBalanceSelfCheck_21_1()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeBalanceSelfCheck_21_1()：平衡腔自检21_1判断";
    qdebug<<debugstr;
#endif

    qint16 value_YG_2 = g_data.module->balance.rd3.rtYG2;
    qint16 value_YG_4 = g_data.module->balance.rd3.rtYG4;

    if(value_YG_2 > SYSTEM_SELF_CHECK_YG2_MAX_PRESSURE_21_1 || value_YG_4 > SYSTEM_SELF_CHECK_YG4_MAX_PRESSURE_21_1)
    {
        m_balanceJudgeTimer->stop();
        disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_21_1);
        m_balanceSustionTimer->stop();
        disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_21_1);

        /*停止齿轮泵*/
        stopGearPumpOfTheSystem();

        if(value_YG_2 > SYSTEM_SELF_CHECK_YG2_MAX_PRESSURE_21_1)
        {
            emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP112,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        }
        if(value_YG_4 > SYSTEM_SELF_CHECK_YG4_MAX_PRESSURE_21_1)
        {
            emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP114,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        }

        emit signal_SelfCheckResult(CHECK_ITEM_OF_BALANCE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_BALANCE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_BALANCE_SYSTEM;
        }
        emit signal_SelfCheckResult(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_SUBPRESSURE_SYSTEM;
        }
    }
}
/*
功能描述：平衡腔自检21_1处理
输    入：/
输    出：/
*/
void systemSelfCheck::slot_disposeBalanceSelfCheck_21_1()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_disposeBalanceSelfCheck_21_1()：平衡腔自检21_1处理";
    qdebug<<debugstr;
#endif

    m_balanceJudgeTimer->stop();
    disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_21_1);
    m_balanceSustionTimer->stop();
    disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_21_1);

    releasePressureOfTheSystem();

    QTimer::singleShot(SYSTEM_SELF_CHECK_RELEASE_PRESSURE_MAX_RUN_TIME*1000,this,SLOT(slot_balanceSelfCheck_21_2()));
}
/*
功能描述：平衡腔自检21_2
输    入：/
输    出：/
*/
void systemSelfCheck::slot_balanceSelfCheck_21_2()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_balanceSelfCheck_21_2()：平衡腔自检21_2";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_21_2);

    g_data.module->balance.wr1.cmd_2 &= ~g_data.module->balance.Balance_WR1_SV14_T;
    g_data.module->balance.wr1.qpv = g_data.systemParameter.qpVoltage.m_value;
    g_data.module->balance.wr1.dpv = SYSTEM_SELF_CHECK_GEAR_PUMP_VOLAGE_VALUE_DP_21_2;
    g_data.module->balance.wr1.ypv = SYSTEM_SELF_CHECK_GEAR_PUMP_VOLAGE_VALUE_YP_21_2;

    /*开V1、V2、V5、V6，关V3、V4、V7、V8*/
    g_data.module->balance.wr1.cmd_1 |= g_data.module->balance.Balance_WR1_V1 | g_data.module->balance.Balance_WR1_V2 | g_data.module->balance.Balance_WR1_V5\
                                        | g_data.module->balance.Balance_WR1_V6;
    g_data.module->balance.wr1.cmd_1 &= ~g_data.module->balance.Balance_WR1_V3 & ~g_data.module->balance.Balance_WR1_V4 & ~g_data.module->balance.Balance_WR1_V7\
                                        & ~g_data.module->balance.Balance_WR1_V8;

    /*YJ1控制SV1*/
    g_data.module->drive.wr0.cmd_1 |= g_data.module->drive.DriveBoard_WR0_CTRL_SV | g_data.module->drive.DriveBoard_WR0_SV1_L;
    g_data.module->drive.wr0.cmd_1 &= ~g_data.module->drive.DriveBoard_WR0_SV1_H;

    /*开SV5、10、11、13，其余关*/
    g_data.module->drive.wr0.sv1_8 |= g_data.module->drive.DriveBoard_WR0_SV5;
    g_data.module->drive.wr0.sv1_8 &= ~g_data.module->drive.DriveBoard_WR0_SV2 & ~g_data.module->drive.DriveBoard_WR0_SV3 & ~g_data.module->drive.DriveBoard_WR0_SV4\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV6 & ~g_data.module->drive.DriveBoard_WR0_SV7 & ~g_data.module->drive.DriveBoard_WR0_SV8;

    g_data.module->drive.wr0.sv9_16 |= g_data.module->drive.DriveBoard_WR0_SV10 | g_data.module->drive.DriveBoard_WR0_SV11 | g_data.module->drive.DriveBoard_WR0_SV13;
    g_data.module->drive.wr0.sv9_16 &= ~g_data.module->drive.DriveBoard_WR0_SV9 & ~g_data.module->drive.DriveBoard_WR0_SV12 & ~g_data.module->drive.DriveBoard_WR0_SV14\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV15 & ~g_data.module->drive.DriveBoard_WR0_SV16;

    g_data.module->drive.wr0.sv17_24 &= ~g_data.module->drive.DriveBoard_WR0_SV17 & ~g_data.module->drive.DriveBoard_WR0_SV18 & ~g_data.module->drive.DriveBoard_WR0_SV19\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV20;

    g_data.module->heat.wr0.cmd_1 &= ~g_data.module->heat.Heat_WR0_SR;

    g_data.module->mixture.wr0.cmd_1 &= 0xf0;
    g_data.module->mixture.wr0.cmd_1 |= g_data.module->mixture.Mixture_WR0_WORK_MOD_STOP;

    g_data.module->ufPump.wr0.cmd_1 &= ~g_data.module->ufPump.UlterFilterPlate_WR0_SR;

    g_data.module->Sync(TAG_BALANCE_WR1 | TAG_DRIVE_WR0 | TAG_HEAT_WR0 | TAG_MIXTURE_WR0 | TAG_UFPUMP_WR0);

    m_countSustionYG2YG4Times = BALANCE_CHECK_YG2_YG4_SUSTION_TIMES_21_2;

    m_balanceJudgeTimer->setInterval(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME*1000);
    connect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_21_2);
    m_balanceJudgeTimer->start();

    m_balanceSustionTimer->setInterval(SYSTEM_SELF_CHECK_SUSTION_TIME_21_2*1000);
    connect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_21_2);
    m_balanceSustionTimer->start();
}
/*
功能描述：平衡腔自检21_2判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeBalanceSelfCheck_21_2()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeBalanceSelfCheck_21_2()：平衡腔自检21_2判断";
    qdebug<<debugstr;
#endif

    qint16 value_YG2 = g_data.module->balance.rd3.rtYG2;
    qint16 value_YG4 = g_data.module->balance.rd3.rtYG4;

    if(value_YG2 > SYSTEM_SELF_CHECK_YG2_MAX_PRESSURE_21_2 || value_YG4 > SYSTEM_SELF_CHECK_YG4_MAX_PRESSURE_21_2)
    {
        m_countSustionYG2YG4Times--;
    }
    else
    {
        m_countSustionYG2YG4Times = BALANCE_CHECK_YG2_YG4_SUSTION_TIMES_21_2;
    }

    if(m_countSustionYG2YG4Times <= 0)
    {
        m_balanceJudgeTimer->stop();
        disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_21_2);
        m_balanceSustionTimer->stop();
        disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_21_2);

        stopGearPumpOfTheSystem();

        if(value_YG2 > SYSTEM_SELF_CHECK_YG2_MAX_PRESSURE_21_2 && value_YG4 > SYSTEM_SELF_CHECK_YG4_MAX_PRESSURE_21_2)
        {
            emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP102,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        }
        else if(value_YG2 > SYSTEM_SELF_CHECK_YG2_MAX_PRESSURE_21_2)
        {
            emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP101,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        }
        else if(value_YG4 > SYSTEM_SELF_CHECK_YG4_MAX_PRESSURE_21_2)
        {
            emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP103,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        }

        emit signal_SelfCheckResult(CHECK_ITEM_OF_BALANCE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_BALANCE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_BALANCE_SYSTEM;
        }
        emit signal_SelfCheckResult(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_SUBPRESSURE_SYSTEM;
        }
    }
}
/*
功能描述：平衡腔自检21_2处理
输    入：/
输    出：/
*/
void systemSelfCheck::slot_disposeBalanceSelfCheck_21_2()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_disposeBalanceSelfCheck_21_2()：平衡腔自检21_2处理";
    qdebug<<debugstr;
#endif

    m_balanceJudgeTimer->stop();
    disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_21_2);
    m_balanceSustionTimer->stop();
    disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_21_2);

    QTimer::singleShot(0,this,SLOT(slot_balanceSelfCheck_22_1()));
}
/*
功能描述：平衡腔自检22_1
输    入：/
输    出：/
*/
void systemSelfCheck::slot_balanceSelfCheck_22_1()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_balanceSelfCheck_22_1()：平衡腔自检22_1";
    qdebug<<debugstr;
#endif

    /*消除平衡腔自检22_*相关报警*/
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP105,INTERVAL_10,SYSTEM_ALARM_DISABLE);
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP107,INTERVAL_10,SYSTEM_ALARM_DISABLE);
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP106,INTERVAL_10,SYSTEM_ALARM_DISABLE);

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_22_1);

    releasePressureOfTheSystem();

    QTimer::singleShot(SYSTEM_SELF_CHECK_RELEASE_PRESSURE_MAX_RUN_TIME*1000,this,SLOT(slot_balanceSelfCheck_22_2()));
}
/*
功能描述：平衡腔自检22_2
输    入：/
输    出：/
*/
void systemSelfCheck::slot_balanceSelfCheck_22_2()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeBalanceSelfCheck_22_1()：平衡腔自检22_2判断";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_22_2);

    g_data.module->balance.wr1.cmd_2 &= ~g_data.module->balance.Balance_WR1_SV14_T;
    g_data.module->balance.wr1.qpv = g_data.systemParameter.qpVoltage.m_value;
    g_data.module->balance.wr1.dpv = SYSTEM_SELF_CHECK_GEAR_PUMP_VOLAGE_VALUE_DP_22_2;
    g_data.module->balance.wr1.ypv = SYSTEM_SELF_CHECK_GEAR_PUMP_VOLAGE_VALUE_YP_22_2;

    /*关V1、V2、V5、V6，开V3、V4、V7、V8*/
    g_data.module->balance.wr1.cmd_1 |= g_data.module->balance.Balance_WR1_V3 | g_data.module->balance.Balance_WR1_V4 | g_data.module->balance.Balance_WR1_V7\
                                        | g_data.module->balance.Balance_WR1_V8;
    g_data.module->balance.wr1.cmd_1 &= ~g_data.module->balance.Balance_WR1_V1 & ~g_data.module->balance.Balance_WR1_V2 & ~g_data.module->balance.Balance_WR1_V5\
                                        & ~g_data.module->balance.Balance_WR1_V6;

    /*YJ1控制SV1*/
    g_data.module->drive.wr0.cmd_1 |= g_data.module->drive.DriveBoard_WR0_CTRL_SV | g_data.module->drive.DriveBoard_WR0_SV1_L;
    g_data.module->drive.wr0.cmd_1 &= ~g_data.module->drive.DriveBoard_WR0_SV1_H;

    /*开SV5、10、11、13，其余关*/
    g_data.module->drive.wr0.sv1_8 |= g_data.module->drive.DriveBoard_WR0_SV5;
    g_data.module->drive.wr0.sv1_8 &= ~g_data.module->drive.DriveBoard_WR0_SV2 & ~g_data.module->drive.DriveBoard_WR0_SV3 & ~g_data.module->drive.DriveBoard_WR0_SV4\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV6 & ~g_data.module->drive.DriveBoard_WR0_SV7 & ~g_data.module->drive.DriveBoard_WR0_SV8;

    g_data.module->drive.wr0.sv9_16 |= g_data.module->drive.DriveBoard_WR0_SV10 | g_data.module->drive.DriveBoard_WR0_SV11 | g_data.module->drive.DriveBoard_WR0_SV13;
    g_data.module->drive.wr0.sv9_16 &= ~g_data.module->drive.DriveBoard_WR0_SV9 & ~g_data.module->drive.DriveBoard_WR0_SV12 & ~g_data.module->drive.DriveBoard_WR0_SV14\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV15 & ~g_data.module->drive.DriveBoard_WR0_SV16;

    g_data.module->drive.wr0.sv17_24 &= ~g_data.module->drive.DriveBoard_WR0_SV17 & ~g_data.module->drive.DriveBoard_WR0_SV18 & ~g_data.module->drive.DriveBoard_WR0_SV19\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV20;

    g_data.module->Sync(TAG_BALANCE_WR1 | TAG_DRIVE_WR0);

    m_countSustionYG2YG4Times = BALANCE_CHECK_YG2_YG4_SUSTION_TIMES_22_2;

    m_balanceJudgeTimer->setInterval(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME*1000);
    connect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_22_2);
    m_balanceJudgeTimer->start();

    m_balanceSustionTimer->setInterval(SYSTEM_SELF_CHECK_SUSTION_TIME_22_2*1000);
    connect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_22_2);
    m_balanceSustionTimer->start();
}
/*
功能描述：平衡腔自检22_2判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeBalanceSelfCheck_22_2()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeBalanceSelfCheck_22_1()：平衡腔自检22_2判断";
    qdebug<<debugstr;
#endif

    qint16 value_YG2 = g_data.module->balance.rd3.rtYG2;
    qint16 value_YG4 = g_data.module->balance.rd3.rtYG4;

    if(value_YG2 > SYSTEM_SELF_CHECK_YG2_MAX_PRESSURE_22_2 || value_YG4 > SYSTEM_SELF_CHECK_YG4_MAX_PRESSURE_22_2)
    {
        m_countSustionYG2YG4Times--;
    }
    else
    {
        m_countSustionYG2YG4Times = BALANCE_CHECK_YG2_YG4_SUSTION_TIMES_22_2;
    }

    if(m_countSustionYG2YG4Times <=0)
    {
        m_balanceJudgeTimer->stop();
        disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_22_2);
        m_balanceSustionTimer->stop();
        disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_22_2);

        stopGearPumpOfTheSystem();

        if(value_YG2 > SYSTEM_SELF_CHECK_YG2_MAX_PRESSURE_22_2 && value_YG4 > SYSTEM_SELF_CHECK_YG4_MAX_PRESSURE_22_2)
        {
            emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP105,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        }
        else if(value_YG2 > SYSTEM_SELF_CHECK_YG2_MAX_PRESSURE_22_2)
        {
            emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP107,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        }
        else if(value_YG4 > SYSTEM_SELF_CHECK_YG4_MAX_PRESSURE_22_2)
        {
            emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP106,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        }

        emit signal_SelfCheckResult(CHECK_ITEM_OF_BALANCE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_BALANCE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_BALANCE_SYSTEM;
        }
        emit signal_SelfCheckResult(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_SUBPRESSURE_SYSTEM;
        }
    }
}
/*
功能描述：平衡腔自检22_2处理
输    入：/
输    出：/
*/
void systemSelfCheck::slot_disposeBalanceSelfCheck_22_2()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_disposeBalanceSelfCheck_22_1()：平衡腔自检22_2处理";
    qdebug<<debugstr;
#endif

    m_balanceJudgeTimer->stop();
    disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_22_2);
    m_balanceSustionTimer->stop();
    disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_22_2);

    QTimer::singleShot(0,this,SLOT(slot_balanceSelfCheck_31()));
}
/*
功能描述：平衡腔自检31
输    入：/
输    出：/
*/
void systemSelfCheck::slot_balanceSelfCheck_31()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_balanceSelfCheck_31()：平衡腔自检31";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_31);

    g_data.module->balance.wr0.cmd_1 = g_data.module->balance.Balance_WR0_WORK_MODEL_NORMAL;
    g_data.module->balance.wr0.flow = 700;
    g_data.module->balance.wr0.qpv = g_data.systemParameter.qpVoltage.m_value;

    /*YJ1控制SV1*/
    g_data.module->drive.wr0.cmd_1 |= g_data.module->drive.DriveBoard_WR0_CTRL_SV | g_data.module->drive.DriveBoard_WR0_SV1_L;
    g_data.module->drive.wr0.cmd_1 &= ~g_data.module->drive.DriveBoard_WR0_SV1_H;

    /*开SV5、10、11、13，其余关*/
    g_data.module->drive.wr0.sv1_8 |= g_data.module->drive.DriveBoard_WR0_SV5;
    g_data.module->drive.wr0.sv1_8 &= ~g_data.module->drive.DriveBoard_WR0_SV2 & ~g_data.module->drive.DriveBoard_WR0_SV3 & ~g_data.module->drive.DriveBoard_WR0_SV4\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV6 & ~g_data.module->drive.DriveBoard_WR0_SV7 & ~g_data.module->drive.DriveBoard_WR0_SV8;

    g_data.module->drive.wr0.sv9_16 |= g_data.module->drive.DriveBoard_WR0_SV10 | g_data.module->drive.DriveBoard_WR0_SV11 | g_data.module->drive.DriveBoard_WR0_SV13;
    g_data.module->drive.wr0.sv9_16 &= ~g_data.module->drive.DriveBoard_WR0_SV9 & ~g_data.module->drive.DriveBoard_WR0_SV12 & ~g_data.module->drive.DriveBoard_WR0_SV14\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV15 & ~g_data.module->drive.DriveBoard_WR0_SV16;

    g_data.module->drive.wr0.sv17_24 &= ~g_data.module->drive.DriveBoard_WR0_SV17 & ~g_data.module->drive.DriveBoard_WR0_SV18 & ~g_data.module->drive.DriveBoard_WR0_SV19\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV20;

    g_data.module->Sync(TAG_BALANCE_WR1 | TAG_DRIVE_WR0);

    QTimer::singleShot(SYSTEM_SELF_CHECK_SUSTION_TIME_31*1000,this,SLOT(slot_balanceSelfCheck_32_1()));
}
/*
功能描述：平衡腔自检32_1
输    入：/
输    出：/
*/
void systemSelfCheck::slot_balanceSelfCheck_32_1()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_balanceSelfCheck_32_1()：平衡腔自检32_1";
    qdebug<<debugstr;
#endif

    /*清除平衡腔32_*相关报警*/
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_PRESSURE_ERR,INTERVAL_10,SYSTEM_ALARM_DISABLE);
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP110,INTERVAL_10,SYSTEM_ALARM_DISABLE);
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP108,INTERVAL_10,SYSTEM_ALARM_DISABLE);
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP113,INTERVAL_10,SYSTEM_ALARM_DISABLE);

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_1);

    releasePressureOfTheSystem();

    QTimer::singleShot(SYSTEM_SELF_CHECK_RELEASE_PRESSURE_MAX_RUN_TIME*1000,this,SLOT(slot_balanceSelfCheck_32_2()));
}
/*
功能描述：平衡腔自检32_2
输    入：/
输    出：/
*/
void systemSelfCheck::slot_balanceSelfCheck_32_2()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_balanceSelfCheck_32_2()：平衡腔自检32_2";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_2);

    g_data.module->balance.wr1.cmd_2 &= ~g_data.module->balance.Balance_WR1_SV14_T;
    g_data.module->balance.wr1.qpv = g_data.systemParameter.qpVoltage.m_value;
    g_data.module->balance.wr1.dpv = SYSTEM_SELF_CHECK_GEAR_PUMP_VOLAGE_VALUE_DP_32_2;
    g_data.module->balance.wr1.ypv = 0;

    /*关V5、V7，其余开*/
    g_data.module->balance.wr1.cmd_1 |= g_data.module->balance.Balance_WR1_V1 | g_data.module->balance.Balance_WR1_V2 | g_data.module->balance.Balance_WR1_V3\
                                        | g_data.module->balance.Balance_WR1_V4 | g_data.module->balance.Balance_WR1_V6 | g_data.module->balance.Balance_WR1_V8;
    g_data.module->balance.wr1.cmd_1 &= ~g_data.module->balance.Balance_WR1_V5 & ~g_data.module->balance.Balance_WR1_V7;

    /*YJ1控制SV1*/
    g_data.module->drive.wr0.cmd_1 |= g_data.module->drive.DriveBoard_WR0_CTRL_SV | g_data.module->drive.DriveBoard_WR0_SV1_L;
    g_data.module->drive.wr0.cmd_1 &= ~g_data.module->drive.DriveBoard_WR0_SV1_H;

    /*开SV5、10、11，其余关*/
    g_data.module->drive.wr0.sv1_8 |= g_data.module->drive.DriveBoard_WR0_SV5;
    g_data.module->drive.wr0.sv1_8 &= ~g_data.module->drive.DriveBoard_WR0_SV2 & ~g_data.module->drive.DriveBoard_WR0_SV3 & ~g_data.module->drive.DriveBoard_WR0_SV4\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV6 & ~g_data.module->drive.DriveBoard_WR0_SV7 & ~g_data.module->drive.DriveBoard_WR0_SV8;

    g_data.module->drive.wr0.sv9_16 |= g_data.module->drive.DriveBoard_WR0_SV10 | g_data.module->drive.DriveBoard_WR0_SV11;
    g_data.module->drive.wr0.sv9_16 &= ~g_data.module->drive.DriveBoard_WR0_SV9 & ~g_data.module->drive.DriveBoard_WR0_SV12 & ~g_data.module->drive.DriveBoard_WR0_SV13\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV14 & ~g_data.module->drive.DriveBoard_WR0_SV15 & ~g_data.module->drive.DriveBoard_WR0_SV16;

    g_data.module->drive.wr0.sv17_24 &= ~g_data.module->drive.DriveBoard_WR0_SV17 & ~g_data.module->drive.DriveBoard_WR0_SV18 & ~g_data.module->drive.DriveBoard_WR0_SV19\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV20;

    g_data.module->Sync(TAG_BALANCE_WR1 | TAG_DRIVE_WR0);

    m_YG3moreThan110kpaTimes = 0;

    m_balanceJudgeTimer->setInterval(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME*1000);
    connect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_32_2);
    m_balanceJudgeTimer->start();

    m_balanceSustionTimer->setInterval(SYSTEM_SELF_CHECK_SUSTION_TIME_32_2*1000);
    connect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_32_2);
    m_balanceSustionTimer->start();
}
/*
功能描述：平衡腔自检32_2判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeBalanceSelfCheck_32_2()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeBalanceSelfCheck_32_2()：平衡腔自检32_2判断";
    qdebug<<debugstr;
#endif

    qint16 value_YG3 = g_data.module->drive.rd1.dp;

    if(value_YG3 > SYSTEM_SELF_CHECK_YG3_MAX_PRESSURE_32_2)
    {
        m_YG3moreThan110kpaTimes++;
        if(m_YG3moreThan110kpaTimes > 6)
        {
            m_YG3moreThan110kpaTimes = 0;

            qint16 value_YG2 = g_data.module->balance.rd3.rtYG2;
            qint16 value_YG4 = g_data.module->balance.rd3.rtYG4;

            m_balanceJudgeTimer->stop();
            disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_32_2);
            m_balanceSustionTimer->stop();
            disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_32_2);

            if(abs(value_YG2*10 - value_YG3) < 100 && abs(value_YG3 - value_YG4*10) < 100)
            {
                QTimer::singleShot(0,this,SLOT(slot_balanceSelfCheck_32_3()));
            }
            else
            {
                emit signal_sendAlarmData(SYSTEM_ERROR_CODE_PRESSURE_ERR,INTERVAL_10,SYSTEM_ALARM_ENABLE);

                stopGearPumpOfTheSystem();

                emit signal_SelfCheckResult(CHECK_ITEM_OF_BALANCE_SYSTEM,SELF_CHECK_ERROR);
                if(m_selfCheckItemList.contains(CHECK_ITEM_OF_BALANCE_SYSTEM) == false)
                {
                    m_selfCheckItemList << CHECK_ITEM_OF_BALANCE_SYSTEM;
                }
                emit signal_SelfCheckResult(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM,SELF_CHECK_ERROR);
                if(m_selfCheckItemList.contains(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM) == false)
                {
                    m_selfCheckItemList << CHECK_ITEM_OF_SUBPRESSURE_SYSTEM;
                }
            }
        }
    }
    else
    {
        m_YG3moreThan110kpaTimes = 0;
    }
}
/*
功能描述：平衡腔自检32_2处理
输    入：/
输    出：/
*/
void systemSelfCheck::slot_disposeBalanceSelfCheck_32_2()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_disposeBalanceSelfCheck_32_2()：平衡腔自检32_2处理";
    qdebug<<debugstr;
#endif

    m_balanceJudgeTimer->stop();
    disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_32_2);
    m_balanceSustionTimer->stop();
    disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_32_2);

    stopGearPumpOfTheSystem();

    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP110,INTERVAL_10,SYSTEM_ALARM_ENABLE);

    emit signal_SelfCheckResult(CHECK_ITEM_OF_BALANCE_SYSTEM,SELF_CHECK_ERROR);
    if(m_selfCheckItemList.contains(CHECK_ITEM_OF_BALANCE_SYSTEM) == false)
    {
        m_selfCheckItemList << CHECK_ITEM_OF_BALANCE_SYSTEM;
    }
    emit signal_SelfCheckResult(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM,SELF_CHECK_ERROR);
    if(m_selfCheckItemList.contains(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM) == false)
    {
        m_selfCheckItemList << CHECK_ITEM_OF_SUBPRESSURE_SYSTEM;
    }
}
/*
功能描述：平衡腔自检32_3
输    入：/
输    出：/
*/
void systemSelfCheck::slot_balanceSelfCheck_32_3()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_balanceSelfCheck_32_3()：平衡腔自检32_3";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_3);

    g_data.module->balance.wr1.dpv = 0;
    g_data.module->balance.wr1.qpv = 0;
    g_data.module->balance.wr1.ypv = 0;

    /*关V6、V8*/
    g_data.module->balance.wr1.cmd_1 &= ~g_data.module->balance.Balance_WR1_V6 & ~g_data.module->balance.Balance_WR1_V8;

    g_data.module->Sync(TAG_BALANCE_WR1);

    m_balanceJudgeTimer->setInterval(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME*1000);
    connect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_32_3);
    QTimer::singleShot(SYSTEM_SELF_CHECK_SUSTION_TIME_32_3*1000,this,[=]{m_balanceJudgeTimer->start();});
}
/*
功能描述：平衡腔自检32_3判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeBalanceSelfCheck_32_3()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeBalanceSelfCheck_32_3()：平衡腔自检32_3判断";
    qdebug<<debugstr;
#endif

    qint16 value_YG3 = g_data.module->drive.rd1.dp;

    m_balanceJudgeTimer->stop();
    disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_32_3);

    if(value_YG3 < SYSTEM_SELF_CHECK_YG3_MAX_PRESSURE_32_3)
    {
        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP108,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        emit signal_SelfCheckResult(CHECK_ITEM_OF_BALANCE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_BALANCE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_BALANCE_SYSTEM;
        }
        emit signal_SelfCheckResult(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_SUBPRESSURE_SYSTEM;
        }
    }
    else
    {
        QTimer::singleShot(0,this,SLOT(slot_balanceSelfCheck_32_4()));
    }
}
/*
功能描述：平衡腔自检32_4
输    入：/
输    出：/
*/
void systemSelfCheck::slot_balanceSelfCheck_32_4()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_balanceSelfCheck_32_4()：平衡腔自检32_4";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_4);

    m_isCheckYG3Reveal = true;
    m_YG3ChangeValue = 0;
    m_preValue = 0;

    m_balanceJudgeTimer->setInterval(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME*1000);
    connect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_32_4);
    m_balanceJudgeTimer->start();

    m_balanceSustionTimer->setInterval(SYSTEM_SELF_CHECK_SUSTION_TIME_32_4*1000);
    connect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_32_4);
    m_balanceSustionTimer->start();
}
/*
功能描述：平衡腔自检32_4判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeBalanceSelfCheck_32_4()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeBalanceSelfCheck_32_4()：平衡腔自检32_4判断";
    qdebug<<debugstr;
#endif

    qint16 value_YG3 = g_data.module->drive.rd1.dp;

    if(m_isCheckYG3Reveal == true)
    {
        m_preValue = value_YG3;
        m_isCheckYG3Reveal = false;
    }
    else
    {
        m_YG3ChangeValue += m_preValue - value_YG3;
        m_preValue = value_YG3;
    }

    if(m_YG3ChangeValue > SYSTEM_SELF_CHECK_YG3_REVEAL_PRESSURE_32_4)
    {
        m_balanceJudgeTimer->stop();
        disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_32_4);
        m_balanceSustionTimer->stop();
        disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_32_4);

        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP108,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        emit signal_SelfCheckResult(CHECK_ITEM_OF_BALANCE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_BALANCE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_BALANCE_SYSTEM;
        }
        emit signal_SelfCheckResult(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_SUBPRESSURE_SYSTEM;
        }
    }
}
/*
功能描述：平衡腔自检32_4处理
输    入：/
输    出：/
*/
void systemSelfCheck::slot_disposeBalanceSelfCheck_32_4()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeBalanceSelfCheck_32_3()：平衡腔自检32_4处理";
    qdebug<<debugstr;
#endif

    m_balanceJudgeTimer->stop();
    disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_32_4);
    m_balanceSustionTimer->stop();
    disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_32_4);

    /*关V2、V4*/
    g_data.module->balance.wr1.cmd_1 &= ~g_data.module->balance.Balance_WR1_V2 & ~g_data.module->balance.Balance_WR1_V4;
    g_data.module->Sync(TAG_BALANCE_WR1);

    QTimer::singleShot(SYSTEM_SELF_CHECK_OPEN_V6_V8_TIME_32_4*1000,this,SLOT(slot_balanceSelfCheck_32_5()));
}
/*
功能描述：平衡腔自检32_5
输    入：/
输    出：/
*/
void systemSelfCheck::slot_balanceSelfCheck_32_5()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_balanceSelfCheck_32_5()：平衡腔自检32_5";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_5);

    /*开V6、V8*/
    g_data.module->balance.wr1.cmd_1 |= g_data.module->balance.Balance_WR1_V6 | g_data.module->balance.Balance_WR1_V8;
    g_data.module->Sync(TAG_BALANCE_WR1);

    m_balanceJudgeTimer->setInterval(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME*1000);
    connect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_32_5);
    QTimer::singleShot(SYSTEM_SELF_CHECK_SUSTION_TIME_32_5*1000,this,[=]{m_balanceJudgeTimer->start();});
}
/*
功能描述：平衡腔自检32_5判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeBalanceSelfCheck_32_5()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeBalanceSelfCheck_32_5()：平衡腔自检32_5判断";
    qdebug<<debugstr;
#endif

    qint16 value_YG3 = g_data.module->drive.rd1.dp;

    m_balanceJudgeTimer->stop();
    disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_32_5);

    if(value_YG3 < SYSTEM_SELF_CHECK_YG3_MAX_PRESSURE_32_5)
    {
        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP113,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        emit signal_SelfCheckResult(CHECK_ITEM_OF_BALANCE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_BALANCE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_BALANCE_SYSTEM;
        }
        emit signal_SelfCheckResult(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_SUBPRESSURE_SYSTEM;
        }
    }
    else
    {
        QTimer::singleShot(0,this,SLOT(slot_balanceSelfCheck_32_6()));
    }
}
/*
功能描述：平衡腔自检32_6
输    入：/
输    出：/
*/
void systemSelfCheck::slot_balanceSelfCheck_32_6()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_balanceSelfCheck_32_6()：平衡腔自检32_6";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_6);

    m_isCheckYG3Reveal = true;
    m_YG3ChangeValue = 0;
    m_preValue = 0;

    m_balanceJudgeTimer->setInterval(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME*1000);
    connect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_32_6);
    m_balanceJudgeTimer->start();

    m_balanceSustionTimer->setInterval(SYSTEM_SELF_CHECK_SUSTION_TIME_32_6*1000);
    connect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_32_6);
    m_balanceSustionTimer->start();
}
/*
功能描述：平衡腔自检32_6判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeBalanceSelfCheck_32_6()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeBalanceSelfCheck_32_6()：平衡腔自检32_6判断";
    qdebug<<debugstr;
#endif

    qint16 value_YG3 = g_data.module->drive.rd1.dp;

    if(m_isCheckYG3Reveal == true)
    {
        m_isCheckYG3Reveal = false;
        m_preValue = value_YG3;
    }
    else
    {
        m_YG3ChangeValue += m_preValue - value_YG3;
        m_preValue = value_YG3;
    }

    if(abs(m_YG3ChangeValue) > SYSTEM_SELF_CHECK_YG3_REVEAL_PRESSURE_32_6)
    {
        m_balanceJudgeTimer->stop();
        disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_32_6);
        m_balanceSustionTimer->stop();
        disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_32_6);

        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP113,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        emit signal_SelfCheckResult(CHECK_ITEM_OF_BALANCE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_BALANCE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_BALANCE_SYSTEM;
        }
        emit signal_SelfCheckResult(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_SUBPRESSURE_SYSTEM;
        }
    }
}
/*
功能描述：平衡腔自检32_6处理
输    入：/
输    出：/
*/
void systemSelfCheck::slot_disposeBalanceSelfCheck_32_6()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_disposeBalanceSelfCheck_32_6()：平衡腔自检32_6处理";
    qdebug<<debugstr;
#endif

    m_balanceJudgeTimer->stop();
    disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_32_6);
    m_balanceSustionTimer->stop();
    disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_32_6);

    QTimer::singleShot(0,this,SLOT(slot_balanceSelfCheck_33_1()));
}
/*
功能描述：平衡腔自检33_1
输    入：/
输    出：/
*/
void systemSelfCheck::slot_balanceSelfCheck_33_1()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_balanceSelfCheck_33_1()：平衡腔自检33_1";
    qdebug<<debugstr;
#endif

    /*清除平衡腔33_*相关报警*/
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP109,INTERVAL_10,SYSTEM_ALARM_DISABLE);
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP110,INTERVAL_10,SYSTEM_ALARM_DISABLE);
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP111,INTERVAL_10,SYSTEM_ALARM_DISABLE);

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_1);

    releasePressureOfTheSystem();

    QTimer::singleShot(SYSTEM_SELF_CHECK_RELEASE_PRESSURE_MAX_RUN_TIME*1000,this,SLOT(slot_balanceSelfCheck_33_2()));
}
/*
功能描述：平衡腔自检33_2
输    入：/
输    出：/
*/
void systemSelfCheck::slot_balanceSelfCheck_33_2()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_balanceSelfCheck_33_2()：平衡腔自检33_2";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_2);

    g_data.module->balance.wr1.cmd_2 &= ~g_data.module->balance.Balance_WR1_SV14_T;
    g_data.module->balance.wr1.qpv = g_data.systemParameter.qpVoltage.m_value;
    g_data.module->balance.wr1.dpv = 0;
    g_data.module->balance.wr1.ypv = SYSTEM_SELF_CHECK_GEAR_PUMP_VOLAGE_VALUE_YP_33_2;

    /*关V1、V3，其余开*/
    g_data.module->balance.wr1.cmd_1 |= g_data.module->balance.Balance_WR1_V2 | g_data.module->balance.Balance_WR1_V4 | g_data.module->balance.Balance_WR1_V5\
                                        | g_data.module->balance.Balance_WR1_V6 | g_data.module->balance.Balance_WR1_V7 | g_data.module->balance.Balance_WR1_V8;
    g_data.module->balance.wr1.cmd_1 &= ~g_data.module->balance.Balance_WR1_V1 & ~g_data.module->balance.Balance_WR1_V3;

    /*YJ1控制SV1*/
    g_data.module->drive.wr0.cmd_1 |= g_data.module->drive.DriveBoard_WR0_CTRL_SV | g_data.module->drive.DriveBoard_WR0_SV1_L;
    g_data.module->drive.wr0.cmd_1 &= ~g_data.module->drive.DriveBoard_WR0_SV1_H;

    /*开SV5、10、11、12、13，其余关*/
    g_data.module->drive.wr0.sv1_8 |= g_data.module->drive.DriveBoard_WR0_SV5;
    g_data.module->drive.wr0.sv1_8 &= ~g_data.module->drive.DriveBoard_WR0_SV2 & ~g_data.module->drive.DriveBoard_WR0_SV3 & ~g_data.module->drive.DriveBoard_WR0_SV4\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV6 & ~g_data.module->drive.DriveBoard_WR0_SV7 & ~g_data.module->drive.DriveBoard_WR0_SV8;

    g_data.module->drive.wr0.sv9_16 |= g_data.module->drive.DriveBoard_WR0_SV10 | g_data.module->drive.DriveBoard_WR0_SV11 | g_data.module->drive.DriveBoard_WR0_SV12\
                                       | g_data.module->drive.DriveBoard_WR0_SV13;
    g_data.module->drive.wr0.sv9_16 &= ~g_data.module->drive.DriveBoard_WR0_SV9 & ~g_data.module->drive.DriveBoard_WR0_SV14 & ~g_data.module->drive.DriveBoard_WR0_SV15\
                                       & ~g_data.module->drive.DriveBoard_WR0_SV16;

    g_data.module->drive.wr0.sv17_24 &= ~g_data.module->drive.DriveBoard_WR0_SV17 & ~g_data.module->drive.DriveBoard_WR0_SV18 & ~g_data.module->drive.DriveBoard_WR0_SV19\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV20;

    g_data.module->Sync(TAG_BALANCE_WR1 | TAG_DRIVE_WR0);

    m_balanceJudgeTimer->setInterval(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME*1000);
    connect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_33_2);
    QTimer::singleShot(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME_33_2*1000,this,[=]{m_balanceJudgeTimer->start();});

    m_balanceSustionTimer->setInterval(SYSTEM_SELF_CHECK_SUSTION_TIME_33_2*1000);
    connect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_33_2);
    m_balanceSustionTimer->start();
}
/*
功能描述：平衡腔自检33_2判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeBalanceSelfCheck_33_2()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeBalanceSelfCheck_33_2()：平衡腔自检33_2判断";
    qdebug<<debugstr;
#endif

    qint16 value_YG4 = g_data.module->balance.rd3.rtYG4;

    if(value_YG4 > SYSTEM_SELF_CHECK_YG4_MAX_PRESSURE_33_2)
    {
        m_balanceJudgeTimer->stop();
        disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_33_2);
        m_balanceSustionTimer->stop();
        disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_33_2);

        QTimer::singleShot(SYSTEM_SELF_CHECK_CLOSE_V5_V7_TIME_33_2*1000,this,SLOT(slot_judgeDisposeBalanceSelfCheck_33_2()));
    }
}
/*
功能描述：平衡腔自检33_2判断处理
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeDisposeBalanceSelfCheck_33_2()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeDisposeBalanceSelfCheck_33_2()：平衡腔自检33_2判断处理";
    qdebug<<debugstr;
#endif

    g_data.module->balance.wr1.cmd_1 &= ~g_data.module->balance.Balance_WR1_V5 & ~g_data.module->balance.Balance_WR1_V7;
    g_data.module->Sync(TAG_BALANCE_WR1);

    QTimer::singleShot(SYSTEM_SELF_CHECK_STOP_YP_TIME_33_2*1000,this,SLOT(slot_balanceSelfCheck_33_3()));
}
/*
功能描述：平衡腔自检33_2处理
输    入：/
输    出：/
*/
void systemSelfCheck::slot_disposeBalanceSelfCheck_33_2()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_disposeBalanceSelfCheck_33_2()：平衡腔自检33_2处理";
    qdebug<<debugstr;
#endif

    m_balanceJudgeTimer->stop();
    disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_33_2);
    m_balanceSustionTimer->stop();
    disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_33_2);

    stopGearPumpOfTheSystem();
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP109,INTERVAL_10,SYSTEM_ALARM_ENABLE);
    emit signal_SelfCheckResult(CHECK_ITEM_OF_BALANCE_SYSTEM,SELF_CHECK_ERROR);
    if(m_selfCheckItemList.contains(CHECK_ITEM_OF_BALANCE_SYSTEM) == false)
    {
        m_selfCheckItemList << CHECK_ITEM_OF_BALANCE_SYSTEM;
    }
    emit signal_SelfCheckResult(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM,SELF_CHECK_ERROR);
    if(m_selfCheckItemList.contains(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM) == false)
    {
        m_selfCheckItemList << CHECK_ITEM_OF_SUBPRESSURE_SYSTEM;
    }
}
/*
功能描述：平衡腔自检33_3
输    入：/
输    出：/
*/
void systemSelfCheck::slot_balanceSelfCheck_33_3()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_balanceSelfCheck_33_3()：平衡腔自检33_3";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_3);

    g_data.module->balance.wr1.dpv = SYSTEM_SELF_CHECK_GEAR_PUMP_VOLAGE_VALUE_DP_33_3;
    g_data.module->balance.wr1.qpv = g_data.systemParameter.qpVoltage.m_value;
    g_data.module->balance.wr1.ypv = 0;

    g_data.module->drive.wr0.sv9_16 &= ~g_data.module->drive.DriveBoard_WR0_SV13;
    g_data.module->Sync(TAG_BALANCE_WR1 | TAG_DRIVE_WR0);

    m_balanceJudgeTimer->setInterval(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME*1000);
    connect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_33_3);
    QTimer::singleShot(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME_33_3*1000,this,[=]{m_balanceJudgeTimer->start();});

    m_balanceSustionTimer->setInterval(SYSTEM_SELF_CHECK_SUSTION_TIME_33_3*1000);
    connect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_33_3);
    m_balanceSustionTimer->start();
}
/*
功能描述：平衡腔自检33_3判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeBalanceSelfCheck_33_3()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeBalanceSelfCheck_33_3()：平衡腔自检33_3判断";
    qdebug<<debugstr;
#endif

    qint16 value_YG3 = g_data.module->drive.rd1.dp;
    if(value_YG3 > SYSTEM_SELF_CHECK_YG3_MAX_PRESSURE_33_3)
    {
        m_balanceJudgeTimer->stop();
        disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_33_3);
        m_balanceSustionTimer->stop();
        disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_33_3);

        QTimer::singleShot(SYSTEM_SELF_CHECK_CLOSE_SV5_SV11_TIME_33_3*1000,this,SLOT(slot_judgeDisposeBalanceSelfCheck_33_3()));
    }
}
/*
功能描述：平衡腔自检33_3判断处理
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeDisposeBalanceSelfCheck_33_3()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeDisposeBalanceSelfCheck_33_3()：平衡腔自检33_3判断处理";
    qdebug<<debugstr;
#endif

    g_data.module->drive.wr0.sv1_8 &= ~g_data.module->drive.DriveBoard_WR0_SV5;
    g_data.module->drive.wr0.sv9_16 &= ~g_data.module->drive.DriveBoard_WR0_SV11;

    g_data.module->Sync(TAG_DRIVE_WR0);

    QTimer::singleShot(SYSTEM_SELF_CHECK_STOP_DP_TIME_33_3*1000,this,SLOT(slot_balanceSelfCheck_33_4()));
}
/*
功能描述：平衡腔自检33_3处理
输    入：/
输    出：/
*/
void systemSelfCheck::slot_disposeBalanceSelfCheck_33_3()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_disposeBalanceSelfCheck_33_3()：平衡腔自检33_3处理";
    qdebug<<debugstr;
#endif

    m_balanceJudgeTimer->stop();
    disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_33_3);
    m_balanceSustionTimer->stop();
    disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_33_3);

    stopGearPumpOfTheSystem();

    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP110,INTERVAL_10,SYSTEM_ALARM_ENABLE);
    emit signal_SelfCheckResult(CHECK_ITEM_OF_BALANCE_SYSTEM,SELF_CHECK_ERROR);
    if(m_selfCheckItemList.contains(CHECK_ITEM_OF_BALANCE_SYSTEM) == false)
    {
        m_selfCheckItemList << CHECK_ITEM_OF_BALANCE_SYSTEM;
    }
    emit signal_SelfCheckResult(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM,SELF_CHECK_ERROR);
    if(m_selfCheckItemList.contains(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM) == false)
    {
        m_selfCheckItemList << CHECK_ITEM_OF_SUBPRESSURE_SYSTEM;
    }
}
/*
功能描述：平衡腔自检33_4
输    入：/
输    出：/
*/
void systemSelfCheck::slot_balanceSelfCheck_33_4()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_balanceSelfCheck_33_4()：平衡腔自检33_4";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_4);

    stopGearPumpOfTheSystem();

    QTimer::singleShot(SYSTEM_SELF_CHECK_OPEN_V5_V7_TIME_33_4*1000,this,SLOT(slot_balanceSelfCheck_33_5()));
}
/*
功能描述：平衡腔自检33_5
输    入：/
输    出：/
*/
void systemSelfCheck::slot_balanceSelfCheck_33_5()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_balanceSelfCheck_33_5()：平衡腔自检33_5";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_5);

    g_data.module->balance.wr1.cmd_1 |= g_data.module->balance.Balance_WR1_V5 | g_data.module->balance.Balance_WR1_V7;

    g_data.module->Sync(TAG_BALANCE_WR1);

    m_balanceJudgeTimer->setInterval(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME*1000);
    connect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_33_5);
    QTimer::singleShot(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME_33_5*1000,this,[=]{m_balanceJudgeTimer->start();});
}
/*
功能描述：平衡腔自检33_5判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeBalanceSelfCheck_33_5()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeBalanceSelfCheck_33_5()：平衡腔自检33_5判断";
    qdebug<<debugstr;
#endif

    qint16 value_YG3 = g_data.module->drive.rd1.dp;

    m_balanceJudgeTimer->stop();
    disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_33_5);

    if(value_YG3 < SYSTEM_SELF_CHECK_YG3_MAX_PRESSURE_33_5)
    {
        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP111,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        emit signal_SelfCheckResult(CHECK_ITEM_OF_BALANCE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_BALANCE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_BALANCE_SYSTEM;
        }
        emit signal_SelfCheckResult(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_SUBPRESSURE_SYSTEM;
        }
    }
    else
    {
        QTimer::singleShot(0,this,SLOT(slot_balanceSelfCheck_33_6()));
    }
}
/*
功能描述：平衡腔自检33_6
输    入：/
输    出：/
*/
void systemSelfCheck::slot_balanceSelfCheck_33_6()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_balanceSelfCheck_33_6()：平衡腔自检33_6";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_6);

    m_isCheckYG3Reveal = true;
    m_preValue = 0;
    m_YG3ChangeValue = 0;
    m_YG3Above90KpaTimes = 0;

    m_balanceJudgeTimer->setInterval(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME*1000);
    connect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_33_6);
    m_balanceJudgeTimer->start();

    m_balanceSustionTimer->setInterval(SYSTEM_SELF_CHECK_SUSTION_TIME_33_6*1000);
    connect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_33_6);
    m_balanceSustionTimer->start();
}
/*
功能描述：平衡腔自检33_6判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeBalanceSelfCheck_33_6()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeBalanceSelfCheck_33_6()：平衡腔自检33_6判断";
    qdebug<<debugstr;
#endif

    qint16 value_YG3 = g_data.module->drive.rd1.dp;

    if(m_isCheckYG3Reveal ==true)
    {
        m_isCheckYG3Reveal = false;
        m_preValue = value_YG3;
    }
    else
    {
        m_YG3ChangeValue += m_preValue - value_YG3;
        m_preValue = value_YG3;
    }

    if(m_YG3ChangeValue > SYSTEM_SELF_CHECK_YG3_REVEAL_PRESSURE_32_6)
    {
        m_balanceJudgeTimer->stop();
        disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_33_6);
        m_balanceSustionTimer->stop();
        disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_33_6);

        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP111,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        emit signal_SelfCheckResult(CHECK_ITEM_OF_BALANCE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_BALANCE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_BALANCE_SYSTEM;
        }
        emit signal_SelfCheckResult(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_SUBPRESSURE_SYSTEM;
        }
    }

    m_YG3Above90KpaTimes++;
    if(m_YG3Above90KpaTimes >12)
    {
        if(m_YG3Above90KpaTimes == 12)
        {
            g_data.module->drive.wr0.sv9_16 &= ~g_data.module->drive.DriveBoard_WR0_SV12;
        }
        if(m_YG3Above90KpaTimes == 13)
        {
            g_data.module->drive.wr0.sv1_8 |= g_data.module->drive.DriveBoard_WR0_SV3;
        }
        g_data.module->Sync(TAG_DRIVE_WR0);
    }
}
/*
功能描述：平衡腔自检33_6处理
输    入：/
输    出：/
*/
void systemSelfCheck::slot_disposeBalanceSelfCheck_33_6()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_disposeBalanceSelfCheck_33_6()：平衡腔自检33_6处理";
    qdebug<<debugstr;
#endif

    m_balanceJudgeTimer->stop();
    disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_33_6);
    m_balanceSustionTimer->stop();
    disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeBalanceSelfCheck_33_6);

    QTimer::singleShot(0,this,SLOT(slot_balanceSelfCheck_36()));
}
/*
功能描述：平衡腔自检36
输    入：/
输    出：/
*/
void systemSelfCheck::slot_balanceSelfCheck_36()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_balanceSelfCheck_36()：平衡腔自检36";
    qdebug<<debugstr;
#endif

    /*清除平衡腔自检36_*报警*/
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP116,INTERVAL_10,SYSTEM_ALARM_DISABLE);

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_36);

    releasePressureOfTheSystem();

    QTimer::singleShot(SYSTEM_SELF_CHECK_RELEASE_PRESSURE_MAX_RUN_TIME*1000,this,SLOT(slot_balanceSelfCheck_36_1()));
}
/*
功能描述：平衡腔自检36_1
输    入：/
输    出：/
*/
void systemSelfCheck::slot_balanceSelfCheck_36_1()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_balanceSelfCheck_36_1()：平衡腔自检36_1";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_36_1);

    g_data.module->balance.wr1.cmd_2 &= ~g_data.module->balance.Balance_WR1_SV14_T;
    g_data.module->balance.wr1.qpv = 0;
    g_data.module->balance.wr1.dpv = 0;
    g_data.module->balance.wr1.ypv = 0;

    /*关V1-V8*/
    g_data.module->balance.wr1.cmd_1 = 0x00;

    /*YJ1控制SV1*/
    g_data.module->drive.wr0.cmd_1 |= g_data.module->drive.DriveBoard_WR0_CTRL_SV | g_data.module->drive.DriveBoard_WR0_SV1_L;
    g_data.module->drive.wr0.cmd_1 &= ~g_data.module->drive.DriveBoard_WR0_SV1_H;

    /*开SV10，其余关*/
    g_data.module->drive.wr0.sv1_8 &= ~g_data.module->drive.DriveBoard_WR0_SV2 & ~g_data.module->drive.DriveBoard_WR0_SV3 & ~g_data.module->drive.DriveBoard_WR0_SV4\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV5 & ~g_data.module->drive.DriveBoard_WR0_SV6 & ~g_data.module->drive.DriveBoard_WR0_SV7\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV8;

    g_data.module->drive.wr0.sv9_16 |= g_data.module->drive.DriveBoard_WR0_SV10;
    g_data.module->drive.wr0.sv9_16 &= ~g_data.module->drive.DriveBoard_WR0_SV9 & ~g_data.module->drive.DriveBoard_WR0_SV11 & ~g_data.module->drive.DriveBoard_WR0_SV12\
                                       & ~g_data.module->drive.DriveBoard_WR0_SV13 & ~g_data.module->drive.DriveBoard_WR0_SV14 & ~g_data.module->drive.DriveBoard_WR0_SV15\
                                       & ~g_data.module->drive.DriveBoard_WR0_SV16;

    g_data.module->drive.wr0.sv17_24 &= ~g_data.module->drive.DriveBoard_WR0_SV17 & ~g_data.module->drive.DriveBoard_WR0_SV18 & ~g_data.module->drive.DriveBoard_WR0_SV19\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV20;

    g_data.module->Sync(TAG_BALANCE_WR1 | TAG_DRIVE_WR0);

    m_preValue = 0;

    m_balanceJudgeTimer->setInterval(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME*1000);
    connect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_36_1);
    QTimer::singleShot(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME_36_1*1000,this,[=]{m_balanceJudgeTimer->start();});
}
/*
功能描述：平衡腔自检36_1判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeBalanceSelfCheck_36_1()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeBalanceSelfCheck_36_1()：平衡腔自检36_1判断";
    qdebug<<debugstr;
#endif

    qint16 value_YG3 = g_data.module->drive.rd1.dp;

    m_preValue = value_YG3;

    m_balanceJudgeTimer->stop();
    disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeBalanceSelfCheck_36_1);
    QTimer::singleShot(0,this,SLOT(slot_balanceSelfCheck_36_2()));
}
/*
功能描述：平衡腔自检36_2
输    入：/
输    出：/
*/
void systemSelfCheck::slot_balanceSelfCheck_36_2()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_balanceSelfCheck_36_2()：平衡腔自检36_2";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_36_2);
    emit signal_SelfCheckStart(CHECK_ITEM_OF_ULTRATILTRATION_SYSTEM,SYSTEM_SELF_CHECK_ULTRATILTRATION_CHECK_MAX_TIME*1000);

    g_data.module->ufPump.wr0.cmd_1 |= g_data.module->ufPump.UlterFilterPlate_WR0_SR | g_data.module->ufPump.UlterFilterPlate_WR0_Z;
    g_data.module->ufPump.wr0.cmd_1 &= ~g_data.module->ufPump.UlterFilterPlate_WR0_T;

    g_data.module->ufPump.wr0.fph = SYSTEM_SELF_CHECK_ITEM_HYPERFILTRATION_PUMP_FLOW_36_2;

    g_data.module->drive.wr0.cmd_1 |= g_data.module->drive.DriveBoard_WR0_CTRL_SV | g_data.module->drive.DriveBoard_WR0_SV1_L;
    g_data.module->drive.wr0.cmd_1 &= ~g_data.module->drive.DriveBoard_WR0_SV1_H;

    g_data.module->drive.wr0.sv1_8 &= ~g_data.module->drive.DriveBoard_WR0_SV5;
    g_data.module->drive.wr0.sv9_16 &= ~g_data.module->drive.DriveBoard_WR0_SV11;

    g_data.module->Sync(TAG_DRIVE_WR0 | TAG_UFPUMP_WR0);
    QTimer::singleShot(SYSTEM_SELF_CHECK_STOP_HYPERFILTRATION_PUMP_TIME_36_2*1000,this,SLOT(slot_disposeBalanceSelfCheck_36_2()));
}
/*
功能描述：平衡腔自检36_2判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeBalanceSelfCheck_36_2()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeBalanceSelfCheck_36_2()：平衡腔自检36_2判断";
    qdebug<<debugstr;
#endif

    qint16 value_YG3 = g_data.module->drive.rd1.dp;

    m_YG3ChangeValue = m_preValue - value_YG3;

    if(m_YG3ChangeValue < SYSTEM_SELF_CHECK_YG3_CHANGE_PRESSURE_36_2)
    {
        stopGearPumpOfTheSystem();

        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP116,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        emit signal_SelfCheckResult(CHECK_ITEM_OF_BALANCE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_BALANCE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_BALANCE_SYSTEM;
        }
        emit signal_SelfCheckResult(CHECK_ITEM_OF_ULTRATILTRATION_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_ULTRATILTRATION_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_ULTRATILTRATION_SYSTEM;
        }
        emit signal_SelfCheckResult(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_SUBPRESSURE_SYSTEM;
        }
    }
    else
    {
        QTimer::singleShot(0,this,SLOT(slot_judgeBalanceSelfCheck()));
    }
}
/*
功能描述：平衡腔自检36_2处理
输    入：/
输    出：/
*/
void systemSelfCheck::slot_disposeBalanceSelfCheck_36_2()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_disposeBalanceSelfCheck_36_2()：平衡腔自检36_2处理";
    qdebug<<debugstr;
#endif

    g_data.module->ufPump.wr0.cmd_1  &= ~g_data.module->ufPump.UlterFilterPlate_WR0_SR;
    g_data.module->Sync(TAG_UFPUMP_WR0);

    QTimer::singleShot(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME*1000,this,SLOT(slot_judgeBalanceSelfCheck_36_2()));
}
/*
功能描述：平衡腔自检完成判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeBalanceSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeBalanceSelfCheck()：平衡腔自检完成判断";
    qdebug<<debugstr;
#endif

    stopGearPumpOfTheSystem();

    g_data.module->drive.wr0.sv9_16 |= g_data.module->drive.DriveBoard_WR0_SV12;
    g_data.module->ufPump.wr0.cmd_1 &= ~g_data.module->ufPump.UlterFilterPlate_WR0_SR;
    g_data.module->Sync(TAG_DRIVE_WR0 | TAG_UFPUMP_WR0);

    emit signal_SelfCheckResult(CHECK_ITEM_OF_BALANCE_SYSTEM,SELF_CHECK_CORRECT);
    if(m_selfCheckItemList.contains(CHECK_ITEM_OF_BALANCE_SYSTEM) == true)
    {
        m_selfCheckItemList.removeOne(CHECK_ITEM_OF_BALANCE_SYSTEM);
    }
    emit signal_SelfCheckResult(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM,SELF_CHECK_CORRECT);
    if(m_selfCheckItemList.contains(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM) == true)
    {
        m_selfCheckItemList.removeOne(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM);
    }
    emit signal_SelfCheckResult(CHECK_ITEM_OF_ULTRATILTRATION_SYSTEM,SELF_CHECK_CORRECT);
    if(m_selfCheckItemList.contains(CHECK_ITEM_OF_ULTRATILTRATION_SYSTEM) == true)
    {
        m_selfCheckItemList.removeOne(CHECK_ITEM_OF_ULTRATILTRATION_SYSTEM);
    }

    /*启动内毒素自检*/
    if(m_checkItem_endotoxin == false)
    {
        endotoxinSelfCheck();
    }
}
/*
功能描述：内毒素自检11
输    入：/
输    出：/
*/
void systemSelfCheck::slot_endotoxinSelfCheck_11()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_endotoxinSelfCheck_11()：内毒素自检11";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM,SYSTEM_SELF_CHECK_ENDOTOXIN_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_11);
    g_data.module->heat.wr0.cmd_1 &= ~g_data.module->heat.Heat_WR0_SR;
    g_data.module->mixture.wr0.cmd_1 &= ~g_data.module->mixture.Mixture_WR0_WORK_MOD_STOP;
    g_data.module->ufPump.wr0.cmd_1 &= ~g_data.module->ufPump.UlterFilterPlate_WR0_SR;
    g_data.module->Sync(TAG_HEAT_WR0 | TAG_MIXTURE_WR0 | TAG_UFPUMP_WR0);

    releasePressureOfTheSystem();

    QTimer::singleShot(SYSTEM_SELF_CHECK_ENDOTOXIN_CHECK_CONTAINUE_TIME_11*1000,this,SLOT(slot_endotoxinSelfCheck_12_1()));
}
/*
功能描述：内毒素自检12_1
输    入：/
输    出：/
*/
void systemSelfCheck::slot_endotoxinSelfCheck_12_1()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_endotoxinSelfCheck_12_1()：内毒素自检12_1";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM,SYSTEM_SELF_CHECK_ENDOTOXIN_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_1);

    g_data.module->balance.wr1.qpv = g_data.systemParameter.qpVoltage.m_value;
    g_data.module->balance.wr1.dpv = 0;
    g_data.module->balance.wr1.ypv = SYSTEM_SELF_CHECK_GEAR_PUMP_VOLAGE_VALUE_YP_12_1;

    /*开v1、v5，其余关*/
    g_data.module->balance.wr1.cmd_1 |= g_data.module->balance.Balance_WR1_V1 | g_data.module->balance.Balance_WR1_V5;
    g_data.module->balance.wr1.cmd_1 &= ~g_data.module->balance.Balance_WR1_V2 & ~g_data.module->balance.Balance_WR1_V3 & ~g_data.module->balance.Balance_WR1_V4\
                                        & ~g_data.module->balance.Balance_WR1_V6 & ~g_data.module->balance.Balance_WR1_V7 & ~g_data.module->balance.Balance_WR1_V8;

    /*SV1关*/
    g_data.module->drive.wr0.cmd_1 |= g_data.module->drive.DriveBoard_WR0_CTRL_SV | g_data.module->drive.DriveBoard_WR0_SV1_L | g_data.module->drive.DriveBoard_WR0_SV1_H;

    /*开SV10、sv11，其余关*/
    g_data.module->drive.wr0.sv1_8 &= ~g_data.module->drive.DriveBoard_WR0_SV2 & ~g_data.module->drive.DriveBoard_WR0_SV3 & ~g_data.module->drive.DriveBoard_WR0_SV4\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV5 & ~g_data.module->drive.DriveBoard_WR0_SV6 & ~g_data.module->drive.DriveBoard_WR0_SV7\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV8;

    g_data.module->drive.wr0.sv9_16 |= g_data.module->drive.DriveBoard_WR0_SV10 | g_data.module->drive.DriveBoard_WR0_SV11;
    g_data.module->drive.wr0.sv9_16 &= ~g_data.module->drive.DriveBoard_WR0_SV9 & ~g_data.module->drive.DriveBoard_WR0_SV12 & ~g_data.module->drive.DriveBoard_WR0_SV13\
                                       & ~g_data.module->drive.DriveBoard_WR0_SV14 & ~g_data.module->drive.DriveBoard_WR0_SV15 & ~g_data.module->drive.DriveBoard_WR0_SV16;

    g_data.module->drive.wr0.sv17_24 &= ~g_data.module->drive.DriveBoard_WR0_SV17 & ~g_data.module->drive.DriveBoard_WR0_SV18 & ~g_data.module->drive.DriveBoard_WR0_SV19\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV20;

    g_data.module->Sync(TAG_BALANCE_WR1 | TAG_DRIVE_WR0);

    m_endotoxinCheckTimes = BALANCE_CHECK_ENDOTOXIN_JUDGE_TIMES;

    m_balanceJudgeTimer->setInterval(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME*1000);
    connect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeEndotoxinSelfCheck_12_1);
    m_balanceJudgeTimer->start();

    m_balanceSustionTimer->setInterval(SYSTEM_SELF_CHECK_SUSTION_TIME_12_1*1000);
    connect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeEndotoxinSelfCheck_12_1);
    m_balanceSustionTimer->start();
}
/*
功能描述：内毒素自检12_1判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeEndotoxinSelfCheck_12_1()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeEndotoxinSelfCheck_12_1()：内毒素自检12_1判断";
    qdebug<<debugstr;
#endif

    qint16 value_YG3 = g_data.module->drive.rd1.dp;

    if(value_YG3 < SYSTEM_SELF_CHECK_YG3_MAX_PRESSURE_12_1)
    {
        m_endotoxinCheckTimes--;
    }
    else
    {
        m_endotoxinCheckTimes = BALANCE_CHECK_ENDOTOXIN_JUDGE_TIMES;
    }

    if(m_endotoxinCheckTimes <= 0)
    {
        m_balanceJudgeTimer->stop();
        disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeEndotoxinSelfCheck_12_1);
        m_balanceSustionTimer->stop();
        disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeEndotoxinSelfCheck_12_1);

        QTimer::singleShot(0,this,SLOT(slot_endotoxinSelfCheck_12_2()));
    }
}
/*
功能描述：内毒素自检12_1处理
输    入：/
输    出：/
*/
void systemSelfCheck::slot_disposeEndotoxinSelfCheck_12_1()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_disposeEndotoxinSelfCheck_12_1()：内毒素自检12_1处理";
    qdebug<<debugstr;
#endif

    m_balanceJudgeTimer->stop();
    disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeEndotoxinSelfCheck_12_1);
    m_balanceSustionTimer->stop();
    disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeEndotoxinSelfCheck_12_1);

    stopGearPumpOfTheSystem();

    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_ENDOTOXIN_FILTE_SELF_CHECK_ZN120,INTERVAL_10,SYSTEM_ALARM_ENABLE);
    emit signal_SelfCheckResult(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM,SELF_CHECK_ERROR);
    if(m_selfCheckItemList.contains(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM) == false)
    {
        m_selfCheckItemList << CHECK_ITEM_OF_ENDOTOXIN_SYSTEM;
    }
}
/*
功能描述：内毒素自检12_2
输    入：/
输    出：/
*/
void systemSelfCheck::slot_endotoxinSelfCheck_12_2()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_endotoxinSelfCheck_12_2()：内毒素自检12_2";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM,SYSTEM_SELF_CHECK_ENDOTOXIN_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_2);

    g_data.module->drive.wr0.sv9_16 |= g_data.module->drive.DriveBoard_WR0_SV15;
    g_data.module->Sync(TAG_DRIVE_WR0);

    m_balanceJudgeTimer->setInterval(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME*1000);
    connect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeEndotoxinSelfCheck_12_2);
    QTimer::singleShot(SYSTEM_SELF_CHECK_OPEN_SV15_TIME_12_2*1000,this,[=]{m_balanceJudgeTimer->start();});

    m_balanceSustionTimer->setInterval(SYSTEM_SELF_CHECK_SUSTION_TIME_12_2*1000);
    connect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeEndotoxinSelfCheck_12_2);
    m_balanceSustionTimer->start();
}
/*
功能描述：内毒素自检12_2判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeEndotoxinSelfCheck_12_2()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeEndotoxinSelfCheck_12_2()：内毒素自检12_2判断";
    qdebug<<debugstr;
#endif

    qint16 value_YG3 = g_data.module->drive.rd1.dp;

    if(value_YG3 < SYSTEM_SELF_CHECK_YG3_MAX_PRESSURE_12_2)
    {
        m_balanceJudgeTimer->stop();
        disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeEndotoxinSelfCheck_12_2);
        m_balanceSustionTimer->stop();
        disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeEndotoxinSelfCheck_12_2);

        QTimer::singleShot(0,this,SLOT(slot_endotoxinSelfCheck_12_3()));
    }
}
/*
功能描述：内毒素自检12_2处理
输    入：/
输    出：/
*/
void systemSelfCheck::slot_disposeEndotoxinSelfCheck_12_2()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_disposeEndotoxinSelfCheck_12_2()：内毒素自检12_2处理";
    qdebug<<debugstr;
#endif

    m_balanceJudgeTimer->stop();
    disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeEndotoxinSelfCheck_12_2);
    m_balanceSustionTimer->stop();
    disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeEndotoxinSelfCheck_12_2);

    stopGearPumpOfTheSystem();

    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_ENDOTOXIN_FILTE_SELF_CHECK_ZN121,INTERVAL_10,SYSTEM_ALARM_ENABLE);
    emit signal_SelfCheckResult(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM,SELF_CHECK_ERROR);
    if(m_selfCheckItemList.contains(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM) == false)
    {
        m_selfCheckItemList << CHECK_ITEM_OF_ENDOTOXIN_SYSTEM;
    }
}
/*
功能描述：内毒素自检12_3
输    入：/
输    出：/
*/
void systemSelfCheck::slot_endotoxinSelfCheck_12_3()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_endotoxinSelfCheck_12_3()：内毒素自检12_3";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM,SYSTEM_SELF_CHECK_ENDOTOXIN_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_3);

    g_data.module->balance.wr1.dpv = 0;
    g_data.module->balance.wr1.ypv = 0;
    g_data.module->balance.wr1.qpv = 0;

    g_data.module->balance.wr1.cmd_1 &= ~g_data.module->balance.Balance_WR1_V1 & ~g_data.module->balance.Balance_WR1_V5;

    g_data.module->Sync(TAG_BALANCE_WR1);

    QTimer::singleShot(SYSTEM_SELF_CHECK_SUSTION_TIME_12_3*1000,this,SLOT(slot_endotoxinSelfCheck_12_4()));
}
/*
功能描述：内毒素自检12_4
输    入：/
输    出：/
*/
void systemSelfCheck::slot_endotoxinSelfCheck_12_4()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_endotoxinSelfCheck_12_4()：内毒素自检12_4";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM,SYSTEM_SELF_CHECK_ENDOTOXIN_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_4);

    g_data.module->ufPump.wr0.cmd_1 |= g_data.module->ufPump.UlterFilterPlate_WR0_SR | g_data.module->ufPump.UlterFilterPlate_WR0_Z;
    g_data.module->ufPump.wr0.cmd_1 &= ~g_data.module->ufPump.UlterFilterPlate_WR0_T;

    g_data.module->ufPump.wr0.fpr = SYSTEM_SELF_CHECK_ITEM_HYPERFILTRATION_PUMP_FPR_12_4;
    g_data.module->ufPump.wr0.fph = SYSTEM_SELF_CHECK_ITEM_HYPERFILTRATION_PUMP_FPH_12_4;

    g_data.module->Sync(TAG_BALANCE_WR0);

    QTimer::singleShot(SYSTEM_SELF_CHECK_SUSTION_TIME_12_4*1000,this,SLOT(slot_endotoxinSelfCheck_12_5()));
}
/*
功能描述：内毒素自检12_5
输    入：/
输    出：/
*/
void systemSelfCheck::slot_endotoxinSelfCheck_12_5()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_endotoxinSelfCheck_12_5()：内毒素自检12_5";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM,SYSTEM_SELF_CHECK_ENDOTOXIN_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_5);

    m_endotoxinCheckTimes = BALANCE_CHECK_ENDOTOXIN_JUDGE_TIMES;

    m_balanceJudgeTimer->setInterval(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME*1000);
    connect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeEndotoxinSelfCheck_12_5);
    m_balanceJudgeTimer->start();

    m_balanceSustionTimer->setInterval(SYSTEM_SELF_CHECK_SUSTION_TIME_12_5*1000);
    connect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeEndotoxinSelfCheck_12_5);
    m_balanceSustionTimer->start();
}
/*
功能描述：内毒素自检12_5判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeEndotoxinSelfCheck_12_5()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeEndotoxinSelfCheck_12_5()：内毒素自检12_5判断";
    qdebug<<debugstr;
#endif

    qint16 value_YG3 = g_data.module->drive.rd1.dp;

    if(value_YG3 < SYSTEM_SELF_CHECK_YG3_MAX_PRESSURE_12_5)
    {
        m_endotoxinCheckTimes--;
    }
    else
    {
        m_endotoxinCheckTimes = BALANCE_CHECK_ENDOTOXIN_JUDGE_TIMES;
    }

    if(m_endotoxinCheckTimes <= 0)
    {
        m_balanceJudgeTimer->stop();
        disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeEndotoxinSelfCheck_12_5);
        m_balanceSustionTimer->stop();
        disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeEndotoxinSelfCheck_12_5);

        QTimer::singleShot(0,this,SLOT(slot_endotoxinSelfCheck_13()));
    }
}
/*
功能描述：内毒素自检12_5处理
输    入：/
输    出：/
*/
void systemSelfCheck::slot_disposeEndotoxinSelfCheck_12_5()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_disposeEndotoxinSelfCheck_12_5()：内毒素自检12_5处理";
    qdebug<<debugstr;
#endif

    m_balanceJudgeTimer->stop();
    disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeEndotoxinSelfCheck_12_5);
    m_balanceSustionTimer->stop();
    disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeEndotoxinSelfCheck_12_5);

    g_data.module->ufPump.wr0.cmd_1 &= ~g_data.module->ufPump.UlterFilterPlate_WR0_SR;
    g_data.module->Sync(TAG_UFPUMP_WR0);

    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_ENDOTOXIN_FILTE_SELF_CHECK_ZN121,INTERVAL_10,SYSTEM_ALARM_ENABLE);
    emit signal_SelfCheckResult(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM,SELF_CHECK_ERROR);
    if(m_selfCheckItemList.contains(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM) == false)
    {
        m_selfCheckItemList << CHECK_ITEM_OF_ENDOTOXIN_SYSTEM;
    }
}
/*
功能描述：内毒素自检13
输    入：/
输    出：/
*/
void systemSelfCheck::slot_endotoxinSelfCheck_13()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_endotoxinSelfCheck_13()：内毒素自检13";
    qdebug<<debugstr;
#endif
    emit signal_SelfCheckStart(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM,SYSTEM_SELF_CHECK_ENDOTOXIN_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_13);

    g_data.module->ufPump.wr0.cmd_1 &= ~g_data.module->ufPump.UlterFilterPlate_WR0_SR;
    g_data.module->Sync(TAG_UFPUMP_WR0);

    m_preValue = 0;

    m_balanceJudgeTimer->setInterval(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME*1000);
    connect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeEndotoxinSelfCheck_13);
    QTimer::singleShot(SYSTEM_SELF_CHECK_SUSTION_TIME_13*1000,this,[=]{m_balanceJudgeTimer->start();});
}
/*
功能描述：内毒素自检13判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeEndotoxinSelfCheck_13()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeEndotoxinSelfCheck_13()：内毒素自检13判断";
    qdebug<<debugstr;
#endif

    m_balanceJudgeTimer->stop();
    disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeEndotoxinSelfCheck_13);

    qint16 value_YG3 = g_data.module->drive.rd1.dp;
    m_preValue = value_YG3;

    if(value_YG3 > SYSTEM_SELF_CHECK_YG3_MAX_PRESSURE_13)
    {
        g_data.module->drive.wr0.sv9_16 &= ~g_data.module->drive.DriveBoard_WR0_SV15;
        g_data.module->Sync(TAG_DRIVE_WR0);

        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_ENDOTOXIN_FILTE_SELF_CHECK_ZN121,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        emit signal_SelfCheckResult(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_ENDOTOXIN_SYSTEM;
        }
    }
    else
    {
        QTimer::singleShot(0,this,SLOT(slot_endotoxinSelfCheck_14()));
    }
}
/*
功能描述：内毒素自检14
输    入：/
输    出：/
*/
void systemSelfCheck::slot_endotoxinSelfCheck_14()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_endotoxinSelfCheck_14()：内毒素自检14";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM,SYSTEM_SELF_CHECK_ENDOTOXIN_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_14);

    m_YG3ChangeValue = 0;

    m_balanceJudgeTimer->setInterval(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME*1000);
    connect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeEndotoxinSelfCheck_14);
    QTimer::singleShot(SYSTEM_SELF_CHECK_SUSTION_TIME_14*1000,this,[=]{m_balanceJudgeTimer->start();});
}
/*
功能描述：内毒素自检14判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeEndotoxinSelfCheck_14()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeEndotoxinSelfCheck_14()：内毒素自检14判断";
    qdebug<<debugstr;
#endif

    m_balanceJudgeTimer->stop();
    disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeEndotoxinSelfCheck_14);

    qint16 value_YG3 = g_data.module->drive.rd1.dp;

    m_YG3ChangeValue = m_preValue - value_YG3;

    g_data.module->drive.wr0.sv9_16 &= ~g_data.module->drive.DriveBoard_WR0_SV15;
    g_data.module->Sync(TAG_DRIVE_WR0);

    if(abs(m_YG3ChangeValue) > SYSTEM_SELF_CHECK_YG3_REVEAL_PRESSURE_14)
    {
        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_ENDOTOXIN_FILTE_SELF_CHECK_ZN121,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        emit signal_SelfCheckResult(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM) == false)
        {
            m_selfCheckItemList << CHECK_ITEM_OF_ENDOTOXIN_SYSTEM;
        }
    }
    else
    {
        QTimer::singleShot(0,this,SLOT(slot_endotoxinSelfCheck_15_1()));
    }
}
/*
功能描述：内毒素自检15_1
输    入：/
输    出：/
*/
void systemSelfCheck::slot_endotoxinSelfCheck_15_1()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_endotoxinSelfCheck_15_1()：内毒素自检15_1";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM,SYSTEM_SELF_CHECK_ENDOTOXIN_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_15_1);

    g_data.module->balance.wr0.qpv = g_data.systemParameter.qpVoltage.m_value;
    g_data.module->balance.wr0.cmd_1 = g_data.module->balance.Balance_WR0_WORK_MODEL_NORMAL;
    g_data.module->balance.wr0.flow = 500;

    /*YJ1控制SV1*/
    g_data.module->drive.wr0.cmd_1 |= g_data.module->drive.DriveBoard_WR0_CTRL_SV | g_data.module->drive.DriveBoard_WR0_SV1_L;
    g_data.module->drive.wr0.cmd_1 &= ~g_data.module->drive.DriveBoard_WR0_SV1_H;

    /*开SV10、11、13，其余关*/
    g_data.module->drive.wr0.sv1_8 &= ~g_data.module->drive.DriveBoard_WR0_SV2 & ~g_data.module->drive.DriveBoard_WR0_SV3 & ~g_data.module->drive.DriveBoard_WR0_SV4\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV5 & ~g_data.module->drive.DriveBoard_WR0_SV6 & ~g_data.module->drive.DriveBoard_WR0_SV7\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV8;

    g_data.module->drive.wr0.sv9_16 |= g_data.module->drive.DriveBoard_WR0_SV10 | g_data.module->drive.DriveBoard_WR0_SV11 | g_data.module->drive.DriveBoard_WR0_SV13;
    g_data.module->drive.wr0.sv9_16 &= ~g_data.module->drive.DriveBoard_WR0_SV9 & ~g_data.module->drive.DriveBoard_WR0_SV12 & ~g_data.module->drive.DriveBoard_WR0_SV14\
                                       & ~g_data.module->drive.DriveBoard_WR0_SV15 & ~g_data.module->drive.DriveBoard_WR0_SV16;

    g_data.module->drive.wr0.sv17_24 &= ~g_data.module->drive.DriveBoard_WR0_SV17 & ~g_data.module->drive.DriveBoard_WR0_SV18 & ~g_data.module->drive.DriveBoard_WR0_SV19\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV20;

    g_data.module->Sync(TAG_BALANCE_WR0 | TAG_DRIVE_WR0);

    QTimer::singleShot(SYSTEM_SELF_CHECK_SUSTION_TIME_15_1*1000,this,SLOT(slot_endotoxinSelfCheck_15_2()));
}
/*
功能描述：内毒素自检15_2
输    入：/
输    出：/
*/
void systemSelfCheck::slot_endotoxinSelfCheck_15_2()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_endotoxinSelfCheck_15_2()：内毒素自检15_2";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM,SYSTEM_SELF_CHECK_ENDOTOXIN_CHECK_MAX_TIME*1000,CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_15_2);

    g_data.module->drive.wr0.sv1_8 |= g_data.module->drive.DriveBoard_WR0_SV5;
    g_data.module->drive.wr0.sv9_16 &= ~g_data.module->drive.DriveBoard_WR0_SV11;
    g_data.module->Sync(TAG_DRIVE_WR0);

    if(m_reCheckEndotoxin15 == true)
    {
        m_reCheckEndotoxin15 = false;
        QTimer::singleShot(SYSTEM_SELF_CHECK_SUSTION_TIME_15_2*1000,this,SLOT(slot_endotoxinSelfCheck_15_1()));
    }
    else
    {
        m_reCheckEndotoxin15 = true;
        QTimer::singleShot(SYSTEM_SELF_CHECK_SUSTION_TIME_15_2*1000,this,SLOT(slot_judgeendotoxinSelfCheck()));
    }
}
/*
功能描述：内毒素自检完成判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeendotoxinSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeendotoxinSelfCheck()：内毒素自检完成判断";
    qdebug<<debugstr;
#endif

    g_data.module->balance.wr0.cmd_1 = g_data.module->balance.Balance_WR0_WORK_MODEL_STOP;
    g_data.module->Sync(TAG_BALANCE_WR0);

    emit signal_SelfCheckResult(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM,SELF_CHECK_CORRECT);
    if(m_selfCheckItemList.contains(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM) == true)
    {
        m_selfCheckItemList.removeOne(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM);
    }

    if(m_checkItem_liquor == false)
    {
        /*启动配液自检*/
        liquorSelfCheck();
    }
    if(m_checkItem_temp == false)
    {
        /*启动加热自检*/
        dialystateTempSelfCheck();
    }
}
/*
功能描述：加热自检
输    入：/
输    出：/
*/
void systemSelfCheck::slot_dialystateTempSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_dialystateTempSelfCheck()：加热自检";
    qdebug<<debugstr;
#endif

    qint16 value_TEMP = g_data.module->mixture.rd0.rtAtemp;

    m_preTempValue = value_TEMP;
    m_isCheckTempReveal = false;

    startBalanceSystem();

    g_data.module->heat.wr0.cmd_1 |= g_data.module->heat.Heat_WR0_SR;
    g_data.module->heat.wr0.temp = SYSTEM_SELF_CHECK_HEAT_CHECK_TARGET_TEMP;
    g_data.module->heat.wr0.alarm_h = SYSTEM_SELF_CHECK_HEAT_CHECK_TARGET_TEMP + 50;
    g_data.module->heat.wr0.alarm_l = SYSTEM_SELF_CHECK_HEAT_CHECK_TARGET_TEMP - 50;
    g_data.module->heat.wr0.flow = 500;
    g_data.module->heat.wr1.adjust = g_data.systemParameter.temp_Comp.m_value;
    g_data.module->Sync(TAG_HEAT_WR0 | TAG_HEAT_WR1);

    m_balanceJudgeTimer->setInterval(SYSTEM_SELF_CHECK_ITEM_JUDGE_TIME*1000);
    connect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeDialystateTempSelfCheck);
    m_balanceJudgeTimer->start();

    m_balanceSustionTimer->setInterval(SYSTEM_SELF_CHECK_HEAT_CHECK_OVER_TIME*1000);
    connect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeDialystateTempSelfCheck);
    m_balanceSustionTimer->start();
}
/*
功能描述：加热自检判断
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeDialystateTempSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeDialystateTempSelfCheck()：加热自检判断";
    qdebug<<debugstr;
#endif

    qint16 value_TEMP = g_data.module->mixture.rd0.rtAtemp;

    m_TempChangeValue += m_preTempValue - value_TEMP;
    m_preTempValue = value_TEMP;

    if(value_TEMP > SYSTEM_SELF_CHECK_HEAT_CHECK_MIN_TEMP || abs(m_TempChangeValue) > SYSTEM_SELF_CHECK_HEAT_CHECK_CHANGE_TEMP)
    {
        m_balanceJudgeTimer->stop();
        disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeDialystateTempSelfCheck);
        m_balanceSustionTimer->stop();
        disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeDialystateTempSelfCheck);

        stopDialysateTempSystem();
        stopBalanceSyatem();

        emit signal_SelfCheckResult(CHECK_ITEM_OF_HEAT_SYSTEM,SELF_CHECK_CORRECT);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_HEAT_SYSTEM) == true)
        {
            m_selfCheckItemList.removeOne(CHECK_ITEM_OF_HEAT_SYSTEM);
        }
    }
}
/*
功能描述：加热自检处理
输    入：/
输    出：/
*/
void systemSelfCheck::slot_disposeDialystateTempSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_disposeDialystateTempSelfCheck()：加热自检处理";
    qdebug<<debugstr;
#endif

    m_balanceJudgeTimer->stop();
    disconnect(m_balanceJudgeTimer,&QTimer::timeout,this,&systemSelfCheck::slot_judgeDialystateTempSelfCheck);
    m_balanceSustionTimer->stop();
    disconnect(m_balanceSustionTimer,&QTimer::timeout,this,&systemSelfCheck::slot_disposeDialystateTempSelfCheck);

    stopDialysateTempSystem();
    stopBalanceSyatem();

    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_DIALYSATE_TEMPERATURE_SELF_CHECK,INTERVAL_10,SYSTEM_ALARM_ENABLE);
    emit signal_SelfCheckResult(CHECK_ITEM_OF_HEAT_SYSTEM,SELF_CHECK_ERROR);
    if(m_selfCheckItemList.contains(CHECK_ITEM_OF_HEAT_SYSTEM) == false)
    {
        m_selfCheckItemList << CHECK_ITEM_OF_HEAT_SYSTEM;
    }
}

/*
功能描述：判断A/B吸液管状态
输    入：/
输    出：/
*/
void systemSelfCheck::slot_judgeABSutionTubeStatus()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::slot_judgeABSutionTubeStatus()：判断A/B吸液管状态";
    qdebug<<debugstr;
#endif

    bool status_A = (bool)(g_data.module->drive.rd0.std_2 & g_data.module->drive.DriveBoard_RD0_CAJ);
    bool status_B = (bool)(g_data.module->drive.rd0.std_2 & g_data.module->drive.DriveBoard_RD0_CBJ);

    if(status_A != true && status_B != true)
    {
        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_LIQUID_A_B_STRAWS_INTO_LIQUID_A_B,INTERVAL_30,SYSTEM_ALARM_ENABLE);
        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_LIQUID_A_STRAWS_INTO_LIQUID_A,INTERVAL_30,SYSTEM_ALARM_DISABLE);
        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_LIQUID_B_STRAWS_INTO_LIQUID_B,INTERVAL_30,SYSTEM_ALARM_DISABLE);
    }
    else if(status_A != true)
    {
        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_LIQUID_A_STRAWS_INTO_LIQUID_A,INTERVAL_30,SYSTEM_ALARM_ENABLE);
        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_LIQUID_A_B_STRAWS_INTO_LIQUID_A_B,INTERVAL_30,SYSTEM_ALARM_DISABLE);
        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_LIQUID_B_STRAWS_INTO_LIQUID_B,INTERVAL_30,SYSTEM_ALARM_DISABLE);
    }
    else if(status_B != true)
    {
        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_LIQUID_B_STRAWS_INTO_LIQUID_B,INTERVAL_30,SYSTEM_ALARM_ENABLE);
        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_LIQUID_A_B_STRAWS_INTO_LIQUID_A_B,INTERVAL_30,SYSTEM_ALARM_DISABLE);
        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_LIQUID_A_STRAWS_INTO_LIQUID_A,INTERVAL_30,SYSTEM_ALARM_DISABLE);
    }
    else
    {
        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_LIQUID_A_B_STRAWS_INTO_LIQUID_A_B,INTERVAL_30,SYSTEM_ALARM_DISABLE);
        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_LIQUID_A_STRAWS_INTO_LIQUID_A,INTERVAL_30,SYSTEM_ALARM_DISABLE);
        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_LIQUID_B_STRAWS_INTO_LIQUID_B,INTERVAL_30,SYSTEM_ALARM_DISABLE);
    }
}
/*
功能描述：监控系统检测
输    入：/
输    出：/
*/
void systemSelfCheck::monitorSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::monitorSelfCheck()：监控系统检测";
    qdebug<<debugstr;
#endif

    /*清除监控系统自检相关报警*/
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_GAS_SELF_CHECK,INTERVAL_10,SYSTEM_ALARM_DISABLE);
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BLOOD_LEAK_SELF_CHECK,INTERVAL_10,SYSTEM_ALARM_DISABLE);
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BLOOD_SELF_CHECK,INTERVAL_10,SYSTEM_ALARM_DISABLE);

    emit signal_SelfCheckStart(CHECK_ITEM_OF_MONITOR_SYSTEM,SYSTEM_SELF_CHECK_MONITOR_CHECK_MAX_TIME*1000);
    m_checkItem_monitor = true;

    bool status_GAS = (bool)(g_data.module->drive.rd0.std_1 & g_data.module->drive.DriveBoard_RD0_GAS);
    bool status_BLD = (bool)(g_data.module->drive.rd0.std_1 & g_data.module->drive.DriveBoard_RD0_BLD);
    bool status_BLOOD = (bool)(g_data.module->drive.rd0.std_1 & g_data.module->drive.DriveBoard_RD0_BLOOD);

    if(status_GAS == true && status_BLD == true && status_BLOOD == true)
    {
        emit signal_SelfCheckResult(CHECK_ITEM_OF_MONITOR_SYSTEM,SELF_CHECK_CORRECT);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_MONITOR_SYSTEM) == true)
        {
            m_selfCheckItemList.removeOne(CHECK_ITEM_OF_MONITOR_SYSTEM);
        }

        if(m_checkItem_choke == false)
        {
            /*启动阻流夹自检*/
            chokedFlowMonitorSelfCheck();
        }
    }
    else
    {
        emit signal_SelfCheckResult(CHECK_ITEM_OF_MONITOR_SYSTEM,SELF_CHECK_ERROR);
        if(m_selfCheckItemList.contains(CHECK_ITEM_OF_MONITOR_SYSTEM) == false)
        {
            m_selfCheckItemList<<CHECK_ITEM_OF_MONITOR_SYSTEM;
        }

        if(status_GAS == false)
        {
            emit signal_sendAlarmData(SYSTEM_ERROR_CODE_GAS_SELF_CHECK,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        }
        if(status_BLD == false)
        {
            emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BLOOD_LEAK_SELF_CHECK,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        }
        if(status_BLOOD == false)
        {
            emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BLOOD_SELF_CHECK,INTERVAL_10,SYSTEM_ALARM_ENABLE);
        }
    }
}
/*
功能描述：血路系统检测
输    入：/
输    出：/
*/
void systemSelfCheck::bloodPumpSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::bloodPumpSelfCheck()：血路系统检测";
    qdebug<<debugstr;
#endif

    /*清除血路系统自检相关报警*/
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BLOOD_PUMP_SELF_CHECK,INTERVAL_10,SYSTEM_ALARM_DISABLE);

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BLOOD_SYSTEM,SYSTEM_SELF_CHECK_BLOOD_CHECK_MAX_TIME*1000);
    m_checkItem_bloodPump = true;

    g_data.module->bloodPump.wr0.cmd_1 = g_data.module->bloodPump.DCmotor_WR0_M1 | g_data.module->bloodPump.DCmotor_WR0_M0 | g_data.module->bloodPump.DCmotor_WR0_SR;
    g_data.module->Sync(TAG_BLOOD_WR0);

    QTimer::singleShot(SYSTEM_SELF_CHECK_BLOOD_CHECK_MAX_TIME*1000,this,SLOT(slot_judgeBloodPumpSelfCheck()));
}
/*
功能描述：补液系统检测
输    入：/
输    出：/
*/
void systemSelfCheck::fluidinfusionPumpSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::fluidinfusionPumpSelfCheck()：补液系统检测";
    qdebug<<debugstr;
#endif

    /*清除补液系统自检相关报警*/
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_FLUID_INFUSION_PUMP_SELF_CHECK,INTERVAL_10,SYSTEM_ALARM_DISABLE);

    emit signal_SelfCheckStart(CHECK_ITEM_OF_FLUID_INFUSION_SYSTEM,SYSTEM_SELF_CHECK_FLUID_CHECK_MAX_TIME*1000);
    m_checkItem_fluidPump = true;

    g_data.module->fuildPump.wr0.cmd_1 = g_data.module->fuildPump.DCmotor_WR0_M1 | g_data.module->fuildPump.DCmotor_WR0_M0 | g_data.module->fuildPump.DCmotor_WR0_SR;
    g_data.module->Sync(TAG_FLUID_WR0);

    QTimer::singleShot(SYSTEM_SELF_CHECK_FLUID_CHECK_MAX_TIME*1000,this,SLOT(slot_judgeFluidinfusionPumpSelfCheck()));
}
/*
功能描述：抗凝系统检测
输    入：/
输    出：/
*/
void systemSelfCheck::heparinPumpSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::heparinPumpSelfCheck()：抗凝系统检测";
    qdebug<<debugstr;
#endif

    /*清除抗凝系统自检相关报警*/
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_HEPARIN_PUMP_SELF_CHECK_NOT_BOM,INTERVAL_10,SYSTEM_ALARM_DISABLE);
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_HEPARIN_PUMP_SELF_CHECK_NOT_TOP,INTERVAL_10,SYSTEM_ALARM_DISABLE);

    emit signal_SelfCheckStart(CHECK_ITEM_OF_HEPARIN_SYSTEM,SYSTEM_SELF_CHECK_HEPARIN_CHECK_MAX_TIME_TOTAL*1000);

    m_checkItem_heparPump = true;

    if(m_isHeparinPumpFirstCheck == true)
    {
        g_data.module->hePump.wr0.cmd_1 |= g_data.module->hePump.HeparinPlate_WR0_SR | g_data.module->hePump.HeparinPlate_WR0_Z | g_data.module->hePump.HeparinPlate_WR0_M0;
        g_data.module->hePump.wr0.cmd_1 &= ~g_data.module->hePump.HeparinPlate_WR0_T & ~g_data.module->hePump.HeparinPlate_WR0_M1;
        g_data.module->hePump.wr0.type = 20;
        g_data.module->hePump.wr0.fph = 10000;
    }
    else
    {
        g_data.module->hePump.wr0.cmd_1 |= g_data.module->hePump.HeparinPlate_WR0_M1;
        g_data.module->hePump.wr0.cmd_1 &= ~g_data.module->hePump.HeparinPlate_WR0_M0;
    }

    g_data.module->Sync(TAG_HEPUMP_WR0);

    QTimer::singleShot(SYSTEM_SELF_CHECK_HEPARIN_CHECK_MAX_TIME_SINGLE*1000,this,SLOT(slot_judgeHeparinPumpSelfCheck()));
}
/*
功能描述：阻流夹检测
输    入：/
输    出：/
*/
void systemSelfCheck::chokedFlowMonitorSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::chokedFlowMonitorSelfCheck()：阻流夹检测";
    qdebug<<debugstr;
#endif

    /*清除阻流夹自检相关报警*/
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_CHOKED_FLOW_MONITOR_SELF_CHECK,INTERVAL_10,SYSTEM_ALARM_DISABLE);

    emit signal_SelfCheckStart(CHECK_ITEM_OF_CHOKED_FLOW_SYSTEM,SYSTEM_SELF_CHECK_CHOKED_CHECK_MAX_TIME_TOTAL*1000);
    m_checkItem_choke = true;
    if(m_isChokeFirstCheck == true)
    {
        g_data.module->drive.wr0.cmd_1 &= ~g_data.module->drive.DriveBoard_WR0_ZLJ;
    }
    else
    {
        g_data.module->drive.wr0.cmd_1 |= g_data.module->drive.DriveBoard_WR0_ZLJ;
    }

    g_data.module->Sync(TAG_DRIVE_WR0);

    QTimer::singleShot(SYSTEM_SELF_CHECK_CHOKED_CHECK_MAX_TIME_SINGLE*1000,this,SLOT(slot_judgeChokedFlowMonitorSelfCheck()));
}
/*
功能描述：平衡腔检测
输    入：/
输    出：/
*/
void systemSelfCheck::balanceSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::balanceSelfCheck()：平衡腔检测";
    qdebug<<debugstr;
#endif

    /*清除平衡腔自检相关报警*/
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP100,INTERVAL_10,SYSTEM_ALARM_DISABLE);

    emit signal_SelfCheckStart(CHECK_ITEM_OF_BALANCE_SYSTEM,SYSTEM_SELF_CHECK_BALANCE_CHECK_MAX_TIME*1000);
    emit signal_SelfCheckStart(CHECK_ITEM_OF_SUBPRESSURE_SYSTEM,SYSTEM_SELF_CHECK_SUBPRESSURE_CHECK_MAX_TIME*1000);
    m_checkItem_balance = true;

    QTimer::singleShot(0,this,SLOT(slot_judgeSubpressureSelfCheck()));
}
/*
功能描述：内毒素检测
输    入：/
输    出：/
*/
void systemSelfCheck::endotoxinSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::endotoxinSelfCheck()：内毒素检测";
    qdebug<<debugstr;
#endif

    /*清除内毒素相关报警*/
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_ENDOTOXIN_FILTE_SELF_CHECK_ZN120,INTERVAL_10,SYSTEM_ALARM_DISABLE);
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_ENDOTOXIN_FILTE_SELF_CHECK_ZN121,INTERVAL_10,SYSTEM_ALARM_DISABLE);

    emit signal_SelfCheckStart(CHECK_ITEM_OF_ENDOTOXIN_SYSTEM,SYSTEM_SELF_CHECK_ENDOTOXIN_CHECK_MAX_TIME*1000);
    m_checkItem_endotoxin = true;

    QTimer::singleShot(0,this,SLOT(slot_endotoxinSelfCheck_11()));
}
/*
功能描述：加热检测
输    入：/
输    出：/
*/
void systemSelfCheck::dialystateTempSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::dialystateTempSelfCheck()：加热检测";
    qdebug<<debugstr;
#endif

    /*清除加热自检相关报警*/
    emit signal_sendAlarmData(SYSTEM_ERROR_CODE_DIALYSATE_TEMPERATURE_SELF_CHECK,INTERVAL_10,SYSTEM_ALARM_DISABLE);

    emit signal_SelfCheckStart(CHECK_ITEM_OF_HEAT_SYSTEM,SYSTEM_SELF_CHECK_HEAT_CHECK_MAX_TIME*1000);
    m_checkItem_temp = true;

    m_preTempValue = 0;
    m_TempChangeValue = 0;
    m_isCheckTempReveal = true;
    QTimer::singleShot(0,this,SLOT(slot_dialystateTempSelfCheck()));
}
/*
功能描述：配液检测
输    入：/
输    出：/
*/
void systemSelfCheck::liquorSelfCheck()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::liquorSelfCheck()：配液检测";
    qdebug<<debugstr;
#endif

    emit signal_SelfCheckStart(CHECK_ITEM_OF_MIXED_SYSTEM,SYSTEM_SELF_CHECK_MIXED_CHECK_MAX_TIME*1000);
}
/*
功能描述：释放系统压力
输    入：/
输    出：/
*/
void systemSelfCheck::releasePressureOfTheSystem()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::releasePressureOfTheSystem()：释放系统压力";
    qdebug<<debugstr;
#endif

    /*打开V1-V8*/
    g_data.module->balance.wr1.cmd_1 |= g_data.module->balance.Balance_WR1_V1 | g_data.module->balance.Balance_WR1_V2 | g_data.module->balance.Balance_WR1_V3 \
                                        | g_data.module->balance.Balance_WR1_V4 | g_data.module->balance.Balance_WR1_V5 | g_data.module->balance.Balance_WR1_V6\
                                        | g_data.module->balance.Balance_WR1_V7 | g_data.module->balance.Balance_WR1_V8;
    /*停止QP、DP、YP*/
    g_data.module->balance.wr1.qpv = 0;
    g_data.module->balance.wr1.dpv = 0;
    g_data.module->balance.wr1.ypv = 0;
    /*强关SV1*/
    g_data.module->drive.wr0.cmd_1 |= g_data.module->drive.DriveBoard_WR0_CTRL_SV | g_data.module->drive.DriveBoard_WR0_SV1_H | g_data.module->drive.DriveBoard_WR0_SV1_L;
    /*开SV5、10、11、13，其余关*/
    g_data.module->drive.wr0.sv1_8 |= g_data.module->drive.DriveBoard_WR0_SV5;
    g_data.module->drive.wr0.sv1_8 &= ~g_data.module->drive.DriveBoard_WR0_SV2 & ~g_data.module->drive.DriveBoard_WR0_SV3 & ~g_data.module->drive.DriveBoard_WR0_SV4\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV6 & ~g_data.module->drive.DriveBoard_WR0_SV7 & ~g_data.module->drive.DriveBoard_WR0_SV8;

    g_data.module->drive.wr0.sv9_16 |= g_data.module->drive.DriveBoard_WR0_SV10 | g_data.module->drive.DriveBoard_WR0_SV11 | g_data.module->drive.DriveBoard_WR0_SV13;
    g_data.module->drive.wr0.sv9_16 &= ~g_data.module->drive.DriveBoard_WR0_SV9 & ~g_data.module->drive.DriveBoard_WR0_SV12 & ~g_data.module->drive.DriveBoard_WR0_SV14\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV15 & ~g_data.module->drive.DriveBoard_WR0_SV16;

    g_data.module->drive.wr0.sv17_24 &= ~g_data.module->drive.DriveBoard_WR0_SV17 & ~g_data.module->drive.DriveBoard_WR0_SV18 & ~g_data.module->drive.DriveBoard_WR0_SV19\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV20;
    g_data.module->Sync(TAG_BALANCE_WR1 | TAG_DRIVE_WR0);
}
/*
功能描述：停止齿轮泵
输    入：/
输    出：/
*/
void systemSelfCheck::stopGearPumpOfTheSystem()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::stopGearPumpOfTheSystem()：停止齿轮泵";
    qdebug<<debugstr;
#endif

    g_data.module->balance.wr1.qpv = 0;
    g_data.module->balance.wr1.dpv = 0;
    g_data.module->balance.wr1.ypv = 0;
    g_data.module->Sync(TAG_BALANCE_WR1);
}
/*
功能描述：启动平衡系统
输    入：/
输    出：/
*/
void systemSelfCheck::startBalanceSystem()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::startBalanceSystem()：启动平衡系统";
    qdebug<<debugstr;
#endif

    g_data.module->balance.wr0.cmd_1 = g_data.module->balance.Balance_WR0_WORK_MODEL_NORMAL;
    g_data.module->balance.wr0.flow = 500;
    g_data.module->balance.wr0.qpv = g_data.systemParameter.qpVoltage.m_value;

    g_data.module->drive.wr0.cmd_1 |= g_data.module->drive.DriveBoard_WR0_CTRL_SV | g_data.module->drive.DriveBoard_WR0_SV1_L;
    g_data.module->drive.wr0.cmd_1 &= ~g_data.module->drive.DriveBoard_WR0_SV1_H;

    /*开SV5、10、13，其余关*/
    g_data.module->drive.wr0.sv1_8 |= g_data.module->drive.DriveBoard_WR0_SV5;
    g_data.module->drive.wr0.sv1_8 &= ~g_data.module->drive.DriveBoard_WR0_SV2 & ~g_data.module->drive.DriveBoard_WR0_SV3 & ~g_data.module->drive.DriveBoard_WR0_SV4\
                                      & ~g_data.module->drive.DriveBoard_WR0_SV6 & ~g_data.module->drive.DriveBoard_WR0_SV7 & ~g_data.module->drive.DriveBoard_WR0_SV8;

    g_data.module->drive.wr0.sv9_16 |= g_data.module->drive.DriveBoard_WR0_SV10 | g_data.module->drive.DriveBoard_WR0_SV13;
    g_data.module->drive.wr0.sv9_16 &= ~g_data.module->drive.DriveBoard_WR0_SV9 & ~g_data.module->drive.DriveBoard_WR0_SV11 & ~g_data.module->drive.DriveBoard_WR0_SV12\
                                       & ~g_data.module->drive.DriveBoard_WR0_SV14 & ~g_data.module->drive.DriveBoard_WR0_SV15 & ~g_data.module->drive.DriveBoard_WR0_SV16;

    g_data.module->drive.wr0.sv17_24 &= ~g_data.module->drive.DriveBoard_WR0_SV17 & ~g_data.module->drive.DriveBoard_WR0_SV18 & ~g_data.module->drive.DriveBoard_WR0_SV19\
                                        & ~g_data.module->drive.DriveBoard_WR0_SV20;

    /*是否有干粉桶*/
    g_data.module->drive.wr0.sv17_24 |= g_data.module->drive.DriveBoard_WR0_SV17;

    g_data.module->Sync(TAG_BALANCE_WR0 | TAG_DRIVE_WR0);
}
/*
功能描述：停止平衡系统
输    入：/
输    出：/
*/
void systemSelfCheck::stopBalanceSyatem()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::stopBalanceSyatem()：停止平衡系统";
    qdebug<<debugstr;
#endif

    g_data.module->balance.wr0.cmd_1 = g_data.module->balance.Balance_WR0_WORK_MODEL_STOP;
    g_data.module->Sync(TAG_BALANCE_WR0);
}
/*
功能描述：停止加热系统
输    入：/
输    出：/
*/
void systemSelfCheck::stopDialysateTempSystem()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::stopDialysateTempSystem()：停止加热系统";
    qdebug<<debugstr;
#endif

    g_data.module->heat.wr0.cmd_1 &= ~g_data.module->heat.Heat_WR0_SR;
    g_data.module->Sync(TAG_HEAT_WR0);
}
/*
功能描述：开启加热系统
输    入：/
输    出：/
*/
void systemSelfCheck::startDialysateTempSystem()
{
#if DEBUG_MODEL || DEBUG_MODEL_SYSTEMSELFCHECK
    QString debugstr="void systemSelfCheck::startDialysateTempSystem()：开启加热系统";
    qdebug<<debugstr;
#endif

    g_data.module->heat.wr1.adjust = g_data.systemParameter.temp_Comp.m_value;
    g_data.module->heat.wr0.cmd_1 |= g_data.module->heat.Heat_WR0_SR;
    g_data.module->heat.wr0.temp = g_data.parameter.dislysateTemp.m_value;
    g_data.module->heat.wr0.alarm_h = g_data.alarm.tempAlarmHight.m_value;
    g_data.module->heat.wr0.alarm_l = g_data.alarm.tempAlarmLow.m_value;
    g_data.module->heat.wr0.flow = 500;
    g_data.module->Sync(TAG_HEAT_WR0);
}
