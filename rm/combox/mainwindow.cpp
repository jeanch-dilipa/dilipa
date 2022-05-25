#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextBlock>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model=new QFileSystemModel(this);
    model->setRootPath(QDir::currentPath());
    ui->treeView->setModel(model);
    ui->listView->setModel(model);
    ui->tableView->setModel(model);
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),ui->listView,SLOT(setRootPath(QModelIndex)));
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),ui->tableView,SLOT(setRootPath(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_csh_clicked()
{
    ui->comboBox->clear();
    for (int i=0;i<20;i++)
    {
        ui->comboBox->addItem(QString::asprintf("item %d",i));
    }
}

void MainWindow::on_qc_clicked()
{
    ui->comboBox->clear();
}

void MainWindow::on_yh_clicked()
{
    QMap<QString,int> map;
    map.insert("部门职责",1);
    map.insert("部门目标",2);
    map.insert("绩效考核",3);
    ui->comboBox_2->clear();
    foreach(const QString str,map.keys())
        ui->comboBox_2->addItem(str,map.value(str));
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->plainTextEdit->appendPlainText(arg1);
}

void MainWindow::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    ui->plainTextEdit->appendPlainText(arg1+"号"+ui->comboBox_2->currentData().toString());
}

void MainWindow::on_tj_clicked()
{
    QTextDocument* td=ui->plainTextEdit->document();
    int line=td->blockCount();
    for (int i=0;i<line;i++)
    {
        QTextBlock tl=td->findBlockByNumber(i);
        ui->comboBox_2->addItem(tl.text());
    }
}

void MainWindow::on_textqc_clicked()
{
    ui->plainTextEdit->clear();
}

void MainWindow::on_plainTextEdit_customContextMenuRequested(const QPoint &pos)
{
    QMenu* menu=ui->plainTextEdit->createStandardContextMenu();
    menu->exec(pos);
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    ui->plainTextEdit->appendPlainText(model->filePath(index));
    ui->plainTextEdit->appendPlainText(model->type(index));
    ui->plainTextEdit->appendPlainText(model->fileName(index));
    int sz=model->size(index)/1024;
    if(sz>1024)
        ui->plainTextEdit->appendPlainText(sz/1024+"mb");
    else
        ui->plainTextEdit->appendPlainText(sz+"kb");
}
