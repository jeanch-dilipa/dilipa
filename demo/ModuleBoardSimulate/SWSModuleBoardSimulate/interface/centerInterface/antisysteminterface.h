#ifndef ANTISYSTEMINTERFACE_H
#define ANTISYSTEMINTERFACE_H

#include "systeminterfacebase.h"

namespace Ui {
class AntiSystemInterface;
}

class AntiSystemInterface : public SystemInterfaceBase
{
    Q_OBJECT

public:
    explicit AntiSystemInterface(QWidget *parent = 0);
    ~AntiSystemInterface();

protected:
    void initBtnBind();

private slots:
    void on_comSwitchBtn_hepBoard_toggled(bool checked); //肝素板通讯开关

private:
    Ui::AntiSystemInterface *ui;
};

#endif // ANTISYSTEMINTERFACE_H
