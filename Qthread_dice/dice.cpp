#include "dice.h"
#include "windows.h"
#include "windef.h"

#include <QTime>
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QMutexLocker>
#include <QReadWriteLock>
#include <QWaitCondition>

dice::dice(QThread *parent)
{
    Q_UNUSED(parent);
}

void dice::dicestart()
{
    dice_pause=false;
}

void dice::dicestop()
{
    dice_stop=true;
}

//void dice::init()
//{
//    dice_stop=false;
//    dice_pause=true;
//    dice_count=0;
//    dice_view=0;
//    threadpk=pk::no;
//}

void dice::dicepause()
{
    dice_pause=true;
}

void dice::run()
{
    dice_pause=true;
    dice_stop=false;
    dice_count=0;
    qsrand(QTime::currentTime().msec());//初始化随机函数种子，qsrand是线程安全的
    while(!dice_stop)
    {
        if(!dice_pause)
        {
//            QMutexLocker mutel(&mute);
//            mute.lock();
            int rand=qrand();
            dice_view=(rand%6)+1;
            dice_count++;
            QString str=QString("%1").arg(quintptr(QThread::currentThreadId()));
//            mute.unlock();
            if(dice_count==100)
                threadpk=yes;
            qDebug()<<threadpk;
            emit newdicecreate(dice_count,dice_view,str);

        }
//        QThread::msleep(200);
    }
    quit();
//    QReadWriteLock rw;  //读写锁
//    rw.lockForRead();
//    rw.lockForWrite();
//    QWaitCondition wc;  //线程同步
//    wc.wait(&mute);
//    wc.wakeAll();
//    wc.wakeOne();


}
