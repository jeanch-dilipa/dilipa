#ifndef SERIALPORTCONTROL_H
#define SERIALPORTCONTROL_H

#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QtSerialPort/QSerialPort>
#include <QTimer>
#include <QPointer>

#include "common/common.h"
#include "common/systemAlarmCodes.h"
#include "controllayer/crc.h"
#include "controllayer/alarmcontrol.h"

#define INITSerialportControl (serialportControl::initSerialportControl())

class serialportControl : public QThread
{
    Q_OBJECT
public:
    explicit serialportControl();
    ~ serialportControl();

    static serialportControl *initSerialportControl();
    static void deSerialportControl();

protected:
    void run();

    void slot_serialportDataArrived();                                                                                                    //串口数据到达
    void slot_serialportDataSend(QByteArray sendData);                                                                                    //串口数据发送
    void slot_serialportError(const QSerialPort::SerialPortError serialportError);                                                        //串口异常

signals:
    void signal_sendAlarmData(int alarmCode,int alarmInterval,int alarmEnable);                                                           //报警信号传递
    void signal_serialportDataArrived(QByteArray);                                                                                        //转发串口数据给主控
    void signal_modelBoardDataLoading(QByteArray);                                                                                        //转发模块数据到相应串口

private:
    static serialportControl                       *s_serialportControl;
    static QMutex                                   s_mutexLocker;

    QPointer<QSerialPort>                           m_serialport;                                                                         //串口实例
    QPointer<QTimer>                                m_frameEndTimer;                                                                      //断帧定时器
    QByteArray                                      m_arrivedDataBuff;                                                                    //接收数据缓冲

    QPointer<alarmcontrol>                          m_alarmcontrol;                                                                       //报警线程

};

#endif // SERIALPORTCONTROL_H
