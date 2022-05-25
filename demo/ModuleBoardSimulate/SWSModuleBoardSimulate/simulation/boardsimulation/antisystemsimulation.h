#ifndef ANTISYSTEMSIMULATION_H
#define ANTISYSTEMSIMULATION_H

#include "boardsimulationbase.h"
#include "common/publicdata.h"

class AntiSystemSimulation : public BoardSimulationBase
{
    Q_OBJECT
public:
    explicit AntiSystemSimulation(QObject *parent = nullptr);

    void recvWriteCmd4000(ModuleBoardAddrType addr, SystemBusCommandType cmd, const QByteArray &data); //接收4000写命令
    void recvWriteCmd6000(ModuleBoardAddrType addr, SystemBusCommandType cmd, const QByteArray &data); //接收6000写命令

protected:
    void initSimData();               //初始化模拟数据（父类自动调用）
    void loadData4000();              //装载4000数据（父类自动调用）
    void loadData6000();              //装载6000数据（父类自动调用）

private slots:
    void slotCalcHepFlowTimeout();    //肝素累计推注流量定时器超时

private:
    void ctrlCalcRotationTimer();     //自动控制肝素累计推注流量定时器

private:
    QTimer *m_calcHepTotalFlowTimer;  //肝素累计推注流量定时器
    QMap<int, int> m_Symap;           //注射器型号表
    double m_hepTotalFlow = 0;        //肝素累计推注流量
    double m_beforeAppendVolume = -1; //标记肝素追加前的已推注总量
    bool m_isAppend = false;          //是否正在追加
};

#endif // ANTISYSTEMSIMULATION_H
