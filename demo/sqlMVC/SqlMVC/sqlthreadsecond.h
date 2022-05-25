#ifndef SQLTHREADSECOND_H
#define SQLTHREADSECOND_H

#include <QThread>
#include "QtSql/QSqlTableModel"
#include "QSqlRecord"
class SqlthreadSecond : public QThread
{
    Q_OBJECT
public:
    explicit SqlthreadSecond(QObject *parent = 0);
private:
    void run();
    int Cont;
    QSqlTableModel myTableModel;
    QSqlRecord TempRecord;
signals:

public slots:
    void TimeTick();

};

#endif // SQLTHREADSECOND_H
