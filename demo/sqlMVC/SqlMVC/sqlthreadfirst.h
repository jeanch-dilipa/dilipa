#ifndef SQLTHREADFIRST_H
#define SQLTHREADFIRST_H

#include <QThread>
#include "QtSql/QSqlTableModel"
#include "QSqlRecord"
class SqlthreadFirst : public QThread
{
    Q_OBJECT
public:
    explicit SqlthreadFirst(QObject *parent = 0);
private:
    void run();
    int Cont;
    QSqlTableModel myTableModel;
    QSqlRecord TempRecord;
signals:

public slots:
    void TimeTick();
};

#endif // SQLTHREADFIRST_H
