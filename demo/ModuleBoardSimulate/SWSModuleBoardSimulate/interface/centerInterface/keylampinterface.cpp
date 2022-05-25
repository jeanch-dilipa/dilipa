#include "keylampinterface.h"
#include "ui_keylampinterface.h"

keyLampInterface::keyLampInterface(QWidget *parent) : SystemInterfaceBase(parent), ui(new Ui::keyLampInterface)
{
    ui->setupUi(this);

    //初始化版本编辑器
    initVersionLineEdit(ui->lineEdit_monitorBoard_softVer, &g_simDa.keyLamp.monitorBoardSoftVer, true);
    initVersionLineEdit(ui->lineEdit_monitorBoard_hardVer, &g_simDa.keyLamp.monitorBoardHardVer, false);

    //默认通讯打开
    ui->comSwitchBtn_monitorBoard->setChecked(true);
}

keyLampInterface::~keyLampInterface()
{
    delete ui;
}

void keyLampInterface::initBtnBind()
{

}

void keyLampInterface::on_comSwitchBtn_monitorBoard_toggled(bool checked)
{
    g_simDa.keyLamp.monitorBoardComSW = checked;
}
