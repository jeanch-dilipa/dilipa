#include "datadealthread.h"

dataDealThread *dataDealThread::s_dataDealThread = nullptr;
QMutex dataDealThread::s_mutexLocker;

/*
功能描述：构造函数
输    入：/
输    出：/
*/
dataDealThread::dataDealThread()
{
#if DEBUG_MODEL || DEBUG_MODEL_DATADEALTHREAD
    QString debugstr="dataDealThread::dataDealThread():构造函数";
    qdebug<<debugstr;
#endif
    this->start();
}
/*
功能描述：析构函数
输    入：/
输    出：/
*/
dataDealThread::~dataDealThread()
{
#if DEBUG_MODEL || DEBUG_MODEL_DATADEALTHREAD
    QString debugstr="dataDealThread::~dataDealThread():析构函数";
    qdebug<<debugstr;
#endif

}
/*
功能描述：创建自身
输    入：/
输    出：/
*/
dataDealThread *dataDealThread::initDataDealThread()
{
#if DEBUG_MODEL || DEBUG_MODEL_DATADEALTHREAD
    QString debugstr="dataDealThread *dataDealThread::initDataDealThread():创建自身";
    qdebug<<debugstr;
#endif

    if(!s_dataDealThread)
    {
        QMutexLocker locker(&s_mutexLocker);
        {
            if(!s_dataDealThread)
            {
                s_dataDealThread = new dataDealThread();
            }
        }
    }
    return s_dataDealThread;
}
/*
功能描述：销毁自身
输    入：/
输    出：/
*/
void dataDealThread::deDataDealThread()
{
#if DEBUG_MODEL || DEBUG_MODEL_DATADEALTHREAD
    QString debugstr="void dataDealThread::deDataDealThread():销毁自身";
    qdebug<<debugstr;
#endif

    if(s_dataDealThread)
    {
        QMutexLocker locker(&s_mutexLocker);
        if(s_dataDealThread)
        {
            s_dataDealThread->exit(0);
            s_dataDealThread->wait();
            delete s_dataDealThread;
            s_dataDealThread = nullptr;
        }
    }
}
/*
功能描述：线程run
输    入：/
输    出：/
*/
void dataDealThread::run()
{
#if DEBUG_MODEL || DEBUG_MODEL_DATADEALTHREAD
    QString debugstr="void dataDealThread::run():线程";
    qdebug<<debugstr;
#endif


    this->exec();
}
