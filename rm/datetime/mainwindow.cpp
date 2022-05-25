#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    t1=new QTimer(this);
    t1->stop();
    t1->setInterval(1000);
    connect(t1,SIGNAL(timeout()),this,SLOT(on_timer_timeout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_show_clicked()
{
    QDateTime dt=QDateTime::currentDateTime();
    ui->timeEdit->setTime(dt.time());
    ui->display->setText(dt.toString("hh:mm:ss"));
    ui->dateEdit->setDate(dt.date());
    ui->display->append(dt.toString("yyyy:mm:dd"));
    ui->dateTimeEdit->setDateTime(dt);
    ui->display->append(dt.toString("yyyy-mm-dd hh:mm:ss"));
    qDebug() << dt;
}

void MainWindow::on_set_clicked()
{
    QString str=ui->datetime->text();
    str=str.trimmed();
    QDateTime dt=QDateTime::fromString(str,"yyyy-MM-dd hh:mm:ss");
    ui->dateTimeEdit->setDateTime(dt);
    ui->dateTimeEdit->show();
}

void MainWindow::on_calendarWidget_selectionChanged()
{
    QDate date=ui->calendarWidget->selectedDate();
    QString str=date.toString("yyyy:MM:dd");
    ui->display->append(str);
}

void MainWindow::on_timer_timeout()
{
    QTime t=QTime::currentTime();
    ui->display->append(t.toString());
    int value=ui->progressBar->value();
    value++;
    if(value==61)
        value=0;
    ui->progressBar->setValue(value);
}

void MainWindow::on_start_clicked()
{
    t1->start();
    t2.start();
    ui->progressBar->setValue(0);
    ui->start->setEnabled(false);
    ui->stop->setEnabled(true);
}

void MainWindow::on_stop_clicked()
{
    t1->stop();
    int t=t2.elapsed();
    QString str=QString::asprintf("流逝时间：%d秒，%d毫秒",t/1000,t%1000);
    ui->display->append(str);
    ui->start->setEnabled(true);
    ui->stop->setEnabled(false);
}


