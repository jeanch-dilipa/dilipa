#include "repeater.h"

repeater::repeater(QObject *parent) : QObject(parent)
{
#if DEBUG_MODEL
    QString debugstr=tr("repeater::repeater(QObject *parent) : QObject(parent):类构造函数");
    emit signaldebugserialport(debugstr);
    qdebug<<debugstr;
#endif

    serialport *serialport=CardSerialport;
    connect(this,&repeater::signalstartconnect,serialport,&serialport::signalgetserialport);
    connect(this,&repeater::signalcardrecordsrequst,serialport,&serialport::signalcardrecordsrequst);
    connect(this,&repeater::signaltherapeuticschedule,serialport,&serialport::signaltherapeuticschedule);
    connect(this,&repeater::signalwriteuserbasicinfo,serialport,&serialport::signalwriteuserbasicinfo);

    connect(serialport,&serialport::signalconnectresult,this,&repeater::signalconnectresult);
    connect(serialport,&serialport::signaldebugserialport,this,&repeater::signaldebugserialport);
    connect(serialport,&serialport::signalICbasicinfo,this,&repeater::signalICbasicinfo);
    connect(serialport,&serialport::signaluserbasicinfo,this,&repeater::signaluserbasicinfo);
    connect(serialport,&serialport::signalcardcordsinfo,this,&repeater::signalcardcordsinfo);
    connect(serialport,&serialport::signaltherepeuticscheduleinfo1,this,&repeater::signaltherepeuticscheduleinfo1);
    connect(serialport,&serialport::signaltherepeuticscheduleinfo2,this,&repeater::signaltherepeuticscheduleinfo2);

    QTimer::singleShot(10,this,[this](){emit signalconnectbtnclick(true);});
}

repeater::~repeater()
{
#if DEBUG_MODEL
    QString debugstr=tr("repeater::~repeater():析构函数");
    emit signaldebugserialport(debugstr);
    qdebug<<debugstr;
#endif

    serialport::deinitserialport();
}
