#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "QFlags"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Dialog *d=new Dialog(this);
    d->setrowcolumn(10,10);
    int ret=d->exec();
    if(ret==QDialog::Accepted)
    {
        int row=d->row();
        int column=d->column();
        ui->textEdit->append(QString::number(row));
        ui->textEdit->append(QString::number(column));
    }
    delete d;
}
