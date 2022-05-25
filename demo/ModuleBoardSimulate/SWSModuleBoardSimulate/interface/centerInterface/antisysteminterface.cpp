#include "antisysteminterface.h"
#include "ui_antisysteminterface.h"
#include <QRegExpValidator>

AntiSystemInterface::AntiSystemInterface(QWidget *parent) : SystemInterfaceBase(parent), ui(new Ui::AntiSystemInterface)
{
    ui->setupUi(this);

    //初始化版本编辑器
    initVersionLineEdit(ui->lineEdit_hepBoard_softVer, &g_simDa.antiSys.hepBoardSoftVer, true);
    initVersionLineEdit(ui->lineEdit_hepBoard_hardVer, &g_simDa.antiSys.hepBoardHardVer, false);

    //默认通讯开关打开
    ui->comSwitchBtn_hepBoard->setChecked(true);
}

AntiSystemInterface::~AntiSystemInterface()
{
    delete ui;
}

void AntiSystemInterface::initBtnBind()
{
    addBtnBindItem(ui->hepPumpSWBtn, &g_simDa.antiSys.hepPumpSW, tr("肝素泵开关"), tr("关"), tr("开"));
    addBtnBindItem(ui->hepPumpDirecBtn, &g_simDa.antiSys.hepPumpDirec, tr("肝素泵方向"), tr("前进"), tr("后退"));
    addBtnBindItem(ui->hepPumpBlockBtn, &g_simDa.antiSys.hepPumpBlock, tr("肝素泵堵转"), tr("否"), tr("是"));
    addBtnBindItem(ui->injectorSpeciBtn, &g_simDa.antiSys.injectorSpeci, tr("注射器规格"), {"无", "10", "20", "30", "50"});
    addBtnBindItem(ui->arriveBottomBtn, &g_simDa.antiSys.arriveBottom, tr("肝素到底"), tr("否"), tr("是"));
    addBtnBindItem(ui->arriveTopBtn, &g_simDa.antiSys.arriveTop, tr("肝素到顶"), tr("否"), tr("是"));
    addBtnBindItem(ui->hepPlateMoveBtn, &g_simDa.antiSys.hepPlateMove, tr("肝素推板"), tr("正常"), tr("被移动"));
    addBtnBindItem(ui->hepLightBtn, &g_simDa.antiSys.hepLight, tr("光电开关"), tr("正常"), tr("遮挡"));
    addBtnBindItem(ui->hepPumpErrorBtn, &g_simDa.antiSys.hepPumpError, tr("肝素泵故障"), tr("否"), tr("是"));
    addBtnBindItem(ui->hepTargetFlowBtn, &g_simDa.antiSys.hepTargetFlow, tr("肝素目标流量"));
    addBtnBindItem(ui->hepRealFlowBtn, &g_simDa.antiSys.hepRealFlow, tr("肝素实际流量"));
    addBtnBindItem(ui->hepTotalFlowBtn, &g_simDa.antiSys.hepTotalFlow, tr("肝素累计流量"));
}

void AntiSystemInterface::on_comSwitchBtn_hepBoard_toggled(bool checked)
{
    g_simDa.antiSys.hepBoardComSW = checked;
}
