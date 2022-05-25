#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    /*背景色*/
    pal.setColor(QPalette::Background,QColor(230,234,235));
    setPalette(pal);

    ui->pushButton->setStyleSheet("background-color:rgb(10,207,151);border-radius:10px");

    /*阴影效果*/
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(12,12);
    shadow_effect->setColor(Qt::gray);
    shadow_effect->setBlurRadius(5);
    ui->pushButton->setGraphicsEffect(shadow_effect);

    QGraphicsDropShadowEffect *shadow_effect1 = new QGraphicsDropShadowEffect(this);
    shadow_effect1->setOffset(10,10);
    shadow_effect1->setColor(Qt::red);
    shadow_effect1->setBlurRadius(5);
    ui->pushButton->setGraphicsEffect(shadow_effect1);

//    ui->pushButton_2->setStyleSheet("background-color:'#DAE0E6';border-radius:10px");
//    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);

//    connect(this,&MainWidget::setProgressValue,this,&MainWidget::drawProgressArc);

    ui->startTime_Value->setText(startTime.toString("hh:mm"));
    ui->remainingTime_Value->setText(remainingTime.toString("hh:mm:ss"));
    ui->endTime_Value->setText(endTime.toString("hh:mm"));

    refreshTimer.setInterval(1000);
    connect(&refreshTimer,&QTimer::timeout,this,&MainWidget::slotUpdate);
    refreshTimer.start();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

//    painter.translate(this->width() / 2,this->height() / 2 + 10);

//    qDebug()<<QDateTime::currentDateTime();
    drawOuterArc(painter);/*外弧*/
    drawInnerArc(painter);/*内弧*/
    drawMaskLayer(painter);/*遮罩*/
    drawEndpointArc(painter);/*端点弧*/
    drawBackGroundArc(painter);/*背景弧*/
    drawProgressArc(painter);/*进度绘制*/
//    qDebug()<<QDateTime::currentDateTime();

//    qDebug()<<QDateTime::currentDateTime();
//    drawOuterArc(painter);/*外弧*/
//    drawProgressShadeArc(painter);/*进度盘*/
//    drawInnerArc(painter);/*内弧*/
//    drawMaskLayer(painter);/*遮罩*/
//    drawEndpointArc(painter);/*端点弧*/
//    drawEndpointShadeArc(painter);/*进度端点*/
//    drawBackGroundArc(painter);/*背景弧*/
//    drawProgressArc(painter);/*进度绘制*/
//    qDebug()<<QDateTime::currentDateTime();
}

void MainWidget::drawOuterArc(QPainter &painter)
{

    QConicalGradient conicalGradient(centerPoint, 0);

    conicalGradient.setColorAt(0, QColor(171,187,201));
    conicalGradient.setColorAt(60.0/360.0, QColor(171,187,201));
    conicalGradient.setColorAt(180.0/360.0, QColor(255,255,255));
    conicalGradient.setColorAt(300.0/360.0, QColor(255,255,255));
    conicalGradient.setColorAt(360/360, QColor(171,187,201));

    QBrush brush(conicalGradient);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);
    painter.drawEllipse(centerPoint, progressRadius + 14, progressRadius + 14);
}

void MainWidget::drawInnerArc(QPainter &painter)
{
    QConicalGradient conicalGradient(centerPoint, 0);

    conicalGradient.setColorAt(0, QColor(255,255,255));
    conicalGradient.setColorAt(90.0/360.0, QColor(255,255,255));
    conicalGradient.setColorAt(180.0/360.0, QColor(171,187,201));
    conicalGradient.setColorAt(270/360, QColor(255,255,255));
    conicalGradient.setColorAt(360/360, QColor(255,255,255));

    QBrush brush(conicalGradient);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);
    painter.drawEllipse(centerPoint, progressRadius - 14, progressRadius - 14);
}

void MainWidget::drawMaskLayer(QPainter &painter)
{
    /*环形底部遮罩*/
    QRectF rect(centerPoint.x() - progressRadius,centerPoint.y() - progressRadius,progressRadius * 2,progressRadius * 2);
    painter.setPen(QPen(QColor(230,234,235),38,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter.drawArc(rect,213*16,114*16);
    /*内部遮罩*/
    QBrush brush(QColor(230,234,235));
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);
    painter.drawEllipse(centerPoint, progressRadius - 15, progressRadius - 15);
}

void MainWidget::drawEndpointArc(QPainter &painter)
{
    /*左端点*/
    QConicalGradient conicalGradientLeft(centerPoint.x() - sqrt(3) / 2 * progressRadius,centerPoint.y() + progressRadius / 2, 0);
    conicalGradientLeft.setColorAt(0, QColor(171,187,201));
    conicalGradientLeft.setColorAt(60.0/360.0, QColor(255,255,255));
    conicalGradientLeft.setColorAt(90.0/360.0, QColor(255,255,255));
    conicalGradientLeft.setColorAt(300.0/360.0, QColor(255,255,255));
    conicalGradientLeft.setColorAt(360/360, QColor(171,187,201));

    QBrush brushLeft(conicalGradientLeft);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brushLeft);
    painter.drawEllipse(QPoint(centerPoint.x() - sqrt(3) / 2 * progressRadius,centerPoint.y() + progressRadius / 2),13,13);

    /*右端点*/
    QConicalGradient conicalGradientRight(centerPoint.x() + sqrt(3) / 2 * progressRadius,centerPoint.y() + progressRadius / 2, 0);
    conicalGradientRight.setColorAt(0, QColor(171,187,201));
    conicalGradientRight.setColorAt(60.0/360.0, QColor(255,255,255));
    conicalGradientRight.setColorAt(90.0/360.0, QColor(255,255,255));
    conicalGradientRight.setColorAt(300.0/360.0, QColor(255,255,255));
    conicalGradientRight.setColorAt(360/360, QColor(171,187,201));

    QBrush brushRight(conicalGradientRight);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brushRight);
    painter.drawEllipse(QPoint(centerPoint.x() + sqrt(3) / 2 * progressRadius,centerPoint.y() + progressRadius / 2),13,13);
}

void MainWidget::drawProgressShadeArc(QPainter &painter)
{
    QConicalGradient conicalGradient(centerPoint, 0);

    conicalGradient.setColorAt(0, QColor(38,132,255));
    conicalGradient.setColorAt(60.0/360.0, QColor(38,132,255));
    conicalGradient.setColorAt(120.0/360.0, QColor(39, 86, 155));
    conicalGradient.setColorAt(180/360, QColor(38,132,255));
    conicalGradient.setColorAt(360/360, QColor(38,132,255));

    QBrush brush(conicalGradient);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);
    painter.drawEllipse(centerPoint, progressRadius + 12, progressRadius + 12);
}

void MainWidget::drawEndpointShadeArc(QPainter &painter)
{
    /*左端点*/
    painter.setPen(QPen(QColor(39,86,155),24,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter.drawArc(QRectF(centerPoint.x() - progressRadius,centerPoint.y() - progressRadius,progressRadius * 2,progressRadius * 2),200 * 16,10 * 16);

    /*右端点*/
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(38, 128, 247));
    painter.drawEllipse(QPoint(centerPoint.x() + sqrt(3) / 2 * progressRadius,centerPoint.y() + progressRadius / 2),12,12);
}

void MainWidget::drawBackGroundArc(QPainter &painter)
{
    QRectF rect(centerPoint.x() - progressRadius,centerPoint.y() - progressRadius,progressRadius * 2,progressRadius * 2);
    painter.setPen(QPen(QColor(221,225,228),24,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter.drawArc(rect,-30 * 16,240 * 16);
}

void MainWidget::drawProgressArc(QPainter &painter)
{
    QRectF rect(centerPoint.x() - progressRadius,centerPoint.y() - progressRadius,progressRadius * 2,progressRadius * 2);
    painter.setPen(QPen(QColor(68,127,213),22,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter.drawArc(rect,(210 - 240.0 * progressValue) * 16 ,240.0 * progressValue * 16);
}

void MainWidget::slotUpdate()
{
    remainingTime = remainingTime.addSecs(-60);
    if(remainingTime == QDateTime::fromString("00:00:00","hh:mm:ss"))
    {
        refreshTimer.stop();
        disconnect(&refreshTimer,&QTimer::timeout,this,&MainWidget::slotUpdate);
    }
    ui->remainingTime_Value->setText(remainingTime.toString("hh:mm:ss"));
    progressValue = (remainingTime.secsTo(totalTime) * 1.00 / startTime.secsTo(endTime));
    update();
}

void MainWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<event->pos();
    progressValue++;
    update();
}
