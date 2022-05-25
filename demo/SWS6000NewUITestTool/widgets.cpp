#include "widgets.h"
#include "ui_widgets.h"
#include <QGridLayout>
#include "effects/qcustompushbutton.h"

Widgets::Widgets(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widgets)
{
    ui->setupUi(this);

//    QGridLayout *layout = new QGridLayout(this);
//    this->setLayout(layout);
    ui->gridLayout->setSpacing(20);
    for(int i = 0; i<20; ++i)
    {
        QCustomPushButton *button = new QCustomPushButton(this);
        button->setFixedSize(120,120);
        button->setStyleSheet("background-color:#F0F0F0;border-radius:20px;font-size:20px;");
        button->setText("BUTTON"+QString::number(i+1));
        ui->gridLayout->addWidget(button, i/5, i%5);
    }
}

Widgets::~Widgets()
{
    delete ui;
}

void Widgets::on_toolButton_clicked()
{
    this->hide();
}
