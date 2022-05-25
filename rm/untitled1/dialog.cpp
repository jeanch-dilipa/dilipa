#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

int Dialog::row()
{
    return ui->spinBox->value();
}

int Dialog::column()
{
    return ui->spinBox_2->value();
}

void Dialog::setrowcolumn(int row, int column)
{
    ui->spinBox->setValue(row);
    ui->spinBox_2->setValue(column);
}
