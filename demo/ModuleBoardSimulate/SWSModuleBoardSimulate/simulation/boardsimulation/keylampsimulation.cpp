#include "keylampsimulation.h"

keyLampSimulation::keyLampSimulation(QObject *parent) : BoardSimulationBase(parent)
{

}

void keyLampSimulation::recvWriteCmd4000(ModuleBoardAddrType /*addr*/, SystemBusCommandType cmd, const QByteArray &data)
{
    Q_UNUSED(cmd)
    Q_UNUSED(data)
}

void keyLampSimulation::recvWriteCmd6000(ModuleBoardAddrType /*addr*/, SystemBusCommandType cmd, const QByteArray &data)
{
    Q_UNUSED(cmd)
    Q_UNUSED(data)
}

void keyLampSimulation::initSimData()
{
    //插入模块板版本信息
    m_boardVersionCode = C_MonitorBoardVersion;
    m_boardVersionList << &g_simDa.keyLamp.monitorBoardSoftVer << &g_simDa.keyLamp.monitorBoardHardVer;
}

void keyLampSimulation::loadData4000()
{
    ///todo
}

void keyLampSimulation::loadData6000()
{
    //--------------------------监控板软硬件版本--------------------------------<
    g_mbd.md6.mbd.rd7.sv = g_simDa.keyLamp.monitorBoardSoftVer;
    g_mbd.md6.mbd.rd7.hv = g_simDa.keyLamp.monitorBoardHardVer;

    ///todo
}
