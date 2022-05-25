#include "pressuremonitor.h"
#include "ui_pressuremonitor.h"

PressureMonitor::PressureMonitor(QWidget *parent, QColor backgroundAndTopColor, QColor progressAndNoniusColor, int minlimit, int maxlimit, int dsMinlimit, int dsMaxlimit, int currentValue,QString progressName)
    :QWidget(parent), ui(new Ui::PressureMonitor)
{
    ui->setupUi(this);

    this->backgroundAndTopColor = backgroundAndTopColor;
    this->progressAndNoniusColor = progressAndNoniusColor;
    this->minlimit = minlimit;
    this->maxlimit = maxlimit;
    this->dsMinlimit = dsMinlimit;
    this->dsMaxlimit = dsMaxlimit;
    this->currentValue = currentValue;
    this->progressName = progressName;

    pal.setColor(QPalette::Background,QColor("#E6EAEB"));
    setPalette(pal);

    ui->progressName->setText(QString(progressName));
    ui->dsprogressLow->setText(QString::number(dsMinlimit));
    ui->dsprogessUp->setText(QString::number(dsMaxlimit));
    ui->progressValue->setText(QString::number(currentValue));

    refreshTimer.setInterval(1000);
    connect(&refreshTimer,&QTimer::timeout,this,&PressureMonitor::slotUpdate);
//    refreshTimer.start();
}

PressureMonitor::~PressureMonitor()
{
    delete ui;
}

void PressureMonitor::paintEvent(QPaintEvent *)
{

    qDebug()<<1;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    drawUpLowLine(painter);/*上下线*/
    drawPointArc(painter);/*端点*/
    drawBackground(painter);/*背景*/
    drawProgress(painter);/*进度*/
    drawCurrentValue(painter);/*游标*/
}

void PressureMonitor::mousePressEvent(QMouseEvent *event)
{
    dsMaxlimit = event->pos().x();
    dsMinlimit = event->pos().y();
    currentValue = dsMaxlimit / 2 + dsMinlimit / 2;
}

void PressureMonitor::drawUpLowLine(QPainter &painter)
{
    painter.setPen(QPen(backgroundAndTopColor,2,Qt::SolidLine));
    painter.drawLine(20,125,this->width() - 20,125);
    painter.setPen(QPen(QColor("#FFFFFF"),2,Qt::SolidLine));
    painter.drawLine(20,145,this->width() - 20,145);
}

void PressureMonitor::drawPointArc(QPainter &painter)
{
    /*左端点*/
    QConicalGradient conicalGradientLeft(21,134, 0);
    conicalGradientLeft.setColorAt(0, backgroundAndTopColor);
    conicalGradientLeft.setColorAt(60.0/360.0, backgroundAndTopColor);
    conicalGradientLeft.setColorAt(90.0/360.0, backgroundAndTopColor);
    conicalGradientLeft.setColorAt(210.0/360.0, QColor("#FFFFFF"));
    conicalGradientLeft.setColorAt(360/360, QColor("#FFFFFF"));

    QBrush brushLeft(conicalGradientLeft);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brushLeft);
    painter.drawEllipse(11,124,21,21);

    /*右端点*/
    QConicalGradient conicalGradientRight(this->width() - 31,134, 0);
    conicalGradientRight.setColorAt(0, QColor("#FFFFFF"));
    conicalGradientRight.setColorAt(60.0/360.0, backgroundAndTopColor);
    conicalGradientLeft.setColorAt(90.0/360.0, backgroundAndTopColor);
    conicalGradientRight.setColorAt(180.0/360.0, backgroundAndTopColor);
    conicalGradientRight.setColorAt(360/360, QColor("#FFFFFF"));

    QBrush brushRight(conicalGradientRight);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brushRight);
    painter.drawEllipse(this->width() - 31,124,21,21);
}

void PressureMonitor::drawBackground(QPainter &painter)
{
    painter.setPen(QPen(QColor("#DAEDF2"),17,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter.drawLine(20,135,this->width() - 20,135);
}

void PressureMonitor::drawProgress(QPainter &painter)
{
    painter.setPen(QPen(progressAndNoniusColor,15,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter.drawLine(23 + (this->width() - 40) * 1.00 / (maxlimit - minlimit) * (maxlimit - dsMaxlimit),135,23 + (this->width() - 40) * 1.00 / (maxlimit - minlimit) * (maxlimit - dsMinlimit),135);
}

void PressureMonitor::drawCurrentValue(QPainter &painter)
{
    int currentValuePointX = 20 + (this->width() - 20) * 1.00 / (maxlimit - minlimit) * abs(currentValue - maxlimit);

    painter.setPen(QPen(QColor("#D3E6FF"),2,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter.drawLine(currentValuePointX,128,currentValuePointX,142);

    painter.setPen(progressAndNoniusColor);
    painter.setBrush(progressAndNoniusColor);
    QPointF points[3] = {QPointF(currentValuePointX - 7,113),QPointF(currentValuePointX,121),QPointF(currentValuePointX + 7,113)};
    painter.drawPolygon(points,3);
}

void PressureMonitor::slotUpdate()
{
    ui->dsprogressLow->setText(QString::number(dsMinlimit));
    ui->dsprogessUp->setText(QString::number(dsMaxlimit));
    ui->progressValue->setText(QString::number(currentValue));

    update();
}
