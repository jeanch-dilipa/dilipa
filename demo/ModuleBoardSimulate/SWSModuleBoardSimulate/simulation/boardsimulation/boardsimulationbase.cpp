#include "boardsimulationbase.h"
#include "common/publicdata.h"

#define LOAD_SET_DATA_TIME 500 /*装载设置数据周期 ms*/

QList<BoardSimulationBase *> BoardSimulationBase::s_simSysList;

BoardSimulationBase::BoardSimulationBase(QObject *parent) : QObject(parent)
{
    //创建随机数发生器
    m_randomGenerator = new RandomDataGenerator(this);

    //创建装载数据定时器
    m_loadDataTimer = new QTimer(this);
    connect(m_loadDataTimer, &QTimer::timeout, this, &BoardSimulationBase::slotLoadDataTimeout);
    m_loadDataTimer->start(LOAD_SET_DATA_TIME);

    //保存对象指针
    s_simSysList.append(this);

    //自动调用子类模拟数据初始化函数
    QTimer::singleShot(0, this, [this](){
        initSimData();
    });
}

BoardSimulationBase::~BoardSimulationBase()
{
    s_simSysList.removeAll(this);
}

SimDataSt *BoardSimulationBase::findSimData(SimDataCode code)
{
    SimDataSt *smd = Q_NULLPTR;

    foreach(BoardSimulationBase *base, s_simSysList)
    {
        smd = base->simDataMap().value(code);
        if(smd)
        {
            break;
        }
    }

    return smd;
}

QList<ushort *> BoardSimulationBase::findBoardVerList(SimDataCode code)
{
    foreach(BoardSimulationBase *base, s_simSysList)
    {
        if(base->m_boardVersionCode == code)
        {
            return base->m_boardVersionList;
        }
    }

    return QList<ushort *>();
}

void BoardSimulationBase::addSimDataInit(SimDataCode code, SimDataSt *smd, ValueType valueType, int decimals)
{
    smd->set.valueType = valueType;
    smd->set.decimals = decimals;
    smd->code = code;
    m_simDataMap.insert(code, smd);

    //可以自动模拟的默认自动模拟
    if(smd->set.valueType == BinaryValueWithAuto
            || smd->set.valueType == NumericValueWithAuto
            || smd->set.valueType == NumericValueWithAutoRange
            || smd->set.valueType == EnumValueWithAuto)
    {
        smd->set.mode = AutoSimMode;
    }
}

void BoardSimulationBase::slotLoadDataTimeout()
{
    //装载模拟数据
    if(g_ss.machineType == SWS4000)
    {
        loadData4000();
    }
    else
    {   //默认装载6000
        loadData6000();
    }

    //检查模拟设置修改
    foreach(SimDataSt *smd, m_simDataMap.values())
    {
        checkSetChange(*smd);
    }
}

void BoardSimulationBase::checkSetChange(SimDataSt &smd)
{
    if(smd.set.changed)
    {   //设置发生改变
        smd.set.changed = false;
        if(smd.set.valueType >= NumericValue && smd.set.valueType <= NumericValueWithAutoRange)
        {
            m_randomGenerator->removeTarget(RandomTargetSt(&smd.value));
            if(smd.set.valueType == NumericValueWithAutoRange)
            {
                m_randomGenerator->removeTarget(RandomTargetSt(&smd.fluctValue));
            }
        }

        switch(smd.set.mode)
        {   //注：固定模拟数据已直接在设定时加载，这里无需动作
        case RandomSimMode: //随机值，添加到随机数产生器中
            if(smd.set.valueType >= NumericValue && smd.set.valueType <= NumericValueWithAutoRange)
            {   //数值型的才能模拟随机值
                m_randomGenerator->addTarget(RandomTargetSt(&smd.value, smd.set.randomMinValue, smd.set.randomMaxValue, smd.set.decimals));
            }
            break;
        case AutoSimMode:   //自动模拟
            if(smd.set.valueType == NumericValueWithAutoRange) //跟随主控时有波动范围的，使用随机数产生器产生偏移量
            {
                m_randomGenerator->addTarget(RandomTargetSt(&smd.fluctValue, smd.set.autoSubValue, smd.set.autoAddValue, smd.set.decimals, true));
            }
            break;
        default:
            break;
        }
    }
}

void BoardSimulationBase::setBitInByte(quint8 &byte, int bit, bool set)
{
    _setBitInByte(byte, bit, set);
}

void BoardSimulationBase::setBitInByte4(quint32 &byte, quint32 bit, bool set)
{
    _setBitInByte(byte, bit, set);
}

template<typename T, typename K>
void BoardSimulationBase::_setBitInByte(T &byte, K bit, bool set)
{
    if(set)
    {   //置位
        byte |= bit;
    }
    else
    {   //复位
        byte &= ~bit;
    }
}
