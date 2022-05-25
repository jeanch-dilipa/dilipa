#ifndef MIXULTRASYSTEMSIMULATION_H
#define MIXULTRASYSTEMSIMULATION_H

#include "boardsimulationbase.h"
#include "common/publicdata.h"

class MixUltraSystemSimulation : public BoardSimulationBase
{
    Q_OBJECT
public:
    explicit MixUltraSystemSimulation(QObject *parent = nullptr);
    ~MixUltraSystemSimulation();

    void recvWriteCmd4000(ModuleBoardAddrType addr, SystemBusCommandType cmd, const QByteArray &data); //接收4000写命令
    void recvWriteCmd6000(ModuleBoardAddrType addr, SystemBusCommandType cmd, const QByteArray &data); //接收6000写命令

protected:
    void initSimData();           //初始化模拟数据（父类自动调用）
    void loadData4000();          //装载4000数据（父类自动调用）
    void loadData6000();          //装载6000数据（父类自动调用）

private slots:
    void slotCalcRotationNum();   //计算转数

private:
    void ctrlCalcRotationTimer(); //自动控制累计转数定时器

private:
    QTimer *m_calcRotNumTimer;    //累计转数定时器
    double m_APumpRolls = 0;      //A泵累计转数
    double m_BPumpRolls = 0;      //B泵累计转数
    double m_ufPumpRolls = 0;     //超滤泵累计转数
};

#endif // MIXULTRASYSTEMSIMULATION_H
