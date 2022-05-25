#ifndef PARAVANE_H
#define PARAVANE_H

#include <QObject>
#include <QThread>
#include <QDebug>

#define qdebug qDebug()<<__FILE__<<__LINE__

class Paravane : public QThread
{
    Q_OBJECT
public:
    Paravane();

signals:
    void signal_createthunder(int,int);
    void signal_setthunder(QList<int> thunderlist);
    void signal_judgethunder(int);
    void signal_showthunder(int thundercount);

private:
    void slot_createthunder(int thundercol,int thundernum);
    void slot_judgethunder(int thunderindex);

private:
        QList<int> thunderlist;
        int thundercolumn;
};

#endif // PARAVANE_H
