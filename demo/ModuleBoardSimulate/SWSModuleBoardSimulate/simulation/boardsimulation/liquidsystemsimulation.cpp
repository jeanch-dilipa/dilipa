#include "liquidsystemsimulation.h"

#define LOAD_SET_DATA_TIME  500  /*装载设置数据周期 ms*/
#define DP_FPR              3    /*DP流量转速比*/
#define YP_FPR              3    /*YP流量转速比*/
#define BALANCE_VOLUME      95.0 /*默认平衡腔容积*/

LiquidSystemSimulation::LiquidSystemSimulation(QObject *parent) : BoardSimulationBase(parent)
{
    m_multiUseTimer = new QTimer(this);
    connect(m_multiUseTimer, &QTimer::timeout, this, &LiquidSystemSimulation::slotMultiUseTimerTimeout);
    m_multiUseTimer->start(1000);
}

LiquidSystemSimulation::~LiquidSystemSimulation()
{
}

void LiquidSystemSimulation::recvWriteCmd4000(ModuleBoardAddrType addr, SystemBusCommandType cmd, const QByteArray &data)
{
    if(addr == DRIVER_BOARD_ADDR4)
    {   //驱动板
        ///todo 待写
    }
    else if(addr == BALANCE_CHAMBER_BOARD_ADDR4)
    {   //平衡腔板
        switch(cmd)
        {
        case WRITE_COMMAND_0: //平衡腔开关及流量控制命令
            memcpy(&g_mbd.md4.balance.wr0, data.data(), sizeof(g_mbd.md4.balance.wr0));
            break;
        case WRITE_COMMAND_1: //平衡腔电磁阀及齿轮泵控制命令
            memcpy(&g_mbd.md4.balance.wr1, data.data(), sizeof(g_mbd.md4.balance.wr1));
            break;
        case WRITE_COMMAND_2: //压力校正命令
            memcpy(&g_mbd.md4.balance.wr2, data.data(), sizeof(g_mbd.md4.balance.wr2));
            break;
        case WRITE_COMMAND_3: //齿轮泵方向及SV14控制命令
            memcpy(&g_mbd.md4.balance.wr3, data.data(), sizeof(g_mbd.md4.balance.wr3));
            break;
        case WRITE_COMMAND_9: //升级命令
            ///预留
            break;
        default:
            break;
        }
    }
    else if(addr == HEATER_BOARD_ADDR4)
    {   //加热板
        switch(cmd)
        {
        case WRITE_COMMAND_0: //加热控制命令
            memcpy(&g_mbd.md4.heat.wr0, data.data(), sizeof(g_mbd.md4.heat.wr0));
            break;
        case WRITE_COMMAND_1: //温度补偿
            memcpy(&g_mbd.md4.heat.wr1, data.data(), sizeof(g_mbd.md4.heat.wr1));
            break;
        default:
            break;
        }
    }
}

void LiquidSystemSimulation::recvWriteCmd6000(ModuleBoardAddrType /*addr*/, SystemBusCommandType cmd, const QByteArray &data)
{
    switch(cmd)
    {
    case WRITE_COMMAND_0: //水路控制命令
        memcpy(&g_mbd.md6.ldd.wr0, data.data(), sizeof(g_mbd.md6.ldd.wr0));
        break;
    case WRITE_COMMAND_1: //加热控制命令
        memcpy(&g_mbd.md6.ldd.wr1, data.data(), sizeof(g_mbd.md6.ldd.wr1));
        break;
    case WRITE_COMMAND_2: //温度校正命令
        ///预留
        break;
    case WRITE_COMMAND_3: //液压传感器校正命令
        ///预留
        break;
    case WRITE_COMMAND_9: //升级命令信息
        ///预留
        break;
    default:
        break;
    }
}

void LiquidSystemSimulation::slotMultiUseTimerTimeout()
{
    //模拟YJ1开关
    if(g_simDa.liquidSys.YJ1.set.mode == AutoSimMode)
    {
        m_simYJ1OnOffTime++;
        if(m_simYJ1OnOffTime > 3)
        {
            m_simYJ1OnOffTime = 0;
            g_simDa.liquidSys.YJ1.value = !g_simDa.liquidSys.YJ1.value;
        }
    }

    //模拟V1~V8切换
    if((bool)g_simDa.liquidSys.balanceSW.value)
    {   //平衡腔打开才切换
        int changeMaxTime = g_simDa.liquidSys.DPTime.value;
        if(changeMaxTime < g_simDa.liquidSys.YPTime.value)
        {   //取较大的时间
            changeMaxTime = g_simDa.liquidSys.YPTime.value;
        }
        if(changeMaxTime < 2)
        {
            changeMaxTime = 2;
        }
        if(changeMaxTime > 90)
        {
            changeMaxTime = 90;
        }
        if(++m_V1_V8ChangeTime >= changeMaxTime)
        {   //到达切换时间
            m_V1_V8ChangeTime = 0;
            if(tempV1_V8Sim == 0x69)
            {
                tempV1_V8Sim = 0x96; //切换到2、3、5、8阶段
            }
            else
            {
                tempV1_V8Sim = 0x69; //切换到1、4、6、7阶段
            }
        }
    }
    else
    {
        tempV1_V8Sim = 0x00; //全关
    }
}

void LiquidSystemSimulation::initSimData()
{
    //设置模拟数据类型
    addSimDataInit(C_WG1, &g_simDa.liquidSys.WG1, NumericValue, 2);                     //WG1值
    addSimDataInit(C_WG5, &g_simDa.liquidSys.WG5, NumericValueWithAutoRange, 2);        //WG5值
    addSimDataInit(C_WG6, &g_simDa.liquidSys.WG6, NumericValueWithAutoRange, 2);        //WG6值
    addSimDataInit(C_YG1, &g_simDa.liquidSys.YG1, NumericValue, 1);                     //YG1
    addSimDataInit(C_YG2, &g_simDa.liquidSys.YG2, NumericValue, 1);                     //YG2
    addSimDataInit(C_YG3, &g_simDa.liquidSys.YG3, NumericValue, 1);                     //YG3
    addSimDataInit(C_YG4, &g_simDa.liquidSys.YG4, NumericValue, 1);                     //YG4
    addSimDataInit(C_DiaFlow, &g_simDa.liquidSys.diaFlow, NumericValueWithAutoRange);   //透析液流量
    addSimDataInit(C_DPSpeed, &g_simDa.liquidSys.DPSpeed, NumericValueWithAutoRange);   //DP转速
    addSimDataInit(C_YPSpeed, &g_simDa.liquidSys.YPSpeed, NumericValueWithAutoRange);   //YP转速
    addSimDataInit(C_QPSpeed, &g_simDa.liquidSys.QPSpeed, NumericValueWithAutoRange);   //QP转速
    addSimDataInit(C_DPTime, &g_simDa.liquidSys.DPTime, NumericValueWithAuto, 1);       //DP推膜时间
    addSimDataInit(C_YPTime, &g_simDa.liquidSys.YPTime, NumericValueWithAuto, 1);       //YP推膜时间
    addSimDataInit(C_YG2High, &g_simDa.liquidSys.YG2High, NumericValueWithAuto, 1);     //进液高压
    addSimDataInit(C_YG2Low, &g_simDa.liquidSys.YG2Low, NumericValueWithAuto, 1);       //进液低压
    addSimDataInit(C_YG4High, &g_simDa.liquidSys.YG4High, NumericValueWithAuto, 1);     //废液高压
    addSimDataInit(C_YG4Low, &g_simDa.liquidSys.YG4Low, NumericValueWithAuto, 1);       //废液低压

    addSimDataInit(C_BalanceSW, &g_simDa.liquidSys.balanceSW, BinaryValueWithAuto);     //平衡腔开关
    addSimDataInit(C_HeatSW, &g_simDa.liquidSys.heatSW, BinaryValueWithAuto);           //加热开关
    addSimDataInit(C_HeatForceOff, &g_simDa.liquidSys.heatForceOff, BinaryValue);       //加热强关
    addSimDataInit(C_HeatDutyFactor, &g_simDa.liquidSys.heatDutyFactor, NumericValue);  //加热占空比
    addSimDataInit(C_YK, &g_simDa.liquidSys.YK, BinaryValue);                           //YK
    addSimDataInit(C_YJ1, &g_simDa.liquidSys.YJ1, BinaryValueWithAuto);                 //YJ1
    addSimDataInit(C_YJ2, &g_simDa.liquidSys.YJ2, BinaryValue);                         //YJ2
    addSimDataInit(C_YJ3, &g_simDa.liquidSys.YJ3, BinaryValue);                         //YJ3
    addSimDataInit(C_YJ4, &g_simDa.liquidSys.YJ4, BinaryValue);                         //YJ4
    addSimDataInit(C_YJ5, &g_simDa.liquidSys.YJ5, BinaryValue);                         //YJ5
    addSimDataInit(C_LeftSubJoint, &g_simDa.liquidSys.leftSubJoint, BinaryValue);       //左补液接头
    addSimDataInit(C_RightSubJoint, &g_simDa.liquidSys.rightSubJoint, BinaryValue);     //右补液接头
    addSimDataInit(C_AStraw, &g_simDa.liquidSys.AStraw, BinaryValue);                   //A液吸管
    addSimDataInit(C_BStraw, &g_simDa.liquidSys.BStraw, BinaryValue);                   //B液吸管
    addSimDataInit(C_DiaJointRed, &g_simDa.liquidSys.diaJointRed, BinaryValue);         //红色透析器接头
    addSimDataInit(C_DiaJointBlue, &g_simDa.liquidSys.diaJointBlue, BinaryValue);       //蓝色透析器接头
    for(int i = 1; i <= 8; i++)
    {
        addSimDataInit(SimDataCode(C_V1+i-1), &g_simDa.liquidSys.V[i], BinaryValueWithAuto);   //V1~V8
    }
    for(int i = 1; i <= 24; i++)
    {
        addSimDataInit(SimDataCode(C_SV1+i-1), &g_simDa.liquidSys.SV[i], BinaryValueWithAuto); //SV1~SV8
    }

    addSimDataInit(C_WaterSupply, &g_simDa.liquidSys.waterSupply, BinaryValue);         //供水
    addSimDataInit(C_InletWaterLevel, &g_simDa.liquidSys.inletWaterLevel, BinaryValue); //进水位长时间无变化
    addSimDataInit(C_DiaAir, &g_simDa.liquidSys.air, BinaryValue);                      //透析液空气过多
    addSimDataInit(C_YG4LowPre, &g_simDa.liquidSys.YG4LowPreTooHigh, BinaryValue);      //废液压低压高
    addSimDataInit(C_YG2LowPre, &g_simDa.liquidSys.YG2LowPreTooHigh, BinaryValue);      //进液压低压高
    addSimDataInit(C_BloodLeak, &g_simDa.liquidSys.bloodLeak, BinaryValue);             //漏血
    addSimDataInit(C_FluidLeak1, &g_simDa.liquidSys.fluidLeak1, BinaryValue);           //漏液传感器1
    addSimDataInit(C_FluidLeak2, &g_simDa.liquidSys.fluidLeak2, BinaryValue);           //漏液传感器2
    addSimDataInit(C_YG1OutLimit, &g_simDa.liquidSys.yg1OutLimit, BinaryValue);         //进液压
    addSimDataInit(C_YG4OutLimit, &g_simDa.liquidSys.yg4OutLimit, BinaryValue);         //废液压
    addSimDataInit(C_QPSpeedError, &g_simDa.liquidSys.QPSpeedError, BinaryValue);       //QP转速异常
    addSimDataInit(C_DPSpeedError, &g_simDa.liquidSys.DPSpeedError, BinaryValue);       //DP转速异常
    addSimDataInit(C_YPSpeedError, &g_simDa.liquidSys.YPSpeedError, BinaryValue);       //YP转速异常
    addSimDataInit(C_M1Leak, &g_simDa.liquidSys.M1Leak, BinaryValue);                   //膜片M1泄漏
    addSimDataInit(C_M2Leak, &g_simDa.liquidSys.M2Leak, BinaryValue);                   //膜片M2泄漏
    addSimDataInit(C_V1V7Leak, &g_simDa.liquidSys.V1V7Leak, BinaryValue);               //V1/V7泄漏
    addSimDataInit(C_V2V8Leak, &g_simDa.liquidSys.V2V8Leak, BinaryValue);               //V2/V8泄漏
    addSimDataInit(C_V3V5Leak, &g_simDa.liquidSys.V3V5Leak, BinaryValue);               //V3/V5泄漏
    addSimDataInit(C_V4V6Leak, &g_simDa.liquidSys.V4V6Leak, BinaryValue);               //V4/V6泄漏
    addSimDataInit(C_SV13Leak, &g_simDa.liquidSys.SV13Leak, BinaryValue);               //SV13泄漏
    addSimDataInit(C_SV14Leak, &g_simDa.liquidSys.SV14Leak, BinaryValue);               //SV14泄漏
    addSimDataInit(C_YG2DataError, &g_simDa.liquidSys.YG2DataError, BinaryValue);       //YG2数据异常
    addSimDataInit(C_YG4DataError, &g_simDa.liquidSys.YG4DataError, BinaryValue);       //YG4数据异常
    addSimDataInit(C_YG13Com, &g_simDa.liquidSys.YG13Com, BinaryValue);                 //YG1/3通信异常
    addSimDataInit(C_DiaTempSensor, &g_simDa.liquidSys.diaTempSensor, BinaryValue);     //透析液温度传感器异常
    addSimDataInit(C_HeatTempSensor, &g_simDa.liquidSys.heatTempSensor, BinaryValue);   //加热温度传感器异常

    //插入模块板版本信息
    m_boardVersionCode = C_LiquidSysBoardVersion;
    m_boardVersionList << &g_simDa.liquidSys.liquidBoardSoftVer << &g_simDa.liquidSys.liquidBoardHardVer
                       << &g_simDa.liquidSys.liquidPreBoardSoftVer << &g_simDa.liquidSys.liquidPreBoardHardVer
                       << &g_simDa.liquidSys.driveBoardSoftVer << &g_simDa.liquidSys.driveBoardHardVer
                       << &g_simDa.liquidSys.balanceBoardSoftVer << &g_simDa.liquidSys.balanceBoardHardVer
                       << &g_simDa.liquidSys.heatBoardSoftVer << &g_simDa.liquidSys.heatBoardHardVer;

    ///zf_test 一些数据默认初始化，便于测试
    g_simDa.liquidSys.AStraw.value = 1;
    g_simDa.liquidSys.AStraw.set.fixValue = 1;
    g_simDa.liquidSys.BStraw.value = 1;
    g_simDa.liquidSys.BStraw.set.fixValue = 1;
    g_simDa.liquidSys.diaJointRed.value = 1;
    g_simDa.liquidSys.diaJointRed.set.fixValue = 1;
    g_simDa.liquidSys.diaJointBlue.value = 1;
    g_simDa.liquidSys.diaJointBlue.set.fixValue = 1;
    g_simDa.liquidSys.YG1.value = -80.5;
    g_simDa.liquidSys.YG1.set.fixValue = -80.5;
    ///zf_test_end
}

void LiquidSystemSimulation::loadData4000()
{
    //--------------------------------驱动板软硬件版本-------------------------------------<
    g_mbd.md4.drive.rd7.ver_s = g_simDa.liquidSys.driveBoardSoftVer;
    g_mbd.md4.drive.rd7.ver_h = g_simDa.liquidSys.driveBoardHardVer;

    //-------------------------------平衡腔板软硬件版本------------------------------------<
    g_mbd.md4.balance.rd7.ver_s = g_simDa.liquidSys.balanceBoardSoftVer;
    g_mbd.md4.balance.rd7.ver_h = g_simDa.liquidSys.balanceBoardHardVer;

    //--------------------------------加热板软硬件版本-------------------------------------<
    g_mbd.md4.heat.rd7.ver_s = g_simDa.liquidSys.heatBoardSoftVer;
    g_mbd.md4.heat.rd7.ver_h = g_simDa.liquidSys.heatBoardHardVer;

    //--------------------------------WG1（放大10倍）------------------------------------<
    g_mbd.md4.heat.rd0.rtTemp_i = g_simDa.liquidSys.WG1.value*10;

    //--------------------------------WG6（放大10倍）------------------------------------<
    if(g_simDa.liquidSys.WG6.set.mode == AutoSimMode)
    {
        g_simDa.liquidSys.WG6.value = g_mbd.md4.heat.wr0.temp/10.0 + g_simDa.liquidSys.WG6.fluctValue;
    }
    g_mbd.md4.heat.rd0.rtTemp_o = g_simDa.liquidSys.WG6.value*10;

    //----------------------------设定加热温度（放大10倍）---------------------------------<
    g_mbd.md4.heat.rd0.temp_s = g_mbd.md4.heat.wr0.temp;

    //--------------------------------YG1、YG3（放大10倍）-------------------------------<
    g_mbd.md4.drive.rd0.np = g_simDa.liquidSys.YG1.value*10;
    g_mbd.md4.drive.rd1.dp = g_simDa.liquidSys.YG3.value*10;

    //-----------------------------------YG2、YG4---------------------------------------<
    g_mbd.md4.balance.rd3.rtYG2 = g_simDa.liquidSys.YG2.value;
    g_mbd.md4.balance.rd3.rtYG4 = g_simDa.liquidSys.YG4.value;

    //-----------------------------------DP转速------------------------------------------<
    if(g_simDa.liquidSys.DPSpeed.set.mode == AutoSimMode)
    {   //根据透析液流量计算转速
        if((bool)g_simDa.liquidSys.balanceSW.value)
        {
            g_simDa.liquidSys.DPSpeed.value =  g_simDa.liquidSys.diaFlow.value*DP_FPR + g_simDa.liquidSys.DPSpeed.fluctValue;
        }
        else
        {
            g_simDa.liquidSys.DPSpeed.value = 0;
        }
    }
    g_mbd.md4.balance.rd1.dprpm = g_simDa.liquidSys.DPSpeed.value;

    //-----------------------------------YP转速------------------------------------------<
    if(g_simDa.liquidSys.YPSpeed.set.mode == AutoSimMode)
    {
        if((bool)g_simDa.liquidSys.balanceSW.value)
        {
            g_simDa.liquidSys.YPSpeed.value = g_simDa.liquidSys.diaFlow.value*YP_FPR +  g_simDa.liquidSys.YPSpeed.fluctValue;
        }
        else
        {
            g_simDa.liquidSys.YPSpeed.value = 0;
        }
    }
    g_mbd.md4.balance.rd1.yprpm = g_simDa.liquidSys.YPSpeed.value;

    //-----------------------------------QP转速------------------------------------------<
    if(g_simDa.liquidSys.QPSpeed.set.mode == AutoSimMode)
    {   //注：电压和转速的比值大概是1000
        g_simDa.liquidSys.QPSpeed.value = g_mbd.md4.balance.wr0.qpv*100 + g_simDa.liquidSys.QPSpeed.fluctValue;
    }
    g_mbd.md4.balance.rd1.qprpm = g_simDa.liquidSys.QPSpeed.value;

    //-------------------------------DP推膜时间（放大10倍）--------------------------------<
    if(g_simDa.liquidSys.DPTime.set.mode == AutoSimMode)
    {
        if(g_simDa.liquidSys.diaFlow.value > 1)
        {   //推膜时间（s）= 平衡腔容积÷平衡腔流量×60
            g_simDa.liquidSys.DPTime.value = BALANCE_VOLUME/g_simDa.liquidSys.diaFlow.value*60 - 0.1 + g_simDa.liquidSys.DPTime.fluctValue;
        }
        else
        {
            g_simDa.liquidSys.DPTime.value = 0;
        }
    }
    g_mbd.md4.balance.rd1.dpt = g_simDa.liquidSys.DPTime.value*10;

    //-------------------------------YP推膜时间（放大10倍）--------------------------------<
    if(g_simDa.liquidSys.YPTime.set.mode == AutoSimMode)
    {
        if(g_simDa.liquidSys.diaFlow.value > 1)
        {   //推膜时间（s）= 平衡腔容积÷平衡腔流量×60
            g_simDa.liquidSys.YPTime.value = BALANCE_VOLUME/g_simDa.liquidSys.diaFlow.value*60 - 0.3 + g_simDa.liquidSys.DPTime.fluctValue;
        }
        else
        {
            g_simDa.liquidSys.YPTime.value = 0;
        }
    }
    g_mbd.md4.balance.rd1.ypt = g_simDa.liquidSys.YPTime.value*10;

    //-----------------------------------进液高压--------------------------------------<
    if(g_simDa.liquidSys.YG2High.set.mode == AutoSimMode)
    {
        g_simDa.liquidSys.YG2High.value = 141.0 + g_simDa.liquidSys.YG2High.fluctValue;
    }
    g_mbd.md4.balance.rd0.yg2h = g_simDa.liquidSys.YG2High.value;

    //-----------------------------------进液低压--------------------------------------<
    if(g_simDa.liquidSys.YG2Low.set.mode == AutoSimMode)
    {
        g_simDa.liquidSys.YG2Low.value = g_simDa.liquidSys.diaFlow.value/10.0 + g_simDa.liquidSys.YG2Low.fluctValue;
    }
    g_mbd.md4.balance.rd0.yg2l = g_simDa.liquidSys.YG2Low.value;

    //-----------------------------------废液高压--------------------------------------<
    if(g_simDa.liquidSys.YG4High.set.mode == AutoSimMode)
    {
        g_simDa.liquidSys.YG4High.value = 140.0 + g_simDa.liquidSys.YG4High.fluctValue;
    }
    g_mbd.md4.balance.rd0.yg4h = g_simDa.liquidSys.YG4High.value;

    //-----------------------------------废液低压--------------------------------------<
    if(g_simDa.liquidSys.YG4Low.set.mode == AutoSimMode)
    {
        g_simDa.liquidSys.YG4Low.value = g_simDa.liquidSys.diaFlow.value/20.0 + g_simDa.liquidSys.YG4Low.fluctValue;
    }
    g_mbd.md4.balance.rd0.yg4l = g_simDa.liquidSys.YG4Low.value;

    //--------------------------------平衡腔开关状态---------------------------------------<
    if(g_simDa.liquidSys.balanceSW.set.mode == AutoSimMode)
    {
        g_simDa.liquidSys.balanceSW.value = (g_mbd.md4.balance.wr0.cmd == BALANCE_WR0_WORK_MODEL_NORMAL);
    }
    setBitInByte(g_mbd.md4.balance.rd0.status, BALANCE_RD0_BK_G, g_simDa.liquidSys.balanceSW.value);

    //-----------------------------------加热开关----------------------------------------<
    if(g_simDa.liquidSys.heatSW.set.mode == AutoSimMode)
    {
        g_simDa.liquidSys.heatSW.value = !!(g_mbd.md4.heat.wr0.cmd & HEAT_WR0_SR);
    }
    setBitInByte(g_mbd.md4.heat.rd0.status, HEAT_RD0_ST, g_simDa.liquidSys.heatSW.value);

    //-----------------------------------YK ~ YJ5---------------------------------------<
    setBitInByte(g_mbd.md4.drive.rd0.status1, DRIVERBOARD_RD0_YK, g_simDa.liquidSys.YK.value);   //YK
    setBitInByte(g_mbd.md4.drive.rd0.status2, DRIVERBOARD_RD0_YJ1, g_simDa.liquidSys.YJ1.value); //YJ1
    setBitInByte(g_mbd.md4.balance.rd0.status, BALANCE_RD0_CQ2, g_simDa.liquidSys.YJ2.value);    //YJ2
    setBitInByte(g_mbd.md4.balance.rd0.status, BALANCE_RD0_CQ3, g_simDa.liquidSys.YJ3.value);    //YJ3
    setBitInByte(g_mbd.md4.drive.rd0.status1, DRIVERBOARD_RD0_YJ4, g_simDa.liquidSys.YJ4.value); //YJ4

    //-----------------------------------A、B液吸管--------------------------------------<
    setBitInByte(g_mbd.md4.drive.rd0.status2, DRIVERBOARD_RD0_CAJ, g_simDa.liquidSys.AStraw.value); //A吸管
    setBitInByte(g_mbd.md4.drive.rd0.status2, DRIVERBOARD_RD0_CBJ, g_simDa.liquidSys.BStraw.value); //B吸管

    //---------------------------------红、蓝透析器接头-----------------------------------<
    setBitInByte(g_mbd.md4.drive.rd0.status1, DRIVERBOARD_RD0_WA, g_simDa.liquidSys.diaJointRed.value);  //红色透析器接头
    setBitInByte(g_mbd.md4.drive.rd0.status1, DRIVERBOARD_RD0_WB, g_simDa.liquidSys.diaJointBlue.value); //蓝色透析器接头

    //-----------------------------------报警---------------------------------------------<
    setBitInByte(g_mbd.md4.heat.rd0.status, HEAT_RD0_YJ1, g_simDa.liquidSys.inletWaterLevel.value);               //进水位长时间无变化
    setBitInByte(g_mbd.md4.balance.rd0.err1, BALANCE_RD0_ERR_GAS_LEAK, g_simDa.liquidSys.air.value);              //透析液空气过多
    setBitInByte(g_mbd.md4.balance.rd0.err1, BALANCE_RD0_ERR_BC1_JAM, g_simDa.liquidSys.diaphBlock.value);        //平衡腔膜片受阻
    setBitInByte(g_mbd.md4.drive.rd0.status1, DRIVERBOARD_RD0_BLD, !g_simDa.liquidSys.bloodLeak.value);           //漏血
    setBitInByte(g_mbd.md4.drive.rd0.status2, DRIVERBOARD_RD0_LD, g_simDa.liquidSys.fluidLeak1.value);            //漏液传感器1
    setBitInByte(g_mbd.md4.balance.rd0.err2, BALANCE_RD0_ERR_YG2_DATA_ERR, g_simDa.liquidSys.yg1OutLimit.value);  //进液压超限
    setBitInByte(g_mbd.md4.balance.rd0.err2, BALANCE_RD0_ERR_YG4_DATA_ERR, g_simDa.liquidSys.yg4OutLimit.value);  //废液压超限
    setBitInByte(g_mbd.md4.balance.rd0.err2, BALANCE_RD0_ERR_QP_ERR, g_simDa.liquidSys.QPSpeedError.value);       //QP转速异常
    setBitInByte(g_mbd.md4.balance.rd0.err1, BALANCE_RD0_ERR_DP_ERR, g_simDa.liquidSys.DPSpeedError.value);       //DP转速异常
    setBitInByte(g_mbd.md4.balance.rd0.err2, BALANCE_RD0_ERR_YP_ERR, g_simDa.liquidSys.YPSpeedError.value);       //YP转速异常
    setBitInByte(g_mbd.md4.balance.rd0.err1, BALANCE_RD0_ERR_BC_D_LEAK, g_simDa.liquidSys.M1Leak.value);          //膜片M1泄漏
    setBitInByte(g_mbd.md4.balance.rd0.err2, BALANCE_RD0_ERR_SV14_LEAK, g_simDa.liquidSys.SV14Leak.value);        //SV14泄漏
    setBitInByte(g_mbd.md4.balance.rd0.err2, BALANCE_RD0_ERR_YG2_DATA_ERR, g_simDa.liquidSys.YG2DataError.value); //YG2数据异常（仅4000）
    setBitInByte(g_mbd.md4.balance.rd0.err2, BALANCE_RD0_ERR_YG4_DATA_ERR, g_simDa.liquidSys.YG4DataError.value); //YG4数据异常（仅4000）
    setBitInByte(g_mbd.md4.heat.rd0.status, HEAT_RD0_NE1, g_simDa.liquidSys.diaTempSensor.value);                 //透析液温度传感器异常（仅4000）
    setBitInByte(g_mbd.md4.heat.rd0.status, HEAT_RD0_NE0, g_simDa.liquidSys.heatTempSensor.value);                //加热温度传感器异常（仅4000）

    //下面的内容无法上传到主控（无对应RD通信协议），但需更新模拟器界面显示
    //---------------------------------透析液流量-----------------------------------------<
    if(g_simDa.liquidSys.diaFlow.set.mode == AutoSimMode)
    {
        g_simDa.liquidSys.diaFlow.value = g_mbd.md4.balance.wr0.flow + g_simDa.liquidSys.diaFlow.fluctValue;
    }

    //--------------------------------电磁阀（SV1~SV24）-----------------------------------<
    if(g_simDa.liquidSys.diaFlow.set.mode == AutoSimMode)
    {
        quint32 wrSv = (g_mbd.md4.drive.wr0.sv >> 8);
        for(int i = 0; i < 20; i++)
        {
            g_simDa.liquidSys.SV[i+1].value = !!(wrSv & (0x01 << i));
        }
    }
}

void LiquidSystemSimulation::loadData6000()
{
    //--------------------------------水路板软硬件版本-------------------------------------<
    g_mbd.md6.ldd.rd7.sv = g_simDa.liquidSys.liquidBoardSoftVer;
    g_mbd.md6.ldd.rd7.hv = g_simDa.liquidSys.liquidBoardHardVer;

    //------------------------------水路压力板软硬件版本------------------------------------<
    g_mbd.md6.ldd.rd7.YG13_sv = g_simDa.liquidSys.liquidPreBoardSoftVer;
    g_mbd.md6.ldd.rd7.YG13_hv = g_simDa.liquidSys.liquidPreBoardHardVer;

    //--------------------------------WG1（放大100倍）------------------------------------<
    g_mbd.md6.ldd.rd0.WG1_temperature = g_simDa.liquidSys.WG1.value*100;

    //--------------------------------WG5（放大100倍）------------------------------------<
    if(g_simDa.liquidSys.WG5.set.mode == AutoSimMode)
    {   //加热器出口温度，基础按设定温度+5°C
        g_simDa.liquidSys.WG5.value = (g_mbd.md6.ldd.wr1.temp + g_mbd.md6.ldd.wr1.temp_Offset)/100.0 + 5 + g_simDa.liquidSys.WG5.fluctValue;
    }
    g_mbd.md6.ldd.rd0.WG5_temperature = g_simDa.liquidSys.WG5.value*100;

    //--------------------------------WG6（放大100倍）------------------------------------<
    if(g_simDa.liquidSys.WG6.set.mode == AutoSimMode)
    {
        g_simDa.liquidSys.WG6.value = (g_mbd.md6.ldd.wr1.temp + g_mbd.md6.ldd.wr1.temp_Offset)/100.0 + g_simDa.liquidSys.WG6.fluctValue;
    }
    g_mbd.md6.ldd.rd0.WG6_temperature = g_simDa.liquidSys.WG6.value*100;

    //--------------------------------YG1~YG4（放大10倍）---------------------------------<
    g_mbd.md6.ldd.rd0.YG1_pressure = g_simDa.liquidSys.YG1.value*10;
    g_mbd.md6.ldd.rd0.YG2_pressure = g_simDa.liquidSys.YG2.value*10;
    g_mbd.md6.ldd.rd0.YG3_pressure = g_simDa.liquidSys.YG3.value*10;
    g_mbd.md6.ldd.rd0.YG4_pressure = g_simDa.liquidSys.YG4.value*10;

    //---------------------------------透析液流量-----------------------------------------<
    if(g_simDa.liquidSys.diaFlow.set.mode == AutoSimMode)
    {
        g_simDa.liquidSys.diaFlow.value = g_mbd.md6.ldd.wr0.flow + g_simDa.liquidSys.diaFlow.fluctValue;
    }
    g_mbd.md6.ldd.rd1.flow = g_simDa.liquidSys.diaFlow.value;

    //-----------------------------------DP转速------------------------------------------<
    if(g_simDa.liquidSys.DPSpeed.set.mode == AutoSimMode)
    {   //根据透析液流量计算转速
        if((bool)g_simDa.liquidSys.balanceSW.value)
        {
            if(g_mbd.md6.ldd.wr0.GP_cmd & LDB_WR0_DP_CTLED)
            {   //DP由主控控制
                g_simDa.liquidSys.DPSpeed.value = g_mbd.md6.ldd.wr0.DP_targetSpeed + g_simDa.liquidSys.DPSpeed.fluctValue;
            }
            else
            {
                g_simDa.liquidSys.DPSpeed.value = g_simDa.liquidSys.diaFlow.value*DP_FPR + g_simDa.liquidSys.DPSpeed.fluctValue;
            }
        }
        else
        {
            g_simDa.liquidSys.DPSpeed.value = 0;
        }
    }
    g_mbd.md6.ldd.rd1.DP_LiveSpeed = g_simDa.liquidSys.DPSpeed.value;

    //-----------------------------------YP转速------------------------------------------<
    if(g_simDa.liquidSys.YPSpeed.set.mode == AutoSimMode)
    {
        if((bool)g_simDa.liquidSys.balanceSW.value)
        {
            if(g_mbd.md6.ldd.wr0.GP_cmd & LDB_WR0_YP_CTLED)
            {   //YP由主控控制
                g_simDa.liquidSys.YPSpeed.value = g_mbd.md6.ldd.wr0.YP_targetSpeed + g_simDa.liquidSys.YPSpeed.fluctValue;
            }
            else
            {
                g_simDa.liquidSys.YPSpeed.value = g_simDa.liquidSys.diaFlow.value*YP_FPR +  g_simDa.liquidSys.YPSpeed.fluctValue;
            }
        }
        else
        {
            g_simDa.liquidSys.YPSpeed.value = 0;
        }
    }
    g_mbd.md6.ldd.rd1.YP_LiveSpeed = g_simDa.liquidSys.YPSpeed.value;

    //-----------------------------------QP转速------------------------------------------<
    if(g_simDa.liquidSys.QPSpeed.set.mode == AutoSimMode)
    {
        g_simDa.liquidSys.QPSpeed.value = g_mbd.md6.ldd.wr0.QP_targetSpeed + g_simDa.liquidSys.QPSpeed.fluctValue;
    }
    g_mbd.md6.ldd.rd1.QP_LiveSpeed = g_simDa.liquidSys.QPSpeed.value;

    //-------------------------------DP推膜时间（放大10倍）--------------------------------<
    if(g_simDa.liquidSys.DPTime.set.mode == AutoSimMode)
    {
        if(g_simDa.liquidSys.diaFlow.value > 1)
        {   //推膜时间（s）= 平衡腔容积÷平衡腔流量×60
            g_simDa.liquidSys.DPTime.value = g_mbd.md6.ldd.wr0.volume/10.0/g_simDa.liquidSys.diaFlow.value*60 - 0.1 + g_simDa.liquidSys.DPTime.fluctValue;
        }
        else
        {
            g_simDa.liquidSys.DPTime.value = 0;
        }
    }
    g_mbd.md6.ldd.rd1.DP_time = g_simDa.liquidSys.DPTime.value*10;

    //-------------------------------YP推膜时间（放大10倍）--------------------------------<
    if(g_simDa.liquidSys.YPTime.set.mode == AutoSimMode)
    {
        if(g_simDa.liquidSys.diaFlow.value > 1)
        {   //推膜时间（s）= 平衡腔容积÷平衡腔流量×60
            g_simDa.liquidSys.YPTime.value = g_mbd.md6.ldd.wr0.volume/10.0/g_simDa.liquidSys.diaFlow.value*60 - 0.3 + g_simDa.liquidSys.DPTime.fluctValue;
        }
        else
        {
            g_simDa.liquidSys.YPTime.value = 0;
        }
    }
    g_mbd.md6.ldd.rd1.YP_time = g_simDa.liquidSys.YPTime.value*10;

    //-------------------------------进液高压（放大10倍）--------------------------------<
    if(g_simDa.liquidSys.YG2High.set.mode == AutoSimMode)
    {
        g_simDa.liquidSys.YG2High.value = 141.0 + g_simDa.liquidSys.YG2High.fluctValue;
    }
    g_mbd.md6.ldd.rd1.YG2_MP = g_simDa.liquidSys.YG2High.value*10;

    //-------------------------------进液低压（放大10倍）--------------------------------<
    if(g_simDa.liquidSys.YG2Low.set.mode == AutoSimMode)
    {
        g_simDa.liquidSys.YG2Low.value = g_simDa.liquidSys.diaFlow.value/10.0 + g_simDa.liquidSys.YG2Low.fluctValue;
    }
    g_mbd.md6.ldd.rd1.YG2_AP = g_simDa.liquidSys.YG2Low.value*10;

    //-------------------------------废液高压（放大10倍）--------------------------------<
    if(g_simDa.liquidSys.YG4High.set.mode == AutoSimMode)
    {
        g_simDa.liquidSys.YG4High.value = 140.0 + g_simDa.liquidSys.YG4High.fluctValue;
    }
    g_mbd.md6.ldd.rd1.YG4_MP = g_simDa.liquidSys.YG4High.value*10;

    //-------------------------------废液低压（放大10倍）--------------------------------<
    if(g_simDa.liquidSys.YG4Low.set.mode == AutoSimMode)
    {
        g_simDa.liquidSys.YG4Low.value = g_simDa.liquidSys.diaFlow.value/20.0 + g_simDa.liquidSys.YG4Low.fluctValue;
    }
    g_mbd.md6.ldd.rd1.YG4_AP = g_simDa.liquidSys.YG4Low.value*10;

    //--------------------------------平衡腔开关状态---------------------------------------<
    if(g_simDa.liquidSys.balanceSW.set.mode == AutoSimMode)
    {
        g_simDa.liquidSys.balanceSW.value = !!g_mbd.md6.ldd.wr0.mode;
    }
    setBitInByte(g_mbd.md6.ldd.rd0.w_st1, LDB_RD0_BS_RS, g_simDa.liquidSys.balanceSW.value);

    //-----------------------------------加热开关----------------------------------------<
    if(g_simDa.liquidSys.heatSW.set.mode == AutoSimMode)
    {
        g_simDa.liquidSys.heatSW.value = !!(g_mbd.md6.ldd.wr1.cmd & LDB_WR1_HEATER_ON);
        if((bool)g_simDa.liquidSys.heatForceOff.value)
        {   //若加热强关
            g_simDa.liquidSys.heatSW.value = 0;
        }
    }
    setBitInByte(g_mbd.md6.ldd.rd0.w_st1, LDB_RD0_HT_RS, g_simDa.liquidSys.heatSW.value);

    //-----------------------------------加热强关----------------------------------------<
    setBitInByte(g_mbd.md6.ldd.rd0.w_st1, LDB_RD0_FH, g_simDa.liquidSys.heatForceOff.value);

    //--------------------------------加热占空比（放大10倍）-------------------------------<
    g_mbd.md6.ldd.rd0.heatcycle = g_simDa.liquidSys.heatDutyFactor.value*10;

    //-----------------------------------YK ~ YJ5---------------------------------------<
    setBitInByte(g_mbd.md6.ldd.rd0.st1, LDB_RD0_YK_RD, g_simDa.liquidSys.YK.value);   //YK
    setBitInByte(g_mbd.md6.ldd.rd0.st1, LDB_RD0_YJ1_RD, g_simDa.liquidSys.YJ1.value); //YJ1
    setBitInByte(g_mbd.md6.ldd.rd0.st1, LDB_RD0_YJ2_RD, g_simDa.liquidSys.YJ2.value); //YJ2
    setBitInByte(g_mbd.md6.ldd.rd0.st1, LDB_RD0_YJ3_RD, g_simDa.liquidSys.YJ3.value); //YJ3
    setBitInByte(g_mbd.md6.ldd.rd0.st2, LDB_RD0_GF_RD, g_simDa.liquidSys.YJ4.value);  //YJ4
    setBitInByte(g_mbd.md6.ldd.rd0.st1, LDB_RD0_YJ5_RD, g_simDa.liquidSys.YJ5.value); //YJ5

    //----------------------------------左补液接头---------------------------------------<
    setBitInByte(g_mbd.md6.ldd.rd0.st2, LDB_RD0_SBB_RD, g_simDa.liquidSys.leftSubJoint.value);

    //----------------------------------右补液接头---------------------------------------<
    setBitInByte(g_mbd.md6.ldd.rd0.st2, LDB_RD0_SBA_RD, g_simDa.liquidSys.rightSubJoint.value);

    //-----------------------------------A液吸管-----------------------------------------<
    setBitInByte(g_mbd.md6.ldd.rd0.st1, LDB_RD0_A_RD, g_simDa.liquidSys.AStraw.value);

    //-----------------------------------B液吸管-----------------------------------------<
    setBitInByte(g_mbd.md6.ldd.rd0.st1, LDB_RD0_B_RD, g_simDa.liquidSys.BStraw.value);

    //---------------------------------透析器接头红---------------------------------------<
    setBitInByte(g_mbd.md6.ldd.rd0.st1, LDB_RD0_DCA_RD, g_simDa.liquidSys.diaJointRed.value);

    //---------------------------------透析器接头蓝---------------------------------------<
    setBitInByte(g_mbd.md6.ldd.rd0.st2, LDB_RD0_DCB_RD, g_simDa.liquidSys.diaJointBlue.value);

    //---------------------------------电磁阀（V1~V8）------------------------------------<
    quint16 *wrV = (quint16 *)&g_mbd.md6.ldd.wr0.v_c1; //写命令的V1~V8控制，内存是连续的，取2个字节
    quint8 vSt = 0;
    for(int i = 0; i < 8; i++)
    {
        if(g_simDa.liquidSys.V[i+1].set.mode == AutoSimMode)
        {
            vSt = (*wrV >> (i*2)) & 0x03;
            if(vSt == LDB_WR0_ON_MSB)
            {   //开启
                g_simDa.liquidSys.V[i+1].value = 1;
            }
            else if(vSt == LDB_WR0_OFF_MSB)
            {   //关闭
                g_simDa.liquidSys.V[i+1].value = 0;
            }
            else
            {   //模块控制（暂为正常切换）
                g_simDa.liquidSys.V[i+1].value = !!(tempV1_V8Sim & (1 << i));
            }
        }
        setBitInByte(g_mbd.md6.ldd.rd1.V_S, (1 << i), g_simDa.liquidSys.V[i+1].value);
    }

    //--------------------------------电磁阀（SV1~SV24）-----------------------------------<
    quint32 *rdSV = (quint32 *)&g_mbd.md6.ldd.rd1.SV_S1; //读命令的SV控制，内存是连续的，取前3个字节
    quint64 *wrSV = (quint64 *)&g_mbd.md6.ldd.wr0.sv_c1; //写命令的SV控制，内存是连续的，取前6个字节
    quint8 svSt = 0;
    for(int i = 0; i < 24; i++)
    {
        if(g_simDa.liquidSys.SV[i+1].set.mode == AutoSimMode)
        {   //自动模拟，按照主控下发的命令
            svSt = (*wrSV >> (i*2)) & 0x03;
            if(svSt == LDB_WR0_ON_MSB)
            {   //开启
                g_simDa.liquidSys.SV[i+1].value = 1;
            }
            else if(svSt == LDB_WR0_OFF_MSB)
            {   //关闭
                g_simDa.liquidSys.SV[i+1].value = 0;
            }
        }
        setBitInByte4(*rdSV, (1 << i), g_simDa.liquidSys.SV[i+1].value);
    }

    //-----------------------------------报警---------------------------------------------<
    setBitInByte(g_mbd.md6.ldd.rd0.w_st1, LDB_RD0_WS, g_simDa.liquidSys.waterSupply.value);          //供水
    setBitInByte(g_mbd.md6.ldd.rd0.w_st1, LDB_RD0_LH_YG2, g_simDa.liquidSys.YG2LowPreTooHigh.value); //进液压低压高
    setBitInByte(g_mbd.md6.ldd.rd0.w_st1, LDB_RD0_LH_YG4, g_simDa.liquidSys.YG4LowPreTooHigh.value); //废液压低压高
    setBitInByte(g_mbd.md6.ldd.rd0.st2, LDB_RD0_BL_RD, g_simDa.liquidSys.bloodLeak.value);           //漏血
    setBitInByte(g_mbd.md6.ldd.rd0.w_st1, LDB_RD0_WL, g_simDa.liquidSys.inletWaterLevel.value);      //进水位长时间无变化
    setBitInByte(g_mbd.md6.ldd.rd0.w_st1, LDB_RD0_DA, g_simDa.liquidSys.air.value);                  //透析液空气过多
    setBitInByte(g_mbd.md6.ldd.rd0.st2, LDB_RD0_LL1_RD, g_simDa.liquidSys.fluidLeak1.value);         //漏液传感器1
    setBitInByte(g_mbd.md6.ldd.rd0.st2, LDB_RD0_LL2_RD, g_simDa.liquidSys.fluidLeak2.value);         //漏液传感器2
    setBitInByte(g_mbd.md6.ldd.rd0.w_st2, LDB_RD0_OL_YG2, g_simDa.liquidSys.yg1OutLimit.value);      //进液压超限
    setBitInByte(g_mbd.md6.ldd.rd0.w_st2, LDB_RD0_OL_YG4, g_simDa.liquidSys.yg4OutLimit.value);      //废液压超限
    setBitInByte(g_mbd.md6.ldd.rd0.w_st2, LDB_RD0_SA_QP, g_simDa.liquidSys.QPSpeedError.value);      //QP转速异常
    setBitInByte(g_mbd.md6.ldd.rd0.w_st2, LDB_RD0_SA_DP, g_simDa.liquidSys.DPSpeedError.value);      //DP转速异常
    setBitInByte(g_mbd.md6.ldd.rd0.w_st2, LDB_RD0_SA_YP, g_simDa.liquidSys.YPSpeedError.value);      //YP转速异常
    setBitInByte(g_mbd.md6.ldd.rd0.w_st3, LDB_RD0_LK_M1, g_simDa.liquidSys.M1Leak.value);            //膜片M1泄漏
    setBitInByte(g_mbd.md6.ldd.rd0.w_st3, LDB_RD0_LK_M2, g_simDa.liquidSys.M2Leak.value);            //膜片M2泄漏
    setBitInByte(g_mbd.md6.ldd.rd0.w_st3, LDB_RD0_LK_V1V7, g_simDa.liquidSys.V1V7Leak.value);        //V1/V7泄漏
    setBitInByte(g_mbd.md6.ldd.rd0.w_st3, LDB_RD0_LK_V2V8, g_simDa.liquidSys.V2V8Leak.value);        //V2/V8泄漏
    setBitInByte(g_mbd.md6.ldd.rd0.w_st3, LDB_RD0_LK_V3V5, g_simDa.liquidSys.V3V5Leak.value);        //V3/V5泄漏
    setBitInByte(g_mbd.md6.ldd.rd0.w_st3, LDB_RD0_LK_V4V6, g_simDa.liquidSys.V4V6Leak.value);        //V4/V6泄漏
    setBitInByte(g_mbd.md6.ldd.rd0.w_st3, LDB_RD0_LK_SV13, g_simDa.liquidSys.SV13Leak.value);        //SV13泄漏
    setBitInByte(g_mbd.md6.ldd.rd0.w_st3, LDB_RD0_LK_SV14, g_simDa.liquidSys.SV14Leak.value);        //SV14泄漏
    setBitInByte(g_mbd.md6.ldd.rd0.w_st2, LDB_RD0_CE_HPB, g_simDa.liquidSys.YG13Com.value);          //YG1/3通信异常
}
