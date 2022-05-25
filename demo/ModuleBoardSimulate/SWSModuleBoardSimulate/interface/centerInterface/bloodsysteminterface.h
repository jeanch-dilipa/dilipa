#ifndef BLOODSYSTEMINTERFACE_H
#define BLOODSYSTEMINTERFACE_H

#include "systeminterfacebase.h"

namespace Ui {
class BloodSystemInterface;
}

class BloodSystemInterface : public SystemInterfaceBase
{
    Q_OBJECT

public:
    explicit BloodSystemInterface(QWidget *parent = 0);
    ~BloodSystemInterface();

protected:
    void initBtnBind(); //初始化按钮与数据绑定，父类自动调用

private slots:
    void on_comSwitchBtn_bloodBoard_toggled(bool checked);     //血路板通讯开关
    void on_comSwitchBtn_bloodPumpBoard_toggled(bool checked); //血泵板通讯开关
    void on_comSwitchBtn_subPumpBoard_toggled(bool checked);   //补液泵板通讯开关

private:
    Ui::BloodSystemInterface *ui;
};

#endif // BLOODSYSTEMINTERFACE_H
