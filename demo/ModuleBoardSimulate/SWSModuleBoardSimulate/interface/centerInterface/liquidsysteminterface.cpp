#include "liquidsysteminterface.h"
#include "ui_liquidsysteminterface.h"
#include "uart/uart485.h"
#include <QRegExpValidator>

LiquidSystemInterface::LiquidSystemInterface(QWidget *parent) : SystemInterfaceBase(parent), ui(new Ui::LiquidSystemInterface)
{
    ui->setupUi(this);
    ui->lastPageBtn->setDisabled(true);
    ui->stackedWidget->setCurrentIndex(0);

    //初始化版本显示窗口
    initVerStackedWidget(ui->stackedWidget_ver);

    //初始化版本输入框
    initVersionLineEdit(ui->lineEdit_liquidBoard_softVer, &g_simDa.liquidSys.liquidBoardSoftVer, true);
    initVersionLineEdit(ui->lineEdit_liquidBoard_hardVer,  &g_simDa.liquidSys.liquidBoardHardVer, false);
    initVersionLineEdit(ui->lineEdit_liquidPreBoard_softVer, &g_simDa.liquidSys.liquidPreBoardSoftVer, true);
    initVersionLineEdit(ui->lineEdit_liquidPreBoard_hardVer, &g_simDa.liquidSys.liquidPreBoardHardVer, false);
    initVersionLineEdit(ui->lineEdit_driveBoard_softVer, &g_simDa.liquidSys.driveBoardSoftVer, true);
    initVersionLineEdit(ui->lineEdit_driveBoard_hardVer, &g_simDa.liquidSys.driveBoardHardVer, false);
    initVersionLineEdit(ui->lineEdit_balanceBoard_softVer, &g_simDa.liquidSys.balanceBoardSoftVer, true);
    initVersionLineEdit(ui->lineEdit_balanceBoard_hardVer, &g_simDa.liquidSys.balanceBoardHardVer, false);
    initVersionLineEdit(ui->lineEdit_heatBoard_softVer, &g_simDa.liquidSys.heatBoardSoftVer, true);
    initVersionLineEdit(ui->lineEdit_heatBoard_hardVer, &g_simDa.liquidSys.heatBoardHardVer, false);

    //默认通讯打开
    ui->comSwitchBtn_liquidBoard->setChecked(true);
    ui->comSwitchBtn_driveBoard->setChecked(true);
    ui->comSwitchBtn_balanceBoard->setChecked(true);
    ui->comSwitchBtn_heatBoard->setChecked(true);
}

LiquidSystemInterface::~LiquidSystemInterface()
{
    delete ui;
}

void LiquidSystemInterface::initBtnBind()
{
    //传感器值
    addBtnBindItem(ui->wg1Btn, &g_simDa.liquidSys.WG1, tr("WG1"));
    addBtnBindItem(ui->wg5Btn, &g_simDa.liquidSys.WG5, tr("WG5"));
    addBtnBindItem(ui->wg6Btn, &g_simDa.liquidSys.WG6, tr("WG6"));
    addBtnBindItem(ui->yg1Btn, &g_simDa.liquidSys.YG1, tr("YG1"));
    addBtnBindItem(ui->yg2Btn, &g_simDa.liquidSys.YG2, tr("YG2"));
    addBtnBindItem(ui->yg3Btn, &g_simDa.liquidSys.YG3, tr("YG3"));
    addBtnBindItem(ui->yg4Btn, &g_simDa.liquidSys.YG4, tr("YG4"));
    addBtnBindItem(ui->diaFlowBtn, &g_simDa.liquidSys.diaFlow, tr("透析液流量"));
    addBtnBindItem(ui->DPSpeedBtn, &g_simDa.liquidSys.DPSpeed, tr("DP转速"));
    addBtnBindItem(ui->YPSpeedBtn, &g_simDa.liquidSys.YPSpeed, tr("YP转速"));
    addBtnBindItem(ui->QPSpeedBtn, &g_simDa.liquidSys.QPSpeed, tr("QP转速"));
    addBtnBindItem(ui->DPTimeBtn, &g_simDa.liquidSys.DPTime, tr("DP推膜时间"));
    addBtnBindItem(ui->YPTimeBtn, &g_simDa.liquidSys.YPTime, tr("YP推膜时间"));
    addBtnBindItem(ui->yg2HighBtn, &g_simDa.liquidSys.YG2High, tr("进液高压"));
    addBtnBindItem(ui->yg2LowBtn, &g_simDa.liquidSys.YG2Low, tr("进液低压"));
    addBtnBindItem(ui->yg4HighBtn, &g_simDa.liquidSys.YG4High, tr("废液高压"));
    addBtnBindItem(ui->yg4LowBtn, &g_simDa.liquidSys.YG4Low, tr("废液低压"));

    //传感器状态
    addBtnBindItem(ui->balanceBtn, &g_simDa.liquidSys.balanceSW, tr("平衡腔"), tr("停止"), tr("运行"));
    addBtnBindItem(ui->heatBtn, &g_simDa.liquidSys.heatSW, tr("加热"), tr("关"), tr("开"));
    addBtnBindItem(ui->heatForceOffBtn, &g_simDa.liquidSys.heatForceOff, tr("加热强关"), tr("否"), tr("是"));
    addBtnBindItem(ui->heatDutyFactorBtn, &g_simDa.liquidSys.heatDutyFactor, tr("加热占空比"), tr("否"), tr("是"));
    addBtnBindItem(ui->YKBtn, &g_simDa.liquidSys.YK, tr("YK"), tr("闭合"), tr("断开"));
    addBtnBindItem(ui->YJ1Btn, &g_simDa.liquidSys.YJ1, tr("YJ1"), tr("闭合"), tr("断开"));
    addBtnBindItem(ui->YJ2Btn, &g_simDa.liquidSys.YJ2, tr("YJ2"), tr("闭合"), tr("断开"));
    addBtnBindItem(ui->YJ3Btn, &g_simDa.liquidSys.YJ3, tr("YJ3"), tr("闭合"), tr("断开"));
    addBtnBindItem(ui->YJ4Btn, &g_simDa.liquidSys.YJ4, tr("YJ4"), tr("闭合"), tr("断开"));
    addBtnBindItem(ui->YJ5Btn, &g_simDa.liquidSys.YJ5, tr("YJ5"), tr("闭合"), tr("断开"));
    addBtnBindItem(ui->leftSubJointBtn, &g_simDa.liquidSys.leftSubJoint, tr("左补液接头"), tr("闭合"), tr("断开"));
    addBtnBindItem(ui->rightSubJointBtn, &g_simDa.liquidSys.rightSubJoint, tr("右补液接头"), tr("闭合"), tr("断开"));
    addBtnBindItem(ui->AStrawBtn, &g_simDa.liquidSys.AStraw, tr("A液吸管"), tr("闭合"), tr("断开"));
    addBtnBindItem(ui->BStrawBtn, &g_simDa.liquidSys.BStraw, tr("B液吸管"), tr("闭合"), tr("断开"));
    addBtnBindItem(ui->diaJointRedBtn, &g_simDa.liquidSys.diaJointRed, tr("透析器接头红"), tr("闭合"), tr("断开"));
    addBtnBindItem(ui->diaJointBlueBtn, &g_simDa.liquidSys.diaJointBlue, tr("透析器接头蓝"), tr("闭合"), tr("断开"));

    //电磁阀状态
    addBtnBindItem(ui->v1Btn, &g_simDa.liquidSys.V[1], tr("V1"), tr("关"), tr("开"));
    addBtnBindItem(ui->v2Btn, &g_simDa.liquidSys.V[2], tr("V2"), tr("关"), tr("开"));
    addBtnBindItem(ui->v3Btn, &g_simDa.liquidSys.V[3], tr("V3"), tr("关"), tr("开"));
    addBtnBindItem(ui->v4Btn, &g_simDa.liquidSys.V[4], tr("V4"), tr("关"), tr("开"));
    addBtnBindItem(ui->v5Btn, &g_simDa.liquidSys.V[5], tr("V5"), tr("关"), tr("开"));
    addBtnBindItem(ui->v6Btn, &g_simDa.liquidSys.V[6], tr("V6"), tr("关"), tr("开"));
    addBtnBindItem(ui->v7Btn, &g_simDa.liquidSys.V[7], tr("V7"), tr("关"), tr("开"));
    addBtnBindItem(ui->v8Btn, &g_simDa.liquidSys.V[8], tr("V8"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv1Btn, &g_simDa.liquidSys.SV[1], tr("SV1"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv2Btn, &g_simDa.liquidSys.SV[2], tr("SV2"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv3Btn, &g_simDa.liquidSys.SV[3], tr("SV3"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv4Btn, &g_simDa.liquidSys.SV[4], tr("SV4"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv5Btn, &g_simDa.liquidSys.SV[5], tr("SV5"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv6Btn, &g_simDa.liquidSys.SV[6], tr("SV6"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv7Btn, &g_simDa.liquidSys.SV[7], tr("SV7"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv8Btn, &g_simDa.liquidSys.SV[8], tr("SV8"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv9Btn, &g_simDa.liquidSys.SV[9], tr("SV9"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv10Btn, &g_simDa.liquidSys.SV[10], tr("SV10"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv11Btn, &g_simDa.liquidSys.SV[11], tr("SV11"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv12Btn, &g_simDa.liquidSys.SV[12], tr("SV12"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv13Btn, &g_simDa.liquidSys.SV[13], tr("SV13"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv14Btn, &g_simDa.liquidSys.SV[14], tr("SV14"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv15Btn, &g_simDa.liquidSys.SV[15], tr("SV15"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv16Btn, &g_simDa.liquidSys.SV[16], tr("SV16"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv17Btn, &g_simDa.liquidSys.SV[17], tr("SV17"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv18Btn, &g_simDa.liquidSys.SV[18], tr("SV18"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv19Btn, &g_simDa.liquidSys.SV[19], tr("SV19"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv20Btn, &g_simDa.liquidSys.SV[20], tr("SV20"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv21Btn, &g_simDa.liquidSys.SV[21], tr("SV21"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv22Btn, &g_simDa.liquidSys.SV[22], tr("SV22"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv23Btn, &g_simDa.liquidSys.SV[23], tr("SV23"), tr("关"), tr("开"));
    addBtnBindItem(ui->sv24Btn, &g_simDa.liquidSys.SV[24], tr("SV24"), tr("关"), tr("开"));

    //报警
    addBtnBindItem(ui->waterSupplyBtn, &g_simDa.liquidSys.waterSupply, tr("供水"), tr("正常"), tr("不足"));
    addBtnBindItem(ui->inletWaterLevelBtn, &g_simDa.liquidSys.inletWaterLevel, tr("进水位长时间无变化"), tr("正常"), tr("异常"));
    addBtnBindItem(ui->airBtn, &g_simDa.liquidSys.air, tr("透析液空气"), tr("正常"), tr("过多"));
    addBtnBindItem(ui->YG2LowPreTooHighBtn, &g_simDa.liquidSys.YG2LowPreTooHigh, tr("进液低压"), tr("正常"), tr("过高"));
    addBtnBindItem(ui->YG4LowPreTooHighBtn, &g_simDa.liquidSys.YG4LowPreTooHigh, tr("废液低压"), tr("正常"), tr("过高"));
    addBtnBindItem(ui->bloodLeakBtn, &g_simDa.liquidSys.bloodLeak, tr("漏血"), tr("正常"), tr("漏血"));
    addBtnBindItem(ui->fluidLeak1Btn, &g_simDa.liquidSys.fluidLeak1, tr("漏液传感器1"), tr("正常"), tr("漏液"));
    addBtnBindItem(ui->fluidLeak2Btn, &g_simDa.liquidSys.fluidLeak2, tr("漏液传感器2"), tr("正常"), tr("漏液"));
    addBtnBindItem(ui->yg1OutLimitBtn, &g_simDa.liquidSys.yg1OutLimit, tr("进液压"), tr("正常"), tr("超限"));
    addBtnBindItem(ui->yg4OutLimitBtn, &g_simDa.liquidSys.yg4OutLimit, tr("废液压"), tr("正常"), tr("超限"));
    addBtnBindItem(ui->QPSpeedErrorBtn, &g_simDa.liquidSys.QPSpeedError, tr("QP转速"), tr("正常"), tr("异常"));
    addBtnBindItem(ui->DPSpeedErrorBtn, &g_simDa.liquidSys.DPSpeedError, tr("DP转速"), tr("正常"), tr("异常"));
    addBtnBindItem(ui->YPSpeedErrorBtn, &g_simDa.liquidSys.YPSpeedError, tr("YP转速"), tr("正常"), tr("异常"));
    addBtnBindItem(ui->M1LeakBtn, &g_simDa.liquidSys.M1Leak, tr("膜片M1"), tr("正常"), tr("泄漏"));
    addBtnBindItem(ui->M2LeakBtn, &g_simDa.liquidSys.M2Leak, tr("膜片M2"), tr("正常"), tr("泄漏"));
    addBtnBindItem(ui->V1V7LeakBtn, &g_simDa.liquidSys.V1V7Leak, tr("V1/V7"), tr("正常"), tr("泄漏"));
    addBtnBindItem(ui->V2V8LeakBtn, &g_simDa.liquidSys.V2V8Leak, tr("V2/V8"), tr("正常"), tr("泄漏"));
    addBtnBindItem(ui->V3V5LeakBtn, &g_simDa.liquidSys.V3V5Leak, tr("V3/V5"), tr("正常"), tr("泄漏"));
    addBtnBindItem(ui->V4V6LeakBtn, &g_simDa.liquidSys.V4V6Leak, tr("V4/V6"), tr("正常"), tr("泄漏"));
    addBtnBindItem(ui->SV13LeakBtn, &g_simDa.liquidSys.SV13Leak, tr("SV13"), tr("正常"), tr("泄漏"));
    addBtnBindItem(ui->SV14LeakBtn, &g_simDa.liquidSys.SV14Leak, tr("SV14"), tr("正常"), tr("泄漏"));
    addBtnBindItem(ui->YG2DataErrorBtn, &g_simDa.liquidSys.YG2DataError, tr("YG2数据"), tr("正常"), tr("异常"));
    addBtnBindItem(ui->YG4DataErrorBtn, &g_simDa.liquidSys.YG4DataError, tr("YG4数据"), tr("正常"), tr("异常"));
    addBtnBindItem(ui->YG13ComBtn, &g_simDa.liquidSys.YG13Com, tr("压力板通信"), tr("正常"), tr("异常"));
    addBtnBindItem(ui->diaTempSensorBtn, &g_simDa.liquidSys.diaTempSensor, tr("透析液温度传感器"), tr("正常"), tr("异常"));
    addBtnBindItem(ui->heatTempSensorBtn, &g_simDa.liquidSys.heatTempSensor, tr("加热温度传感器"), tr("正常"), tr("异常"));
}

void LiquidSystemInterface::on_lastPageBtn_clicked()
{
    int index = ui->stackedWidget->currentIndex() - 1;
    if(index < 0)
    {
        index = 0;
    }

    ui->stackedWidget->setCurrentIndex(index);
    judgePageBtnEnable();
}

void LiquidSystemInterface::on_nextPageBtn_clicked()
{
    int index = ui->stackedWidget->currentIndex() + 1;
    if(index >= ui->stackedWidget->count())
    {
        index = ui->stackedWidget->count()-1;
    }

    ui->stackedWidget->setCurrentIndex(index);
    judgePageBtnEnable();
}

void LiquidSystemInterface::judgePageBtnEnable()
{
    if(ui->stackedWidget->currentIndex() == 0)
    {
        ui->lastPageBtn->setEnabled(false);
        ui->nextPageBtn->setEnabled(true);
    }
    else if(ui->stackedWidget->currentIndex() == (ui->stackedWidget->count() - 1))
    {
        ui->lastPageBtn->setEnabled(true);
        ui->nextPageBtn->setEnabled(false);
    }
    else
    {
        ui->lastPageBtn->setEnabled(true);
        ui->nextPageBtn->setEnabled(true);
    }
}

void LiquidSystemInterface::on_comSwitchBtn_liquidBoard_toggled(bool checked)
{
    g_simDa.liquidSys.liquidBoardComSW = checked;
}

void LiquidSystemInterface::on_comSwitchBtn_driveBoard_toggled(bool checked)
{
    g_simDa.liquidSys.driveBoardComSW = checked;
}

void LiquidSystemInterface::on_comSwitchBtn_balanceBoard_toggled(bool checked)
{
    g_simDa.liquidSys.balanceBoardComSW = checked;
}

void LiquidSystemInterface::on_comSwitchBtn_heatBoard_toggled(bool checked)
{
    g_simDa.liquidSys.heatBoardComSW = checked;
}
