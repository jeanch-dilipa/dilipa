#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QValidator"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRegExp regexp("[A-Za-z][0-9][0-9]{0,2}");
    ui->lineEdit->setValidator(new QRegExpValidator(regexp,this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->ok->setEnabled(true);
}

