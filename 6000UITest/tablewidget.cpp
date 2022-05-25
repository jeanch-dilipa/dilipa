#include "tablewidget.h"
#include "ui_tablewidget.h"

tableWidget::tableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tableWidget)
{
    ui->setupUi(this);

    ui->tableWidget_2->setAlternatingRowColors(true);
    m_header.insert(0,tr("报警时间"));
    m_header.insert(1,tr("报警内容"));
    m_header.insert(2,tr("模式"));
    m_header.insert(3,tr("状态"));
    m_header.insert(4,tr("运行时间"));
    m_model = new QStandardItemModel();
    ui->tableWidget_2->setModel(m_model);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);    //设置表格的单元为只读属性，即不能编辑
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::NoSelection); //设置为不能选择
    ui->tableWidget_2->setAlternatingRowColors(true);//设置行背景色交替改变

    QStringList head = {"1", "2", "3"};
    ui->tableWidget_2->setHorizontalHeaderLabels(head);

}

tableWidget::~tableWidget()
{
    delete ui;
}
