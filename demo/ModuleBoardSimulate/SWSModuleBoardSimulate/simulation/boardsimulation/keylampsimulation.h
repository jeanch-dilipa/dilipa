#ifndef KEYLAMPSIMULATION_H
#define KEYLAMPSIMULATION_H

#include "boardsimulationbase.h"
#include "common/publicdata.h"

class keyLampSimulation : public BoardSimulationBase
{
    Q_OBJECT
public:
    explicit keyLampSimulation(QObject *parent = nullptr);

    void recvWriteCmd4000(ModuleBoardAddrType addr, SystemBusCommandType cmd, const QByteArray &data); //接收4000写命令
    void recvWriteCmd6000(ModuleBoardAddrType addr, SystemBusCommandType cmd, const QByteArray &data); //接收6000写命令

protected:
    void initSimData();               //初始化模拟数据（父类自动调用）
    void loadData4000();              //装载4000数据（父类自动调用）
    void loadData6000();              //装载6000数据（父类自动调用）
};

#endif // KEYLAMPSIMULATION_H
