#include "tetris.h"

#include <QRandomGenerator>

Tetris::Tetris(QObject *parent) : QObject(parent)
{
    connect(this,&Tetris::signal_initblockspace,this,&Tetris::initblockspace);
    connect(this,&Tetris::signal_blockdrop,this,&Tetris::blockdrop);
    connect(this,&Tetris::signal_appendblockspace,this,&Tetris::appendblocktospace);
    connect(this,&Tetris::signal_unabledrop,this,&Tetris::whethergameover);
    connect(this,&Tetris::signal_change_block,this,&Tetris::change_block);
    connect(this,&Tetris::signal_move_left_right_down,this,&Tetris::move_left_right_down);
}

Tetris::~Tetris()
{
    delete m_blockspace;
}

void Tetris::initblockspace(int column, int row)
{
    currentblock=nextblock=QRandomGenerator::global()->bounded(5);
    emit signal_nextblock(nextblock);

    m_columnnum=column;
    m_rownum=row;
    m_blockspace=new int *[m_rownum];
    for(int i=0;i<m_rownum;i++)
        m_blockspace[i]=new int[m_columnnum];
    for(int i=0;i<m_rownum;i++)
        for(int j=0;j<m_columnnum;j++)
            m_blockspace[i][j]=0;
    sendblockspace();
    appendblocktospace(nextblock);
}

void Tetris::appendblocktospace(int blocknum)
{
    currentblock=blocknum;
    nextblock=QRandomGenerator::global()->bounded(5);
    emit signal_nextblock(nextblock);

    int count=0;
    switch (currentblock)
    {
        case 0:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    m_blockspace[i][(m_columnnum)/2+j]=specialblock1[i][j];
                    if(1==specialblock1[i][j])
                    {
                        count+=1;
                        switch (count)
                        {
                            case 1:
                                point1=QPoint(i,(m_columnnum)/2+j);break;
                            case 2:
                                point2=QPoint(i,(m_columnnum)/2+j);break;
                            case 3:
                                point3=QPoint(i,(m_columnnum)/2+j);break;
                            case 4:
                                point4=QPoint(i,(m_columnnum)/2+j);break;
                        }
                    }
                }
            block1status=0;
            break;
        case 1:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    m_blockspace[i][(m_columnnum)/2+j]=specialblock2[i][j];
                    if(1==specialblock2[i][j])
                    {
                        count+=1;
                        switch (count)
                        {
                            case 1:
                                point1=QPoint(i,(m_columnnum)/2+j);break;
                            case 2:
                                point2=QPoint(i,(m_columnnum)/2+j);break;
                            case 3:
                                point3=QPoint(i,(m_columnnum)/2+j);break;
                            case 4:
                                point4=QPoint(i,(m_columnnum)/2+j);break;
                        }
                    }
                }
            block2status=0;
            break;
        case 2:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    m_blockspace[i][(m_columnnum)/2+j]=specialblock3[i][j];
                    if(1==specialblock3[i][j])
                    {
                        count+=1;
                        switch (count)
                        {
                            case 1:
                                point1=QPoint(i,(m_columnnum)/2+j);break;
                            case 2:
                                point2=QPoint(i,(m_columnnum)/2+j);break;
                            case 3:
                                point3=QPoint(i,(m_columnnum)/2+j);break;
                            case 4:
                                point4=QPoint(i,(m_columnnum)/2+j);break;
                        }
                    }
                }
            block3status=0;
            break;
        case 3:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    m_blockspace[i][(m_columnnum)/2+j]=specialblock4[i][j];
                    if(1==specialblock4[i][j])
                    {
                        count+=1;
                        switch (count)
                        {
                            case 1:
                                point1=QPoint(i,(m_columnnum)/2+j);break;
                            case 2:
                                point2=QPoint(i,(m_columnnum)/2+j);break;
                            case 3:
                                point3=QPoint(i,(m_columnnum)/2+j);break;
                            case 4:
                                point4=QPoint(i,(m_columnnum)/2+j);break;
                        }
                    }
                }
            block4status=0;
            break;
        case 4:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    m_blockspace[i][(m_columnnum)/2+j]=specialblock5[i][j];
                    if(1==specialblock5[i][j])
                    {
                        count+=1;
                        switch (count)
                        {
                            case 1:
                                point1=QPoint(i,(m_columnnum)/2+j);break;
                            case 2:
                                point2=QPoint(i,(m_columnnum)/2+j);break;
                            case 3:
                                point3=QPoint(i,(m_columnnum)/2+j);break;
                            case 4:
                                point4=QPoint(i,(m_columnnum)/2+j);break;
                        }
                    }
                }
            block5status=0;
            break;
    }
    sendblockspace();
}

void Tetris::blockdrop()
{
    if(whetherdrop())
    {
        fillblock(false);
        point1.rx()+=1;
        point2.rx()+=1;
        point3.rx()+=1;
        point4.rx()+=1;
        fillblock(true);
        sendblockspace();
    }
    else
    {
        Integral_eliminate();
        emit signal_unabledrop();
    }
}

void Tetris::sendblockspace()
{
    for(int i=0;i<m_rownum;i++)
        for(int j=0;j<m_columnnum;j++)
        {
            if(1==m_blockspace[i][j])
                emit signal_newblockspace(i,j,1);
            else
                emit signal_newblockspace(i,j,0);
        }
    emit signal_spacedatasendend();
}

bool Tetris::whetherdrop()
{
    bool isdrop=true;
    int maxrow=point1.rx()>point2.rx()?point1.rx():point2.rx();
    maxrow=maxrow>point3.rx()?maxrow:point3.rx();
    maxrow=maxrow>point4.rx()?maxrow:point4.rx();
    QList<QPoint> pointlist;
    pointlist<<point1<<point2<<point3<<point4;
    if(maxrow<m_rownum-1)
    {
        if(1==m_blockspace[point1.rx()+1][point1.ry()]&&!pointlist.contains(QPoint(point1.rx()+1,point1.ry())))
            isdrop=false;
        if(1==m_blockspace[point2.rx()+1][point2.ry()]&&!pointlist.contains(QPoint(point2.rx()+1,point2.ry())))
            isdrop=false;
        if(1==m_blockspace[point3.rx()+1][point3.ry()]&&!pointlist.contains(QPoint(point3.rx()+1,point3.ry())))
            isdrop=false;
        if(1==m_blockspace[point4.rx()+1][point4.ry()]&&!pointlist.contains(QPoint(point4.rx()+1,point4.ry())))
            isdrop=false;
    }
    else
        isdrop=false;
    return isdrop;
}

void Tetris::whethergameover()
{
    int maxrow=point1.rx()>point2.rx()?point1.rx():point2.rx();
    maxrow=maxrow>point3.rx()?maxrow:point3.rx();
    maxrow=maxrow>point4.rx()?maxrow:point4.rx();
    if(4>=maxrow)
    {
        emit signal_gameover();
    }
    else
        emit signal_appendblockspace(nextblock);
}

void Tetris::move_left_right_down(QString movestr)
{
    if("left"==movestr)
        if(whetherleft())
        {
            fillblock(false);
            point1.ry()-=1;
            point2.ry()-=1;
            point3.ry()-=1;
            point4.ry()-=1;
            fillblock(true);
            sendblockspace();
        }
    if("right"==movestr)
        if(whetherright())
        {
            fillblock(false);
            point1.ry()+=1;
            point2.ry()+=1;
            point3.ry()+=1;
            point4.ry()+=1;
            fillblock(true);
            sendblockspace();
        }
    if("down"==movestr)
        if(whetherdrop())
        {
            fillblock(false);
            point1.rx()+=1;
            point2.rx()+=1;
            point3.rx()+=1;
            point4.rx()+=1;
            fillblock(true);
            sendblockspace();
        }
}

void Tetris::change_block()
{

    switch (currentblock)
    {
        case 0:
            if(0==block1status)
            {
                if(0==m_blockspace[point4.rx()-2][point4.ry()-1]&&0==m_blockspace[point2.rx()][point2.ry()+1]&&0==m_blockspace[point1.rx()+1][point1.ry()+2])
                {
                    fillblock(false);
                    point1.rx()+=1;point1.ry()+=2;
                    point2.ry()+=1;
                    point3.rx()-=1;
                    point4.rx()-=2;point4.ry()-=1;
                    fillblock(true);
                }
            }
            if(1==block1status)
            {
                if(0==m_blockspace[point4.rx()+2][point4.ry()+1]&&0==m_blockspace[point3.rx()+1][point3.ry()]&&0==m_blockspace[point1.rx()-1][point1.ry()-2])
                {
                    fillblock(false);
                    point1.rx()-=1;point1.ry()-=2;
                    point2.ry()-=1;
                    point3.rx()+=1;
                    point4.rx()+=2;point4.ry()+=1;
                    fillblock(true);
                }
            }
            block1status+=1;
            if(block1status>1)block1status=0;
            sendblockspace();
            break;
        case 1:
            break;
        case 2:
            if(0==block3status)
            {
                if(0==m_blockspace[point4.rx()+1][point4.ry()-1]&&0==m_blockspace[point1.rx()+2][point1.ry()+2])
                {
                    fillblock(false);
                    point1.rx()+=2;point1.ry()+=2;
                    point2.rx()+=1;point2.ry()+=1;
                    point4.rx()+=1;point4.ry()-=1;
                    fillblock(true);
                }
            }
            if(1==block3status)
            {
                if(0==m_blockspace[point4.rx()-1][point4.ry()-1]&&0==m_blockspace[point1.rx()+2][point1.ry()-2])
                {
                    fillblock(false);
                    point1.rx()+=2;point1.ry()-=2;
                    point2.rx()+=1;point2.ry()-=1;
                    point4.rx()-=1;point4.ry()-=1;
                    fillblock(true);
                }
            }
            if(2==block3status)
            {
                if(0==m_blockspace[point4.rx()-1][point4.ry()+1]&&0==m_blockspace[point1.rx()-2][point1.ry()-2])
                {
                    fillblock(false);
                    point1.rx()-=2;point1.ry()-=2;
                    point2.rx()-=1;point2.ry()-=1;
                    point4.rx()-=1;point4.ry()+=1;
                    fillblock(true);
                }
            }
            if(3==block3status)
            {
                if(0==m_blockspace[point4.rx()+1][point4.ry()+1]&&0==m_blockspace[point1.rx()-2][point1.ry()+2])
                {
                    fillblock(false);
                    point1.rx()-=2;point1.ry()+=2;
                    point2.rx()-=1;point2.ry()+=1;
                    point4.rx()+=1;point4.ry()+=1;
                    fillblock(true);
                }
            }
            block3status+=1;
            if(block3status>3)block3status=0;
            sendblockspace();
            break;
        case 3:
            if(0==block4status)
            {
                if(0==m_blockspace[point2.rx()+1][point2.ry()+1]&&0==m_blockspace[point1.rx()+2][point1.ry()+2])
                {
                    fillblock(false);
                    point1.rx()+=2;point1.ry()+=2;
                    point2.rx()+=1;point2.ry()+=1;
                    point3.rx()-=1;point3.ry()+=1;
                    fillblock(true);
                }
            }
            if(1==block4status)
            {
                if(0==m_blockspace[point2.rx()+1][point2.ry()-1]&&0==m_blockspace[point1.rx()+2][point1.ry()-2])
                {
                    fillblock(false);
                    point1.rx()+=2;point1.ry()-=2;
                    point2.rx()+=1;point2.ry()-=1;
                    point3.rx()+=1;point3.ry()+=1;
                    fillblock(true);
                }
            }
            if(2==block4status)
            {
                if(0==m_blockspace[point2.rx()-1][point2.ry()-1]&&0==m_blockspace[point1.rx()-2][point1.ry()-2])
                {
                    fillblock(false);
                    point1.rx()-=2;point1.ry()-=2;
                    point2.rx()-=1;point2.ry()-=1;
                    point3.rx()+=1;point3.ry()-=1;
                    fillblock(true);
                }
            }
            if(3==block4status)
            {
                if(0==m_blockspace[point2.rx()-1][point2.ry()+1]&&0==m_blockspace[point1.rx()-2][point1.ry()+2])
                {
                    fillblock(false);
                    point1.rx()-=2;point1.ry()+=2;
                    point2.rx()-=1;point2.ry()+=1;
                    point3.rx()-=1;point3.ry()-=1;
                    fillblock(true);
                }
            }
            block4status+=1;
            if(block4status>3)block4status=0;
            sendblockspace();
            break;
        case 4:
            if(0==block5status)
            {
                if(0==m_blockspace[point4.rx()+1][point4.ry()-1])
                {
                    fillblock(false);
                    point1.rx()+=1;point1.ry()+=1;
                    point2.rx()-=1;point2.ry()+=1;
                    point4.rx()+=1;point4.ry()-=1;
                    fillblock(true);
                }
            }
            if(1==block5status)
            {
                if(0==m_blockspace[point4.rx()-1][point4.ry()-1])
                {
                    fillblock(false);
                    point1.rx()+=1;point1.ry()-=1;
                    point2.rx()+=1;point2.ry()+=1;
                    point4.rx()-=1;point4.ry()-=1;
                    fillblock(true);
                }
            }
            if(2==block5status)
            {
                if(0==m_blockspace[point4.rx()-1][point4.ry()+1])
                {
                    fillblock(false);
                    point1.rx()-=1;point1.ry()-=1;
                    point2.rx()+=1;point2.ry()-=1;
                    point4.rx()-=1;point4.ry()+=1;
                    fillblock(true);
                }
            }
            if(3==block5status)
            {
                if(0==m_blockspace[point4.rx()+1][point4.ry()+1])
                {
                    fillblock(false);
                    point1.rx()-=1;point1.ry()+=1;
                    point2.rx()-=1;point2.ry()-=1;
                    point4.rx()+=1;point4.ry()+=1;
                    fillblock(true);
                }
            }
            block5status+=1;
            if(block5status>3)block5status=0;
            sendblockspace();
            break;
    }
}

bool Tetris::whetherleft()
{
    bool isleft=true;
    int mincolumn=point1.ry()<point2.ry()?point1.ry():point2.ry();
    mincolumn=mincolumn<point3.ry()?mincolumn:point3.ry();
    mincolumn=mincolumn<point4.ry()?mincolumn:point4.ry();
    QList<QPoint> pointlist;
    pointlist<<point1<<point2<<point3<<point4;
    if(mincolumn>0)
    {
        if(1==m_blockspace[point1.rx()][point1.ry()-1]&&!pointlist.contains(QPoint(point1.rx(),point1.ry()-1)))
            isleft=false;
        if(1==m_blockspace[point2.rx()][point2.ry()-1]&&!pointlist.contains(QPoint(point2.rx(),point2.ry()-1)))
            isleft=false;
        if(1==m_blockspace[point3.rx()][point3.ry()-1]&&!pointlist.contains(QPoint(point3.rx(),point3.ry()-1)))
            isleft=false;
        if(1==m_blockspace[point4.rx()][point4.ry()-1]&&!pointlist.contains(QPoint(point4.rx(),point4.ry()-1)))
            isleft=false;
    }
    else
        isleft=false;
    return isleft;
}

bool Tetris::whetherright()
{
    bool isright=true;
    int maxcolumn=point1.ry()>point2.ry()?point1.ry():point2.ry();
    maxcolumn=maxcolumn>point3.ry()?maxcolumn:point3.ry();
    maxcolumn=maxcolumn>point4.ry()?maxcolumn:point4.ry();
    QList<QPoint> pointlist;
    pointlist<<point1<<point2<<point3<<point4;
    if(maxcolumn<m_columnnum-1)
    {
        if(1==m_blockspace[point1.rx()][point1.ry()+1]&&!pointlist.contains(QPoint(point1.rx(),point1.ry()+1)))
            isright=false;
        if(1==m_blockspace[point2.rx()][point2.ry()+1]&&!pointlist.contains(QPoint(point2.rx(),point2.ry()+1)))
            isright=false;
        if(1==m_blockspace[point3.rx()][point3.ry()+1]&&!pointlist.contains(QPoint(point3.rx(),point3.ry()+1)))
            isright=false;
        if(1==m_blockspace[point4.rx()][point4.ry()+1]&&!pointlist.contains(QPoint(point4.rx(),point4.ry()+1)))
            isright=false;
    }
    else
        isright=false;
    return isright;
}

void Tetris::fillblock(bool property)
{
    m_blockspace[point1.rx()][point1.ry()]=property;
    m_blockspace[point2.rx()][point2.ry()]=property;
    m_blockspace[point3.rx()][point3.ry()]=property;
    m_blockspace[point4.rx()][point4.ry()]=property;
}

void Tetris::Integral_eliminate()
{
    for(int i=m_rownum-1;i>=4;i--)
    {
        int countrow=0;
        for(int j=m_columnnum-1;j>=0;j--)
        {
            countrow+=m_blockspace[i][j];
        }
        if(countrow==m_columnnum)
        {
            emit signal_integral();
            for(int j=m_columnnum-1;j>=0;j--)
            {
                m_blockspace[i][j]=0;
            }
            for(int m=i;m>4;m--)
                for(int n=0;n<m_columnnum;n++)
                {
                    m_blockspace[m][n]=m_blockspace[m-1][n];
                }
        }
    }
    sendblockspace();
}
