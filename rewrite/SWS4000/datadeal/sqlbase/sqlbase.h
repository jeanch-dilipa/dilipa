/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   sqlbase.h
    info:	Database retrieval interface
******************************************************************************/

#ifndef SQLBASE_H
#define SQLBASE_H

#include <QObject>
#include <QMutex>
#include <QMutexLocker>
#include <QPointer>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "datadeal/common/publicdata.h"
#include "datadeal/common/functioncode.h"

class SqlBase : public QObject
{
    Q_OBJECT

public:
    static SqlBase& initSqlBase(const QString dbName);

private:
    explicit SqlBase(const QString dbName);
    virtual ~SqlBase();

private:
    static QPointer<SqlBase>                    s_sql;
    static QMutex                              *s_mutexLocker;

    QSqlDatabase                                m_db;
    QSqlQuery                                   m_query;
};

#endif // SQLBASE_H
