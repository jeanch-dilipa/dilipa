#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPalette>
#include <QColor>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <math.h>
#include <QDebug>
#include <QDateTime>
#include <QTimer>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void drawOuterArc(QPainter &painter);
    void drawInnerArc(QPainter &painter);
    void drawMaskLayer(QPainter &painter);
    void drawBackGroundArc(QPainter &painter);
    void drawEndpointArc(QPainter &painter);
    void drawProgressArc(QPainter &painter);
    void drawProgressShadeArc(QPainter &painter);
    void drawEndpointShadeArc(QPainter &painter);

    void slotUpdate();

signals:
    void setProgressValue(quint8);
private:
    Ui::MainWidget *ui;
    QPalette        pal;

    QTimer          refreshTimer;
    QPoint          centerPoint = QPoint(185,155);
    quint8          progressRadius = 140;
    float           progressValue = 0.0;

    QDateTime       startTime = QDateTime::fromString("12:23","hh:mm");
    QDateTime       endTime = QDateTime::fromString("16:23","hh:mm");
    QDateTime       remainingTime = QDateTime::fromString("04:00:00","hh:mm:ss");
    QDateTime       totalTime = QDateTime::fromString("04:00:00","hh:mm:ss");
};
#endif // MAINWIDGET_H
