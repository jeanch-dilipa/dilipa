#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
}

Dialog::~Dialog()
{

}

void Dialog::accpet()
{
    emit useragechange(newage);
    QDialog::accept();
}
