#ifndef TETRIS_H
#define TETRIS_H

#include <QObject>
#include <QDebug>
#include <QPoint>

#define qdebug qDebug()<<__FILE__<<__LINE__

class Tetris : public QObject
{
    Q_OBJECT
public:
    explicit Tetris(QObject *parent = nullptr);
    ~Tetris();

    void initblockspace(int column,int row);
    void appendblocktospace(int blocknum);
    void blockdrop();
    void sendblockspace();
    bool whetherdrop();
    void whethergameover();
    void move_left_right_down(QString movestr);
    void change_block();
    bool whetherleft();
    bool whetherright();
    void fillblock(bool property);
    void Integral_eliminate();

signals:
    void signal_initblockspace(int,int);
    void signal_newblockspace(int m_row,int m_column,int m_isblock);
    void signal_blockdrop();
    void signal_spacedatasendend();
    void signal_appendblockspace(int);
    void signal_unabledrop();
    void signal_gameover();
    void signal_nextblock(int nextblock);
    void signal_move_left_right_down(QString);
    void signal_change_block();
    void signal_integral();

private:
    int m_columnnum;
    int m_rownum;
    quint8 nextblock;
    quint8 currentblock;

    QPoint point1;
    QPoint point2;
    QPoint point3;
    QPoint point4;
    int **m_blockspace;       //灵活数组放在末尾
    int specialblock1[4][4]={{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}};
    quint8 block1status=0;
    int specialblock2[4][4]={{0,0,0,0},{0,0,0,0},{0,1,1,0},{0,1,1,0}};
    quint8 block2status=0;
    int specialblock3[4][4]={{0,0,0,0},{0,1,0,0},{0,1,0,0},{0,1,1,0}};
    quint8 block3status=0;
    int specialblock4[4][4]={{0,0,0,0},{0,0,1,0},{0,0,1,0},{0,1,1,0}};
    quint8 block4status=0;
    int specialblock5[4][4]={{0,0,0,0},{0,0,0,0},{0,1,0,0},{1,1,1,0}};
    quint8 block5status=0;
};

#endif // TETRIS_H
