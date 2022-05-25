#ifndef SQLBASE_H
#define SQLBASE_H

#include <QObject>
#include <QtSql/QtSql>
#include <QtSql/QSqlQuery>

#include "common/common.h"
#include "common/systemAlarmCodes.h"

class sqlbase :public QObject
{
    Q_OBJECT
public:
    explicit sqlbase(const QString &name = QString(SQL_DATA_RUN_FILE_NAME));
    ~ sqlbase();

    bool Exec(const QString &command);                                                                                                    //执行单条语句
    void Exec(const QList<QString> &commandList);                                                                                         //执行事务

    QSqlQuery Query(const QString &command);                                                                                              //查询

//signals:
//    void signal_sendAlarmData(int alarmCode,int alarmInterval,int alarmEnable);                                                           //报警信号传递

private:
    QString                                db_name;                                                                                       //数据库名称
    QSqlDatabase                           db;                                                                                            //数据库
    QSqlQuery                              query;                                                                                         //查询
};

#endif // SQLBASE_H
