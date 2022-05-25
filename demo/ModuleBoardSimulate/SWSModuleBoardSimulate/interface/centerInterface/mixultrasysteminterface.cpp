#include "mixultrasysteminterface.h"
#include "ui_mixultrasysteminterface.h"
#include <QRegExpValidator>

MixUltraSystemInterface::MixUltraSystemInterface(QWidget *parent) : SystemInterfaceBase(parent), ui(new Ui::MixUltraSystemInterface)
{
    ui->setupUi(this);

    //初始化版本显示窗口
    initVerStackedWidget(ui->stackedWidget_ver);

    //初始化版本输入框
    initVersionLineEdit(ui->lineEdit_mixUfBoard_softVer, &g_simDa.mixUltraSys.mixUfBoardSoftVer, true);
    initVersionLineEdit(ui->lineEdit_mixUfBoard_hardVer, &g_simDa.mixUltraSys.mixUfBoardHardVer, false);
    initVersionLineEdit(ui->lineEdit_mixBoard_softVer, &g_simDa.mixUltraSys.mixBoardSoftVer, true);
    initVersionLineEdit(ui->lineEdit_mixBoard_hardVer, &g_simDa.mixUltraSys.mixBoardHardVer, false);
    initVersionLineEdit(ui->lineEdit_ufBoard_softVer, &g_simDa.mixUltraSys.ufBoardSoftVer, true);
    initVersionLineEdit(ui->lineEdit_ufBoard_hardVer, &g_simDa.mixUltraSys.ufBoardHardVer, false);
    initVersionLineEdit(ui->lineEdit_condBoard_softVer, &g_simDa.mixUltraSys.condBoardSoftVer, true);
    initVersionLineEdit(ui->lineEdit_condBoard_hardVer, &g_simDa.mixUltraSys.condBoardHardVer, false);

    //默认通讯开关打开
    ui->comSwitchBtn_mixUfBoard->setChecked(true);
    ui->comSwitchBtn_mixBoard->setChecked(true);
    ui->comSwitchBtn_ufBoard->setChecked(true);
    ui->comSwitchBtn_condBoard->setChecked(true);
}

MixUltraSystemInterface::~MixUltraSystemInterface()
{
    delete ui;
}

void MixUltraSystemInterface::initBtnBind()
{
    addBtnBindItem(ui->mixSWBtn, &g_simDa.mixUltraSys.mixSW, tr("配液开关"), tr("关"), tr("开"));
    addBtnBindItem(ui->BCondBtn, &g_simDa.mixUltraSys.BCond, tr("B电导"));
    addBtnBindItem(ui->ACondBtn, &g_simDa.mixUltraSys.ACond, tr("A电导"));
    addBtnBindItem(ui->CCondBtn, &g_simDa.mixUltraSys.CCond, tr("C电导"));
    addBtnBindItem(ui->adjustRangeBtn, &g_simDa.mixUltraSys.adjustRange, tr("配液调整范围"));
    addBtnBindItem(ui->wg2Btn, &g_simDa.mixUltraSys.WG2, tr("WG2"));
    addBtnBindItem(ui->wg3Btn, &g_simDa.mixUltraSys.WG3, tr("WG3"));
    addBtnBindItem(ui->wg4Btn, &g_simDa.mixUltraSys.WG4, tr("WG4"));
    addBtnBindItem(ui->APumpSWBtn, &g_simDa.mixUltraSys.APumpSW, tr("A泵开关"), tr("关"), tr("开"));
    addBtnBindItem(ui->APumpDirecBtn, &g_simDa.mixUltraSys.APumpDirec, tr("A泵方向"), tr("正转"), tr("反转"));
    addBtnBindItem(ui->APumpBlockBtn, &g_simDa.mixUltraSys.APumpBlock, tr("A泵堵转"), tr("正常"), tr("堵转"));
    addBtnBindItem(ui->APumpPhaseLossBtn, &g_simDa.mixUltraSys.APumpPhaseLoss, tr("A泵缺相"), tr("正常"), tr("缺相"));
    addBtnBindItem(ui->APumpTargetSpeedBtn, &g_simDa.mixUltraSys.APumpTargetSpeed, tr("A泵目标转速"));
    addBtnBindItem(ui->APumpRealSpeedBtn, &g_simDa.mixUltraSys.APumpRealSpeed, tr("A泵实际转速"));
    addBtnBindItem(ui->APumpRollsBtn, &g_simDa.mixUltraSys.APumpRolls, tr("A泵累计转数"));
    addBtnBindItem(ui->BPumpSWBtn, &g_simDa.mixUltraSys.BPumpSW, tr("B泵开关"), tr("关"), tr("开"));
    addBtnBindItem(ui->BPumpDirecBtn, &g_simDa.mixUltraSys.BPumpDirec, tr("B泵方向"), tr("正转"), tr("反转"));
    addBtnBindItem(ui->BPumpBlockBtn, &g_simDa.mixUltraSys.BPumpBlock, tr("B泵堵转"), tr("正常"), tr("堵转"));
    addBtnBindItem(ui->BPumpPhaseLossBtn, &g_simDa.mixUltraSys.BPumpPhaseLoss, tr("B泵缺相"), tr("正常"), tr("缺相"));
    addBtnBindItem(ui->BPumpTargetSpeedBtn, &g_simDa.mixUltraSys.BPumpTargetSpeed, tr("B泵目标转速"));
    addBtnBindItem(ui->BPumpRealSpeedBtn, &g_simDa.mixUltraSys.BPumpRealSpeed, tr("B泵实际转速"));
    addBtnBindItem(ui->BPumpRollsBtn, &g_simDa.mixUltraSys.BPumpRolls, tr("B泵累计转数"));
    addBtnBindItem(ui->ufPumpSWBtn, &g_simDa.mixUltraSys.ufPumpSW, tr("超滤泵开关"), tr("关"), tr("开"));
    addBtnBindItem(ui->ufPumpDirecBtn, &g_simDa.mixUltraSys.ufPumpDirec, tr("超滤泵方向"), tr("正转"), tr("反转"));
    addBtnBindItem(ui->ufPumpBlockBtn, &g_simDa.mixUltraSys.ufPumpBlock, tr("超滤泵堵转"), tr("正常"), tr("堵转"));
    addBtnBindItem(ui->ufPumpPhaseLossBtn, &g_simDa.mixUltraSys.ufPumpPhaseLoss, tr("超滤泵缺相"), tr("正常"), tr("缺相"));
    addBtnBindItem(ui->ufPumpTargetSpeedBtn, &g_simDa.mixUltraSys.ufPumpTargetSpeed, tr("超滤泵目标转速"));
    addBtnBindItem(ui->ufPumpRealSpeedBtn, &g_simDa.mixUltraSys.ufPumpRealSpeed, tr("超滤泵实际转速"));
    addBtnBindItem(ui->ufPumpRollsBtn, &g_simDa.mixUltraSys.ufPumpRolls, tr("超滤泵累计转数"));
}

void MixUltraSystemInterface::on_comSwitchBtn_mixUfBoard_toggled(bool checked)
{
    g_simDa.mixUltraSys.mixUfBoardComSW = checked;
}

void MixUltraSystemInterface::on_comSwitchBtn_mixBoard_toggled(bool checked)
{
    g_simDa.mixUltraSys.mixBoardComSW = checked;
}

void MixUltraSystemInterface::on_comSwitchBtn_ufBoard_toggled(bool checked)
{
    g_simDa.mixUltraSys.ufBoardComSW = checked;
}

void MixUltraSystemInterface::on_comSwitchBtn_condBoard_toggled(bool checked)
{
    g_simDa.mixUltraSys.condBoardComSW = checked;
}
