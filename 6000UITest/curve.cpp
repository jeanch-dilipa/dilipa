#include "curve.h"
#include "ui_curve.h"

Curve::Curve(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Curve)
{
    ui->setupUi(this);
}

Curve::~Curve()
{
    delete ui;
}

void Curve::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    /*上下左右预留40*/
    /*画背景*/
    int space_x = (this->width() - 80) / 8;
    int space_y = (this->height() - 80) / 4;
    painter.setPen(QPen(Qt::gray,1,Qt::DotLine,Qt::RoundCap,Qt::RoundJoin));
    for(int i = 0;i <= 4;i++)
    {
        painter.drawText(15,40 + space_y * i,tr("%1%").arg(100 - i * 25));
        painter.drawLine(40,40 + space_y * i,this->width() - 40,40 + space_y * i);
    }
    for(int j = 0;j <= 8;j++)
    {
        painter.drawText(40 + space_x * j,this->height() - 20,tr("%1%").arg(j * 25 / 2));
        painter.drawLine(40 + space_x * j,40,40 + space_x * j,this->height() - 40);
    }
//    /*假定一分钟取一点*/
    /*画曲线*/
    int positionWidget = space_x / 60;
    int positionHeight = space_y / 8;

    for(int k = 1;k < 600;k++)
    {
        painter.setPen(QPen(Qt::red,2,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
        painter.drawLine(k * positionWidget + 40,this->height() - 40 - sqrt(k) * positionHeight,(k + 1) * positionWidget + 40,this->height() - 40 - sqrt(k + 1) * positionHeight);

        painter.setPen(Qt::NoPen);
        QLinearGradient line(k * positionWidget + 40,this->height() - 40 - sqrt(k) * positionHeight,(k) * positionWidget + 40,this->height() - 40);
        line.setColorAt(0,QColor("#ECC1C0"));
        line.setColorAt(1,QColor("#00000000"));
        QBrush brush(line);
        painter.setBrush(brush);
        painter.drawRect(k * positionWidget + 40,this->height() - 40 - sqrt(k) * positionHeight,positionWidget,sqrt(k) * positionHeight);
    }
}
