#include "mainwidget.h"

#include <QPushButton>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *p=new QPushButton(this);
    p->setText("切换子窗口");
    p->move(50,50);

    setWindowTitle("主窗口");
    setMaximumSize(200,200);

//    connect(p,SIGNAL(clicked()),this,SLOT(slot_switch()));
//    connect(&sub,SIGNAL(signal_main()),this,SLOT(slot_switch()));

    connect(p,&QPushButton::clicked,this,&MainWidget::slot_switch);

    void (subwidget::*funtion)()=&subwidget::signal_main;
    connect(&sub,funtion,this,&MainWidget::slot_switch);

//    QPushButton *p1=new QPushButton(this);
//    connect(p,&QPushButton::released,this,MainWidget::close());
}

void MainWidget::slot_switch()
{
    if(log)
    {
        hide();
        sub.show();
        qDebug()<<"f";
        log=false;
    }
    else
    {
        sub.hide();
        show();
        qDebug()<<"l";
        log=true;
    }

}

MainWidget::~MainWidget()
{
}

