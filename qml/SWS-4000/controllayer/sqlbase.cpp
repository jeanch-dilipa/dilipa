#include "sqlbase.h"

/*
功能描述：sqlbase类构造函数
输    入：/
输    出：/
*/
sqlbase::sqlbase(const QString &name)
{
#if DEBUG_MODEL || DEBUG_MODEL_SQLBASE
    QString debugstr="sqlbase::sqlbase(const QString &name):构造函数";
    qdebug<<debugstr;
#endif

    db_name = name;

//    if(db_name == OP_REC_DATA_BASE_FILE_NAME)
//    {

//    }

    if(db.contains(db_name))
    {
        db = QSqlDatabase::database(db_name);
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE",db_name);
    }

    db.setDatabaseName(db_name);

    if(!db.open())
    {
//        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_DATABASE_OPEN_ERROR,INTERVAL_30,SYSTEM_ALARM_ENABLE);
    }
    else
    {
        query = QSqlQuery(db);
    }
}
/*
功能描述：sqlbase类析构函数
输    入：/
输    出：/
*/
sqlbase::~sqlbase()
{
#if DEBUG_MODEL || DEBUG_MODEL_SQLBASE
    QString debugstr="sqlbase::~sqlbase():析构函数";
    qdebug<<debugstr;
#endif

    if(db.isOpen())
    {
        db.close();
    }
    QSqlDatabase::removeDatabase("QSQLITE");
}
/*
功能描述：执行单条语句
输    入：SQL语句
输    出：/
*/
bool sqlbase::Exec(const QString &command)
{
#if DEBUG_MODEL || DEBUG_MODEL_SQLBASE
    QString debugstr="bool sqlbase::Exec(const QString &command):执行单条语句";
    qdebug<<debugstr;
#endif

    bool result = query.exec(command);
    if(!result)
    {
        QSqlError error = query.lastError();
        qdebug<<error;
//        emit signal_sendAlarmData(SYSTEM_ERROR_CODE_DATABASE_READ_ERROR,INTERVAL_30,SYSTEM_ALARM_ENABLE);
    }
    return result;
}
/*
功能描述：执行事务
输    入：SQL语句集
输    出：/
*/
void sqlbase::Exec(const QList<QString> &commandList)
{
#if DEBUG_MODEL || DEBUG_MODEL_SQLBASE
    QString debugstr="bool sqlbase::Exec(const QList<QString> &commandList):执行事务";
    qdebug<<debugstr;
#endif

    if(db.transaction())
    {
        for(int i = 0;i < commandList.size();i++)
        {
            Exec(commandList.at(i));
        }
        if(!db.commit())
        {
//            emit signal_sendAlarmData(SYSTEM_ERROR_CODE_DATABASE_READ_ERROR,INTERVAL_30,SYSTEM_ALARM_ENABLE);
        }
    }
}
/*
功能描述：查询
输    入：SQL语句
输    出：/
*/
QSqlQuery sqlbase::Query(const QString &command)
{
#if DEBUG_MODEL || DEBUG_MODEL_SQLBASE
    QString debugstr="QSqlQuery sqlbase::Query(const QString &command):查询";
    qdebug<<debugstr;
#endif

    bool result = Exec(command);
    if(!result)
    {
//        QSqlError error = query.lastError();
    }
    return query;
}
