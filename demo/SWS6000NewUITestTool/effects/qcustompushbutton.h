#ifndef QCUSTOMPUSHBUTTON_H
#define QCUSTOMPUSHBUTTON_H

#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include "qinnershadow.h"

class QCustomPushButton : public QPushButton
{
public:
    QCustomPushButton(QWidget *parent = Q_NULLPTR);
protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

private:

};

#endif // QCUSTOMPUSHBUTTON_H
