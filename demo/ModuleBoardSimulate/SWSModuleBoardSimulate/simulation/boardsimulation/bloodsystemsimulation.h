#ifndef BLOODSYSTEMSIMULATION_H
#define BLOODSYSTEMSIMULATION_H

#include "boardsimulationbase.h"
#include "common/publicdata.h"

class BloodSystemSimulation : public BoardSimulationBase
{
    Q_OBJECT
public:
    explicit BloodSystemSimulation(QObject *parent = 0);
    ~BloodSystemSimulation();

    void recvWriteCmd4000(ModuleBoardAddrType addr, SystemBusCommandType cmd, const QByteArray &data); //接收4000写命令
    void recvWriteCmd6000(ModuleBoardAddrType addr, SystemBusCommandType cmd, const QByteArray &data); //接收6000写命令

private slots:
    void slotCalcRotationNum();       //计算转数

protected:
    void initSimData();               //初始化模拟数据（父类自动调用）
    void loadData4000();              //装载4000数据（父类自动调用）
    void loadData6000();              //装载6000数据（父类自动调用）

private:
    void ctrlCalcRotationTimer();     //自动控制累计转数定时器

private:
    QTimer *m_calcRotNumTimer;        //累计转数定时器
    double m_bloodPumpRolls = 0;      //血泵累计转数
    double m_subPumpRolls = 0;        //置换液泵累计转数
};

#endif // BLOODSYSTEMSIMULATION_H
