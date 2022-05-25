#include "paravane.h"

#include <QRandomGenerator>
#include <QList>

Paravane::Paravane()
{
    connect(this,&Paravane::signal_createthunder,this,&Paravane::slot_createthunder);
    connect(this,&Paravane::signal_judgethunder,this,&Paravane::slot_judgethunder);
}

void Paravane::slot_createthunder(int thundercol,int thundernum)
{
    thundercolumn=thundercol;
    while(thunderlist.length()<thundernum)
    {
        int thunder=QRandomGenerator::global()->bounded(thundernum*thundernum);
        if(!thunderlist.contains(thunder))
            thunderlist<<thunder;
    }
    qdebug<<thunderlist;
    emit signal_setthunder(thunderlist);
}

void Paravane::slot_judgethunder(int thunderindex)
{
    if(thunderlist.contains(thunderindex))
    {
        emit signal_showthunder(10);
    }
    else
    {
        int thundercount=0;
        int num=0;
        if((thunderindex+1)%thundercolumn==0)
        {
            num+=1;
            if(thunderindex-10>=0&&thunderlist.contains(thunderindex-10))thundercount++;
            if(thunderindex-1>=0&&thunderlist.contains(thunderindex-1))thundercount++;
            if(thunderindex+8>=0&&thunderlist.contains(thunderindex+8))thundercount++;
            if(thunderindex-9>=0&&thunderlist.contains(thunderindex-9))thundercount++;
            if(thunderindex+9>=0&&thunderlist.contains(thunderindex+9))thundercount++;
        }
        else if((thunderindex+1)%thundercolumn==1)
        {
            num+=2;
            if(thunderindex-8>=0&&thunderlist.contains(thunderindex-8))thundercount++;
            if(thunderindex+1>=0&&thunderlist.contains(thunderindex+1))thundercount++;
            if(thunderindex+10>=0&&thunderlist.contains(thunderindex+10))thundercount++;
            if(thunderindex-9>=0&&thunderlist.contains(thunderindex-9))thundercount++;
            if(thunderindex+9>=0&&thunderlist.contains(thunderindex+9))thundercount++;
        }
        else
        {
            if(thunderindex-10>=0&&thunderlist.contains(thunderindex-10))thundercount++;
            if(thunderindex-1>=0&&thunderlist.contains(thunderindex-1))thundercount++;
            if(thunderindex+8>=0&&thunderlist.contains(thunderindex+8))thundercount++;
            if(thunderindex-8>=0&&thunderlist.contains(thunderindex-8))thundercount++;
            if(thunderindex+1>=0&&thunderlist.contains(thunderindex+1))thundercount++;
            if(thunderindex+10>=0&&thunderlist.contains(thunderindex+10))thundercount++;
            if(thunderindex-9>=0&&thunderlist.contains(thunderindex-9))thundercount++;
            if(thunderindex+9>=0&&thunderlist.contains(thunderindex+9))thundercount++;
            num+=3;
        }
        emit signal_showthunder(thundercount);

    }
}
