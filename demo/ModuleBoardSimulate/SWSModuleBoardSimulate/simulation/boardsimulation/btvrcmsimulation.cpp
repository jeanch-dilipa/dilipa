#include "btvrcmsimulation.h"

BTVRCMSimulation::BTVRCMSimulation(QObject *parent) : BoardSimulationBase(parent)
{

}

void BTVRCMSimulation::recvWriteCmd(ModuleBoardAddrType addr, SystemBusCommandType cmd, const QByteArray &data)
{
    if(addr == BLOOD_TEMP_VOLUME_MODULE_ADDR)
    {   //血温血容量模块地址
        switch(cmd)
        {
        case WRITE_COMMAND_0: //血温传感器校正命令
            ///预留
            break;
        case WRITE_COMMAND_1: //血容量控制命令
            memcpy(&g_mbd.btv.wr1, data.data(), sizeof(g_mbd.btv.wr1));

            if(g_mbd.btv.wr1.cmd & BTVSB_WR1_SET_BV0)
            {   //设置当前状态为BV0
                m_autoBV0 = g_simDa.btvRcm.BV.value;
            }
            break;
        case WRITE_COMMAND_2: //血容量校正命令
            ///预留
            break;
        case WRITE_COMMAND_9: //升级命令
            ///预留
            break;
        default:
            break;
        }
    }
    else if(addr == UREA_SENSORE_MODULE_ADDR)
    {   //实时清除率模块地址
        switch(cmd)
        {
        case WRITE_COMMAND_0: //实时清除率检测模块控制命令
            memcpy(&g_mbd.rcm.wr0, data.data(), sizeof(g_mbd.rcm.wr0));

            if(g_mbd.rcm.wr0.cmd & US_WR0_CS)
            {   //执行零点校正
                m_isAutoRCMCorrect = true;
            }
            break;
        case WRITE_COMMAND_9: //升级命令信息
            ///预留
            break;
        default:
            break;
        }
    }
}

void BTVRCMSimulation::initSimData()
{
    addSimDataInit(C_VTStatus, &g_simDa.btvRcm.VTStatus, BinaryValue);             //静脉血温传感器状态
    addSimDataInit(C_ATStatus, &g_simDa.btvRcm.ATStatus, BinaryValue);             //动脉血温传感器状态
    addSimDataInit(C_VT, &g_simDa.btvRcm.VT, NumericValue, 2);                     //静脉血温
    addSimDataInit(C_AT, &g_simDa.btvRcm.AT, NumericValue, 2);                     //动脉血温
    addSimDataInit(C_BVStatus, &g_simDa.btvRcm.BVStatus, BinaryValue);             //血容量传感器状态
    addSimDataInit(C_bloodDetect, &g_simDa.btvRcm.bloodDetect, BinaryValue);       //是否检测到血液
    addSimDataInit(C_BVCover, &g_simDa.btvRcm.BVCover, BinaryValue);               //血容量监测盖
    addSimDataInit(C_LEDSW, &g_simDa.btvRcm.LEDSW, BinaryValueWithAuto);           //近红外LED状态
    addSimDataInit(C_BV_V, &g_simDa.btvRcm.BV_V, NumericValue);                    //受光电压
    addSimDataInit(C_BV, &g_simDa.btvRcm.BV, NumericValue);                        //血容量
    addSimDataInit(C_BV0, &g_simDa.btvRcm.BV0, NumericValueWithAuto);              //初始血容量
    addSimDataInit(C_RBV, &g_simDa.btvRcm.RBV, NumericValueWithAuto, 2);           //相对血容量
    addSimDataInit(C_RCMCorrect, &g_simDa.btvRcm.RCMCorrect, BinaryValueWithAuto); //实时清除率监测传感器校正
    addSimDataInit(C_RCMStatus, &g_simDa.btvRcm.RCMStatus, BinaryValue);           //实时清除率监测传感器状态
    addSimDataInit(C_RCMDetect, &g_simDa.btvRcm.RCMDetect, BinaryValueWithAuto);   //实时清除率监测检测状态
    addSimDataInit(C_abs, &g_simDa.btvRcm.abs, NumericValue, 2);                   //吸光度

    //插入模块板版本信息
    m_boardVersionCode = C_BtvRcmBoardVersion;
    m_boardVersionList << &g_simDa.btvRcm.btvBoardSoftVer << &g_simDa.btvRcm.btvBoardHardVer
                       << &g_simDa.btvRcm.rcmBoardSoftVer << &g_simDa.btvRcm.rcmBoardHardVer;
}

void BTVRCMSimulation::loadData4000()
{
    loadData6000(); //4000、6000协议相同
}

void BTVRCMSimulation::loadData6000()
{
    //----------------------------软硬件版本-------------------------------------<
    g_mbd.btv.rd7.sv = g_simDa.btvRcm.btvBoardSoftVer;
    g_mbd.btv.rd7.hv = g_simDa.btvRcm.btvBoardHardVer;
    g_mbd.rcm.rd7.sv = g_simDa.btvRcm.rcmBoardSoftVer;
    g_mbd.rcm.rd7.hv = g_simDa.btvRcm.rcmBoardHardVer;

    //------------------------静脉血温传感器状态----------------------------------<
    setBitInByte(g_mbd.btv.rd0.st, BTVSB_RD0_VS_ERR, g_simDa.btvRcm.VTStatus.value);

    //------------------------动脉血温传感器状态----------------------------------<
    setBitInByte(g_mbd.btv.rd0.st, BTVSB_RD0_AS_ERR, g_simDa.btvRcm.ATStatus.value);

    //-----------------------静脉血温（放大100倍）--------------------------------<
    g_mbd.btv.rd0.vt = (g_simDa.btvRcm.VT.value + 0.005)*100;

    //-----------------------动脉血温（放大100倍）--------------------------------<
    g_mbd.btv.rd0.at = (g_simDa.btvRcm.AT.value + 0.005)*100;

    //-------------------------血容量传感器状态-----------------------------------<
    setBitInByte(g_mbd.btv.rd2.st, BTVSB_RD2_BV_ST, g_simDa.btvRcm.BVStatus.value);

    //--------------------------是否检测到血液------------------------------------<
    setBitInByte(g_mbd.btv.rd2.st, BTVSB_RD2_BD_ST, g_simDa.btvRcm.bloodDetect.value);

    //---------------------------血容量监测盖-------------------------------------<
    setBitInByte(g_mbd.btv.rd2.st, BTVSB_RD2_COVER_ST, g_simDa.btvRcm.BVCover.value);

    //--------------------------近红外LED状态------------------------------------<
    if(g_simDa.btvRcm.LEDSW.set.mode == AutoSimMode)
    {
        if(g_mbd.btv.wr1.cmd & BTVSB_WR1_LED_CMD)
        {   //主控控制
            g_simDa.btvRcm.LEDSW.value = !!(g_mbd.btv.wr1.cmd & BTVSB_WR1_LED_ONOFF);
        }
        else
        {   //模块控制
            g_simDa.btvRcm.LEDSW.value = 1; //自动模拟，暂时直接为打开
        }
    }
    setBitInByte(g_mbd.btv.rd2.st, BTVSB_RD2_LED_ST, g_simDa.btvRcm.LEDSW.value);

    //----------------------------受光电压---------------------------------------<
    g_mbd.btv.rd2.bv_v = g_simDa.btvRcm.BV_V.value;

    //-----------------------------血容量----------------------------------------<
    g_mbd.btv.rd2.bv = g_simDa.btvRcm.BV.value;

    //----------------------------初始血容量--------------------------------------<
    if(g_simDa.btvRcm.BV0.set.mode == AutoSimMode)
    {
        g_simDa.btvRcm.BV0.value = m_autoBV0;
    }
    g_mbd.btv.rd2.bv0 = g_simDa.btvRcm.BV0.value;

    //------------------------相对血容量（放大100）--------------------------------<
    if(g_simDa.btvRcm.RBV.set.mode == AutoSimMode)
    {   //自动：实时血容量÷初始血容量×100%
        if((uint)g_simDa.btvRcm.BV0.value)
        {   //初始血容量未设置或为0
            g_simDa.btvRcm.RBV.value = g_simDa.btvRcm.BV.value/g_simDa.btvRcm.BV0.value*100;
        }
        else
        {
            g_simDa.btvRcm.RBV.value = 0;
        }
    }
    g_mbd.btv.rd2.rbv = (g_simDa.btvRcm.RBV.value + 0.005)*100;

    //----------------------实时清除率监测传感器校正--------------------------------<
    if(g_simDa.btvRcm.RCMCorrect.set.mode == AutoSimMode)
    {
        g_simDa.btvRcm.RCMCorrect.value = m_isAutoRCMCorrect;
    }
    setBitInByte(g_mbd.rcm.rd0.st, US_RD0_CT, g_simDa.btvRcm.RCMCorrect.value);

    //----------------------实时清除率监测传感器状态--------------------------------<
    setBitInByte(g_mbd.rcm.rd0.st, US_RD0_ST, g_simDa.btvRcm.RCMStatus.value);

    //-----------------------实时清除率监测检测状态---------------------------------<
    if(g_simDa.btvRcm.RCMDetect.set.mode == AutoSimMode)
    {
        g_simDa.btvRcm.RCMDetect.value = !!(g_mbd.rcm.wr0.cmd & US_WR0_SR);
    }
    setBitInByte(g_mbd.rcm.rd0.st, US_RD0_SR, g_simDa.btvRcm.RCMDetect.value);

    //--------------------------吸光度（放大100）----------------------------------<
    g_mbd.rcm.rd0.abs = (g_simDa.btvRcm.abs.value + 0.005)*100;
}
