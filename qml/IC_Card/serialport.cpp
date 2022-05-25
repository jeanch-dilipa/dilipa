#include "serialport.h"

#define IC_CARD_DEVICE_ADDRESS          0x27        //IC卡读写地址

#define HAND_SHAKE_TIMER                1000        //握手超时
#define GETOVER_TIMER                   10          //数据传输结束
#define PEPLY_OUT_TIMER                 3000        //回复超时
#define AUTO_CONNECT_TIMER              6000        //自动连接串口
#define MAX_FAIL_NUM                    3           //最大失败次数

serialport *serialport::s_initserial=nullptr;
QMutex serialport::s_mutex;

serialport::serialport()
{
#if DEBUG_MODEL
    QString debugstr=tr("serialport::serialport():类构造函数");
    emit signaldebugserialport(debugstr);
    qdebug<<debugstr;
#endif

    this->moveToThread(this);
    this->start();
}

serialport *serialport::initserialport()
{
#if DEBUG_MODEL
    qdebug<<tr("serialport *serialport::initserialport():锁定");
#endif

    if(!s_initserial)
    {
        QMutexLocker locker(&s_mutex);
        if(!s_initserial)
        {
            s_initserial=new serialport();
        }
    }
    return s_initserial;
}

void serialport::deinitserialport()
{
#if DEBUG_MODEL
    qdebug<<tr("void serialport::deinitserialport():解锁");
#endif

    if(s_initserial)
    {
        QMutexLocker locker(&s_mutex);
        if(s_initserial)
        {
            delete s_initserial;
            s_initserial=nullptr;
        }
    }
}

void serialport::run()
{
#if DEBUG_MODEL
    QString debugstr=tr("void serialport::run():运行");
    emit signaldebugserialport(debugstr);
    qdebug<<debugstr;
#endif

    m_serial=new QSerialPort(this);
    m_serial->setBaudRate(QSerialPort::Baud115200);//波特率
    m_serial->setParity(QSerialPort::NoParity);//校验位
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);//流控制
    connect(m_serial,&QSerialPort::readyRead,this,&serialport::readserialportdata);
    connect(m_serial,(void (QSerialPort:: *)(QSerialPort::SerialPortError))&QSerialPort::error,this,&serialport::serialportdisconnect);

    connect(this,&serialport::signalgetserialport,this,&serialport::slotgetserialportlist);
    connect(this,&serialport::signalcardrecordsrequst,this,&serialport::readcardrecords);

    handshaketimer=new QTimer();
    handshaketimer->setSingleShot(true);
    handshaketimer->setInterval(HAND_SHAKE_TIMER);
    connect(handshaketimer,&QTimer::timeout,this,&serialport::tryconnectserialport);

    getovertimer=new QTimer(this);
    getovertimer->setSingleShot(true);
    getovertimer->setInterval(GETOVER_TIMER);
    connect(getovertimer,&QTimer::timeout,this,&serialport::analyseserialportdata);

    replyouttimer=new QTimer(this);
    replyouttimer->setSingleShot(true);
    replyouttimer->setInterval(PEPLY_OUT_TIMER);
    connect(replyouttimer,&QTimer::timeout,this,&serialport::reoperate);

    serialporttimer=new QTimer(this);
    serialporttimer->setSingleShot(true);
    serialporttimer->setInterval(AUTO_CONNECT_TIMER);
    connect(serialporttimer,&QTimer::timeout,this,&serialport::tryconnectserialport);

    this->exec();//进入事件循环
}

void serialport::slotgetserialportlist()
{
#if DEBUG_MODEL
    QString debugstr=tr("void serialport::slotgetserialportlist():获取可用串口列表");
    emit signaldebugserialport(debugstr);
    qdebug<<debugstr;
#endif

    serialportlist=QSerialPortInfo::availablePorts();
    currentportindex=0;
    tryconnectserialport();
}

void serialport::senddatatoserialport(QByteArray senddata, bool addcrc)
{
#if DEBUG_MODEL
    QString debugstr=tr("void serialport::senddatatoserialport(QByteArray senddata, bool addcrc):串口数据发送");
    emit signaldebugserialport(debugstr);
    qdebug<<debugstr;
#endif

    serialportsenddata=senddata;
    if(addcrc)
    {
        ushort crcnum=CRC((unsigned char *)senddata.data(),senddata.length()).Sum();
        int size=senddata.size();
        senddata[size]=crcnum&0xff;
        senddata[size+1]=crcnum>>8;
    }

    if(!m_serial->isOpen())
    {
        emit signaldebugserialport(tr("串口打开失败"));
        return;
    }

    if(m_serial->write(senddata)!=senddata.size())
    {
        emit signaldebugserialport(tr("数据丢失"));
        return;
    }
    else
    {
        replyouttimer->start();
        emit signaldebugserialport(tr("发送数据：")+senddata.toHex());
    }
}

void serialport::readserialportdata()
{
#if DEBUG_MODEL
    QString debugstr=tr("void serialport::readserialportdata():读取串口数据");
    emit signaldebugserialport(debugstr);
    qdebug<<debugstr;
#endif

    serialportdata+=m_serial->readAll();
    getovertimer->start();
    replyouttimer->stop();
}

void serialport::tryconnectserialport()
{
#if DEBUG_MODEL
    QString debugstr=tr("void serialport::tryconnectserialport():尝试连接串口");
    emit signaldebugserialport(debugstr);
    qdebug<<debugstr;
#endif

    if(m_serial->isOpen())
        m_serial->close();
    if(currentportindex<serialportlist.size())
        m_serial->setPortName(serialportlist.at(currentportindex).portName());
    else
    {
        emit signaldebugserialport(tr("没有找到正确的串口"));
        emit signalconnectresult(false);
        return;
    }

    currentportindex++;

    isTryconnecting=true;
    if(m_serial->open(QIODevice::ReadWrite))
    {
        senddatatoserialport(QByteArray::fromHex("27 21 00 01 02 03 04 05"));
        handshaketimer->start();
    }
    else
        QTimer::singleShot(10,this,&serialport::tryconnectserialport);
    isTryconnecting=false;
}

void serialport::serialportdisconnect(QSerialPort::SerialPortError error)
{
#if DEBUG_MODEL
    QString debugstr=tr("void serialport::serialportdisconnect(QSerialPort::SerialPortError):串口连接断开");
    emit signaldebugserialport(debugstr);
    qdebug<<debugstr;
#endif

    if(error!=QSerialPort::NoError)
    {
        emit signalconnectresult(false);
        currentportindex=0;
        if(!serialporttimer->isActive())
            serialporttimer->start();
    }
}

void serialport::analyseserialportdata()
{
#if DEBUG_MODEL
    QString debugstr=tr("void serialport::analyseserialportdata():解析数据");
    emit signaldebugserialport(debugstr);
    qdebug<<debugstr;
#endif
    QByteArray alldata=serialportdata;
    serialportdata.clear();
    getovertimer->stop();

    emit signaldebugserialport(tr("收到数据：")+alldata.toHex());

    if(CRC((uchar *)alldata.data(),alldata.size()).Sum())
    {
        emit signaldebugserialport(tr("CRC校验失败"));
        return;
    }

    if(alldata.size()<4||alldata.at(0)!=IC_CARD_DEVICE_ADDRESS)
    {
        emit signaldebugserialport(tr("非法数据"));
        return;
    }

    alldata.resize(alldata.size()-2); //去除末尾CRC
    connecttype cmdType = (connecttype)alldata.at(1);

    QByteArray pureData;

    if(alldata.size() > 2)
    {   //提取纯数据，去除地址和功能码
        pureData = QByteArray(alldata.data()+2, alldata.size()-2);
    }

    if(cmdType == HANDSHAKE_CONNECT)
    {
        emit signaldebugserialport(tr("握手成功"));
        if(serialporttimer->isActive())
            serialporttimer->stop();
        handshaketimer->stop();
        emit signalconnectresult(true);

        QTimer::singleShot(50,this,[this]()       //连接成功后下位机自动上传rd0
        {
            QByteArray senddata;
            senddata[0]=IC_CARD_DEVICE_ADDRESS;
            senddata[1]=READ_CONNECT_0;
            senddatatoserialport(senddata);
        });
    }
    else if(cmdType == READ_CONNECT_0)
    {
        if(pureData.size()==sizeof (CARDDATA::RD0_CARD_STYLE))
        {
            CARDDATA::RD0_CARD_STYLE rd0;
            memcpy(&rd0,pureData.data(),pureData.size());
            if(rd0.UID!=0 && rd0.card_style==CARDDATA::CPU_CARD)
            {
                emit signaldebugserialport(QString("卡类型：%1,UID：%2").arg(rd0.card_style).arg(rd0.UID));
                emit signalICbasicinfo(rd0.card_style,QString("%1").arg(rd0.UID));
                QTimer::singleShot(50,this,[this](){readuserbasicinfo();});
            }
            else if(!rd0.UID)
            {
                emit signaldebugserialport(tr("无卡/卡被移除/信号弱"));
                emit signalICbasicinfo(rd0.card_style,QString("%1").arg(rd0.UID));
            }
        }
    }
    else if(cmdType == READ_CONNECT_1)
    {
        if(pureData.size()>1)
        {
            qdebug<<pureData.toHex();
            pureData=QByteArray(pureData.data()+1,pureData.size()-1);   //去掉数据长度位
            qdebug<<pureData.toHex();

            if(pureData.size()==sizeof (CARDDATA::USER_BASIC_INFO))
            {
                CARDDATA::CardUserInfo userinfo;
                CARDDATA::USER_BASIC_INFO basicinfo;
                memcpy(&basicinfo,pureData.data(),pureData.size());

                userinfo.type=(CARDDATA::card_type)basicinfo.card_type;
                userinfo.name=QString::fromUtf8(basicinfo.name);
                userinfo.gender=(CARDDATA::gender_type)basicinfo.gender;
                userinfo.birth=QDate::fromJulianDay(basicinfo.birthday);
                userinfo.height=basicinfo.stature;
                userinfo.beforeWeight=basicinfo.uf_before_weight/10.0f;
                userinfo.afterWeight=basicinfo.uf_after_weight/10.0f;
                emit signaluserbasicinfo(userinfo.type,userinfo.name,userinfo.gender,userinfo.birth.toString("yyyy-MM-dd"),userinfo.height,userinfo.beforeWeight,userinfo.afterWeight);
            }
            else if(pureData.size()==sizeof (CARDDATA::CREDIT_CARD_RECORDS_ADDR)+2)
            {
                CARDDATA::CREDIT_CARD_RECORDS_ADDR card_record;
                memcpy(&card_record,pureData.data(),pureData.size());
                qdebug<<card_record.currentrecords<<card_record.recordscount;
            }
        }
        else
        {
            emit signaldebugserialport(tr("rd1读取失败"));
        }
    }
    else if(cmdType == WRITE_CONNECT_0||cmdType == WRITE_CONNECT_1||cmdType == FORMAT_CONNECT)
    {

    }
}

void serialport::readuserbasicinfo()
{
#if DEBUG_MODEL
    QString debugstr=tr("void serialport::readuserbasicinfo():获取卡基本信息");
    emit signaldebugserialport(debugstr);
    qdebug<<debugstr;
#endif

    QByteArray senddata;
    senddata[0]=IC_CARD_DEVICE_ADDRESS;
    senddata[1]=READ_CONNECT_1;
    senddata[2]=USER_BASIC_INFO_ADDRESS;
    senddata[3]=USER_BASIC_INFO_ADDRESS>>8;
    senddata[4]=sizeof (CARDDATA::USER_BASIC_INFO);
    senddatatoserialport(senddata);
    serialportfailnum=0;
}

void serialport::readcardrecords()
{
#if DEBUG_MODEL
    QString debugstr=tr("void serialport::readcardrecords():获取刷卡记录");
    emit signaldebugserialport(debugstr);
    qdebug<<debugstr;
#endif

    QByteArray senddata;
    senddata[0]=IC_CARD_DEVICE_ADDRESS;
    senddata[1]=READ_CONNECT_1;
    senddata[2]=CREDIT_CARD_RECORDS_START_ADDRESS&0xff;
    senddata[3]=CREDIT_CARD_RECORDS_START_ADDRESS>>8;
    senddata[4]=sizeof (CARDDATA::CREDIT_CARD_RECORDS_ADDR)+2;
    senddatatoserialport(senddata);
    serialportfailnum=0;
}

void serialport::reoperate()
{
#if DEBUG_MODEL
    QString debugstr=tr("void serialport::reoperate():失败重试");
    emit signaldebugserialport(debugstr);
    qdebug<<debugstr;
#endif

    if(serialportfailnum<MAX_FAIL_NUM)
    {
        serialportfailnum++;
        senddatatoserialport(serialportsenddata);
    }
    else
        emit signaldebugserialport(tr("IC卡操作失败"));
}

