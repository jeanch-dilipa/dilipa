#ifndef SYSTEMSELFCHECK_H
#define SYSTEMSELFCHECK_H

#include <QObject>
#include <QMutex>
#include <QMutexLocker>
#include <QPointer>
#include <QTimer>

#include "common/common.h"
#include "common/systemSelfCheckItem.h"
#include "global/publicdata.h"
#include "controllayer/alarmcontrol.h"

#define INITSystemSelfCheck (systemSelfCheck::initSystemSelfCheck())

class systemSelfCheck : public QObject
{
    Q_OBJECT
public:
    explicit systemSelfCheck(QObject *parent = nullptr);
    ~ systemSelfCheck();

    static systemSelfCheck *initSystemSelfCheck();
    static void deSystemSelfCheck();

private:
    void connectOutSignal();                                                                                                    //连接外部信号
    void feedWaterSelfCheck();                                                                                                  //供水检测
    void monitorSelfCheck();                                                                                                    //监控系统检测
    void bloodPumpSelfCheck();                                                                                                  //血路系统检测
    void fluidinfusionPumpSelfCheck();                                                                                          //补液泵检测
    void heparinPumpSelfCheck();                                                                                                //肝素泵检测
    void chokedFlowMonitorSelfCheck();                                                                                          //阻流夹检测
    void balanceSelfCheck();                                                                                                    //平衡腔检测
    void endotoxinSelfCheck();                                                                                                  //内毒素自检
    void dialystateTempSelfCheck();                                                                                             //加热自检
    void liquorSelfCheck();                                                                                                     //配液自检

    void releasePressureOfTheSystem();                                                                                          //释放系统压力
    void stopGearPumpOfTheSystem();                                                                                             //停止齿轮泵
    void startBalanceSystem();                                                                                                  //启动平衡系统
    void stopBalanceSyatem();                                                                                                   //停止平衡系统
    void stopDialysateTempSystem();                                                                                             //停止加热系统
    void startDialysateTempSystem();                                                                                            //开启加热系统

private slots:
    void slot_systemSelfChekStart();                                                                                            //开始自检
    void slot_judgeReSelfCheck(const int checkItem);                                                                            //判断重新自检项
    void slot_judgeABSutionTubeStatus();                                                                                        //判断A\B吸液管状态
    void slot_judgeFeedWaterSelfCheck();                                                                                        //供水自检判断
    void slot_judgeBloodPumpSelfCheck();                                                                                        //血路系统自检判断
    void slot_judgeFluidinfusionPumpSelfCheck();                                                                                //补液系统自检判断
    void slot_judgeHeparinPumpSelfCheck();                                                                                      //抗凝系统自检判断
    void slot_judgeChokedFlowMonitorSelfCheck();                                                                                //阻流夹自检判断
    void slot_judgeSubpressureSelfCheck();                                                                                      //负压灌状态判断
    void slot_judgeBalanceSelfCheck_11();                                                                                       //平衡腔自检11判断
    void slot_balanceSelfCheck_21_1();                                                                                          //平衡腔自检21_1
    void slot_judgeBalanceSelfCheck_21_1();                                                                                     //平衡腔自检21_1判断
    void slot_disposeBalanceSelfCheck_21_1();                                                                                   //平衡腔自检21_1处理
    void slot_balanceSelfCheck_21_2();                                                                                          //平衡腔自检21_2
    void slot_judgeBalanceSelfCheck_21_2();                                                                                     //平衡腔自检21_2判断
    void slot_disposeBalanceSelfCheck_21_2();                                                                                   //平衡腔自检21_2处理
    void slot_balanceSelfCheck_22_1();                                                                                          //平衡腔自检22_1
    void slot_balanceSelfCheck_22_2();                                                                                          //平衡腔自检22_2
    void slot_judgeBalanceSelfCheck_22_2();                                                                                     //平衡腔自检22_2判断
    void slot_disposeBalanceSelfCheck_22_2();                                                                                   //平衡腔自检22_2处理
    void slot_balanceSelfCheck_31();                                                                                            //平衡腔自检31
    void slot_balanceSelfCheck_32_1();                                                                                          //平衡腔自检32_1
    void slot_balanceSelfCheck_32_2();                                                                                          //平衡腔自检32_2
    void slot_judgeBalanceSelfCheck_32_2();                                                                                     //平衡腔自检32_2判断
    void slot_disposeBalanceSelfCheck_32_2();                                                                                   //平衡腔自检32_2处理
    void slot_balanceSelfCheck_32_3();                                                                                          //平衡腔自检32_3
    void slot_judgeBalanceSelfCheck_32_3();                                                                                     //平衡腔自检32_3判断
    void slot_balanceSelfCheck_32_4();                                                                                          //平衡腔自检32_4
    void slot_judgeBalanceSelfCheck_32_4();                                                                                     //平衡腔自检32_4判断
    void slot_disposeBalanceSelfCheck_32_4();                                                                                   //平衡腔自检32_4处理
    void slot_balanceSelfCheck_32_5();                                                                                          //平衡腔自检32_5
    void slot_judgeBalanceSelfCheck_32_5();                                                                                     //平衡腔自检32_5判断
    void slot_balanceSelfCheck_32_6();                                                                                          //平衡腔自检32_6
    void slot_judgeBalanceSelfCheck_32_6();                                                                                     //平衡腔自检32_6判断
    void slot_disposeBalanceSelfCheck_32_6();                                                                                   //平衡腔自检32_6处理
    void slot_balanceSelfCheck_33_1();                                                                                          //平衡腔自检33_1
    void slot_balanceSelfCheck_33_2();                                                                                          //平衡腔自检33_2
    void slot_judgeBalanceSelfCheck_33_2();                                                                                     //平衡腔自检33_2判断
    void slot_judgeDisposeBalanceSelfCheck_33_2();                                                                              //平衡腔自检33_2判断处理
    void slot_disposeBalanceSelfCheck_33_2();                                                                                   //平衡腔自检33_2处理
    void slot_balanceSelfCheck_33_3();                                                                                          //平衡腔自检33_3
    void slot_judgeBalanceSelfCheck_33_3();                                                                                     //平衡腔自检33_3判断
    void slot_judgeDisposeBalanceSelfCheck_33_3();                                                                              //平衡腔自检33_3判断处理
    void slot_disposeBalanceSelfCheck_33_3();                                                                                   //平衡腔自检33_3处理
    void slot_balanceSelfCheck_33_4();                                                                                          //平衡腔自检33_4
    void slot_balanceSelfCheck_33_5();                                                                                          //平衡腔自检33_5
    void slot_judgeBalanceSelfCheck_33_5();                                                                                     //平衡腔自检33_5判断
    void slot_balanceSelfCheck_33_6();                                                                                          //平衡腔自检33_6
    void slot_judgeBalanceSelfCheck_33_6();                                                                                     //平衡腔自检33_6判断
    void slot_disposeBalanceSelfCheck_33_6();                                                                                   //平衡腔自检33_6处理
    void slot_balanceSelfCheck_36();                                                                                            //平衡腔自检36
    void slot_balanceSelfCheck_36_1();                                                                                          //平衡腔自检36_1
    void slot_judgeBalanceSelfCheck_36_1();                                                                                     //平衡腔自检36_1判断
    void slot_balanceSelfCheck_36_2();                                                                                          //平衡腔自检36_2
    void slot_judgeBalanceSelfCheck_36_2();                                                                                     //平衡腔自检36_2判断
    void slot_disposeBalanceSelfCheck_36_2();                                                                                   //平衡腔自检36_2处理
    void slot_judgeBalanceSelfCheck();                                                                                          //平衡腔自检完成判断
    void slot_endotoxinSelfCheck_11();                                                                                          //内毒素自检11
    void slot_endotoxinSelfCheck_12_1();                                                                                        //内毒素自检12_1
    void slot_judgeEndotoxinSelfCheck_12_1();                                                                                   //内毒素自检12_1判断
    void slot_disposeEndotoxinSelfCheck_12_1();                                                                                 //内毒素自检12_1处理
    void slot_endotoxinSelfCheck_12_2();                                                                                        //内毒素自检12_2
    void slot_judgeEndotoxinSelfCheck_12_2();                                                                                   //内毒素自检12_2判断
    void slot_disposeEndotoxinSelfCheck_12_2();                                                                                 //内毒素自检12_2处理
    void slot_endotoxinSelfCheck_12_3();                                                                                        //内毒素自检12_3
    void slot_endotoxinSelfCheck_12_4();                                                                                        //内毒素自检12_4
    void slot_endotoxinSelfCheck_12_5();                                                                                        //内毒素自检12_5
    void slot_judgeEndotoxinSelfCheck_12_5();                                                                                   //内毒素自检12_5判断
    void slot_disposeEndotoxinSelfCheck_12_5();                                                                                 //内毒素自检12_5处理
    void slot_endotoxinSelfCheck_13();                                                                                          //内毒素自检13
    void slot_judgeEndotoxinSelfCheck_13();                                                                                     //内毒素自检13判断
    void slot_endotoxinSelfCheck_14();                                                                                          //内毒素自检14
    void slot_judgeEndotoxinSelfCheck_14();                                                                                     //内毒素自检14判断
    void slot_endotoxinSelfCheck_15_1();                                                                                        //内毒素自检15_1
    void slot_endotoxinSelfCheck_15_2();                                                                                        //内毒素自检15_2
    void slot_judgeendotoxinSelfCheck();                                                                                        //内毒素自检完成判断
    void slot_dialystateTempSelfCheck();                                                                                        //加热自检
    void slot_judgeDialystateTempSelfCheck();                                                                                   //加热自检判断
    void slot_disposeDialystateTempSelfCheck();                                                                                 //加热自检处理

signals:
    void signal_createSystemSelfCheck();                                                                                        //创建自检界面
    void signal_sendAlarmData(int alarmCode,int alarmInterval,int alarmEnable);                                                 //报警信号传递
    void signal_SelfCheckStart(const int checkItem,const int checkTime,const int checkSubItem = 0);                             //检测开始
    void signal_SelfCheckResult(const int checkItem,const int checkResult);                                                     //检测结果
    void signal_reSelfCheck(const int checkItem);                                                                               //重新检测

private:
    static systemSelfCheck                          *s_systemSelfCheck;
    static QMutex                                    s_mutexLocker;

    QPointer<alarmcontrol>                           m_alarmcontrol;                                                             //报警线程

    QPointer<QTimer>                                 m_ABSuctionTubeStatus;                                                      //A\B吸液管位置检测定时器
    QPointer<QTimer>                                 m_balanceJudgeTimer;                                                        //平衡腔单步判断定时器
    QPointer<QTimer>                                 m_balanceSustionTimer;                                                      //平衡腔单步检测持续时间定时器
    QList<int>                                       m_selfCheckItemList;                                                        //自检项目合集
    bool                                             m_checkItem_monitor;                                                        //是否开始检测监控系统
    bool                                             m_checkItem_bloodPump;                                                      //是否开始检测血路系统
    bool                                             m_checkItem_fluidPump;                                                      //是否开始检测补液系统
    bool                                             m_checkItem_heparPump;                                                      //是否开始检测抗凝系统
    bool                                             m_checkItem_choke;                                                          //是否开始检测阻流夹
    bool                                             m_checkItem_balance;                                                        //是否开始检测平衡腔
    bool                                             m_checkItem_endotoxin;                                                      //是否开始检测内毒素
    bool                                             m_checkItem_temp;                                                           //是否开始检测加热
    bool                                             m_checkItem_liquor;                                                         //是否开始检测配液
    bool                                             m_isHeparinPumpFirstCheck;                                                  // 0/1 肝素泵反向检测/正向检测
    bool                                             m_isChokeFirstCheck;                                                        // 0/1 阻流夹打开/关闭检测
    bool                                             m_isCheckYG3Reveal;                                                         //开始YG3泄漏检测
    bool                                             m_reCheckEndotoxin15;                                                       //内毒素自检重复15
    bool                                             m_isCheckTempReveal;                                                        //开始加热检测
    int                                              m_feedWaterSelfCheckTimes;                                                  //最大供水检测次数
    int                                              m_countSustionYG2YG4Times;                                                  //平衡腔自检YG2、YG4连续出错次数
    int                                              m_YG3moreThan110kpaTimes;                                                   //平衡腔自检YG3超过110KPA次数
    int                                              m_YG3ChangeValue;                                                           //平衡腔自检YG3泄漏量
    int                                              m_preValue;                                                                 //平衡腔自检前次YG3压力值
    int                                              m_TempChangeValue;                                                          //加热自检温度变化量
    int                                              m_preTempValue;                                                             //加热自检前次温度值
    int                                              m_YG3Above90KpaTimes;                                                       //平衡腔自检YG3保压90Kpa时间
    int                                              m_endotoxinCheckTimes;                                                      //内毒素自检符合次数

};

#endif // SYSTEMSELFCHECK_H
