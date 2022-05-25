#include "heteroideus.h"
#include "ui_heteroideus.h"

Heteroideus::Heteroideus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Heteroideus)
{
    ui->setupUi(this);
    image.load("F:/dilipa/qt/test/6000UITest/edit_50px.png");
    this->setWindowFlags(Qt::FramelessWindowHint);
//    this->setAttribute(Qt::WA_TranslucentBackground);//穿透二选一
}

Heteroideus::~Heteroideus()
{
    delete ui;
}

void Heteroideus::paintEvent(QPaintEvent *)
{
    image = image.scaled(size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    QPainter painter(this);
    painter.drawImage(rect(),image);
    QBitmap bmp = QBitmap::fromImage(image.createAlphaMask());
    this->setMask(bmp);

}
