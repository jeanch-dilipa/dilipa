#ifndef MIXULTRASYSTEMINTERFACE_H
#define MIXULTRASYSTEMINTERFACE_H

#include "systeminterfacebase.h"

namespace Ui {
class MixUltraSystemInterface;
}

class MixUltraSystemInterface : public SystemInterfaceBase
{
    Q_OBJECT

public:
    explicit MixUltraSystemInterface(QWidget *parent = 0);
    ~MixUltraSystemInterface();

protected:
    void initBtnBind();

private slots:
    void on_comSwitchBtn_mixUfBoard_toggled(bool checked);  //配液超滤板通讯开关
    void on_comSwitchBtn_mixBoard_toggled(bool checked);    //配液板通讯开关
    void on_comSwitchBtn_ufBoard_toggled(bool checked);     //超滤板通讯开关
    void on_comSwitchBtn_condBoard_toggled(bool checked);   //电导板通讯开关

private:
    Ui::MixUltraSystemInterface *ui;
};

#endif // MIXULTRASYSTEMINTERFACE_H
