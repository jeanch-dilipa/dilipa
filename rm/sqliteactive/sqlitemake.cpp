#include "sqlitemake.h"
#include "ui_sqlitemake.h"

#include <QtDebug>
#include <QFileDialog>
#include <QStringList>
#include <QSqlError>
#include <QItemSelectionModel>
#include <QSqlTableModel>

sqlitemake::sqlitemake(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::sqlitemake)
{
    ui->setupUi(this);
    if(QSqlDatabase::contains("sqliteconnect"))
    {
        db=QSqlDatabase::database("sqliteconnect");
    }
    else
    {
        QString str=QFileDialog::getOpenFileName(this,"选择数据库","E:/sqlitedb/","*.db");
//        QStringList list=str.split("/");
//        foreach(QString str,list)
//        {
//            if(str.contains(".db"))
//                dbfile=str;
//        }
        db=QSqlDatabase::addDatabase("QSQLITE","sqliteconnect");
        qDebug()<<dbfile<<str;
        db.setDatabaseName(str);
    }
    QSqlQuery query(db);
//    querymodel=new QSqlQueryModel(this);    //查询模型
//    section=new QItemSelectionModel(querymodel);    //选择模型

    tablemodel=new QSqlTableModel(this,db);
    section=new QItemSelectionModel(tablemodel);

//    ui->tableView->setModel(querymodel);
    ui->tableView->setModel(tablemodel);

    ui->tableView->setSelectionModel(section);

    if(db.open())
    {
        QString sql="select * from Provincial_region";
        query.prepare(sql);
        if(query.exec())
        {
//            record=query.record();
//            qDebug()<<record;
            qDebug()<<"id     name";
            while(query.next())
            {

                int id=query.value(0).toInt();
                QString name=query.value(1).toString();
                qDebug()<<QString("%1    %2").arg(id).arg(name);
            }
        }
        else
            qDebug()<<query.lastError();

        tablemodel->setTable("testtable");  //在数据库打开之后载设置表名
        tablemodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        tablemodel->select();
        tablemodel->setHeaderData(0,Qt::Horizontal,"id");
        tablemodel->setHeaderData(1,Qt::Horizontal,"name");

//        querymodel->setQuery(query);
//        querymodel->setHeaderData(0,Qt::Horizontal,"id");
//        querymodel->setHeaderData(1,Qt::Horizontal,"name");
        db.close();
    }
    else
        qDebug()<<db.lastError();
}

sqlitemake::~sqlitemake()
{
    delete ui;
}

