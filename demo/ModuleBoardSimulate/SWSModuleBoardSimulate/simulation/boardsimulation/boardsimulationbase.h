#ifndef BOARDSIMULATIONBASE_H
#define BOARDSIMULATIONBASE_H

#include <QObject>
#include <QHash>
#include "simulation/simulationsetdata.h"
#include "simulation/randomdatagenerator.h"

class BoardSimulationBase : public QObject
{
    Q_OBJECT
public:
    explicit BoardSimulationBase(QObject *parent = nullptr);
    virtual ~BoardSimulationBase();

    QHash<SimDataCode, SimDataSt *> &simDataMap() {return m_simDataMap;} //返回模拟数据序列
    QList<ushort *> &boardVersionList() {return m_boardVersionList;}     //返回模块板版本序列
    SimDataCode boardVerCode() {return m_boardVersionCode;}              //返回模块板版本信息功能码

    static SimDataSt *findSimData(SimDataCode code);                     //通过功能码找到对应的模拟数据指针
    static QList<ushort *> findBoardVerList(SimDataCode code);           //通过功能码找到模块板版本信息列表
    static const QList<BoardSimulationBase *> &simSysList() {return s_simSysList;} //返回模拟对象指针

protected:
    virtual void initSimData() = 0;   //初始化模拟数据，子类实现
    virtual void loadData4000() = 0;  //装载4000数据，子类实现
    virtual void loadData6000() = 0;  //装载6000数据，子类实现
    void addSimDataInit(SimDataCode code, SimDataSt *smd, ValueType valueType, int decimals = 0); //初始化一个模拟数据
    void checkSetChange(SimDataSt &smd);                      //检查某数据设置的修改
    void setBitInByte(quint8 &byte, int bit, bool set);       //改变字节中的某一位的0或1
    void setBitInByte4(quint32 &byte, quint32 bit, bool set); //改变字节中的某一位的0或1（4字节版）
    template<typename T, typename K>
    void _setBitInByte(T &, K, bool);

private slots:
    void slotLoadDataTimeout();

protected:
    SimDataCode m_boardVersionCode = C_Invalid;       //模块板版本信息功能码
    QList<ushort *> m_boardVersionList;               //保存板子版本信息序列

private:
    RandomDataGenerator *m_randomGenerator;           //随机数发生器
    QHash<SimDataCode, SimDataSt *> m_simDataMap;     //保存模拟数据序列
    QTimer *m_loadDataTimer;                          //装载数据定时器
    static QList<BoardSimulationBase *> s_simSysList; //保存所有new出的子类指针
};

#endif // BOARDSIMULATIONBASE_H
