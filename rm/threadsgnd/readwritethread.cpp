#include "readwritethread.h"
#include <QDebug>

const int buffsize=8;
int buff1[buffsize];
int buff2[buffsize];

int valuewritebuff=1;
int createbuff=0;

int data=0;

QSemaphore readbuff(2);
QSemaphore writebuff;

readthread::readthread()
{
}
void readthread::run()
{
    if(readbuff.available()>0)
        readbuff.acquire(readbuff.available());
    while(!over)
    {
        readbuff.acquire(1);
        int temp[buffsize];
        if(valuewritebuff==1)
            for(int i=0;i<buffsize;i++)
                temp[i]=buff2[i];
        else
            for(int i=0;i<buffsize;i++)
                temp[i]=buff1[i];
        writebuff.release(1);
        emit readbuffsignal(temp,buffsize,createbuff);
    }
}

void readthread::threadstop()
{
    over=true;
}
writethread::writethread()
{
}
void writethread::run()
{
    if(writebuff.available()<2)
        writebuff.release(2-writebuff.available());
    while(!over)
    {
        writebuff.acquire(1);
        for(int i=0;i<buffsize;i++)
        {
            if(valuewritebuff==1)
                buff1[i]=data;
            else
                buff2[i]=data;
            data++;
            msleep(1);
        }
        createbuff++;
        if(valuewritebuff==1)
            valuewritebuff=2;
        else
            valuewritebuff=1;
        readbuff.release(1);
    }
}

void writethread::threadstop()
{
    over=true;
}
