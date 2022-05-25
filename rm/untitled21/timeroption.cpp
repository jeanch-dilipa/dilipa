#include "timeroption.h"
#include <QTimer>
#include <QTime>
#include <QDebug>

QTimer timer;
QTime time1;

timeroption::timeroption(QWidget *parent) : QWidget(parent)
{
    timer.stop();
    timer.setInterval(2000);
    qDebug()<<time1.currentTime();
    timer.start();
    connect(&timer,&QTimer::timeout,[=](){qDebug()<<time1.currentTime();});
}

void timeroption::kk()
{

}
