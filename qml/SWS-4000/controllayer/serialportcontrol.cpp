#include "serialportcontrol.h"

serialportControl *serialportControl::s_serialportControl=nullptr;
QMutex serialportControl::s_mutexLocker;

/*
功能描述：serialportControl类构造函数
输    入：/
输    出：/
*/
serialportControl::serialportControl()
{
#if DEBUG_MODEL || DEBUG_MODEL_SERIALPORTCONTROL
    QString debugstr="serialportControl::serialportControl():构造函数";
    qdebug<<debugstr;
#endif
/*QObject: Cannot create children for a parent that is in a different thread. (Parent is QSerialPort(0x2b88250), parent's thread is serialportControl(0x2b7c3d8), current thread is QThread(0x7c0db0)*/
    this->moveToThread(this);
    this->start();
}
/*
功能描述：serialportControl类析构函数
输    入：/
输    出：/
*/
serialportControl::~serialportControl()
{
#if DEBUG_MODEL || DEBUG_MODEL_SERIALPORTCONTROL
    QString debugstr="serialportControl::~serialportControl():析构函数";
    qdebug<<debugstr;
#endif

    m_alarmcontrol = nullptr;
    m_serialport = nullptr;
    if(m_frameEndTimer){delete m_frameEndTimer;m_frameEndTimer = nullptr;}
}
/*
功能描述：创建自身
输    入：/
输    出：/
*/
serialportControl *serialportControl::initSerialportControl()
{
#if DEBUG_MODEL || DEBUG_MODEL_SERIALPORTCONTROL
    QString debugstr="serialportControl *serialportControl::initSerialportControl():创建自身";
    qdebug<<debugstr;
#endif

    if(!s_serialportControl)
    {
        QMutexLocker locker(&s_mutexLocker);
        if(!s_serialportControl)
        {
            s_serialportControl = new serialportControl();
        }
    }
    return s_serialportControl;
}
/*
功能描述：销毁自身
输    入：/
输    出：/
*/
void serialportControl::deSerialportControl()
{
#if DEBUG_MODEL || DEBUG_MODEL_SERIALPORTCONTROL
    QString debugstr="void serialportControl::deSerialportControl()：销毁自身";
    qdebug<<debugstr;
#endif

    if(s_serialportControl)
    {
        QMutexLocker locker(&s_mutexLocker);
        if(s_serialportControl)
        {
            s_serialportControl->exit(0);
            s_serialportControl->wait();
            delete s_serialportControl;
            s_serialportControl = nullptr;
        }
    }
}
/*
功能描述：线程run
输    入：/
输    出：/
*/
void serialportControl::run()
{
#if DEBUG_MODEL || DEBUG_MODEL_SERIALPORTCONTROL
    QString debugstr="void serialportControl::run()：线程";
    qdebug<<debugstr;
#endif

    m_serialport = new QSerialPort();
    m_serialport->setPortName("COM4");
    m_serialport->setBaudRate(QSerialPort::Baud115200);
    m_serialport->setDataBits(QSerialPort::Data8);
    m_serialport->setParity(QSerialPort::NoParity);
    m_serialport->setStopBits(QSerialPort::OneStop);
    m_serialport->setFlowControl(QSerialPort::NoFlowControl);
    m_serialport->open(QIODevice::ReadWrite);

    connect(m_serialport,&QSerialPort::readyRead,this,&serialportControl::slot_serialportDataArrived);
    connect(m_serialport,(void (QSerialPort::*)(QSerialPort::SerialPortError))&QSerialPort::error,this,&serialportControl::slot_serialportError);

    m_arrivedDataBuff.clear();

    m_frameEndTimer = new QTimer();
    connect(m_frameEndTimer,&QTimer::timeout,[this]{
                                                    if(!CRC((uchar *)m_arrivedDataBuff.data(),m_arrivedDataBuff.size()).Sum())
                                                    {
                                                         emit signal_serialportDataArrived(m_arrivedDataBuff);
                                                    }
                                                    m_arrivedDataBuff.clear();
                                                   });
    m_frameEndTimer->setInterval(5);

    connect(s_serialportControl,&serialportControl::signal_modelBoardDataLoading,s_serialportControl,&serialportControl::slot_serialportDataSend);

    m_alarmcontrol = INITAlarmControl;
    connect(this,&serialportControl::signal_sendAlarmData,m_alarmcontrol,&alarmcontrol::signal_receivedAlarmData);

    /*进入事件循环*/
    this->exec();
}
/*
功能描述：串口数据到达
输    入：/
输    出：/
*/
void serialportControl::slot_serialportDataArrived()
{
#if DEBUG_MODEL || DEBUG_MODEL_SERIALPORTCONTROL
    QString debugstr="void serialportControl::slot_serialportDataArrived()：串口数据到达";
    qdebug<<debugstr;
#endif

    m_arrivedDataBuff.append(m_serialport->readAll());
    m_frameEndTimer->start();
}
/*
功能描述：串口数据发送
输    入：/
输    出：/
*/
void serialportControl::slot_serialportDataSend(QByteArray sendData)
{
#if DEBUG_MODEL || DEBUG_MODEL_SERIALPORTCONTROL
    QString debugstr="void serialportControl::slot_serialportDataSend(QByteArray sendData)：串口数据发送";
    qdebug<<debugstr;
#endif

    ushort CRCnum = CRC((unsigned char *)sendData.data(),sendData.length()).Sum();
    sendData[sendData.size()] = CRCnum & 0xff;
    sendData[sendData.size()] = CRCnum >> 8;

    m_serialport->write(sendData);
    m_serialport->flush();
}
/*
功能描述：串口出错
输    入：串口错误类型SerialPortError
输    出：/
*/
void serialportControl::slot_serialportError(QSerialPort::SerialPortError serialportError)
{
#if DEBUG_MODEL || DEBUG_MODEL_SERIALPORTCONTROL
    QString debugstr="void serialportControl::slot_serialportError(QSerialPort::SerialPortError)：串口出错";
    qdebug<<debugstr;
#endif
    if(serialportError != QSerialPort::NoError)
    {
        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_MODULE_BORD_ERROR,CONTINUE,SYSTEM_ALARM_ENABLE);
    }
}
