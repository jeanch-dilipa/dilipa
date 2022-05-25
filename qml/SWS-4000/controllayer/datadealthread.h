#ifndef DATADEALTHREAD_H
#define DATADEALTHREAD_H

#include <QThread>
#include <QMutex>
#include <QMutexLocker>

#define INITDataDealThread (dataDealThread::initDataDealThread())

class dataDealThread : public QThread
{
public:
    dataDealThread();
    ~dataDealThread();

    static dataDealThread *initDataDealThread();
    static void deDataDealThread();

protected:
    void run();

    void bloodValueChange(quint8 bloodValue);

private:
    void signal_bloodValueChange(quint8);                                                                                                         //血泵值改变信号

private:
    static dataDealThread                                   *s_dataDealThread;
    static QMutex                                            s_mutexLocker;
};

#endif // DATADEALTHREAD_H
