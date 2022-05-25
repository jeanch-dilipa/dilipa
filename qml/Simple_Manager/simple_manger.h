#ifndef SIMPLE_MANGER_H
#define SIMPLE_MANGER_H

#include <QThread>
#include <QObject>
#include <QDebug>

#include "sqllitemake.h"

#define qdebug qDebug()<<__FILE__<<__LINE__

class Simple_Manger : public QThread
{
    Q_OBJECT
public:
    Simple_Manger();

signals:
    void signal_selectregion(QString,QString,QString,QString);
    void signal_returnregionlist(QString regionrow,QStringList regionlist,QStringList gradelist);

private:
    SqlLiteMake sqlite;
};

#endif // SIMPLE_MANGER_H
