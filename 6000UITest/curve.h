#ifndef CURVE_H
#define CURVE_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <math.h>
#include <QLinearGradient>

namespace Ui {
class Curve;
}

class Curve : public QWidget
{
    Q_OBJECT

public:
    explicit Curve(QWidget *parent = nullptr);
    ~Curve();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::Curve *ui;
};

#endif // CURVE_H
