/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   sqlbase.cpp
    info:	Database retrieval interface
******************************************************************************/

#include "sqlbase.h"

QPointer<SqlBase> SqlBase::s_sql = nullptr;
QMutex *SqlBase::s_mutexLocker = nullptr;

/****************************************************************************
接口描述: 创建数据库查询类实例
输   入: /
输   出: /
******************************************************************************/
SqlBase &SqlBase::initSqlBase(const QString dbName)
{
    if(nullptr == s_sql)
    {
        QMutexLocker locker(s_mutexLocker);
        if(nullptr == s_sql)
        {
            s_sql = new SqlBase(dbName);
        }
    }

    return *s_sql;
}

/****************************************************************************
接口描述: 数据库查询类析构函数
输   入: /
输   出: /
******************************************************************************/
SqlBase::SqlBase(const QString dbName)
{
   if(true == m_db.contains(dbName))
   {
       m_db = QSqlDatabase::database(dbName);
   }
   else
   {
       m_db = QSqlDatabase::addDatabase("QSQLITE", dbName);
   }

   m_db.setDatabaseName(dbName);

   if(false == m_db.open())
   {
        g_pd.m_fcValue.replace(FC_sqlDataBaseCheck, 1);
   }

   m_query = QSqlQuery(m_db);
}

/****************************************************************************
接口描述: 数据库查询类析构函数
输   入: /
输   出: /
******************************************************************************/
SqlBase::~SqlBase()
{

}
