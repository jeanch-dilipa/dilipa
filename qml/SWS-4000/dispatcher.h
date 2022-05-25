#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QObject>
#include <QPointer>

#include "common/common.h"
#include "interface/systemselfcheck/systemselfcheck.h"
#include "interface/correct/correct.h"
#include "interface/detect/detect.h"
#include "interface/startinterface.h"
#include "controllayer/alarmcontrol.h"
#include "controllayer/serialportcontrol.h"
#include "common/systemSelfCheckItem.h"
#include "controllayer/datadealthread.h"

class Dispatcher : public QObject
{
    Q_OBJECT
public:
    explicit Dispatcher(QObject *parent = nullptr);
    ~ Dispatcher();

private:
    void createSystemSelfCheck();                                                                                                           //创建自检
    void destroySystemSelfCheck();                                                                                                          //销毁自检
    void createSchema();                                                                                                                    //创建准备
    void destroySchema();                                                                                                                   //销毁准备
    void createCorrectInterface();                                                                                                          //创建校正
    void destroyCorrectInterface();                                                                                                         //销毁校正
    void createDetectInterface();                                                                                                           //创建检测
    void destroyDetectInterface();                                                                                                          //销毁检测

    void createDataDealThread();                                                                                                            //创建数据处理线程
    void destroyDataDealThread();                                                                                                           //销毁数据处理线程

signals:
    /*alarmcontrol*/
    void signal_clearAllAlarm();                                                                                                            //清除所有报警信号
    void signal_showAlarmToInterface(int alarmCode,int alarmGrade,int alarmEnable);                                                         //发送报警信息到界面
    /*startInterface*/
    void signal_createStartInterface();                                                                                                     //创建启动界面
    /*correct*/
    void signal_createCorrectInterface();                                                                                                   //创建校正界面
    void signal_destroyCorrectInterface();                                                                                                  //销毁校正界面
    /*detect*/
    void signal_createDetectInterface();                                                                                                    //创建检测界面
    void signal_destroyDetectInterface();                                                                                                   //销毁检测界面
    /*systemSelfCheck*/
    void signal_createSystemSelfCheck();                                                                                                    //创建自检界面
    void signal_destroySystemSelfCheck();                                                                                                   //销毁自检界面
    void signal_SelfCheckStart(const int checkItem,const int checkTime,const int checkSubItem = 0);                                         //检测开始
    void signal_SelfCheckResult(const int checkItem,const int checkResult);                                                                 //检测结果
    void signal_reSelfCheck(const int checkItem);                                                                                           //重新检测
    /*schema*/
    void signal_createSchema();                                                                                                             //创建模式界面
    void signal_destroySchema();                                                                                                            //销毁模式界面
    /*dataDealThread*/
    void signal_bloodValueChange();                                                                                                         //血泵值改变信号

private:
    QPointer<startInterface>                              m_startInterface;                                                                 //启动界面
    QPointer<systemSelfCheck>                             m_systemSelfCheck;                                                                //自检界面
    QPointer<correct>                                     m_correctInterface;                                                               //校正界面
    QPointer<detect>                                      m_detectInterface;                                                                //检测界面

    QPointer<alarmcontrol>                                m_alarmControl;                                                                   //报警检测线程
    QPointer<dataDealThread>                              m_dataDealThread;                                                                 //数据处理线程
};

#endif // DISPATCHER_H
