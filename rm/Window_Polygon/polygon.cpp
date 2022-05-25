#include "polygon.h"

#include <QPainter>

Polygon::Polygon(QWidget *parent)
    : QMainWindow(parent)
{
}

Polygon::~Polygon()
{
}

void Polygon::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.drawPixmap(0,0,width(),height(),QPixmap(":/new/image/file"));
}

