#include "testthread.h"
#include <QDebug>
#include <QThread>

    QMutex m_mutex;
    QThread *qt;
    int k=0;

testthread::testthread(QObject *parent) : QThread(parent)
{
//    this->moveToThread(this);
//    this->start();
}

testthread::~testthread()
{
    this->quit();
    this->wait();
}

void testthread::run()
{
    for(int i=0;i<100;)
    {
        i=j;
//        m_mutex.lock();
        qDebug()<<"threadid"<<QThread::currentThread()<<"    "<<i<<k;
//        m_mutex.unlock();
        j++;
        k+=j;
        emit pubdata(j);
    }
    this->quit();
}

void testthread::fun(int j)
{
    this->j=j+1;
}
