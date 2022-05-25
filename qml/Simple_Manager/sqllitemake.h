#ifndef SQLLITEMAKE_H
#define SQLLITEMAKE_H

#include <QThread>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#define qdebug qDebug()<<__FILE__<<__LINE__
#define DB_FILEPATH "F:/dilipa/qt/qml/Simple_Manager/Simple_Manger.db"

class SqlLiteMake : public  QThread
{
    Q_OBJECT
public:
    SqlLiteMake();

public:
    void sqllite_insert();
    void sqllite_delete();
    void sqllite_update();
    void sqllite_select(QString region_table,QString region_column1,QString region_column2,QString where1);

signals:
    void signal_returnregionlist(QString,QStringList ,QStringList );


private:
    QSqlDatabase db;
    QSqlQuery query;
};

#endif // SQLLITEMAKE_H
