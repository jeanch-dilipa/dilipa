#include "gobang.h"

#include <QDebug>
#include <QPoint>

#define qdebug  qDebug()<<__FILE__<<__LINE__

gobang::gobang(QObject *parent) : QObject(parent)
{
    connect(this,&gobang::signal_initchess,this,&gobang::initchess);
    connect(this,&gobang::signal_recordchess,this,&gobang::recordchess);
    connect(this,&gobang::signal_detectionchess,this,&gobang::detectionchess);
    connect(this,&gobang::signal_takeback,this,&gobang::takeback);
    connect(this,&gobang::signal_clearchess,this,&gobang::clearchess);
}

void gobang::initchess(int linenum)
{
    this->linenum=linenum;
    chess=new int *[linenum];
    for(int i=0;i<linenum;i++)
    {
        chess[i]=new int [linenum];
        for(int j=0;j<linenum;j++)
            chess[i][j]=0;
    }
}

void gobang::recordchess(int i, int j, int num)
{
    chess[i][j]=num;
    if(QPoint(0,0)!=point1)
        point2=point1;
    point1=QPoint(i,j);
}

void gobang::detectionchess()
{
    for(int i=0;i<linenum;i++)
    {
        for(int j=0;j<linenum;j++)
        {
            int count=0;
            if(0!=chess[i][j])//red1
            {
                for(int k=0;k<4;k++)
                {
                    if(0==k)
                    {
                        count=checkchessup(1,i,j,chess[i][j]);
                        count=checkchessdown(count,i,j,chess[i][j]);
                    }
                    if(1==k)
                    {
                        count=checkchessleft(1,i,j,chess[i][j]);
                        count=checkchessright(count,i,j,chess[i][j]);
                    }
                    if(2==k)
                    {
                        count=checkchessleftup(1,i,j,chess[i][j]);
                        count=checkchessrightdown(count,i,j,chess[i][j]);
                    }
                    if(3==k)
                    {
                        count=checkchessleftdown(1,i,j,chess[i][j]);
                        count=checkchessrightup(count,i,j,chess[i][j]);
                    }
                    if(5==count)
                    {
                        emit signal_voctory(chess[i][j],"vectory!");
                        break;
                    }
                }
            }
        }
    }
}

void gobang::takeback()
{
    if(QPoint(0,0)!=point1)
    {
        chess[point1.rx()][point1.ry()]=0;
        emit signal_repaint(point1.rx(),point1.ry());
        point1=QPoint(0,0);
    }
    else
        if(QPoint(0,0)!=point2)
        {
            chess[point2.rx()][point2.ry()]=0;
            emit signal_repaint(point2.rx(),point2.ry());
            point2=QPoint(0,0);
        }
}

int gobang::checkchessup(int count, int i, int j, int num)
{
    if(j<linenum-1&&i<linenum-1&&i>0&&j>0)
    {
        if(num==chess[i-1][j])
        {
            count+=1;
            count=checkchessup(count,i-1,j,num);
        }
    }
    return count;
}

int gobang::checkchessleft(int count, int i, int j, int num)
{
    if(j<linenum-1&&i<linenum-1&&i>0&&j>0)
    {
        if(num==chess[i][j-1])
        {
            count+=1;
            count=checkchessleft(count,i,j-1,num);
        }
    }
    return count;
}

int gobang::checkchessleftup(int count, int i, int j, int num)
{
    if(j<linenum-1&&i<linenum-1&&i>0&&j>0)
    {
        if(num==chess[i-1][j-1])
        {
            count+=1;
            count=checkchessleftup(count,i-1,j-1,num);
        }
    }
    return count;
}

int gobang::checkchessrightup(int count, int i, int j, int num)
{
    if(j<linenum-1&&i<linenum-1&&i>0&&j>0)
    {
        if(num==chess[i-1][j+1])
        {
            count+=1;
            count=checkchessrightup(count,i-1,j+1,num);
        }
    }
    return count;
}

void gobang::clearchess()
{
    for(int i=1;i<linenum;i++)
    {
        for(int j=1;j<linenum;j++)
        {
                chess[i][j]=0;
        }
    }
}

int gobang::checkchessdown(int count, int i, int j, int num)
{
    if(j<linenum-1&&i<linenum-1&&i>0&&j>0)
    {
        if(num==chess[i+1][j])
        {
            count+=1;
            count=checkchessdown(count,i+1,j,num);
        }
    }
    return count;
}

int gobang::checkchessright(int count, int i, int j, int num)
{
    if(j<linenum-1&&i<linenum-1&&i>0&&j>0)
    {
        if(num==chess[i][j+1])
        {
            count+=1;
            count=checkchessright(count,i,j+1,num);
        }
    }
    return count;
}

int gobang::checkchessrightdown(int count, int i, int j, int num)
{
    if(j<linenum-1&&i<linenum-1&&i>0&&j>0)
    {
        if(num==chess[i+1][j+1])
        {
            count+=1;
            count=checkchessrightdown(count,i+1,j+1,num);
        }
    }
    return count;
}

int gobang::checkchessleftdown(int count, int i, int j, int num)
{
    if(j<linenum-1&&i<linenum-1&&i>0&&j>0)
    {
        if(num==chess[i+1][j-1])
        {
            count+=1;
            count=checkchessleftdown(count,i+1,j-1,num);
        }
    }
    return count;
}
