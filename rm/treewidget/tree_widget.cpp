#include "tree_widget.h"

#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QDebug>

tree_Widget::tree_Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(200,200);
    tw=new QTreeWidget(this);

    init();

    connect(tw,&QTreeWidget::itemChanged,this,&tree_Widget::slot_itemchanged);

}

void tree_Widget::slot_itemchanged(QTreeWidgetItem *item,int i)
{
    if(Qt::Checked==item->checkState(0))
    {
        int count =item->childCount();
        if(count>0)
        {
            for(int j=0;j<count;j++)
                item->child(j)->setCheckState(0,Qt::Checked);
        }
        else
        {
            updateitem(item,i);
        }
    }
    else if(Qt::Unchecked==item->checkState(0))
    {
        int count =item->childCount();
        if(count>0)
        {
            for(int j=0;j<count;j++)
                item->child(j)->setCheckState(0,Qt::Unchecked);
        }
        else
        {
            updateitem(item,i);
        }
    }
}

void tree_Widget::updateitem(QTreeWidgetItem *item, int)
{
    QTreeWidgetItem *t=item->parent();
    int count=t->childCount();
    int sum=0;
    for(int j=0;j<count;j++)
    {
        if(t->child(j)->checkState(0)==Qt::Checked)
            sum++;
    }
    if(sum==count)
        t->setCheckState(0,Qt::Checked);
    if(sum<count&&sum>0)
        t->setCheckState(0,Qt::PartiallyChecked);
    if(sum<=0)
        t->setCheckState(0,Qt::Unchecked);
}

void tree_Widget::init()
{
    QTreeWidgetItem *twi0=new QTreeWidgetItem(tw);
    twi0->setText(0,"0");
    twi0->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);
    twi0->setCheckState(0,Qt::Unchecked);

    QTreeWidgetItem *twi01=new QTreeWidgetItem(twi0);
    twi01->setText(0,"01");
    twi01->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);
    twi01->setCheckState(0,Qt::Unchecked);

    QTreeWidgetItem *twi02=new QTreeWidgetItem(twi0);
    twi02->setText(0,"02");
    twi02->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);
    twi02->setCheckState(0,Qt::Unchecked);
}

tree_Widget::~tree_Widget()
{
}

