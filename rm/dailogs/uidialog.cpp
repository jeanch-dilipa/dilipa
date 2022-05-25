#include "uidialog.h"
#include "ui_uidialog.h"

uiDialog::uiDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::uiDialog)
{
    ui->setupUi(this);
}

uiDialog::~uiDialog()
{
    delete ui;
}

void uiDialog::on_cancel_clicked()
{
    this->close();
}

void uiDialog::on_ok_clicked()
{
    str=ui->lineEdit->text();
    this->close();
}
