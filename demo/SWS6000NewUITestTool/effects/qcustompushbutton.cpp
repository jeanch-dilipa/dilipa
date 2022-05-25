#include "qcustompushbutton.h"

QCustomPushButton::QCustomPushButton(QWidget *parent) :QPushButton(parent)
{
    QColor shadowColor("#60000000");
    QPoint offset(3,3);
    QGraphicsDropShadowEffect *releaseEffect = new QGraphicsDropShadowEffect(this);
    releaseEffect->setBlurRadius(16);
    releaseEffect->setColor(shadowColor);
    releaseEffect->setOffset(offset);
    setGraphicsEffect(releaseEffect);
    setText("Button");
}

void QCustomPushButton::mousePressEvent(QMouseEvent *e)
{
    QPushButton::mousePressEvent(e);
    QPoint offset(3,3);
    QInnerShadow *pressEffect = new QInnerShadow(this);
    pressEffect->setRadius(5);
    pressEffect->setColor("#B0000000");
    pressEffect->setOffset(offset);
    setGraphicsEffect(pressEffect);
}

void QCustomPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    QPushButton::mouseReleaseEvent(e);
    QPoint offset(3,3);
    QGraphicsDropShadowEffect *releaseEffect = new QGraphicsDropShadowEffect(this);
    releaseEffect->setBlurRadius(16);
    releaseEffect->setColor("#60000000");
    releaseEffect->setOffset(offset);

    setGraphicsEffect(releaseEffect);
}
