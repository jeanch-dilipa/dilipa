#ifndef BTVRCMINTERFACE_H
#define BTVRCMINTERFACE_H

#include <interface/centerInterface/systeminterfacebase.h>

namespace Ui {
class BTVRCMInterface;
}

class BTVRCMInterface : public SystemInterfaceBase
{
    Q_OBJECT

public:
    explicit BTVRCMInterface(QWidget *parent = 0);
    ~BTVRCMInterface();

protected:
    void initBtnBind();

private slots:
    void on_comSwitchBtn_btvBoard_toggled(bool checked); //血温血容板通信开关
    void on_comSwitchBtn_rcmBoard_toggled(bool checked); //实时清除率板通信开关

private:
    Ui::BTVRCMInterface *ui;
};

#endif // BTVRCMINTERFACE_H
