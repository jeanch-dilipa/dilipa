#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
//    ui->groupBox_2->hide();
//    ui->groupBox_3->hide();
//    layout()->setSizeConstraint(QLayout::SetFixedSize);

}

Dialog::~Dialog()
{
    delete ui;
}
