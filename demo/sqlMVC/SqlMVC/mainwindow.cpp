#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDir"
#include "qdebug.h"
#include  <sys/time.h> //用于统计代码运行时间
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    qDebug()<< QThread::currentThread();
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::currentPath()+"/../SqlMVC/TestData.db");
    if(db.open() == false)
    {
        return;
    }
    myTableModel = new QSqlTableModel(this,db);//创建数据模型
    myTableModel->setTable("TestTable");//设置访问的数据库表格
    myTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    myTableModel->select();
    ui->tableView->setModel(myTableModel);

    myTick = new QTimer(this);
    connect(myTick,SIGNAL(timeout()),this,SLOT(TimeOut()));


    mySqlFirst =new SqlthreadFirst(NULL);//新建线程修改表
    mySqlSecond =new SqlthreadSecond(NULL);//新建线程修改表
}
MainWindow::~MainWindow()
{
    delete ui;
    mySqlFirst->quit();
}
struct timeval tpStart,tpEnd;
void MainWindow::TimeOut()
{
//    gettimeofday(&tpStart,NULL);
    myTableModel->select();
//    gettimeofday(&tpEnd,NULL);
//    float timeuse=tpStart.tv_sec-tpEnd.tv_sec + (tpStart.tv_usec-tpEnd.tv_usec)/1000000.0;
//    qDebug()<<timeuse;
}
void MainWindow::on_pushButton_clicked()//添加新行
{
    int id = myTableModel->rowCount();
    myTableModel->insertRow(id);
//    myTableModel->setData(myTableModel->index(id,0),id+1);//添加主键
}
void MainWindow::on_pushButton_2_clicked()//多线程修改
{
    if(mySqlFirst->isRunning())
    {
        mySqlFirst->quit();
        mySqlSecond->quit();
        myTick->stop();
    }
    else
    {
        mySqlFirst->start();
        mySqlSecond->start();
        myTick->start(50);
    }
}
void MainWindow::on_pushButton_3_clicked()//取消修改
{
    myTableModel->revertAll();
}
void MainWindow::on_pushButton_4_clicked()//保存
{
    myTableModel->submitAll();
}
void MainWindow::on_pushButton_5_clicked()//删除选定行
{
    myTableModel->removeRow(ui->tableView->currentIndex().row());
    //保存后生效
    //重新排列ID列
    for(int i=0;i<myTableModel->rowCount();i++)
    {
        myTableModel->setData(myTableModel->index(i,0),i+1);
    }

}
