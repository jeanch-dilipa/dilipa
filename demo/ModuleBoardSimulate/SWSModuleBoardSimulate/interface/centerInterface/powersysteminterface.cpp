#include "powersysteminterface.h"
#include "ui_powersysteminterface.h"
#include <QRegExpValidator>

PowerSystemInterface::PowerSystemInterface(QWidget *parent) : SystemInterfaceBase(parent), ui(new Ui::PowerSystemInterface)
{
    ui->setupUi(this);

    //初始化版本输入框
    initVersionLineEdit(ui->lineEdit_powerBoard_softVer, &g_simDa.powerSys.powerBoardSoftVer, true);
    initVersionLineEdit(ui->lineEdit_powerBoard_hardVer, &g_simDa.powerSys.powerBoardHardVer, false);

    //默认通讯打开
    ui->comSwitchBtn_powerBoard->setChecked(true);
}

PowerSystemInterface::~PowerSystemInterface()
{
    delete ui;
}

void PowerSystemInterface::initBtnBind()
{
    addBtnBindItem(ui->powerErrorBtn, &g_simDa.powerSys.powerError, tr("电源系统"), tr("正常"), tr("故障"));
    addBtnBindItem(ui->chargeStatusBtn, &g_simDa.powerSys.chargeStatus, tr("充电状态"), tr("充电完成"), tr("充电中"));
    addBtnBindItem(ui->batteryStatusBtn, &g_simDa.powerSys.batteryStatus, tr("电池状态"), tr("正常"), tr("异常"));
    addBtnBindItem(ui->cityPowerBtn, &g_simDa.powerSys.cityPower, tr("市电状态"), tr("正常"), tr("异常"));
    addBtnBindItem(ui->powerSupplyBtn, &g_simDa.powerSys.powerSupply, tr("供电状态"), tr("市电"), tr("电池"));
    addBtnBindItem(ui->cityVolBtn, &g_simDa.powerSys.cityVol, tr("市电电压"));
    addBtnBindItem(ui->batteryBtn, &g_simDa.powerSys.battery, tr("电池电量"));
    addBtnBindItem(ui->vol12VBtn, &g_simDa.powerSys.vol12V, tr("12V电压"));
    addBtnBindItem(ui->vol24VBtn, &g_simDa.powerSys.vol24V, tr("24V电压"));
    addBtnBindItem(ui->batteryVolBtn, &g_simDa.powerSys.batteryVol, tr("电池电压"));
}

void PowerSystemInterface::on_comSwitchBtn_powerBoard_toggled(bool checked)
{
    g_simDa.powerSys.powerBoardComSW = checked;
}
