#include "widget.h"
#include "ui_widget.h"

#include <QPalette>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->r,&QRadioButton::clicked,this,&Widget::radiobutton);
    connect(ui->g,&QRadioButton::clicked,this,&Widget::radiobutton);
    connect(ui->b,&QRadioButton::clicked,this,&Widget::radiobutton);
}

Widget::~Widget()
{
    delete ui;
}

void  Widget::radiobutton()
{
    if(ui->r->isChecked())
        ui->r->setStyleSheet("background-color:red");
    else if(ui->g->isChecked())
        ui->g->setStyleSheet("background-color:green");
    else if(ui->b->isChecked())
        ui->b->setStyleSheet("background-color:blue");
    qDebug()<<"y";
}

