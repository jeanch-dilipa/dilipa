#ifndef LIQUIDSYSTEMINTERFACE_H
#define LIQUIDSYSTEMINTERFACE_H

#include "systeminterfacebase.h"

namespace Ui {
class LiquidSystemInterface;
}

class LiquidSystemInterface : public SystemInterfaceBase
{
    Q_OBJECT
public:
    explicit LiquidSystemInterface(QWidget *parent = nullptr);
    ~LiquidSystemInterface();

protected:
    void initBtnBind(); //初始化按钮与数据绑定，父类自动调用

private slots:
    void on_lastPageBtn_clicked();   //上一页按钮
    void on_nextPageBtn_clicked();   //下一页按钮

    void on_comSwitchBtn_liquidBoard_toggled(bool checked);     //水路板通讯开关
    void on_comSwitchBtn_driveBoard_toggled(bool checked);      //驱动板通讯开关
    void on_comSwitchBtn_balanceBoard_toggled(bool checked);    //平衡腔板通讯开关
    void on_comSwitchBtn_heatBoard_toggled(bool checked);       //加热板通讯开关

private:
    void judgePageBtnEnable();

private:
    Ui::LiquidSystemInterface *ui;
};

#endif // LIQUIDSYSTEMINTERFACE_H
