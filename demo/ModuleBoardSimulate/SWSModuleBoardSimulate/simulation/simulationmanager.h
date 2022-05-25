#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include "boardsimulation/bloodsystemsimulation.h"
#include "boardsimulation/liquidsystemsimulation.h"
#include "boardsimulation/mixultrasystemsimulation.h"
#include "boardsimulation/antisystemsimulation.h"
#include "boardsimulation/powersystemsimulation.h"
#include "boardsimulation/keylampsimulation.h"
#include "boardsimulation/btvrcmsimulation.h"
#include <QThread>

class SimulationManager : public QThread
{
    Q_OBJECT
public:
    explicit SimulationManager(QObject *parent = 0);
    ~SimulationManager();

protected:
    void run();

signals:
    void signalLoadSetFileFinished();           //加载设置文件完成

public slots:
    void slotFinished();
    void slotRecvWriteCmd(QByteArray data);     //接收到写命令
    void slotSaveSetToFile(QString fileName);   //保存设置到文件
    void slotLoadSetFromFile(QString fileName); //从文件中加载设置
    void slotRemoveSetFile();                   //清除设置文件

private:
    inline void _outputSetToFile(QTextStream &stream, BoardSimulationBase *smb); //输出到文件

private:
    BloodSystemSimulation    *m_bloodSysSim;    //血路系统模拟器
    LiquidSystemSimulation   *m_liquidSysSim;   //水路系统模拟器
    MixUltraSystemSimulation *m_mixUltraSysSim; //配液超滤系统模拟器
    AntiSystemSimulation     *m_antiSysSim;     //抗凝系统模拟器
    PowerSystemSimulation    *m_PowerSysSim;    //电源系统模拟器
    keyLampSimulation        *m_keyLampSim;     //按键指示灯模拟器
    BTVRCMSimulation         *m_btvRcmSim;      //血温血容与实时清除率监测模拟器
};

#endif // SIMULATIONMANAGER_H
