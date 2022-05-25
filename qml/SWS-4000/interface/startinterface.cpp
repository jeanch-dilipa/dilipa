#include "startinterface.h"

startInterface *startInterface::s_startInterface=nullptr;
QMutex startInterface::s_mutexLocker;

/*
功能描述：startInterface类构造函数
输    入：/
输    出：/
*/
startInterface::startInterface(QObject *parent) : QObject(parent)
{
#if DEBUG_MODEL || DEBUG_MODEL_STARTINTERFACE
    QString debugstr="startInterface::startInterface(QObject *parent) : QObject(parent):构造函数";
    qdebug<<debugstr;
#endif

    QTimer::singleShot(1000,this,SIGNAL(signal_createStartInterface()));
}
/*
功能描述：startInterface类析构函数
输    入：/
输    出：/
*/
startInterface::~startInterface()
{
#if DEBUG_MODEL || DEBUG_MODEL_STARTINTERFACE
    QString debugstr="startInterface::~startInterface():析构函数";
    qdebug<<debugstr;
#endif

//    deStartInterface();
}
/*
功能描述：创建自身
输    入：/
输    出：/
*/
startInterface *startInterface::initStartInterface()
{
#if DEBUG_MODEL || DEBUG_MODEL_STARTINTERFACE
    QString debugstr="startInterface *startInterface::initStartInterface():创建自身";
    qdebug<<debugstr;
#endif

    if(!s_startInterface)
    {
        QMutexLocker locker(&s_mutexLocker);
        if(!s_startInterface)
        {
            s_startInterface = new startInterface();
        }
    }
    return s_startInterface;
}
/*
功能描述：销毁自身
输    入：/
输    出：/
*/
void startInterface::deStartInterface()
{
#if DEBUG_MODEL || DEBUG_MODEL_STARTINTERFACE
    QString debugstr="void startInterface::deStartInterface()：销毁自身";
    qdebug<<debugstr;
#endif

    if(s_startInterface)
    {
        QMutexLocker locker(&s_mutexLocker);
        if(s_startInterface)
        {
            delete s_startInterface;
            s_startInterface = nullptr;
        }
    }
}
