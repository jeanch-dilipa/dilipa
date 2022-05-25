#ifndef CENTER_H
#define CENTER_H

#include <QWidget>
#include <QPointer>
#include <QPalette>

#include "mainwidget.h"
#include "pressuremonitor.h"

namespace Ui {
class Center;
}

class Center : public QWidget
{
    Q_OBJECT

public:
    explicit Center(QWidget *parent = nullptr);
    ~Center();

private:
    Ui::Center *ui;
    QPalette              pal;

    QPointer<MainWidget>     ma;
    QPointer<PressureMonitor> APpre;
    QPointer<PressureMonitor> VPpre;
    QPointer<PressureMonitor> TEMPpre;
};

#endif // CENTER_H
