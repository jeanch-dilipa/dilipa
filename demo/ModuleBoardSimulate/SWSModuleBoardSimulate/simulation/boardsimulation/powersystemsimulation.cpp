#include "powersystemsimulation.h"

PowerSystemSimulation::PowerSystemSimulation(QObject *parent) : BoardSimulationBase(parent)
{

}

void PowerSystemSimulation::recvWriteCmd4000(ModuleBoardAddrType /*addr*/, SystemBusCommandType cmd, const QByteArray &data)
{
    switch(cmd)
    {
    case WRITE_COMMAND_0: //电源控制及自动开机命令
        memcpy(&g_mbd.md4.power.wr0, data.data(), sizeof(g_mbd.md4.power.wr0));

        break;
    case WRITE_COMMAND_1: //同步系统时间命令
        memcpy(&g_mbd.md4.power.wr1, data.data(), sizeof(g_mbd.md4.power.wr1));

        break;
    case WRITE_COMMAND_9:
        ///预留
        break;
    default:
        break;
    }
}

void PowerSystemSimulation::recvWriteCmd6000(ModuleBoardAddrType /*addr*/, SystemBusCommandType cmd, const QByteArray &data)
{
    switch(cmd)
    {
    case WRITE_COMMAND_0: //电源控制命令
        memcpy(&g_mbd.md6.pbd.wr0, data.data(), sizeof(g_mbd.md6.pbd.wr0));

        if((g_mbd.md6.pbd.wr0.cmd & PB_WR0_OFF_ON) == 0)
        {   //电源关机
            ///预留
        }
        break;
    case WRITE_COMMAND_9:
        ///预留
        break;
    default:
        break;
    }
}

void PowerSystemSimulation::initSimData()
{
    addSimDataInit(C_PowerError, &g_simDa.powerSys.powerError, BinaryValue);        //电源故障
    addSimDataInit(C_ChargeStatus, &g_simDa.powerSys.chargeStatus, BinaryValue);    //充电状态
    addSimDataInit(C_BatteryStatus, &g_simDa.powerSys.batteryStatus, BinaryValue);  //电池状态
    addSimDataInit(C_CityPower, &g_simDa.powerSys.cityPower, BinaryValue);          //市电状态
    addSimDataInit(C_PowerSupply, &g_simDa.powerSys.powerSupply, BinaryValue);      //供电状态
    addSimDataInit(C_CityVol, &g_simDa.powerSys.cityVol, NumericValue);             //市电电压
    addSimDataInit(C_Battery, &g_simDa.powerSys.battery, NumericValue);             //电池电量
    addSimDataInit(C_Vol12V, &g_simDa.powerSys.vol12V, NumericValue, 1);            //12V电压
    addSimDataInit(C_Vol24V, &g_simDa.powerSys.vol24V, NumericValue, 1);            //24V电压
    addSimDataInit(C_BatteryVol, &g_simDa.powerSys.batteryVol, NumericValue, 1);    //电池电压

    //插入模块板版本信息
    m_boardVersionCode = C_PowerSysBoardVersion;
    m_boardVersionList << &g_simDa.powerSys.powerBoardSoftVer << &g_simDa.powerSys.powerBoardHardVer;
}

void PowerSystemSimulation::loadData4000()
{
    //-----------------------------软硬件版本-----------------------------------<
    g_mbd.md4.power.rd7.ver_s = g_simDa.powerSys.powerBoardSoftVer;
    g_mbd.md4.power.rd7.ver_h = g_simDa.powerSys.powerBoardHardVer;

    //-----------------------------电源故障-------------------------------------<
    setBitInByte(g_mbd.md4.power.rd0.status, POWER_RD0_POWER_SUPPY_FAILURE, g_simDa.powerSys.powerError.value);

    //--------------------------充电状态、电池状态-------------------------------<
    if(g_simDa.powerSys.batteryStatus.value)
    {   //电池异常
        g_mbd.md4.power.rd0.status |= POWER_RD0_BHBL_HIGH;
        g_mbd.md4.power.rd0.status |= POWER_RD0_BHBL_LOW;
    }
    else
    {
        if(g_simDa.powerSys.chargeStatus.value)
        {   //充电中
            g_mbd.md4.power.rd0.status |= POWER_RD0_BHBL_HIGH;
            g_mbd.md4.power.rd0.status &= ~POWER_RD0_BHBL_LOW;
        }
        else
        {   //充电完成
            g_mbd.md4.power.rd0.status &= ~POWER_RD0_BHBL_HIGH;
            g_mbd.md4.power.rd0.status |= POWER_RD0_BHBL_LOW;
        }
    }

    //-----------------------------市电状态-------------------------------------<
    g_mbd.md4.power.rd0.status &= 0xFC; //默认正常
    if(g_simDa.powerSys.cityPower.value)
    {   //市电异常
        g_mbd.md4.power.rd0.status |= POWER_RD0_VHVL_DOWN;
    }

    //-----------------------------市电电压-------------------------------------<
    g_mbd.md4.power.rd0.s_vol = g_simDa.powerSys.cityVol.value;

    //-----------------------------电池电量-------------------------------------<
    g_mbd.md4.power.rd0.rate = g_simDa.powerSys.battery.value;
}

void PowerSystemSimulation::loadData6000()
{
    //-----------------------------软硬件版本-----------------------------------<
    g_mbd.md6.pbd.rd7.sv = g_simDa.powerSys.powerBoardSoftVer;
    g_mbd.md6.pbd.rd7.hv = g_simDa.powerSys.powerBoardHardVer;

    //-----------------------------电源故障-------------------------------------<
    setBitInByte(g_mbd.md6.pbd.rd0.st, PB_RD0_ET_FAI, g_simDa.powerSys.powerError.value);

    //-----------------------------充电状态-------------------------------------<
    setBitInByte(g_mbd.md6.pbd.rd0.st, PB_RD0_BRUN_BOVER, g_simDa.powerSys.chargeStatus.value);

    //-----------------------------电池状态-------------------------------------<
    setBitInByte(g_mbd.md6.pbd.rd0.st, PB_RD0_BN_BO, g_simDa.powerSys.batteryStatus.value);

    //-----------------------------市电状态-------------------------------------<
    setBitInByte(g_mbd.md6.pbd.rd0.st, PB_RD0_CPN_CPO, g_simDa.powerSys.cityPower.value);

    //-----------------------------供电状态-------------------------------------<
    setBitInByte(g_mbd.md6.pbd.rd0.st, PB_RD0_PS_CPS, g_simDa.powerSys.powerSupply.value);

    //-----------------------------市电电压-------------------------------------<
    g_mbd.md6.pbd.rd0.voItage = g_simDa.powerSys.cityVol.value;

    //-----------------------------电池电量-------------------------------------<
    g_mbd.md6.pbd.rd0.battery = g_simDa.powerSys.battery.value;

    //--------------------------12V电压（放大10倍）------------------------------<
    g_mbd.md6.pbd.rd0.twelveV = g_simDa.powerSys.vol12V.value*10;

    //--------------------------24V电压（放大10倍）------------------------------<
    g_mbd.md6.pbd.rd0.twentyfourV = g_simDa.powerSys.vol24V.value*10;

    //--------------------------电池电压（放大10倍）------------------------------<
    g_mbd.md6.pbd.rd0.battery_VoItage = g_simDa.powerSys.batteryVol.value*10;
}
