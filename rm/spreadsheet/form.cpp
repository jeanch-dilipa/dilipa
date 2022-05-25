#include "form.h"
#include "ui_form.h"
#include "QTextStream"

#include <QFileInfo>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::defaultfile(QString filename)
{
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream stream(&file);
        ui->plainTextEdit->clear();
        ui->plainTextEdit->setPlainText(stream.readAll());
        file.close();
        QFileInfo fileinfo(file);
        this->setWindowTitle(QString(fileinfo.fileName()));
    }
}

void Form::cut()
{
    ui->plainTextEdit->cut();
}

void Form::copy()
{
    ui->plainTextEdit->copy();
}

void Form::paste()
{
    ui->plainTextEdit->paste();
}

void Form::open(QString filename)
{
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream stream(&file);
        ui->plainTextEdit->clear();
        ui->plainTextEdit->setPlainText(stream.readAll());
        file.close();
        QFileInfo fileinfo(file);
        this->setWindowTitle(QString(fileinfo.fileName()));
    }
}
