#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->radioButton_2,SIGNAL(clicked()),this,SLOT(stetextfontcolor()));
    connect(ui->radioButton_3,SIGNAL(clicked()),this,SLOT(stetextfontcolor()));
    connect(ui->radioButton,SIGNAL(clicked()),this,SLOT(stetextfontcolor()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

}


void MainWindow::settextfontcolor()
{
    QPalette palet=ui->textEdit->palette();
    if(ui->radioButton->isChecked())
        palet.setColor(QPalette::Text,Qt::red);
    else if(ui->radioButton_2->isChecked())
        palet.setColor(QPalette::Text,Qt::blue);
    else if(ui->radioButton_3->isChecked())
        palet.setColor(QPalette::Text,Qt::green);
    else
        palet.setColor(QPalette::Text,Qt::green);
    ui->textEdit->setPalette(palet);
}


void MainWindow::on_checkBox_clicked(bool checked)
{
    QFont font=ui->textEdit->font();
    font.setUnderline(checked);
    ui->textEdit->setFont(font);

}

void MainWindow::on_checkBox_2_clicked(bool checked)
{
    QFont font=ui->textEdit->font();
    font.setItalic(checked);
    ui->textEdit->setFont(font);
}

void MainWindow::on_checkBox_3_clicked(bool checked)
{
    QFont font=ui->textEdit->font();
    font.setBold(checked);
    ui->textEdit->setFont(font);
}
