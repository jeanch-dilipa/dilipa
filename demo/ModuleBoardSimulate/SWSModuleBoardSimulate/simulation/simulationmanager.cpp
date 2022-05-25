#include "simulationmanager.h"
#include <QFile>

#ifdef Q_OS_WIN
#define DEFAULT_SAVE_FILE "C:/Windows/Temp/boardsimtoolsetdata.sds" /*默认保存设置文件*/
#else
#define DEFAULT_SAVE_FILE "/tmp/boardsimtoolsetdata.sds" /*默认保存设置文件*/
#endif

///zf_todo 待做：可以excel导入数据曲线数据

SimulationManager::SimulationManager(QObject *parent) : QThread(parent)
{
    this->moveToThread(this);

    connect(this, &QThread::finished, this, &SimulationManager::slotFinished);
}

SimulationManager::~SimulationManager()
{
    if(this->isRunning())
    {
        this->quit();
        this->wait();
    }
}

void SimulationManager::run()
{
    m_bloodSysSim  = new BloodSystemSimulation(this);
    m_liquidSysSim = new LiquidSystemSimulation(this);
    m_mixUltraSysSim = new MixUltraSystemSimulation(this);
    m_antiSysSim = new AntiSystemSimulation(this);
    m_PowerSysSim = new PowerSystemSimulation(this);
    m_keyLampSim = new keyLampSimulation(this);
    m_btvRcmSim = new BTVRCMSimulation(this);

    this->exec();
}

void SimulationManager::slotFinished()
{   //在线程结束时直接删除相关的模拟子对象，防止产生“QObject::killTimer: Timers cannot be stopped from another thread”警告
    delete m_bloodSysSim;
    delete m_liquidSysSim;
    delete m_mixUltraSysSim;
    delete m_antiSysSim;
    delete m_PowerSysSim;
    delete m_keyLampSim;
    delete m_btvRcmSim;
}

void SimulationManager::slotRecvWriteCmd(QByteArray data)
{
    if(data.size() < 2) //至少得有地址、功能码
    {
        return;
    }

    ModuleBoardAddrType  addr = (ModuleBoardAddrType)data.at(0);
    SystemBusCommandType cmd = (SystemBusCommandType)data.at(1);

    data = data.remove(0, 2);

    switch(addr)
    {
    case DRIVER_BOARD_ADDR4:                //4000驱动板
        m_bloodSysSim->recvWriteCmd4000(addr, cmd, data);
        m_liquidSysSim->recvWriteCmd4000(addr, cmd, data);
        break;
    case BLOOD_TRAIL_BOARD_ADDR6:           //6000血路板
        m_bloodSysSim->recvWriteCmd6000(addr, cmd, data);
        break;
    case BLOOD_PUMP_BOARD_ADDR4:            //4000血泵板
    case FLUID_INFUSION_PUMP_BOARD_ADDR4:   //4000补液泵板
        m_bloodSysSim->recvWriteCmd4000(addr, cmd, data);
        break;
    case BALANCE_CHAMBER_BOARD_ADDR4:       //4000平衡腔板
    case HEATER_BOARD_ADDR4:                //4000加热板
        m_liquidSysSim->recvWriteCmd4000(addr, cmd, data);
        break;
    case LIQUID_DRIVER_BOARD_ADDR6:         //6000水路板
        m_liquidSysSim->recvWriteCmd6000(addr, cmd, data);
        break;
    case MIXED_BOARD_ADDR4:                 //4000配液板
    case ULTRAFILTRATION_PUMP_BOARD_ADDR4:  //4000超滤板
    case CONDUCTANCE_BOARD_ADDR4:           //4000电导板
        m_mixUltraSysSim->recvWriteCmd4000(addr, cmd, data);
        break;
    case MIX_ULTRA_BOARD_ADDR6:             //6000配液超滤板
        m_mixUltraSysSim->recvWriteCmd6000(addr, cmd, data);
        break;
    case HEPARIN_PUMP_BOARD_ADDR4:          //4000肝素板
        m_antiSysSim->recvWriteCmd4000(addr, cmd, data);
        break;
    case HEPARIN_BOARD_ADDR6:               //6000肝素板
        m_antiSysSim->recvWriteCmd6000(addr, cmd, data);
        break;
    case POWER_BOARD_ADDR4:                 //4000电源板
        m_PowerSysSim->recvWriteCmd4000(addr, cmd, data);
        break;
    case POWER_BOARD_ADDR6:                 //6000电源板
        m_PowerSysSim->recvWriteCmd6000(addr, cmd, data);
        break;
    case BLOOD_TEMP_VOLUME_MODULE_ADDR:     //血温血容量
    case UREA_SENSORE_MODULE_ADDR:          //实时清除率监测
        m_btvRcmSim->recvWriteCmd(addr, cmd, data);
        break;
    case AIR_DETECTOR_BOARD_ADDR6:          //空气监测板地址
        ///TODO
        break;
    default:
        break;
    }
}

void SimulationManager::slotSaveSetToFile(QString fileName)
{
    if(fileName.isEmpty())
    {
        fileName = DEFAULT_SAVE_FILE;
    }

    QFile file(fileName);
    QTextStream stream(&file);
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        //保存模拟数据设置值
        foreach (BoardSimulationBase *base, BoardSimulationBase::simSysList())
        {
            _outputSetToFile(stream, base);
        }

        //保存其他
        stream << (QString::number(C_MachineSetType) + "," + QString::number(g_ss.machineSetType));

        file.flush();
        file.close();
    }
}

void SimulationManager::slotLoadSetFromFile(QString fileName)
{
    if(fileName.isEmpty())
    {
        fileName = DEFAULT_SAVE_FILE;
    }

    QFile file(fileName);
    QTextStream stream(&file);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!stream.atEnd())
        {
            QStringList lineList = stream.readLine().trimmed().split(',');
            if(lineList.size() == 7)
            {   //模块板模拟数据
                SimDataSt *smd = BoardSimulationBase::findSimData((SimDataCode)lineList[0].toInt());
                if(smd)
                {
                    smd->set.mode = (ValueSimModeType)lineList[1].toInt();
                    smd->set.fixValue = lineList[2].toFloat();
                    smd->set.randomMinValue = lineList[3].toFloat();
                    smd->set.randomMaxValue = lineList[4].toFloat();
                    smd->set.autoSubValue = lineList[5].toFloat();
                    smd->set.autoAddValue = lineList[6].toFloat();

                    if(smd->set.mode == FixSimMode)
                    {   //固定值，直接加载到value中
                        smd->value = smd->set.fixValue;
                    }
                    else
                    {   //随机值或自动模拟，标记更改由模拟系统进行加载
                        smd->set.changed = true;
                    }
                }
            }
            else if(lineList.size() > 1)
            {
                if(lineList[0].toInt() == C_MachineSetType)
                {   //机器类型设置
                    g_ss.machineSetType = (MachineType)lineList[1].toInt();
                }
                else
                {   //查找是否为版本数据
                    QList<ushort *> verList = BoardSimulationBase::findBoardVerList((SimDataCode)lineList[0].toInt());
                    if(verList.size() + 1 == lineList.size())
                    {   //一行第一个为功能码，所以lineList大小要多1
                        for(int i = 0; i < verList.size(); i++)
                        {   //将数据逐个填充
                            *verList[i] = lineList[i+1].toUShort();
                        }
                    }
                }
            }
        }

        file.close();
        emit signalLoadSetFileFinished();
    }
}

void SimulationManager::slotRemoveSetFile()
{
    QFile::remove(DEFAULT_SAVE_FILE);
}

void SimulationManager::_outputSetToFile(QTextStream &stream, BoardSimulationBase *smb)
{
    foreach(SimDataSt *smd, smb->simDataMap().values())
    {
        if(smd->code != C_Invalid)
        {
            stream << QString("%1,%2,%3,%4,%5,%6,%7\n").arg(smd->code).arg(smd->set.mode).arg(smd->set.fixValue)
                      .arg(smd->set.randomMinValue).arg(smd->set.randomMaxValue).arg(smd->set.autoSubValue)
                      .arg(smd->set.autoAddValue);
        }
    }

    //保存板子版本信息
    stream << QString::number(smb->boardVerCode());
    foreach (ushort *ver, smb->boardVersionList())
    {
        stream << ("," + QString::number(*ver));
    }
    stream << "\n";
}
