#include "sqlthreadfirst.h"
#include <QTimer>
SqlthreadFirst::SqlthreadFirst(QObject *parent) :
    QThread(parent)
{
}

void SqlthreadFirst::run()
{
    myTableModel.setTable("TestTable");//使用database已有连接
    myTableModel.setEditStrategy(QSqlTableModel::OnManualSubmit);
    myTableModel.select();
    TempRecord = myTableModel.record(0);//第一行的记录
    Cont = TempRecord.value("Wight").toInt();

    QTimer myTick;
    connect(&myTick,SIGNAL(timeout()),SLOT(TimeTick()));
    myTick.start(100);
    this->exec();
}

void SqlthreadFirst::TimeTick()
{
    myTableModel.setData(myTableModel.index(0,4),Cont++);//直接修改单元格子
    myTableModel.submitAll();
}
