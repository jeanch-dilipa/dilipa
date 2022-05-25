#include "tablewiget.h"
#include "ui_tablewiget.h"
#include <spinboxdelegate.h>

#include <QFileSystemModel>
#include <QDebug>
#include <QStringListModel>
#include <QTimer>
#include <QStandardItemModel>
#include <QItemSelectionModel>

    QFileSystemModel filemodel;
    QStringListModel listmodel;
    QTimer timer;
    QModelIndex index;
    QStandardItemModel *standmodel;
    QItemSelectionModel *selectionmodel;

tableWiget::tableWiget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::tableWiget)
{
    ui->setupUi(this);

    filemodel.setRootPath(QDir::currentPath());

    ui->treeView->setModel(&filemodel);

    QStringList list;
    list<<"kk"<<"kjf"<<"3"<<"4";
    listmodel.setStringList(list);
    qDebug()<<list;
    ui->listView->setModel(&listmodel);
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked);
    listmodel.insertRow(listmodel.rowCount());
    index=listmodel.index(listmodel.rowCount()-1,0);
    listmodel.setData(index,"好的",Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
    timer.setInterval(2000);
    timer.start();
    index=listmodel.index(listmodel.rowCount()-1,0);
    connect(&timer,&QTimer::timeout,this,&tableWiget::removerow);

    standmodel = new QStandardItemModel(5,3,this);
    selectionmodel =new QItemSelectionModel(standmodel);
    ui->tableView->setModel(standmodel);
    ui->tableView->setSelectionModel(selectionmodel);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->setItemDelegateForColumn(1,&sbd);

    ui->undoView->setModel(&filemodel);

    ui->columnView->setModel(&filemodel);

    connect(ui->treeView,&QTreeView::clicked,ui->listView,&QListView::setRootIndex);
    connect(ui->treeView,&QTreeView::clicked,ui->tableView,&QTableView::setRootIndex);
    connect(ui->treeView,&QTreeView::clicked,ui->undoView,&QUndoView::setRootIndex);
    connect(ui->treeView,&QTreeView::clicked,ui->columnView,&QColumnView::setRootIndex);
}

tableWiget::~tableWiget()
{
    delete ui;
}


void tableWiget::on_treeView_clicked(const QModelIndex &index)
{
    qDebug()<<filemodel.isDir(index)<<"/n"<<filemodel.fileName(index)<<"/n"<<filemodel.filePath(index)<<"/n"<<filemodel.type(index);
    int size=filemodel.size(index);
    if(size/1024<1024)
        qDebug()<<QString::number(size/1024)<<"kb";
    else
        qDebug()<<QString::number(size/1024/1024,'f',2)<<"mb";
}
void tableWiget::removerow()
{
    listmodel.removeRow(index.row());
}
