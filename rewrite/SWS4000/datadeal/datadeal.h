/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   datadeal.h
    info:	Data processing
******************************************************************************/

#ifndef DATADEAL_H
#define DATADEAL_H

#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QPointer>

#include "common/common.h"
#include "datadeal/sqlbase/sqlbase.h"

class DataDeal: public QThread
{
    Q_OBJECT

public:
    static DataDeal& initDataDeal();

protected:
    void run();

private:
    explicit DataDeal();
    ~DataDeal();

private:
    static QPointer<DataDeal>               s_datadeal;
    static QMutex                          *s_mutexLocker;

    QPointer<SqlBase>                       m_sql;
};

#endif // DATADEAL_H
