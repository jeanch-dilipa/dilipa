#include "subwidget.h"

#include <QPushButton>
#include <QDebug>

subwidget::subwidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("子窗口");
    setMaximumSize(200,200);

    QPushButton *p=new QPushButton(this);
    p->setText("切换主窗口");
    p->move(50,50);

    connect(p,SIGNAL(clicked()),this,SLOT(slot_emit()));
}

void subwidget::slot_emit()
{
    qDebug()<<"k";
    emit signal_main();
}
