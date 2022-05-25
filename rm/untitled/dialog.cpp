#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->green,SIGNAL(valueChanged(int)),this,SLOT(on_red_valueChanged(int)));
    connect(ui->blue,SIGNAL(valueChanged(int)),this,SLOT(on_red_valueChanged(int)));
    connect(ui->alpha,SIGNAL(valueChanged(int)),this,SLOT(on_red_valueChanged(int)));
}

Dialog::~Dialog()
{
    delete ui;
}


//void Dialog::on_checkBox_2_clicked(bool checked)
//{
//    QFont font=ui->textEdit->font();
//    font.setBold(checked);
//    ui->textEdit->setFont(font);
//}

//void Dialog::on_checkBox_clicked(bool checked)
//{
//    QFont font=ui->textEdit->font();
//    font.setUnderline(checked);
//    ui->textEdit->setFont(font);
//}

//void Dialog::on_checkBox_3_clicked(bool checked)
//{
//    QFont font=ui->textEdit->font();
//    font.setItalic(checked);
//    ui->textEdit->setFont(font);
//}


//void Dialog::on_radioButton_clicked(bool checked)
//{
//    QPalette pal=ui->textEdit->palette();
//    pal.setColor(QPalette::Text,Qt::red);
//    ui->textEdit->setText("red");
//    ui->textEdit->setPalette(pal);
//    QList<QString> list;
//    list<<"a"<<"b"<<"c";
//    QString str;
//    foreach(str,list)
//        qDebug()<<str;
//}

//void Dialog::on_radioButton_2_clicked(bool checked)
//{
//    QPalette pal=ui->textEdit->palette();
//    pal.setColor(QPalette::Text,Qt::blue);
//    ui->textEdit->setText("blue");
//    ui->textEdit->setPalette(pal);
//}

//void Dialog::on_radioButton_3_clicked(bool checked)
//{
//    QPalette pal=ui->textEdit->palette();
//    pal.setColor(QPalette::Text,Qt::green);
//    ui->textEdit->setText("green");
//    ui->textEdit->setPalette(pal);
//}

//void Dialog::on_js_clicked()
//{
//    QString str=ui->sl->text();
//    int sl=str.toInt();
//    str=ui->dj->text();
//    float dj=str.toFloat();
//    float zj=sl*dj;
//    str=str.setNum(zj,'f',0);
//    ui->zj->setText(str);

//}

//void Dialog::on_pushButton_clicked()
//{
//    QString str=ui->zj->text();
//    int zj=str.toInt();
//    ui->e->setText(str.setNum(zj,2));
//    ui->shiliu->setText(str.setNum(zj,16));
//    ui->b->setText(str.setNum(zj,8));
//    ui->spinBox->setValue(zj);
//}

void Dialog::on_red_valueChanged(int value)
{
    int r=ui->red->value();
    int g=ui->green->value();
    int b=ui->blue->value();
    int alpha=ui->alpha->value();
    QColor color;
    color.setRgb(r,g,b,alpha);
    QPalette pal=ui->backgroundcolor->palette();
    pal.setColor(QPalette::Base,color);
    ui->backgroundcolor->setPalette(pal);

}

void Dialog::on_dial_valueChanged(int value)
{
    ui->lcdNumber->display(value);
}

void Dialog::on_horizontalScrollBar_valueChanged(int value)
{
    ui->progressBar->setValue(value);
}

void Dialog::on_verticalSlider_valueChanged(int value)
{
    ui->verticalScrollBar->setValue(value);
}

void Dialog::on_dec_clicked(bool checked)
{
    ui->lcdNumber->setDigitCount(3);
    ui->lcdNumber->setDecMode();

}

void Dialog::on_oct_clicked()
{
    ui->lcdNumber->setDigitCount(4);
    ui->lcdNumber->setOctMode();

}

void Dialog::on_bin_clicked()
{
    ui->lcdNumber->setDigitCount(8);
    ui->lcdNumber->setBinMode();

}

void Dialog::on_hex_clicked()
{
    ui->lcdNumber->setDigitCount(3);
    ui->lcdNumber->setHexMode();

}
