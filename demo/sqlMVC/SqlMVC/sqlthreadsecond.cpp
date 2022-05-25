#include "sqlthreadsecond.h"
#include <QTimer>
SqlthreadSecond::SqlthreadSecond(QObject *parent) :
    QThread(parent)
{
}
void SqlthreadSecond::run()
{
    myTableModel.setTable("TestTable");//使用database已有连接
    myTableModel.setEditStrategy(QSqlTableModel::OnManualSubmit);
    myTableModel.select();
    TempRecord = myTableModel.record(1);
    Cont = TempRecord.value("Wight").toInt();

    QTimer myTick;
    connect(&myTick,SIGNAL(timeout()),SLOT(TimeTick()));
    myTick.start(100);
    this->exec();
}

void SqlthreadSecond::TimeTick()
{
    TempRecord.setValue("Wight",Cont++);
    myTableModel.setRecord(1,TempRecord);//修改一行
    myTableModel.submitAll();
}
