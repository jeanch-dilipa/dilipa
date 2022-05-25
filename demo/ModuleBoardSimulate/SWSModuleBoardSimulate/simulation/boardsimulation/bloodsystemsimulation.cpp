#include "bloodsystemsimulation.h"

BloodSystemSimulation::BloodSystemSimulation(QObject *parent) : BoardSimulationBase(parent)
{
    //创建累计转数定时器
    m_calcRotNumTimer = new QTimer(this);
    m_calcRotNumTimer->setInterval(1000);
    connect(m_calcRotNumTimer, &QTimer::timeout, this, &BloodSystemSimulation::slotCalcRotationNum);
}

BloodSystemSimulation::~BloodSystemSimulation()
{
    if(m_calcRotNumTimer->isActive())
    {
        m_calcRotNumTimer->stop();
    }
}

void BloodSystemSimulation::initSimData()
{
    //初始化模拟数据类型
    addSimDataInit(C_BloodPumpSW, &g_simDa.bloodSys.bloodPumpSW, BinaryValueWithAuto);                         //血泵开关
    addSimDataInit(C_BloodPumpTargetSpeed, &g_simDa.bloodSys.bloodPumpTargetSpeed, NumericValueWithAuto, 1);   //血泵目标转速
    addSimDataInit(C_BloodPumpRealSpeed, &g_simDa.bloodSys.bloodPumpRealSpeed, NumericValueWithAutoRange, 1);  //血泵实时转速
    addSimDataInit(C_BloodPumpRolls, &g_simDa.bloodSys.bloodPumpRolls, NumericValueWithAuto, 2);               //血泵累计转数
    addSimDataInit(C_BloodPumpDirec, &g_simDa.bloodSys.bloodPumpDirec, BinaryValueWithAuto);                   //血泵方向
    addSimDataInit(C_BloodPumpBlock, &g_simDa.bloodSys.bloodPumpBlock, BinaryValue);                           //血泵堵转
    addSimDataInit(C_BloodPumpCover, &g_simDa.bloodSys.bloodPumpCover, BinaryValue);                           //血泵盖
    addSimDataInit(C_BloodPumpFpr, &g_simDa.bloodSys.bloodPumpFpr, NumericValueWithAuto, 1);                   //血泵泵管系数
    addSimDataInit(C_SubPumpSwitch, &g_simDa.bloodSys.subPumpSwitch, BinaryValueWithAuto);                     //置换液泵开关
    addSimDataInit(C_SubPumpTargetSpeed, &g_simDa.bloodSys.subPumpTargetSpeed, NumericValueWithAuto, 1);       //置换液泵目标转速
    addSimDataInit(C_SubPumpRealSpeed, &g_simDa.bloodSys.subPumpRealSpeed, NumericValueWithAutoRange, 1);      //置换液泵实时转速
    addSimDataInit(C_SubPumpRolls, &g_simDa.bloodSys.subPumpRolls, NumericValueWithAuto, 2);                   //置换液泵累计转数
    addSimDataInit(C_SubPumpDirec, &g_simDa.bloodSys.subPumpDirec, BinaryValueWithAuto);                       //置换液泵方向
    addSimDataInit(C_SubPumpBlock, &g_simDa.bloodSys.subPumpBlock, BinaryValue);                               //置换液泵堵转
    addSimDataInit(C_SubPumpCover, &g_simDa.bloodSys.subPumpCover, BinaryValue);                               //置换液泵盖
    addSimDataInit(C_SubPumpFpr, &g_simDa.bloodSys.subPumpFpr, NumericValueWithAuto, 1);                       //置换液泵泵管系数
    addSimDataInit(C_Vp, &g_simDa.bloodSys.vp, NumericValue);                                                  //静脉压
    addSimDataInit(C_Ap, &g_simDa.bloodSys.ap, NumericValue);                                                  //动脉压
    addSimDataInit(C_AirMonitor, &g_simDa.bloodSys.airMonitor, BinaryValue);                                   //空气监测
    addSimDataInit(C_BloodId, &g_simDa.bloodSys.bloodId, BinaryValue);                                         //血液识别
    addSimDataInit(C_ChokeClamp, &g_simDa.bloodSys.chokeClamp, BinaryValueWithAuto);                           //阻流夹
    addSimDataInit(C_VpAD, &g_simDa.bloodSys.vpAD, NumericValue);                                              //静脉压AD值
    addSimDataInit(C_VpZeroAD, &g_simDa.bloodSys.vpZeroAD, NumericValue);                                      //静脉压零点AD值
    addSimDataInit(C_VpSlopeAD, &g_simDa.bloodSys.vpSlopeAD, NumericValue);                                    //静脉压AD斜率值
    addSimDataInit(C_ApAD, &g_simDa.bloodSys.apAD, NumericValue);                                              //动脉压AD值
    addSimDataInit(C_ApZeroAD, &g_simDa.bloodSys.apZeroAD, NumericValue);                                      //动脉压零点AD值
    addSimDataInit(C_ApSlopeAD, &g_simDa.bloodSys.apSlopeAD, NumericValue);                                    //动脉压AD斜率值
    addSimDataInit(C_PAVCom, &g_simDa.bloodSys.PAVCom, BinaryValue);                                           //动静脉压板通信

    //插入模块板版本信息
    m_boardVersionCode = C_BloodSysBoardVersion;
    m_boardVersionList << &g_simDa.bloodSys.bloodBoardSoftVer << &g_simDa.bloodSys.bloodBoardHardVer
                       << &g_simDa.bloodSys.vapBoardSoftVer << &g_simDa.bloodSys.vapBoardHardVer
                       << &g_simDa.bloodSys.bloodPumpBoardSoftVer << &g_simDa.bloodSys.bloodPumpBoardHardVer
                       << &g_simDa.bloodSys.subPumpBoardSoftVer << &g_simDa.bloodSys.subPumpBoardHardVer;

    //血泵、置换液泵泵管系数默认（不能为0，会出问题）
    g_simDa.bloodSys.bloodPumpFpr.value = 1;
    g_simDa.bloodSys.subPumpFpr.value = 1;
    g_mbd.md4.blood.wr0.fpr = 10;
    g_mbd.md4.sub.wr0.fpr = 10;

    ///zf_test 一些数据默认初始化，便于测试
    g_simDa.bloodSys.vp.set.mode = RandomSimMode;
    g_simDa.bloodSys.vp.set.randomMinValue = 69;
    g_simDa.bloodSys.vp.set.randomMaxValue = 75;
    ///zf_test_end
}

void BloodSystemSimulation::recvWriteCmd4000(ModuleBoardAddrType addr, SystemBusCommandType cmd, const QByteArray &data)
{
    if(addr == BLOOD_PUMP_BOARD_ADDR4)
    {   //血泵板
        if(cmd == WRITE_COMMAND_0) //控制命令
        {
            memcpy(&g_mbd.md4.blood.wr0, data.data(), sizeof(g_mbd.md4.blood.wr0));

            if(g_mbd.md4.blood.wr0.cmd & DIRECTPUMP_WR0_Z)
            {   //累计转数清零
                m_bloodPumpRolls = 0;
            }
        }
    }
    else if(addr == FLUID_INFUSION_PUMP_BOARD_ADDR4)
    {   //补液泵板
        if(cmd == WRITE_COMMAND_0) //控制命令
        {
            memcpy(&g_mbd.md4.sub.wr0, data.data(), sizeof(g_mbd.md4.sub.wr0));

            if(g_mbd.md4.sub.wr0.cmd & DIRECTPUMP_WR0_Z)
            {   //累计转数清零
                m_subPumpRolls = 0;
            }
        }
    }
    else if(addr == DRIVER_BOARD_ADDR4)
    {   //驱动板
        if(cmd == WRITE_COMMAND_0)
        {
            memcpy(&g_mbd.md4.drive.wr0, data.data(), sizeof(g_mbd.md4.drive.wr0));
        }
    }
}

void BloodSystemSimulation::recvWriteCmd6000(ModuleBoardAddrType /*addr*/, SystemBusCommandType cmd, const QByteArray &data)
{
    switch(cmd)
    {
    case WRITE_COMMAND_0: //自检命令
        ///预留
        break;
    case WRITE_COMMAND_1: //血泵控制命令
        memcpy(&g_mbd.md6.btd.wr1, data.data(), sizeof(g_mbd.md6.btd.wr1));

        if(g_mbd.md6.btd.wr1.cmd & TDB_WR1_FLOW)
        {   //流量清零
            m_bloodPumpRolls = 0;
        }
        break;
    case WRITE_COMMAND_2: //置换液泵控制命令
        memcpy(&g_mbd.md6.btd.wr2, data.data(), sizeof(g_mbd.md6.btd.wr2));

        if(g_mbd.md6.btd.wr2.cmd & TDB_WR2_FLOW)
        {   //流量清零
            m_subPumpRolls = 0;
        }
        break;
    case WRITE_COMMAND_3: //阻流夹及静脉壶控制命令
        memcpy(&g_mbd.md6.btd.wr3, data.data(), sizeof(g_mbd.md6.btd.wr3));
        break;
    case WRITE_COMMAND_4: //动静脉压力校正命令
        ///预留
        break;
    case WRITE_COMMAND_5: //升级命令
        ///预留
        break;
    default:
        break;
    }
}

void BloodSystemSimulation::slotCalcRotationNum()
{
    if((int)g_simDa.bloodSys.bloodPumpSW.value != 0)
    {
        m_bloodPumpRolls += g_simDa.bloodSys.bloodPumpRealSpeed.value/60.0; //血泵累计转数
    }

    if((int)g_simDa.bloodSys.subPumpSwitch.value != 0)
    {
        m_subPumpRolls += g_simDa.bloodSys.subPumpRealSpeed.value/60.0; //置换液泵累计转数
    }
}

void BloodSystemSimulation::loadData4000()
{
    //-------------------------血泵板软硬件版本--------------------------------<
    g_mbd.md4.blood.rd7.ver_s = g_simDa.bloodSys.bloodPumpBoardSoftVer;
    g_mbd.md4.blood.rd7.ver_h = g_simDa.bloodSys.bloodPumpBoardHardVer;

    //-------------------------补液泵板软硬件版本------------------------------<
    g_mbd.md4.sub.rd7.ver_s = g_simDa.bloodSys.subPumpBoardSoftVer;
    g_mbd.md4.sub.rd7.ver_h = g_simDa.bloodSys.subPumpBoardHardVer;

    //----------------------血泵泵管系数（放大10倍）----------------------------<
    if(g_simDa.bloodSys.bloodPumpFpr.set.mode == AutoSimMode)
    {
        g_simDa.bloodSys.bloodPumpFpr.value = g_mbd.md4.blood.wr0.fpr/10.0;
    }
    g_mbd.md4.blood.rd0.fpr = g_simDa.bloodSys.bloodPumpFpr.value*10;

    //------------------------血泵目标转速（放大10倍）--------------------------<
    if(g_simDa.bloodSys.bloodPumpTargetSpeed.set.mode == AutoSimMode)
    {
        g_simDa.bloodSys.bloodPumpTargetSpeed.value = g_mbd.md4.blood.wr0.fpm/10.0/g_simDa.bloodSys.bloodPumpFpr.value;
    }
    g_mbd.md4.blood.rd0.fpm_set = g_simDa.bloodSys.bloodPumpTargetSpeed.value*g_simDa.bloodSys.bloodPumpFpr.value*10;

    //--------------------------血泵开关--------------------------------------<
    if(g_simDa.bloodSys.bloodPumpSW.set.mode == AutoSimMode)
    {
        g_simDa.bloodSys.bloodPumpSW.value = !!(g_mbd.md4.blood.wr0.cmd & DIRECTPUMP_WR0_SR);
    }
    setBitInByte(g_mbd.md4.blood.rd0.status, DIRECTPUMP_RD0_SR, g_simDa.bloodSys.bloodPumpSW.value);
    ctrlCalcRotationTimer(); //自动控制累计转数定时器

    //-----------------------血泵实时转速（放大10倍）---------------------------<
    if(g_simDa.bloodSys.bloodPumpRealSpeed.set.mode == AutoSimMode)
    {   //自动模拟时，根据目标转速加偏移值计算出实时值
        if((int)g_simDa.bloodSys.bloodPumpSW.value != 0)
        {   //血泵开才有实时转速
            g_simDa.bloodSys.bloodPumpRealSpeed.value = g_simDa.bloodSys.bloodPumpTargetSpeed.value + g_simDa.bloodSys.bloodPumpRealSpeed.fluctValue;
        }
        else
        {   //血泵关，实时转速为0
            g_simDa.bloodSys.bloodPumpRealSpeed.value = 0;
        }
    }
    g_mbd.md4.blood.rd0.fpm_real = g_simDa.bloodSys.bloodPumpRealSpeed.value*g_mbd.md4.blood.wr0.fpr;

    //----------------------血泵累计转数（放大60倍）---------------------------<
    if(g_simDa.bloodSys.bloodPumpRolls.set.mode == AutoSimMode)
    {
        g_simDa.bloodSys.bloodPumpRolls.value = m_bloodPumpRolls;
    }
    g_mbd.md4.blood.rd0.rolls = g_simDa.bloodSys.bloodPumpRolls.value*60;

    //--------------------------血泵方向--------------------------------------<
    if(g_simDa.bloodSys.bloodPumpDirec.set.mode == AutoSimMode)
    {
        g_simDa.bloodSys.bloodPumpDirec.value = !!(g_mbd.md4.blood.wr0.cmd & DIRECTPUMP_WR0_FR);
    }
    setBitInByte(g_mbd.md4.blood.rd0.status, DIRECTPUMP_RD0_FR, g_simDa.bloodSys.bloodPumpDirec.value);

    //--------------------------血泵堵转--------------------------------------<
    setBitInByte(g_mbd.md4.blood.rd0.status, DIRECTPUMP_RD0_ND, g_simDa.bloodSys.bloodPumpBlock.value);

    //---------------------------血泵盖---------------------------------------<
    setBitInByte(g_mbd.md4.blood.rd0.status, TDB_RD1_ON_CLOSED, g_simDa.bloodSys.bloodPumpCover.value);

    //----------------------置换液泵泵管系数（放大10倍）----------------------------<
    if(g_simDa.bloodSys.subPumpFpr.set.mode == AutoSimMode)
    {
        g_simDa.bloodSys.subPumpFpr.value = g_mbd.md4.sub.wr0.fpr/10.0;
    }
    g_mbd.md4.sub.rd0.fpr = g_simDa.bloodSys.subPumpFpr.value*10;

    //------------------------置换液泵目标转速（放大10倍）--------------------------<
    if(g_simDa.bloodSys.subPumpTargetSpeed.set.mode == AutoSimMode)
    {
        g_simDa.bloodSys.subPumpTargetSpeed.value = g_mbd.md4.sub.wr0.fpm/10.0/g_simDa.bloodSys.subPumpFpr.value;
    }
    g_mbd.md4.sub.rd0.fpm_set = g_simDa.bloodSys.subPumpTargetSpeed.value*g_simDa.bloodSys.subPumpFpr.value*10;

    //--------------------------置换液泵开关--------------------------------------<
    if(g_simDa.bloodSys.subPumpSwitch.set.mode == AutoSimMode)
    {
        g_simDa.bloodSys.subPumpSwitch.value = !!(g_mbd.md4.sub.wr0.cmd & DIRECTPUMP_WR0_SR);
    }
    setBitInByte(g_mbd.md4.sub.rd0.status, DIRECTPUMP_RD0_SR, g_simDa.bloodSys.subPumpSwitch.value);

    //-----------------------置换液泵实时转速（放大10倍）---------------------------<
    if(g_simDa.bloodSys.subPumpRealSpeed.set.mode == AutoSimMode)
    {   //自动模拟时，根据目标转速加偏移值计算出实时值
        if((int)g_simDa.bloodSys.subPumpSwitch.value != 0)
        {   //置换液泵开才有实时转速
            g_simDa.bloodSys.subPumpRealSpeed.value = g_simDa.bloodSys.subPumpTargetSpeed.value + g_simDa.bloodSys.subPumpRealSpeed.fluctValue;
        }
        else
        {   //置换液泵关，实时转速为0
            g_simDa.bloodSys.subPumpRealSpeed.value = 0;
        }
    }
    g_mbd.md4.sub.rd0.fpm_real = g_simDa.bloodSys.subPumpRealSpeed.value*g_mbd.md4.sub.wr0.fpr;

    //----------------------置换液泵累计转数（放大60倍）---------------------------<
    if(g_simDa.bloodSys.subPumpRolls.set.mode == AutoSimMode)
    {
        g_simDa.bloodSys.subPumpRolls.value = m_subPumpRolls;
    }
    g_mbd.md4.sub.rd0.rolls = g_simDa.bloodSys.subPumpRolls.value*60;

    //--------------------------置换液泵方向--------------------------------------<
    if(g_simDa.bloodSys.subPumpDirec.set.mode == AutoSimMode)
    {
        g_simDa.bloodSys.subPumpDirec.value = !!(g_mbd.md4.sub.wr0.cmd & DIRECTPUMP_WR0_FR);
    }
    setBitInByte(g_mbd.md4.sub.rd0.status, DIRECTPUMP_RD0_FR, g_simDa.bloodSys.subPumpDirec.value);

    //--------------------------置换液泵堵转--------------------------------------<
    setBitInByte(g_mbd.md4.sub.rd0.status, DIRECTPUMP_RD0_ND, g_simDa.bloodSys.subPumpBlock.value);

    //---------------------------置换液泵盖---------------------------------------<
    setBitInByte(g_mbd.md4.sub.rd0.status, TDB_RD1_ON_CLOSED, g_simDa.bloodSys.subPumpCover.value);

    //------------------------静脉压（放大10倍）-----------------------------------<
    g_mbd.md4.drive.rd1.vp = g_simDa.bloodSys.vp.value*10;

    //------------------------动脉压（放大10倍）-----------------------------------<
    g_mbd.md4.drive.rd1.ap = g_simDa.bloodSys.ap.value*10;

    //-----------------------------空气监测------------------------------------<
    setBitInByte(g_mbd.md4.drive.rd0.status1, DRIVERBOARD_RD0_GAS, g_simDa.bloodSys.airMonitor.value);

    //-----------------------------血液识别------------------------------------<
    setBitInByte(g_mbd.md4.drive.rd0.status2, DRIVERBOARD_RD0_BLOOD, !g_simDa.bloodSys.bloodId.value);

    //------------------------------阻流夹-------------------------------------<
    if(g_simDa.bloodSys.chokeClamp.set.mode == AutoSimMode)
    {
        g_simDa.bloodSys.chokeClamp.value = !!(g_mbd.md4.drive.wr0.cmd & DRIVERBOARD_WR0_ZLJ);
    }
    setBitInByte(g_mbd.md4.drive.rd0.status1, DRIVERBOARD_RD0_ZLJ, g_simDa.bloodSys.chokeClamp.value);
}

void BloodSystemSimulation::loadData6000()
{
    //----------------------------软硬件版本----------------------------------<
    g_mbd.md6.btd.rd7.sv = g_simDa.bloodSys.bloodBoardSoftVer;
    g_mbd.md6.btd.rd7.hv = g_simDa.bloodSys.bloodBoardHardVer;
    g_mbd.md6.btd.rd7.sv_p = g_simDa.bloodSys.vapBoardSoftVer;
    g_mbd.md6.btd.rd7.hv_p = g_simDa.bloodSys.vapBoardHardVer;

    //----------------------血泵目标转速（放大10倍）----------------------------<
    if(g_simDa.bloodSys.bloodPumpTargetSpeed.set.mode == AutoSimMode)
    {
        g_simDa.bloodSys.bloodPumpTargetSpeed.value = g_mbd.md6.btd.wr1.rpm/10.0;
    }
    g_mbd.md6.btd.rd1.rpm_tt = g_simDa.bloodSys.bloodPumpTargetSpeed.value * 10;

    //--------------------------血泵开关--------------------------------------<
    if(g_simDa.bloodSys.bloodPumpSW.set.mode == AutoSimMode)
    {
        g_simDa.bloodSys.bloodPumpSW.value = !!(g_mbd.md6.btd.wr1.cmd & TDB_WR1_BP);
    }
    setBitInByte(g_mbd.md6.btd.rd1.st1, TDB_RD1_ON_OFF, g_simDa.bloodSys.bloodPumpSW.value);
    ctrlCalcRotationTimer(); //自动控制累计转数定时器

    //-----------------------血泵实时转速（放大10倍）---------------------------<
    if(g_simDa.bloodSys.bloodPumpRealSpeed.set.mode == AutoSimMode)
    {   //自动模拟时，根据目标转速加偏移值计算出实时值
        if((int)g_simDa.bloodSys.bloodPumpSW.value != 0)
        {   //血泵开才有实时转速
            g_simDa.bloodSys.bloodPumpRealSpeed.value = g_simDa.bloodSys.bloodPumpTargetSpeed.value + g_simDa.bloodSys.bloodPumpRealSpeed.fluctValue;
        }
        else
        {   //血泵关，实时转速为0
            g_simDa.bloodSys.bloodPumpRealSpeed.value = 0;
        }
    }
    g_mbd.md6.btd.rd1.rpm_rt = g_simDa.bloodSys.bloodPumpRealSpeed.value*10;

    //----------------------血泵累计转数（放大100倍）---------------------------<
    if(g_simDa.bloodSys.bloodPumpRolls.set.mode == AutoSimMode)
    {
        g_simDa.bloodSys.bloodPumpRolls.value = m_bloodPumpRolls;
    }
    g_mbd.md6.btd.rd1.tr = g_simDa.bloodSys.bloodPumpRolls.value*100;

    //--------------------------血泵方向--------------------------------------<
    if(g_simDa.bloodSys.bloodPumpDirec.set.mode == AutoSimMode)
    {
        g_simDa.bloodSys.bloodPumpDirec.value = !!(g_mbd.md6.btd.wr1.cmd & TDB_WR1_CWR);
    }
    setBitInByte(g_mbd.md6.btd.rd1.st1, TDB_RD1_CW, g_simDa.bloodSys.bloodPumpDirec.value);

    //--------------------------血泵堵转--------------------------------------<
    setBitInByte(g_mbd.md6.btd.rd1.st1, TDB_RD1_STALL, g_simDa.bloodSys.bloodPumpBlock.value);

    //---------------------------血泵盖---------------------------------------<
    setBitInByte(g_mbd.md6.btd.rd1.st1, TDB_RD1_ON_CLOSED, g_simDa.bloodSys.bloodPumpCover.value);

    //----------------------置换液泵目标转速（放大10倍）-------------------------<
    if(g_simDa.bloodSys.subPumpTargetSpeed.set.mode == AutoSimMode)
    {
        g_simDa.bloodSys.subPumpTargetSpeed.value = g_mbd.md6.btd.wr2.rpm/10.0;
    }
    g_mbd.md6.btd.rd2.rpm_tt = g_simDa.bloodSys.subPumpTargetSpeed.value * 10;

    //--------------------------置换液泵开关-----------------------------------<
    if(g_simDa.bloodSys.subPumpSwitch.set.mode == AutoSimMode)
    {
        g_simDa.bloodSys.subPumpSwitch.value = !!(g_mbd.md6.btd.wr2.cmd & TDB_WR2_BP);
    }
    setBitInByte(g_mbd.md6.btd.rd2.st1, TDB_RD2_ON_OFF, g_simDa.bloodSys.subPumpSwitch.value);

    //-----------------------置换液泵实时转速（放大10倍）------------------------<
    if(g_simDa.bloodSys.subPumpRealSpeed.set.mode == AutoSimMode)
    {   //跟随主控时，根据主控目标转速加偏移值计算出实时值
        if((int)g_simDa.bloodSys.subPumpSwitch.value != 0)
        {   //置换液泵开才有实时转速
            g_simDa.bloodSys.subPumpRealSpeed.value = g_simDa.bloodSys.subPumpTargetSpeed.value + g_simDa.bloodSys.subPumpRealSpeed.fluctValue;
        }
        else
        {   //置换液泵关，实时转速为0
            g_simDa.bloodSys.subPumpRealSpeed.value = 0;
        }
    }
    g_mbd.md6.btd.rd2.rpm_rt = g_simDa.bloodSys.subPumpRealSpeed.value*10;

    //----------------------置换液泵累计转数（放大100倍）------------------------<
    if(g_simDa.bloodSys.subPumpRolls.set.mode == AutoSimMode)
    {
        g_simDa.bloodSys.subPumpRolls.value = m_subPumpRolls;
    }
    g_mbd.md6.btd.rd2.tr = g_simDa.bloodSys.subPumpRolls.value*100;

    //-------------------------置换液泵方向------------------------------------<
    if(g_simDa.bloodSys.subPumpDirec.set.mode == AutoSimMode)
    {
        g_simDa.bloodSys.subPumpDirec.value = !!(g_mbd.md6.btd.wr2.cmd & TDB_WR2_CWR);
    }
    setBitInByte(g_mbd.md6.btd.rd2.st1, TDB_RD2_CW, g_simDa.bloodSys.subPumpDirec.value);

    //--------------------------置换液泵堵转-----------------------------------<
    setBitInByte(g_mbd.md6.btd.rd2.st1, TDB_RD2_STALL, g_simDa.bloodSys.subPumpBlock.value);

    //---------------------------置换液泵盖------------------------------------<
    setBitInByte(g_mbd.md6.btd.rd2.st1, TDB_RD2_ON_CLOSED, g_simDa.bloodSys.subPumpCover.value);

    //-----------------------------静脉压--------------------------------------<
    g_mbd.md6.btd.rd3.vp = g_simDa.bloodSys.vp.value;

    //-----------------------------动脉压--------------------------------------<
    g_mbd.md6.btd.rd3.ap = g_simDa.bloodSys.ap.value;

    //-----------------------------空气监测------------------------------------<
    setBitInByte(g_mbd.md6.btd.rd3.st, TDB_RD3_AM, g_simDa.bloodSys.airMonitor.value);

    //-----------------------------血液识别------------------------------------<
    setBitInByte(g_mbd.md6.btd.rd3.st, TDB_RD3_BC, g_simDa.bloodSys.bloodId.value);

    //------------------------------阻流夹-------------------------------------<
    if(g_simDa.bloodSys.chokeClamp.set.mode == AutoSimMode)
    {
        g_simDa.bloodSys.chokeClamp.value = (g_mbd.md6.btd.wr3.cmd == TDB_WR3_ON);
    }
    setBitInByte(g_mbd.md6.btd.rd3.st, TDB_RD3_CC, !g_simDa.bloodSys.chokeClamp.value);

    //----------------------------动静脉压板通信--------------------------------<
    setBitInByte(g_mbd.md6.btd.rd3.st, TDB_RD3_BLM, g_simDa.bloodSys.PAVCom.value);
}

void BloodSystemSimulation::ctrlCalcRotationTimer()
{
    if((int)g_simDa.bloodSys.bloodPumpSW.value != 0 || (int)g_simDa.bloodSys.subPumpSwitch.value != 0)
    {   //血泵或置换液泵有一个打开，打开累计转数定时器
        if(!m_calcRotNumTimer->isActive())
        {   //开始累计转数
            m_calcRotNumTimer->start();
        }
    }
    else
    {
        if(m_calcRotNumTimer->isActive())
        {   //停止累计转数
            m_calcRotNumTimer->stop();
        }
    }
}
