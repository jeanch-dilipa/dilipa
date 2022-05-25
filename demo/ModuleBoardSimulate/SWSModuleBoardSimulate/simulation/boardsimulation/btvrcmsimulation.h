#ifndef BTVRCMSIMULATION_H
#define BTVRCMSIMULATION_H

#include "boardsimulationbase.h"
#include "common/publicdata.h"

class BTVRCMSimulation : public BoardSimulationBase
{
    Q_OBJECT
public:
    explicit BTVRCMSimulation(QObject *parent = nullptr);

    void recvWriteCmd(ModuleBoardAddrType addr, SystemBusCommandType cmd, const QByteArray &data); //接收写命令

protected:
    void initSimData();    //初始化模拟数据（父类自动调用）
    void loadData4000();   //装载4000数据（父类自动调用）
    void loadData6000();   //装载6000数据（父类自动调用）

private:
    quint16 m_autoBV0 = 0; //自动模拟时的初始血容量
    bool m_isAutoRCMCorrect = false; //标记自动模拟时，实时清除率是否已经校正
};

#endif // BTVRCMSIMULATION_H
