#include "uart485.h"
#include "crc.h"
#include "common/publicdata.h"

#define OPEN_DEBUG 0
#if OPEN_DEBUG
#include <QDebug>
#include <QTime>
#define CURRENTTIMESTR qPrintable(QTime::currentTime().toString("[HH:mm:ss.zzz]"))
#endif

UART485 *UART485::s_instance = Q_NULLPTR;
QMutex UART485::s_mutex;

#define FRAME_TIME             5    /*断帧时间 ms*/
#define DETECT_MACHINE_OUTTIME 2000 /*检测机型超时时间 ms*/

UART485 *UART485::instance()
{
    if(!s_instance)
    {
        QMutexLocker locker(&s_mutex);
        if(!s_instance)
        {
            s_instance = new UART485();
        }
    }

    return s_instance;
}

void UART485::deInstance()
{
    QMutexLocker locker(&s_mutex);
    if(s_instance)
    {
        delete s_instance;
    }
}

UART485::UART485() : QThread(Q_NULLPTR)
{
    this->moveToThread(this);
}

UART485::~UART485()
{
    if(this->isRunning())
    {
        this->quit();
        this->wait();
    }
}

void UART485::run()
{
    //创建断帧定时器
    m_frameTimer = new QTimer(this);
    connect(m_frameTimer, &QTimer::timeout, this, &UART485::slotFrameOver);
    m_frameTimer->setSingleShot(true);
    m_frameTimer->setInterval(FRAME_TIME);

    //创建串口对象
    m_serial = new QSerialPort(this);
    connect(m_serial, (void (QSerialPort:: *)(QSerialPort::SerialPortError))&QSerialPort::error, this, &UART485::slotErrorOccurred);
    connect(m_serial, &QSerialPort::readyRead, m_frameTimer, (void (QTimer:: *)())&QTimer::start);

    //创建管道方式对象
    m_socket = new QLocalSocket(this);
    connect(m_socket, &QLocalSocket::readyRead, m_frameTimer, (void (QTimer:: *)())&QTimer::start);

    //连接外部触发信号（跨线程）
    connect(this, &UART485::connectToSerial, this, &UART485::slotConnectToSerial);
    connect(this, &UART485::disconnectFromSerial, this, &UART485::slotDisconnectFromSerial);

    //未通讯检测
    m_detectMachineOutTimer = new QTimer(this);
    connect(m_detectMachineOutTimer, &QTimer::timeout, this, [this](){
        if(g_ss.machineSetType == AutoDetectMachine && g_ss.machineType != NoneMachine)
        {   //如果是自动检测机型，判断为无机型
            g_ss.machineType = NoneMachine;
            emit signalMachineTypeChanged();
        }
    });
    m_detectMachineOutTimer->start(DETECT_MACHINE_OUTTIME);

    //线程结束时关闭定时器，防止出错
    connect(this, &QThread::finished, this, [this](){
        m_frameTimer->stop();
        m_detectMachineOutTimer->stop();

        slotDisconnectFromSerial(); //关闭通讯端口，否则下次启动可能连不上
    });

    this->exec();
}

void UART485::slotConnectToSerial(SerialParaType para)
{
    m_bPipeCom = para.pipeCom;
    bool openRes;
    if(m_bPipeCom)
    {   //命名管道方式连接
        m_socket->setServerName(para.portName);
        openRes = m_socket->open(QIODevice::ReadWrite);
    }
    else
    {   //串口方式连接
        m_serial->setBaudRate(para.baud);
        m_serial->setParity(para.parity);
        m_serial->setDataBits(para.dataBits);
        m_serial->setStopBits(para.stopBits);
        m_serial->setPortName(para.portName);
        openRes = m_serial->open(QIODevice::ReadWrite);
    }
    m_frameTimer->stop();
    emit signalConnectSate(openRes, para.portName);
}

void UART485::slotDisconnectFromSerial()
{
    if(m_bPipeCom)
    {
        m_socket->close();
    }
    else
    {
        m_serial->close();
    }
    emit signalConnectSate(false);
}

void UART485::slotErrorOccurred(QSerialPort::SerialPortError error)
{
    if(!m_bPipeCom)
    {
        if(error != QSerialPort::NoError)
        {
            if(m_serial->isOpen())
            {
                m_serial->close();
            }
            emit signalConnectSate(false);
        }
    }
}

void UART485::slotFrameOver()
{
    QByteArray allData;
    if(m_bPipeCom)
    {
        allData = m_socket->readAll();
    }
    else
    {
        allData = m_serial->readAll();
    }

    //进行CRC校验
    bool crcRes = !CRC((uchar *)allData.data(), allData.size()).Sum();
    QList<QByteArray> parseByteList;
    if(!crcRes)
    {   //校验不通过，尝试拆包（使用管道通信时经常可能粘包）
        tryToParsePacket(parseByteList, allData);
    }

    if(parseByteList.isEmpty())
    {   //没有进行过拆包或拆包失败
        if(crcRes)
        {   //校验成功，处理数据
            recvDataHandle(allData);
        }
        else
        {
#if OPEN_DEBUG
            qDebug() << ("[CRC Error]" + printByteArray(allData));
#endif
        }
    }
    else
    {   //经过拆包得到数据
        for(int i = 0; i < parseByteList.size(); i++)
        {
            recvDataHandle(parseByteList[i]);
        }
    }
}

void UART485::recvDataHandle(QByteArray &allData)
{
    if(allData.size() < 4)
    {   //至少4个字节才为一个有效的命令
        return;
    }

    //进行回复
    QByteArray sendByte;
    SystemBusCommandType cmdType = (SystemBusCommandType)allData.at(1);
    if(g_ss.machineSetType == AutoDetectMachine)
    {   //自动判断机器类型
        checkMachineTypeChanged(allData[0]);
    }

    if(!isBoardComOpen(allData[0]))
    {   //该板子通讯开关为关，不回复
        return;
    }

    sendByte.append( allData[0]); //地址
    sendByte.append( cmdType);    //功能码

    if(cmdType >= READ_COMMAND_0 && cmdType <= READ_COMMAND_8) //判断为读命令
    {
        BoardDataPointer ptrSt = g_mbd.rdPtr(allData[0], allData[1]);
        sendByte += QByteArray((char *)ptrSt.ptr, ptrSt.size);

        if(sendByte.size() <= 2)
        {   ///没找到命令，暂时不回复
#if OPEN_DEBUG
            qDebug() << ("[Can not find return data]" + printByteArray(allData));
#endif
            return;
        }
    }
    else if(cmdType >= WRITE_COMMAND_0 && cmdType <= WRITE_COMMAND_9) //判断为写命令
    {
        allData.resize(allData.size()-2);  //去除末尾的CRC
        emit signalRecvWriteCmd(allData);  //发送到数据管理线程处理
    }

    //末尾追加CRC校验并回复
    ushort crcSum = CRC((uchar *)sendByte.data(), sendByte.size()).Sum();
//    int crcPos = sendByte.size();
    sendByte.append(crcSum & 0x00FF);
    sendByte.append(crcSum >> 8);
    if(m_bPipeCom)
    {
        m_socket->write(sendByte);
        m_socket->flush();
    }
    else
    {
        m_serial->write(sendByte);
        m_serial->flush();
    }
}

void UART485::tryToParsePacket(QList<QByteArray> &dstList, QByteArray &srcData)
{
    dstList.clear();
    if(srcData.length() < 4) //至少4个字节才进行解析，暂时没有低于4字节的数据包
    {
        return;
    }

    char *head = srcData.data();
    int len = srcData.length();
    QList<int> likeHeadIndexList({0}); //保存所有有可能是数据包头的索引

    //遍历整个数组，找到来自同一个模块地址发送的所有可以CRC校验通过的数据段
    for(int i = 3; i < len; i++)
    {
        if((*head == *(head + i)) || (i == len-1)) //如果某一个字节和首字节相等，很有可能前一段数据为一个数据包
        {
            bool isCRCPass = false;
            foreach(int li, likeHeadIndexList) //尝试对前面每一个类似数据段进行校验
            {
                char *phaseHead = head + li;
                int phaseLen = i - li;
                if(i == len-1) //如果当前已经检查到最后一个字节了，数据长度应该+1
                {
                    phaseLen++;
                }
                if(phaseLen >= 4) //至少4个字节才有解析的必要
                {
                    CRC crc((uchar *)phaseHead, phaseLen);
                    if(!crc.Sum()) //如果校验通过，则认为该段是一个数据包
                    {
                        dstList.append(QByteArray(phaseHead, phaseLen));
                        isCRCPass = true;
                        break;
                    }
                }
            }

            if(isCRCPass)
            {
                likeHeadIndexList.clear();
            }
            likeHeadIndexList.append(i);
        }
    }
}

QString UART485::printByteArray(const QByteArray &ba)
{
    QString printStr;
    foreach (uchar c, ba) {
        printStr += QString::number(c, 16).rightJustified(2, '0') + " ";
    }
    return printStr;
}

bool UART485::isBoardComOpen(int addr)
{
    bool comSW = true;

    switch(addr)
    {
    case BLOOD_PUMP_BOARD_ADDR4:          //血泵板地址
        comSW = g_simDa.bloodSys.bloodPumpBoardComSW;
        break;
    case FLUID_INFUSION_PUMP_BOARD_ADDR4: //补液泵板地址
        comSW = g_simDa.bloodSys.subPumpBoardComSW;
        break;
    case BLOOD_TRAIL_BOARD_ADDR6:         //血路驱动板地址
        comSW = g_simDa.bloodSys.bloodBoardComSW;
        break;
    case LIQUID_DRIVER_BOARD_ADDR6:       //水路板地址
        comSW = g_simDa.liquidSys.liquidBoardComSW;
        break;
    case DRIVER_BOARD_ADDR4:              //驱动板地址
        comSW = g_simDa.liquidSys.driveBoardComSW;
        break;
    case BALANCE_CHAMBER_BOARD_ADDR4:     //平衡腔板地址
        comSW = g_simDa.liquidSys.balanceBoardComSW;
        break;
    case HEATER_BOARD_ADDR4:              //加热板地址
        comSW = g_simDa.liquidSys.heatBoardComSW;
        break;
    case MIX_ULTRA_BOARD_ADDR6:           //超滤板地址
        comSW = g_simDa.mixUltraSys.mixUfBoardComSW;
        break;
    case MIXED_BOARD_ADDR4:               //配液板地址
        comSW = g_simDa.mixUltraSys.mixBoardComSW;
        break;
    case ULTRAFILTRATION_PUMP_BOARD_ADDR4://超滤板地址
        comSW = g_simDa.mixUltraSys.ufBoardComSW;
        break;
    case CONDUCTANCE_BOARD_ADDR4:         //电导板地址
        comSW = g_simDa.mixUltraSys.condBoardComSW;
        break;
    case HEPARIN_PUMP_BOARD_ADDR4:        //肝素板地址（4000）
    case HEPARIN_BOARD_ADDR6:             //肝素板地址（6000）
        comSW = g_simDa.antiSys.hepBoardComSW;
        break;
    case POWER_BOARD_ADDR4:               //电源板地址（4000）
    case POWER_BOARD_ADDR6:               //电源板地址（6000）
        comSW = g_simDa.powerSys.powerBoardComSW;
        break;
    case MONITOR_BOARD_ADDR6:             //监控板地址
        comSW = g_simDa.keyLamp.monitorBoardComSW;
        break;
    case BLOOD_TEMP_VOLUME_MODULE_ADDR:   //血温血容量模块地址
        comSW = g_simDa.btvRcm.btvBoardComSW;
        break;
    case UREA_SENSORE_MODULE_ADDR:        //实时清除率监测模块地址
        comSW = g_simDa.btvRcm.rcmBoardComSW;
        break;
    default:
        break;
    }

    return comSW;
}

void UART485::checkMachineTypeChanged(int addr)
{
    switch(addr)
    {
    case BLOOD_PUMP_BOARD_ADDR4:             //血泵板地址
    case FLUID_INFUSION_PUMP_BOARD_ADDR4:    //补液泵板地址
    case ULTRAFILTRATION_PUMP_BOARD_ADDR4:   //超滤板地址
    case HEPARIN_PUMP_BOARD_ADDR4:           //肝素板地址
    case DRIVER_BOARD_ADDR4:                 //驱动板地址
    case BALANCE_CHAMBER_BOARD_ADDR4:        //平衡腔板地址
    case MIXED_BOARD_ADDR4:                  //配液板地址
    case CONDUCTANCE_BOARD_ADDR4:            //电导板地址
    case HEATER_BOARD_ADDR4:                 //加热板地址
    case POWER_BOARD_ADDR4:                  //电源板地址
        if(g_ss.machineType != SWS4000)
        {
            g_ss.machineType = SWS4000;
            emit signalMachineTypeChanged();
        }
        m_detectMachineOutTimer->start(DETECT_MACHINE_OUTTIME); //重置判断机型超时定时器
        break;
    case BLOOD_TRAIL_BOARD_ADDR6:          //血路驱动板地址
    case HEPARIN_BOARD_ADDR6:              //肝素板地址
    case LIQUID_DRIVER_BOARD_ADDR6:        //水路驱动板地址
    case MIX_ULTRA_BOARD_ADDR6:            //配液超滤板地址
    case POWER_BOARD_ADDR6:                //电源板地址
        if(g_ss.machineType != SWS6000)
        {
            g_ss.machineType = SWS6000;
            emit signalMachineTypeChanged();
        }
        m_detectMachineOutTimer->start(DETECT_MACHINE_OUTTIME);
        break;
    default:
        break;
    }
}
