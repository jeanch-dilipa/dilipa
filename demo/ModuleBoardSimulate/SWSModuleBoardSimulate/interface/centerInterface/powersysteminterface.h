#ifndef POWERSYSTEMINTERFACE_H
#define POWERSYSTEMINTERFACE_H

#include "systeminterfacebase.h"

namespace Ui {
class PowerSystemInterface;
}

class PowerSystemInterface : public SystemInterfaceBase
{
    Q_OBJECT

public:
    explicit PowerSystemInterface(QWidget *parent = 0);
    ~PowerSystemInterface();

protected:
    void initBtnBind();

private slots:
    void on_comSwitchBtn_powerBoard_toggled(bool checked); //电源板通讯开关

private:
    Ui::PowerSystemInterface *ui;
};

#endif // POWERSYSTEMINTERFACE_H
