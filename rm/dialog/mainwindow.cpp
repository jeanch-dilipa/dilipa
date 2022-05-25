#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDir"
#include "QFileDialog"
#include "QColorDialog"
#include "QFontDialog"
#include "QInputDialog"
#include "QMessageBox"
#include "QDebug"

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


void MainWindow::on_file_clicked()
{
    QString path=QDir::currentPath();
    QString filter="文本文件(*.txt)::图片文件(*.jpg *png *gif)::所有文件(*.*)";
    QString title="选择文件";
    QString filename=QFileDialog::getOpenFileName(this,title,path,filter);
    if(!filename.isEmpty())
        ui->textEdit->setText(filename);
}

void MainWindow::on_color_clicked()
{
    QPalette pal=ui->textEdit->palette();
    QColor qc=pal.color(QPalette::Text);
    QColor cs=QColorDialog::getColor(qc,this,"选择颜色");
    if(cs.isValid())
    {
        pal.setColor(QPalette::Text,cs);
        ui->textEdit->setPalette(pal);
    }
}

void MainWindow::on_font_clicked()
{
    QFont qf=ui->textEdit->font();
    bool ok=false;
    QFont font=QFontDialog::getFont(&ok,qf);
    if(ok)
        ui->textEdit->setFont(font);
}

void MainWindow::on_input_clicked()
{
    QLineEdit::EchoMode iE=QLineEdit::Normal;
    bool ok=false;
    QString str=QInputDialog::getText(this,"文字输入","输入：",iE,"",&ok);
    if(ok&&!str.isEmpty())
        ui->textEdit->setText(str);
    bool ok1=false;
    int i=QInputDialog::getInt(this,"整数输入","输入",0,0,100,1,&ok1);
    if(ok1)
        ui->textEdit->append(QString::asprintf("输入整数：%d",i));
    bool ok2=false;
    float f=QInputDialog::getDouble(this,"浮点输入","输入：",0.0,0.0,100.0,2,&ok2);
    if(ok2)
        ui->textEdit->append(QString::asprintf("浮点输入：%f",f));
    QStringList sl;
    sl<<"1"<<"2"<<"3"<<"4";
    bool ok3=false;
    QString text=QInputDialog::getItem(this,"选择项目","选择",sl,false,1,&ok);
    qDebug()<<text;
    if(ok3&&!text.isEmpty())
        ui->textEdit->append(text);
}

void MainWindow::on_message_clicked()
{
    QMessageBox::StandardButton str=QMessageBox::question(this,"提示","是这样吗",QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,QMessageBox::NoButton);
    if(str==QMessageBox::Yes)
        ui->textEdit->append("是的");
    else if(str==QMessageBox::No)
        ui->textEdit->append("不是");
    else
        ui->textEdit->append("取消了");

}
