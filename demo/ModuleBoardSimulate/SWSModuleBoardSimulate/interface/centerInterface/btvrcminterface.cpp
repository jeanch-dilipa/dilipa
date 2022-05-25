#include "btvrcminterface.h"
#include "ui_btvrcminterface.h"

BTVRCMInterface::BTVRCMInterface(QWidget *parent) : SystemInterfaceBase(parent), ui(new Ui::BTVRCMInterface)
{
    ui->setupUi(this);

    //初始化版本编辑器
    initVersionLineEdit(ui->lineEdit_btvBoard_softVer, &g_simDa.btvRcm.btvBoardSoftVer, true);
    initVersionLineEdit(ui->lineEdit_btvBoard_hardVer, &g_simDa.btvRcm.btvBoardHardVer, false);
    initVersionLineEdit(ui->lineEdit_rcmBoard_softVer, &g_simDa.btvRcm.rcmBoardSoftVer, true);
    initVersionLineEdit(ui->lineEdit_rcmBoard_hardVer, &g_simDa.btvRcm.rcmBoardHardVer, false);

    //默认通讯开关打开
    ui->comSwitchBtn_btvBoard->setChecked(true);
    ui->comSwitchBtn_rcmBoard->setChecked(true);
}

BTVRCMInterface::~BTVRCMInterface()
{
    delete ui;
}

void BTVRCMInterface::initBtnBind()
{
    addBtnBindItem(ui->VTStatusBtn, &g_simDa.btvRcm.VTStatus, tr("静脉血温传感器状态"), tr("正常"), tr("异常"));
    addBtnBindItem(ui->ATStatusBtn, &g_simDa.btvRcm.ATStatus, tr("动脉血温传感器状态"), tr("正常"), tr("异常"));
    addBtnBindItem(ui->VTBtn, &g_simDa.btvRcm.VT, tr("静脉血温"));
    addBtnBindItem(ui->ATBtn, &g_simDa.btvRcm.AT, tr("动脉血温"));
    addBtnBindItem(ui->BVStatusBtn, &g_simDa.btvRcm.BVStatus, tr("血容量传感器"), tr("正常"), tr("异常"));
    addBtnBindItem(ui->bloodDetectBtn, &g_simDa.btvRcm.bloodDetect, tr("血液"), tr("未检测到"), tr("检测到"));
    addBtnBindItem(ui->BVCoverBtn, &g_simDa.btvRcm.BVCover, tr("监测盖"), tr("关闭"), tr("打开"));
    addBtnBindItem(ui->LEDSWBtn, &g_simDa.btvRcm.LEDSW, tr("近红外LED"), tr("关闭"), tr("打开"));
    addBtnBindItem(ui->BV_VBtn, &g_simDa.btvRcm.BV_V, tr("受光电压"));
    addBtnBindItem(ui->BVBtn, &g_simDa.btvRcm.BV, tr("血容量"));
    addBtnBindItem(ui->BV0Btn, &g_simDa.btvRcm.BV0, tr("初始血容量"));
    addBtnBindItem(ui->RBVBtn, &g_simDa.btvRcm.RBV, tr("相对血容量"));
    addBtnBindItem(ui->RCMCorrectBtn, &g_simDa.btvRcm.RCMCorrect, tr("实时清除率传感器校正"), tr("未校正"), tr("已校正"));
    addBtnBindItem(ui->RCMStatusBtn, &g_simDa.btvRcm.RCMStatus, tr("实时清除率传感器状态"), tr("正常"), tr("异常"));
    addBtnBindItem(ui->RCMDetectBtn, &g_simDa.btvRcm.RCMDetect, tr("实时清除率检测状态"), tr("停止"), tr("正在检测"));
    addBtnBindItem(ui->absBtn, &g_simDa.btvRcm.abs, tr("吸光度"));
}

void BTVRCMInterface::on_comSwitchBtn_btvBoard_toggled(bool checked)
{
    g_simDa.btvRcm.btvBoardComSW = checked;
}

void BTVRCMInterface::on_comSwitchBtn_rcmBoard_toggled(bool checked)
{
    g_simDa.btvRcm.rcmBoardComSW = checked;
}
