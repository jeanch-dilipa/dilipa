#ifndef KEYLAMPINTERFACE_H
#define KEYLAMPINTERFACE_H

#include "systeminterfacebase.h"

namespace Ui {
class keyLampInterface;
}

class keyLampInterface : public SystemInterfaceBase
{
    Q_OBJECT

public:
    explicit keyLampInterface(QWidget *parent = nullptr);
    ~keyLampInterface();

protected:
    void initBtnBind();

private slots:
    void on_comSwitchBtn_monitorBoard_toggled(bool checked); //监控板通信开关

private:
    Ui::keyLampInterface *ui;
};

#endif // KEYLAMPINTERFACE_H
