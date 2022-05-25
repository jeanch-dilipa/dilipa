#ifndef PRESSUREMONITOR_H
#define PRESSUREMONITOR_H

#include <QWidget>
#include <QPalette>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QColor>
#include <QTimer>
#include <QTime>

namespace Ui {
class PressureMonitor;
}

class PressureMonitor : public QWidget
{
    Q_OBJECT

public:
    explicit PressureMonitor(QWidget *parent = nullptr,QColor backgroundAndTopColor = QColor("#98BDEB"),QColor progressAndNoniusColor = QColor("#2684FF"),\
                              int minlimit = -700,int maxlimit = 500,int dsMinlimit = -700,int dsMaxlimit = 500,int currentValue = 500,QString progressName = "AP");
    ~PressureMonitor();

    PressureMonitor() = delete ;
    PressureMonitor operator= (const PressureMonitor&) = delete ;
    PressureMonitor(const PressureMonitor&) = delete ;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent * event);
    void drawUpLowLine(QPainter &painter);
    void drawPointArc(QPainter &painter);
    void drawBackground(QPainter &painter);
    void drawProgress(QPainter &painter);
    void drawCurrentValue(QPainter &painter);

    void slotUpdate();

private:
    Ui::PressureMonitor   *ui;
    QPalette              pal;

    QTimer                refreshTimer;

    QString               progressName = "AP";
    QColor                backgroundAndTopColor = QColor("#98BDEB");
    QColor                progressAndNoniusColor = QColor("#2684FF");

    int                   minlimit  =   -700;
    int                   maxlimit  =   500;
    int                   dsMinlimit  =   -100;
    int                   dsMaxlimit  =   30;
    int                   currentValue  = -100;
};

#endif // PRESSUREMONITOR_H
