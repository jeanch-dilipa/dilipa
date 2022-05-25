#ifndef GOBANG_H
#define GOBANG_H

#include <QObject>
#include <QPainter>

class gobang : public QObject
{
    Q_OBJECT
public:
    explicit gobang(QObject *parent = nullptr);

    void initchess(int linenum);
    void recordchess(int i,int j,int num);
    void detectionchess();
    void takeback();
    int checkchessdown(int count,int i,int j,int num);
    int checkchessright(int count,int i,int j,int num);
    int checkchessrightdown(int count,int i,int j,int num);
    int checkchessleftdown(int count,int i,int j,int num);
    int checkchessup(int count,int i,int j,int num);
    int checkchessleft(int count,int i,int j,int num);
    int checkchessleftup(int count,int i,int j,int num);
    int checkchessrightup(int count,int i,int j,int num);
    void clearchess();

signals:
    void signal_initchess(int);
    void signal_recordchess(int,int,int);
    void signal_detectionchess();
    void signal_playerwin();
    void signal_takeback();
    void signal_repaint(int X,int Y);
    void signal_voctory(int play,QString str);
    void signal_clearchess();

private:
    QPoint point1=QPoint(0,0);
    QPoint point2=QPoint(0,0);
    int linenum=0;
    int **chess;
};

#endif // GOBANG_H
