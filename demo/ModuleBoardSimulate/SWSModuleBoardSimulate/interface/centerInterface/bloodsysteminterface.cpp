#include "bloodsysteminterface.h"
#include "ui_bloodsysteminterface.h"
#include "uart/uart485.h"

#define UPDATE_INTERFACE_TIME 500 /*更新界面周期 ms*/

BloodSystemInterface::BloodSystemInterface(QWidget *parent) : SystemInterfaceBase(parent), ui(new Ui::BloodSystemInterface)
{
    ui->setupUi(this);

    //初始化版本显示窗口
    initVerStackedWidget(ui->stackedWidget);

    //初始化版本编辑器
    initVersionLineEdit(ui->lineEdit_bloodBoard_softVer, &g_simDa.bloodSys.bloodBoardSoftVer, true);
    initVersionLineEdit(ui->lineEdit_bloodBoard_hardVer, &g_simDa.bloodSys.bloodBoardHardVer, false);
    initVersionLineEdit(ui->lineEdit_vapBoard_softVer, &g_simDa.bloodSys.vapBoardSoftVer, true);
    initVersionLineEdit(ui->lineEdit_vapBoard_hardVer, &g_simDa.bloodSys.vapBoardHardVer, false);
    initVersionLineEdit(ui->lineEdit_bloodPumpBoard_softVer, &g_simDa.bloodSys.bloodPumpBoardSoftVer, true);
    initVersionLineEdit(ui->lineEdit_bloodPumpBoard_hardVer, &g_simDa.bloodSys.bloodPumpBoardHardVer, false);
    initVersionLineEdit(ui->lineEdit_subPumpBoard_softVer, &g_simDa.bloodSys.subPumpBoardSoftVer, true);
    initVersionLineEdit(ui->lineEdit_subPumpBoard_hardVer, &g_simDa.bloodSys.subPumpBoardHardVer, false);

    //默认通讯开关打开
    ui->comSwitchBtn_bloodBoard->setChecked(true);
    ui->comSwitchBtn_bloodPumpBoard->setChecked(true);
    ui->comSwitchBtn_subPumpBoard->setChecked(true);
}

BloodSystemInterface::~BloodSystemInterface()
{
    delete ui;
}

void BloodSystemInterface::initBtnBind()
{
    addBtnBindItem(ui->bloodPumpSwitchBtn, &g_simDa.bloodSys.bloodPumpSW, tr("血泵开关"), tr("关机"), tr("开机"));
    addBtnBindItem(ui->bloodPumpTargetSpeedBtn, &g_simDa.bloodSys.bloodPumpTargetSpeed, tr("血泵目标转速"));
    addBtnBindItem(ui->bloodPumpRealSpeedBtn, &g_simDa.bloodSys.bloodPumpRealSpeed, tr("血泵实时转速"));
    addBtnBindItem(ui->bloodPumpRollsBtn, &g_simDa.bloodSys.bloodPumpRolls, tr("血泵累计转数"));
    addBtnBindItem(ui->bloodPumpDirecBtn, &g_simDa.bloodSys.bloodPumpDirec, tr("血泵方向"), tr("正转"), tr("反转"));
    addBtnBindItem(ui->bloodPumpBlockBtn, &g_simDa.bloodSys.bloodPumpBlock, tr("血泵堵转"), tr("未堵转"), tr("堵转"));
    addBtnBindItem(ui->bloodPumpCoverBtn, &g_simDa.bloodSys.bloodPumpCover, tr("血泵盖"), tr("关"), tr("开"));
    addBtnBindItem(ui->bloodPumpFprBtn, &g_simDa.bloodSys.bloodPumpFpr, tr("血泵泵管系数"));
    addBtnBindItem(ui->subPumpSwitchBtn, &g_simDa.bloodSys.subPumpSwitch, tr("置换液泵开关"), tr("关机"), tr("开机"));
    addBtnBindItem(ui->subPumpTargetSpeedBtn, &g_simDa.bloodSys.subPumpTargetSpeed, tr("置换液泵目标转速"));
    addBtnBindItem(ui->subPumpDirecBtn, &g_simDa.bloodSys.subPumpDirec, tr("置换液泵方向"), tr("正转"), tr("反转"));
    addBtnBindItem(ui->subPumpRealSpeedBtn, &g_simDa.bloodSys.subPumpRealSpeed, tr("置换液泵实时转速"));
    addBtnBindItem(ui->subPumpBlockBtn, &g_simDa.bloodSys.subPumpBlock, tr("置换液泵堵转"), tr("未堵转"), tr("堵转"));
    addBtnBindItem(ui->subPumpRollsBtn, &g_simDa.bloodSys.subPumpRolls, tr("置换液泵累计转数"));
    addBtnBindItem(ui->subPumpCoverBtn, &g_simDa.bloodSys.subPumpCover, tr("置换液泵盖"), tr("关"), tr("开"));
    addBtnBindItem(ui->subPumpFprBtn, &g_simDa.bloodSys.subPumpFpr, tr("置换液泵泵管系数"));
    addBtnBindItem(ui->vpBtn, &g_simDa.bloodSys.vp, tr("静脉压"));
    addBtnBindItem(ui->apBtn, &g_simDa.bloodSys.ap, tr("动脉压"));
    addBtnBindItem(ui->airMonitorBtn, &g_simDa.bloodSys.airMonitor, tr("空气监测"), tr("无"), tr("有"));
    addBtnBindItem(ui->bloodIdBtn, &g_simDa.bloodSys.bloodId, tr("血液识别"), tr("无"), tr("有"));
    addBtnBindItem(ui->chokeClampBtn, &g_simDa.bloodSys.chokeClamp, tr("阻流夹"), tr("关"), tr("开"));
    addBtnBindItem(ui->vpADBtn, &g_simDa.bloodSys.vpAD, tr("静脉压实时AD值"));
    addBtnBindItem(ui->vpZeroADBtn, &g_simDa.bloodSys.vpZeroAD, tr("静脉压零点AD值"));
    addBtnBindItem(ui->vpSlopeADBtn, &g_simDa.bloodSys.vpSlopeAD, tr("静脉压AD斜率值"));
    addBtnBindItem(ui->apADBtn, &g_simDa.bloodSys.apAD, tr("动脉压实时AD值"));
    addBtnBindItem(ui->apZeroADBtn, &g_simDa.bloodSys.apZeroAD, tr("动脉压零点AD值"));
    addBtnBindItem(ui->apSlopeADBtn, &g_simDa.bloodSys.apSlopeAD, tr("动脉压AD斜率值"));
    addBtnBindItem(ui->PAVComBtn, &g_simDa.bloodSys.PAVCom, tr("动静脉压板通信"), tr("正常"), tr("异常"));
}

void BloodSystemInterface::on_comSwitchBtn_bloodBoard_toggled(bool checked)
{
    g_simDa.bloodSys.bloodBoardComSW = checked;
}

void BloodSystemInterface::on_comSwitchBtn_bloodPumpBoard_toggled(bool checked)
{
    g_simDa.bloodSys.bloodPumpBoardComSW = checked;
}

void BloodSystemInterface::on_comSwitchBtn_subPumpBoard_toggled(bool checked)
{
    g_simDa.bloodSys.subPumpBoardComSW = checked;
}
