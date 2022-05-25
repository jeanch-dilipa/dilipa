#include "sqllitemake.h"
#include <QFile>

SqlLiteMake::SqlLiteMake()
{
    if(QSqlDatabase::contains("sqlliteconnect"))
    {
        db=QSqlDatabase::database("sqlliteconnect");
    }
    else
    {
        db=QSqlDatabase::addDatabase("QSQLITE","sqliteconnect");
        db.setDatabaseName(DB_FILEPATH);
    }
    query=QSqlQuery(db);
}

void SqlLiteMake::sqllite_select(QString region_table,QString region_column1,QString region_column2,QString where1)
{
    if(db.open())
    {
        QString selectsql="select "+region_column1+","+region_column2+" from "+region_table+" where "+where1;
        query.prepare(selectsql);
        if(query.exec())
        {
            QStringList region_list;
            QStringList grade_list;
            while(query.next())
            {
                QString name=query.value(0).toString();
                QString grade=query.value(1).toString();
                region_list.append(name);
                grade_list.append(grade);
            }
            emit signal_returnregionlist(where1,region_list,grade_list);
            query.finish();
        }
        else
            qdebug<<query.lastError();
        db.close();
    }
    else
        qdebug<<db.lastError();
}
