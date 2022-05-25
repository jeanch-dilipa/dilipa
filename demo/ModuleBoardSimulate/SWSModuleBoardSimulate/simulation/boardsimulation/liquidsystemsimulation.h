#ifndef LIQUIDSYSTEMSIMULATION_H
#define LIQUIDSYSTEMSIMULATION_H

#include "boardsimulationbase.h"
#include "common/publicdata.h"

class LiquidSystemSimulation : public BoardSimulationBase
{
    Q_OBJECT
public:
    explicit LiquidSystemSimulation(QObject *parent = nullptr);
    ~LiquidSystemSimulation();

    void recvWriteCmd4000(ModuleBoardAddrType addr, SystemBusCommandType cmd, const QByteArray &data); //接收4000写命令
    void recvWriteCmd6000(ModuleBoardAddrType addr, SystemBusCommandType cmd, const QByteArray &data); //接收6000写命令

private slots:
    void slotMultiUseTimerTimeout();

protected:
    void initSimData();               //初始化模拟数据（父类自动调用）
    void loadData4000();              //装载4000数据（父类自动调用）
    void loadData6000();              //装载6000数据（父类自动调用）

private:
    QTimer *m_multiUseTimer;
    int     m_simYJ1OnOffTime = 0;    //模拟YJ1开关计时
    int     m_V1_V8ChangeTime = 0;    //模拟V1~V8切换计时
    quint8  tempV1_V8Sim = 0;         //临时V1~V8模拟切换状态
};

#endif // LIQUIDSYSTEMSIMULATION_H
