#include "modelboard.h"

modelboard *modelboard::s_modelboard = nullptr;
QMutex modelboard::s_mutexLocker;

/*
功能描述：modelboard类构造函数
输    入：/
输    出：/
*/
modelboard::modelboard(QObject *parent) : QObject(parent)
{
#if DEBUG_MODEL || DEBUG_MODEL_MODELBOARD
    QString debugstr="modelboard::modelboard(QObject *parent) : QObject(parent):构造函数";
    qdebug<<debugstr;
#endif

    m_currentCheckNum = 0;

    m_serialport = INITSerialportControl;
    connect(this,&modelboard::signal_modelBoardDataLoading,m_serialport,&serialportControl::signal_modelBoardDataLoading,Qt::QueuedConnection);

    connect(m_serialport,&serialportControl::signal_serialportDataArrived,this,&modelboard::slot_analySerialportDataArrived);

    m_moduleCheckingTimer = new QTimer();
    m_moduleCheckingTimer->setInterval(150);
    connect(m_moduleCheckingTimer,&QTimer::timeout,this,&modelboard::slot_moduleCheckingSend);
}
/*
功能描述：modelboard类析构函数
输    入：/
输    出：/
*/
modelboard::~modelboard()
{
#if DEBUG_MODEL || DEBUG_MODEL_MODELBOARD
    QString debugstr="modelboard::~modelboard():析构函数";
    qdebug<<debugstr;
#endif

    m_serialport->deSerialportControl();
    m_serialport = nullptr;
    if(m_moduleCheckingTimer){delete m_moduleCheckingTimer;m_moduleCheckingTimer = nullptr;}
}
/*
功能描述：创建自身
输    入：/
输    出：/
*/
modelboard *modelboard::initmodelBoard()
{
#if DEBUG_MODEL || DEBUG_MODEL_MODELBOARD
    QString debugstr="modelboard *modelboard::initmodelBoard():创建自身";
    qdebug<<debugstr;
#endif

    if(!s_modelboard)
    {
        QMutexLocker locker(&s_mutexLocker);
        if(!s_modelboard)
        {
            s_modelboard = new modelboard();
        }
    }
    return s_modelboard;
}
/*
功能描述：销毁自身
输    入：/
输    出：/
*/
void modelboard::demodelboard()
{
#if DEBUG_MODEL || DEBUG_MODEL_MODELBOARD
    QString debugstr="void modelboard::demodelboard():销毁自身";
    qdebug<<debugstr;
#endif

    if(s_modelboard)
    {
        QMutexLocker locker(&s_mutexLocker);
        if(s_modelboard)
        {
            delete s_modelboard;
            s_modelboard = nullptr;
        }
    }
}
/*
功能描述：解析串口数据
输    入：串口接收到的数据
输    出：/
*/
void modelboard::slot_analySerialportDataArrived(QByteArray arriveData)
{
#if DEBUG_MODEL || DEBUG_MODEL_MODELBOARD
    QString debugstr="void modelboard::slot_analySerialportDataArrived(QByteArray arriveData):解析串口数据";
    qdebug<<debugstr;
#endif

    if(arriveData.size() > 4)
    {
        ModuleBoardAddrType addr = (ModuleBoardAddrType)arriveData.at(0);
        SystemBusCommandType funtype = (SystemBusCommandType)arriveData.at(1);
        QByteArray serialdata = QByteArray(arriveData.data() + 2,arriveData.size() - 4);
        serialportDataToModel(addr,funtype,serialdata);
    }
}
/*
功能描述：转发串口数据到相应模块
输    入：addr:地址，funType:功能码，modelData:数据
输    出：/
*/
void modelboard::serialportDataToModel(const int addr, const int funType, const QByteArray modelData)
{
#if DEBUG_MODEL || DEBUG_MODEL_MODELBOARD
    QString debugstr="void modelboard::serialportDataToModel(const int addr, const int funType, const QByteArray modelData):转发串口数据到相应模块";
    qdebug<<debugstr;
#endif

    switch (addr)
    {
        case BLOOD_PUMP_BOARD_ADDRESS:
            switch (funType)
            {
                case SYSTEM_BUS_READ_COMMAND_0:
                    memcpy(&bloodPump.rd0,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_READ_COMMAND_7:
                    memcpy(&bloodPump.rd7,modelData.data(),modelData.size());
                    break;
            }
            break;
        case FLUID_INFUSION_PUMP_BOARD_ADDRESS:
            switch (funType)
            {
                case SYSTEM_BUS_READ_COMMAND_0:
                    memcpy(&fuildPump.rd0,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_READ_COMMAND_7:
                    memcpy(&fuildPump.rd7,modelData.data(),modelData.size());
                    break;
            }
            break;
        case ULTRAFILTRATION_PUMP_BOARD_ADDRESS:
            switch (funType)
            {
                case SYSTEM_BUS_READ_COMMAND_0:
                    memcpy(&ufPump.rd0,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_READ_COMMAND_7:
                    memcpy(&ufPump.rd7,modelData.data(),modelData.size());
                    break;
            }
            break;
        case HEPARIN_PUMP_BOARD_ADDRESS:
            switch (funType)
            {
                case SYSTEM_BUS_READ_COMMAND_0:
                    memcpy(&hePump.rd7,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_READ_COMMAND_7:
                    memcpy(&hePump.rd7,modelData.data(),modelData.size());
                    break;
            }
            break;
        case DRIVER_BOARD_ADDRESS:
            switch (funType)
            {
                case SYSTEM_BUS_READ_COMMAND_0:
                    memcpy(&drive.rd0,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_READ_COMMAND_1:
                    memcpy(&drive.rd1,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_READ_COMMAND_2:
                    memcpy(&drive.rd2,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_READ_COMMAND_7:
                    memcpy(&drive.rd7,modelData.data(),modelData.size());
                    break;
            }
            break;
        case BALANCE_CHAMBER_BOARD_ADDRESS:
            switch (funType)
            {
                case SYSTEM_BUS_READ_COMMAND_0:
                    memcpy(&balance.rd0,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_READ_COMMAND_1:
                    memcpy(&balance.rd1,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_READ_COMMAND_2:
                    memcpy(&balance.rd2,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_READ_COMMAND_3:
                    memcpy(&balance.rd3,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_READ_COMMAND_7:
                    memcpy(&balance.rd7,modelData.data(),modelData.size());
                    break;
            }
            break;
        case MIXED_BOARD_ADDRESS:
            switch (funType)
            {
                case SYSTEM_BUS_READ_COMMAND_0:
                    memcpy(&mixture.rd0,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_READ_COMMAND_1:
                    memcpy(&mixture.rd1,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_READ_COMMAND_7:
                    memcpy(&mixture.rd7,modelData.data(),modelData.size());
                    break;
            }
            break;
        case CONDUCTANCE_BOARD_AB_ADDRESS:
        case CONDUCTANCE_BOARD_C_ADDRESS:
            switch (funType)
            {
                case SYSTEM_BUS_READ_COMMAND_0:
                    memcpy(&cond.rd0,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_READ_COMMAND_1:
                    memcpy(&cond.rd1,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_READ_COMMAND_7:
                    memcpy(&cond.rd7,modelData.data(),modelData.size());
                    break;
            }
            break;
        case MONITOR_BOARD_ADDRESS:
        case KEYPRESS_BOARD_ADDRESS:
            switch (funType)
            {
                case SYSTEM_BUS_READ_COMMAND_7:
                    memcpy(&monitor.rd7,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_KEY_PRESSED_COMMAND:
                    memcpy(&monitor.rd0,modelData.data(),modelData.size());
                    break;
            }
            break;
        case HEATER_BOARD_ADDRESS:
            switch (funType)
            {
                case SYSTEM_BUS_READ_COMMAND_0:
                    memcpy(&heat.rd0,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_READ_COMMAND_7:
                    memcpy(&heat.rd7,modelData.data(),modelData.size());
                    break;
            }
            break;
        case POWER_BOARD_ADDRESS:
            switch (funType)
            {
                case SYSTEM_BUS_READ_COMMAND_0:
                    memcpy(&power.rd0,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_READ_COMMAND_7:
                    memcpy(&power.rd7,modelData.data(),modelData.size());
                    break;
            }
            break;
        case BLOOD_PRESSURE_BOARD_ADDRESS:
            switch (funType)
            {
                case SYSTEM_BUS_READ_COMMAND_0:
                    memcpy(&bloodPressure.rd0,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_READ_COMMAND_1:
                    memcpy(&bloodPressure.rd1,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_READ_COMMAND_2:
                    memcpy(&bloodPressure.rd2,modelData.data(),modelData.size());
                    break;
            }
            break;
        case ONLINE_KTV_BOARD_ADDRESS:
            switch (funType)
            {
                case SYSTEM_BUS_READ_COMMAND_0:
                    memcpy(&onlineKtv.rd0,modelData.data(),modelData.size());
                    break;
                case SYSTEM_BUS_READ_COMMAND_7:
                    memcpy(&onlineKtv.rd7,modelData.data(),modelData.size());
                    break;
            }
            break;
    }
}
/*
功能描述：发送模块数据
输    入：addr:地址，funType:功能码
输    出：/
*/
void modelboard::modelBoardDataLoading(const int addr, const int funType)
{
#if DEBUG_MODEL || DEBUG_MODEL_MODELBOARD
    QString debugstr="void modelboard::modelBoardDataLoading(const int addr, const int funType):发送模块数据";
    qdebug<<debugstr;
#endif

    QByteArray sendData;
    sendData[0] = addr;
    sendData[1] = funType;
    switch (addr)
    {
    case BLOOD_PUMP_BOARD_ADDRESS:
        switch (funType)
        {
            case SYSTEM_BUS_WRITE_COMMAND_0:
                sendData.resize(sizeof (bloodPump.wr0)+2);
                memcpy(sendData.data()+2,&bloodPump.wr0,sizeof (bloodPump.wr0));
                break;
        }
        break;
    case FLUID_INFUSION_PUMP_BOARD_ADDRESS:
        switch (funType)
        {
            case SYSTEM_BUS_WRITE_COMMAND_0:
                sendData.resize(sizeof (fuildPump.wr0)+2);
                memcpy(sendData.data()+2,&fuildPump.wr0,sizeof (fuildPump.wr0));
                break;
        }
        break;
    case ULTRAFILTRATION_PUMP_BOARD_ADDRESS:
        switch (funType)
        {
            case SYSTEM_BUS_WRITE_COMMAND_0:
                sendData.resize(sizeof (ufPump.wr0)+2);
                memcpy(sendData.data()+2,&ufPump.wr0,sizeof (ufPump.wr0));
                break;
        }
        break;
    case HEPARIN_PUMP_BOARD_ADDRESS:
        switch (funType)
        {
            case SYSTEM_BUS_WRITE_COMMAND_0:
                sendData.resize(sizeof (hePump.wr0)+2);
                memcpy(sendData.data()+2,&hePump.wr0,sizeof (hePump.wr0));
                break;
        }
        break;
    case DRIVER_BOARD_ADDRESS:
        switch (funType)
        {
            case SYSTEM_BUS_WRITE_COMMAND_0:
                sendData.resize(sizeof (drive.wr0)+2);
                memcpy(sendData.data(),&drive.wr0,sizeof (drive.wr0));
                break;
            case SYSTEM_BUS_WRITE_COMMAND_1:
                sendData.resize(sizeof (drive.wr1)+2);
                memcpy(sendData.data()+2,&drive.wr1,sizeof (drive.wr1));
                break;
        }
        break;
    case BALANCE_CHAMBER_BOARD_ADDRESS:
        switch (funType)
        {
            case SYSTEM_BUS_WRITE_COMMAND_0:
                sendData.resize(sizeof (balance.wr0)+2);
                memcpy(sendData.data()+2,&balance.wr0,sizeof (balance.wr0));
                break;
            case SYSTEM_BUS_WRITE_COMMAND_1:
                sendData.resize(sizeof (balance.wr1)+2);
                memcpy(sendData.data()+2,&balance.wr1,sizeof (balance.wr1));
                break;
            case SYSTEM_BUS_WRITE_COMMAND_2:
                sendData.resize(sizeof (balance.wr2)+2);
                memcpy(sendData.data()+2,&balance.wr2,sizeof (balance.wr2));
                break;
            case SYSTEM_BUS_WRITE_COMMAND_3:
                sendData.resize(sizeof (balance.wr3)+2);
                memcpy(sendData.data()+2,&balance.wr3,sizeof (balance.wr3));
                break;
        }
        break;
    case MIXED_BOARD_ADDRESS:
        switch (funType)
        {
            case SYSTEM_BUS_WRITE_COMMAND_0:
                sendData.resize(sizeof (mixture.wr0)+2);
                memcpy(sendData.data()+2,&mixture.wr0,sizeof (mixture.wr0));
                break;
            case SYSTEM_BUS_WRITE_COMMAND_1:
                sendData.resize(sizeof (mixture.wr1)+2);
                memcpy(sendData.data()+2,&mixture.wr1,sizeof (mixture.wr1));
                break;
        }
        break;
    case MONITOR_BOARD_ADDRESS:
    case PILOT_LAMP_BOARD_ADDRESS:
        switch (funType)
        {
            case SYSTEM_BUS_PILOT_LAMP_COMMAND:
                sendData.resize(sizeof (monitor.wr0)+2);
                memcpy(sendData.data()+2,&monitor.wr0,sizeof (monitor.wr0));
                break;
        }
        break;
    case HEATER_BOARD_ADDRESS:
        switch (funType)
        {
            case SYSTEM_BUS_WRITE_COMMAND_0:
                sendData.resize(sizeof (heat.wr0)+2);
                memcpy(sendData.data()+2,&heat.wr0,sizeof (heat.wr0));
                break;
            case SYSTEM_BUS_WRITE_COMMAND_1:
                sendData.resize(sizeof (heat.wr1)+2);
                memcpy(sendData.data()+2,&heat.wr1,sizeof (heat.wr1));
                break;
        }
        break;
    case POWER_BOARD_ADDRESS:
        switch (funType)
        {
            case SYSTEM_BUS_WRITE_COMMAND_0:
                sendData.resize(sizeof (power.wr0)+2);
                memcpy(sendData.data()+2,&power.wr0,sizeof (power.wr0));
                break;
            case SYSTEM_BUS_WRITE_COMMAND_1:
                sendData.resize(sizeof (power.wr1)+2);
                memcpy(sendData.data()+2,&power.wr1,sizeof (power.wr1));
                break;
        }
        break;
    case CONDUCTANCE_BOARD_C_ADDRESS:
        switch (funType)
        {
            case SYSTEM_BUS_WRITE_COMMAND_0:
                sendData.resize(sizeof (cond.wr0)+2);
                memcpy(sendData.data()+2,&cond.wr0,sizeof (cond.wr0));
                break;
        }
        break;
    case BLOOD_PRESSURE_BOARD_ADDRESS:
        switch (funType)
        {
            case SYSTEM_BUS_WRITE_COMMAND_0:
                sendData.resize(sizeof (bloodPressure.wr0)+2);
                memcpy(sendData.data()+2,&bloodPressure.wr0,sizeof (bloodPressure.wr0));
                break;
            case SYSTEM_BUS_WRITE_COMMAND_1:
                sendData.resize(sizeof (bloodPressure.wr1)+2);
                memcpy(sendData.data()+2,&bloodPressure.wr1,sizeof (bloodPressure.wr1));
                break;
        }
        break;
    case ONLINE_KTV_BOARD_ADDRESS:
        switch (funType)
        {
            case SYSTEM_BUS_WRITE_COMMAND_0:
                sendData.resize(sizeof (onlineKtv.wr0)+2);
                memcpy(sendData.data()+2,&onlineKtv.wr0,sizeof (onlineKtv.wr0));
                break;
        }
        break;
    }
    emit signal_modelBoardDataLoading(sendData);
}
/*
功能描述：同步模块数据
输    入：tags：要同步的模块
输    出：/
*/
void modelboard::Sync(int tags)
{
#if DEBUG_MODEL || DEBUG_MODEL_MODELBOARD
    QString debugstr="void modelboard::Sync(int tags):同步模块数据";
    qdebug<<debugstr;
#endif

    if (tags & TAG_BLOOD_WR0)
    {
        modelBoardDataLoading(BLOOD_PUMP_BOARD_ADDRESS,SYSTEM_BUS_WRITE_COMMAND_0);
    }
    if (tags & TAG_FLUID_WR0)
    {
        modelBoardDataLoading(FLUID_INFUSION_PUMP_BOARD_ADDRESS, SYSTEM_BUS_WRITE_COMMAND_0);
    }
    if (tags & TAG_UFPUMP_WR0)
    {
        modelBoardDataLoading(ULTRAFILTRATION_PUMP_BOARD_ADDRESS, SYSTEM_BUS_WRITE_COMMAND_0);
    }
    if (tags & TAG_HEPUMP_WR0)
    {
        modelBoardDataLoading(HEPARIN_PUMP_BOARD_ADDRESS, SYSTEM_BUS_WRITE_COMMAND_0);
    }
    if (tags & TAG_DRIVE_WR0)
    {
        modelBoardDataLoading(DRIVER_BOARD_ADDRESS, SYSTEM_BUS_WRITE_COMMAND_0);
    }
    if (tags & TAG_DRIVE_WR1)
    {
        modelBoardDataLoading(DRIVER_BOARD_ADDRESS, SYSTEM_BUS_WRITE_COMMAND_1);
    }
//    if (tags & TAG_MONITORBOOD_WR0)
//    {
//        modelBoardDataLoading(PILOT_LAMP_BOARD_ADDRESS,SYSTEM_BUS_PILOT_LAMP_COMMAND);
//    }
    if (tags & TAG_BALANCE_WR0)
    {
        modelBoardDataLoading(BALANCE_CHAMBER_BOARD_ADDRESS, SYSTEM_BUS_WRITE_COMMAND_0);
    }
    if (tags & TAG_BALANCE_WR1)
    {
        modelBoardDataLoading(BALANCE_CHAMBER_BOARD_ADDRESS, SYSTEM_BUS_WRITE_COMMAND_1);
    }
    if (tags & TAG_BALANCE_WR2)
    {
        modelBoardDataLoading(BALANCE_CHAMBER_BOARD_ADDRESS, SYSTEM_BUS_WRITE_COMMAND_2);
    }
    if (tags & TAG_BALANCE_WR3)
    {
        modelBoardDataLoading(BALANCE_CHAMBER_BOARD_ADDRESS, SYSTEM_BUS_WRITE_COMMAND_3);
    }
    if (tags & TAG_MIXTURE_WR0)
    {
        modelBoardDataLoading(MIXED_BOARD_ADDRESS, SYSTEM_BUS_WRITE_COMMAND_0);
    }
    if (tags & TAG_MIXTURE_WR1)
    {
        modelBoardDataLoading(MIXED_BOARD_ADDRESS, SYSTEM_BUS_WRITE_COMMAND_1);
    }
    if (tags & TAG_COND_WR0)
    {
        modelBoardDataLoading(CONDUCTANCE_BOARD_C_ADDRESS, SYSTEM_BUS_WRITE_COMMAND_0);
    }
    if (tags & TAG_HEAT_WR0)
    {
        modelBoardDataLoading(HEATER_BOARD_ADDRESS, SYSTEM_BUS_WRITE_COMMAND_0);
    }
    if (tags & TAG_HEAT_WR1)
    {
        modelBoardDataLoading(HEATER_BOARD_ADDRESS, SYSTEM_BUS_WRITE_COMMAND_1);
    }
    if (tags & TAG_POWER_WR0)
    {
        modelBoardDataLoading(POWER_BOARD_ADDRESS, SYSTEM_BUS_WRITE_COMMAND_0);
    }
    if (tags & TAG_POWER_WR1)
    {
        modelBoardDataLoading(POWER_BOARD_ADDRESS, SYSTEM_BUS_WRITE_COMMAND_1);
    }
    if (tags & TAG_PILOT_WR0)
    {
        modelBoardDataLoading(PILOT_LAMP_BOARD_ADDRESS, SYSTEM_BUS_PILOT_LAMP_COMMAND);
    }
    if (tags & TAG_BLOODPRESSURE_WR0)
    {
        modelBoardDataLoading(BLOOD_PRESSURE_BOARD_ADDRESS, SYSTEM_BUS_WRITE_COMMAND_0);
    }
    if (tags & TAG_BLOODPRESSURE_WR1)
    {
        modelBoardDataLoading(BLOOD_PRESSURE_BOARD_ADDRESS, SYSTEM_BUS_WRITE_COMMAND_1);
    }
    if (tags & TAG_ONLINEKTV_WR0)
    {
        modelBoardDataLoading(ONLINE_KTV_BOARD_ADDRESS, SYSTEM_BUS_WRITE_COMMAND_0);
    }
}
/*
功能描述：模块数据自动检测
输    入：addr:地址，funType:功能码
输    出：/
*/
void modelboard::slot_moduleCheckingSend()
{
#if DEBUG_MODEL || DEBUG_MODEL_MODELBOARD
    QString debugstr="void modelboard::slot_moduleCheckingSend():模块数据自动检测";
    qdebug<<debugstr;
#endif

    if(!m_moduleCheckingMap.empty())
    {
        QMultiMap<int,int>::iterator iter = m_moduleCheckingMap.begin();
        iter+=m_currentCheckNum;

        QByteArray sendData;
        sendData.append(iter.key());
        sendData.append(iter.value());
        emit signal_modelBoardDataLoading(sendData);

        m_currentCheckNum++;
        if(m_currentCheckNum >= m_moduleCheckingMap.size())
        {
            m_currentCheckNum = 0;
        }
    }
}
/*
功能描述：装载初始化模块
输    入：addr:地址，funType:功能码
输    出：/
*/
void modelboard::loadInitModel(const int addr,const int funType)
{
#if DEBUG_MODEL || DEBUG_MODEL_MODELBOARD
    QString debugstr="void modelboard::loadInitModel(const int addr,const int funType):装载初始化模块";
    qdebug<<debugstr;
#endif

    m_moduleCheckingMap.insert(addr,funType);
    m_moduleCheckingTimer->start();
}
