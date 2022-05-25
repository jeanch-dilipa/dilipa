#include "antisystemsimulation.h"

AntiSystemSimulation::AntiSystemSimulation(QObject *parent) : BoardSimulationBase(parent)
{
    m_Symap.insert(0, 0);
    m_Symap.insert(1, 10);
    m_Symap.insert(2, 20);
    m_Symap.insert(3, 30);
    m_Symap.insert(4, 50);

    //创建累计推注流量定时器
    m_calcHepTotalFlowTimer = new QTimer(this);
    m_calcHepTotalFlowTimer->setInterval(1000);
    connect(m_calcHepTotalFlowTimer, &QTimer::timeout, this, &AntiSystemSimulation::slotCalcHepFlowTimeout);
}

void AntiSystemSimulation::recvWriteCmd4000(ModuleBoardAddrType /*addr*/, SystemBusCommandType cmd, const QByteArray &data)
{
    switch(cmd)
    {
    case WRITE_COMMAND_0: //肝素控制命令
        memcpy(&g_mbd.md4.hep.wr0, data.data(), sizeof(g_mbd.md4.hep.wr0));

        if(g_mbd.md4.hep.wr0.cmd & HEPUMP_WR0_Z)
        {   //肝素流量清零
            m_hepTotalFlow = 0;
        }
        break;
    case WRITE_COMMAND_9:
        ///预留
        break;
    default:
        break;
    }
}

void AntiSystemSimulation::recvWriteCmd6000(ModuleBoardAddrType /*addr*/, SystemBusCommandType cmd, const QByteArray &data)
{
    switch(cmd)
    {
    case WRITE_COMMAND_0: //肝素控制命令
        memcpy(&g_mbd.md6.hpd.wr0, data.data(), sizeof(g_mbd.md6.hpd.wr0));

        if(g_mbd.md6.hpd.wr0.cmd & HPB_WR0_CLN)
        {   //肝素流量清零
            m_hepTotalFlow = 0;
        }
        break;
    case WRITE_COMMAND_1: //追加命令
        memcpy(&g_mbd.md6.hpd.wr1, data.data(), sizeof(g_mbd.md6.hpd.wr0));

        if(g_mbd.md6.hpd.wr1.volume != 0)
        {   //追加量不为0，开始追加
            m_isAppend = true;
        }
        else
        {   //追加量为0，停止追加
            m_isAppend = false;
            m_beforeAppendVolume = -1;
        }
        break;
    case WRITE_COMMAND_9: //升级命令信息
        ///预留
        break;
    default:
        break;
    }
}

void AntiSystemSimulation::initSimData()
{
    addSimDataInit(C_HepPumpSW, &g_simDa.antiSys.hepPumpSW, BinaryValueWithAuto);                  //肝素泵开关
    addSimDataInit(C_HepPumpDirec, &g_simDa.antiSys.hepPumpDirec, BinaryValueWithAuto);            //肝素泵方向
    addSimDataInit(C_HepPumpBlock, &g_simDa.antiSys.hepPumpBlock, BinaryValue);                    //肝素泵堵转
    addSimDataInit(C_InjectorSpeci, &g_simDa.antiSys.injectorSpeci, EnumValueWithAuto);            //注射器规格
    addSimDataInit(C_ArriveBottom, &g_simDa.antiSys.arriveBottom, BinaryValue);                    //肝素到底
    addSimDataInit(C_ArriveTop, &g_simDa.antiSys.arriveTop, BinaryValue);                          //肝素到顶
    addSimDataInit(C_HepPlateMove, &g_simDa.antiSys.hepPlateMove, BinaryValue);                    //肝素推板被移动
    addSimDataInit(C_HepLight, &g_simDa.antiSys.hepLight, BinaryValue);                            //光电开关被遮挡
    addSimDataInit(C_HepPumpError, &g_simDa.antiSys.hepPumpError, BinaryValue);                    //肝素泵故障
    addSimDataInit(C_HepTargetFlow, &g_simDa.antiSys.hepTargetFlow, NumericValueWithAutoRange, 1); //目标流量
    addSimDataInit(C_HepRealFlow, &g_simDa.antiSys.hepRealFlow, NumericValueWithAutoRange, 1);     //实际流量
    addSimDataInit(C_HepTotalFlow, &g_simDa.antiSys.hepTotalFlow, NumericValueWithAuto, 3);        //累计流量

    //插入模块板版本信息
    m_boardVersionCode = C_AntiSysBoardVersion;
    m_boardVersionList << &g_simDa.antiSys.hepBoardSoftVer << &g_simDa.antiSys.hepBoardHardVer;
}

void AntiSystemSimulation::loadData4000()
{
    //----------------------------软硬件版本-------------------------------------<
    g_mbd.md4.hep.rd7.ver_s = g_simDa.antiSys.hepBoardSoftVer;
    g_mbd.md4.hep.rd7.ver_h = g_simDa.antiSys.hepBoardHardVer;

    //----------------------------肝素泵开关-------------------------------------<
    if(g_simDa.antiSys.hepPumpSW.set.mode == AutoSimMode)
    {
        g_simDa.antiSys.hepPumpSW.value = !!(g_mbd.md4.hep.wr0.cmd & HEPUMP_WR0_SR);
    }
    setBitInByte(g_mbd.md4.hep.rd0.status, HEPUMP_RD0_SR, g_simDa.antiSys.hepPumpSW.value);

    //----------------------------肝素泵堵转-------------------------------------<
    setBitInByte(g_mbd.md4.hep.rd0.status, HEPUMP_RD0_ND, g_simDa.antiSys.hepPumpBlock.value);

    //----------------------------肝素泵到底-------------------------------------<
    setBitInByte(g_mbd.md4.hep.rd0.status, HEPUMP_RD0_BOM, g_simDa.antiSys.arriveBottom.value);

    //----------------------------肝素泵到顶-------------------------------------<
    setBitInByte(g_mbd.md4.hep.rd0.status, HEPUMP_RD0_TOP, g_simDa.antiSys.arriveTop.value);

    //----------------------------肝素泵故障-------------------------------------<
    setBitInByte(g_mbd.md4.hep.rd0.status, HEPUMP_RD0_ERR, g_simDa.antiSys.hepPumpError.value);

    //-------------------------目标流量（放大10倍）-------------------------------<
    if(g_simDa.antiSys.hepTargetFlow.set.mode == AutoSimMode)
    {
        g_simDa.antiSys.hepTargetFlow.value = g_mbd.md4.hep.wr0.fph/10.0 + g_simDa.antiSys.hepTargetFlow.fluctValue;
    }
    g_mbd.md4.hep.rd0.fph_set = g_simDa.antiSys.hepTargetFlow.value*10;

    //-------------------------实际流量（放大10倍）--------------------------------<
    if(g_simDa.antiSys.hepRealFlow.set.mode == AutoSimMode)
    {
        g_simDa.antiSys.hepRealFlow.value = g_simDa.antiSys.hepTargetFlow.value + g_simDa.antiSys.hepRealFlow.fluctValue;
    }
    g_mbd.md4.hep.rd0.fph_real = g_simDa.antiSys.hepRealFlow.value*10;

    //-------------------------累计流量（放大10倍）--------------------------------<
    if(g_simDa.antiSys.hepTotalFlow.set.mode == AutoSimMode)
    {
        g_simDa.antiSys.hepTotalFlow.value = m_hepTotalFlow;
    }
    g_mbd.md4.hep.rd0.flow = g_simDa.antiSys.hepTotalFlow.value*10;

    //自动开关流量累计定时器
    ctrlCalcRotationTimer();
}

void AntiSystemSimulation::loadData6000()
{
    //----------------------------软硬件版本-------------------------------------<
    g_mbd.md6.hpd.rd7.sv = g_simDa.antiSys.hepBoardSoftVer;
    g_mbd.md6.hpd.rd7.hv = g_simDa.antiSys.hepBoardHardVer;

    //----------------------------肝素泵开关-------------------------------------<
    if(g_simDa.antiSys.hepPumpSW.set.mode == AutoSimMode)
    {
        g_simDa.antiSys.hepPumpSW.value = !!(g_mbd.md6.hpd.wr0.cmd & HPB_WR0_ON_OFF);
    }
    setBitInByte(g_mbd.md6.hpd.rd0.hp_st1, HPB_RD0_OFF_RD, g_simDa.antiSys.hepPumpSW.value);

    //----------------------------肝素泵方向-------------------------------------<
    if(g_simDa.antiSys.hepPumpDirec.set.mode == AutoSimMode)
    {
        g_simDa.antiSys.hepPumpDirec.value = !!(g_mbd.md6.hpd.wr0.cmd & HPB_WR0_BCK);
    }
    setBitInByte(g_mbd.md6.hpd.rd0.hp_st1, HPB_RD0_BCK_RD, g_simDa.antiSys.hepPumpDirec.value);

    //----------------------------肝素泵堵转-------------------------------------<
    setBitInByte(g_mbd.md6.hpd.rd0.hp_st1, HPB_RD0_FRE_RD, g_simDa.antiSys.hepPumpBlock.value);

    //----------------------------注射器规格-------------------------------------<
    if(g_simDa.antiSys.injectorSpeci.set.mode == AutoSimMode)
    {
        g_simDa.antiSys.injectorSpeci.value = m_Symap.key(g_mbd.md6.hpd.wr0.syringe_type);
    }
    g_mbd.md6.hpd.rd0.Syringe_type = m_Symap.value(g_simDa.antiSys.injectorSpeci.value);

    //----------------------------肝素泵到底-------------------------------------<
    setBitInByte(g_mbd.md6.hpd.rd0.hp_st1, HPB_RD0_ARB_RD, g_simDa.antiSys.arriveBottom.value);

    //---------------------------肝素推板被移动-----------------------------------<
    setBitInByte(g_mbd.md6.hpd.rd0.hp_st1, HPB_RD0_PPM_RD, g_simDa.antiSys.hepPlateMove.value);

    //---------------------------光电开关被遮挡-----------------------------------<
    setBitInByte(g_mbd.md6.hpd.rd0.hp_st1, HPB_RD0_SLT_RD, g_simDa.antiSys.hepLight.value);

    //-------------------------实际流量（放大10倍）--------------------------------<
    if(g_simDa.antiSys.hepRealFlow.set.mode == AutoSimMode)
    {
        if(m_isAppend)
        {
            g_simDa.antiSys.hepRealFlow.value = g_mbd.md6.hpd.wr1.rate/10.0;
        }
        else
        {
            g_simDa.antiSys.hepRealFlow.value = g_mbd.md6.hpd.wr0.flow/10.0 + g_simDa.antiSys.hepRealFlow.fluctValue;
        }
    }
    g_mbd.md6.hpd.rd0.HP_LF = g_simDa.antiSys.hepRealFlow.value*10;

    //-------------------------累计流量（放大1000倍）------------------------------<
    if(g_simDa.antiSys.hepTotalFlow.set.mode == AutoSimMode)
    {
        g_simDa.antiSys.hepTotalFlow.value = m_hepTotalFlow;
    }
    g_mbd.md6.hpd.rd0.HP_SF = g_simDa.antiSys.hepTotalFlow.value*1000;

    //自动开关流量累计定时器
    ctrlCalcRotationTimer();
}

void AntiSystemSimulation::ctrlCalcRotationTimer()
{
    if((int)g_simDa.antiSys.hepPumpSW.value != 0)
    {
        if(!m_calcHepTotalFlowTimer->isActive())
        {   //开始累计转数
            m_calcHepTotalFlowTimer->start();
        }
    }
    else
    {
        if(m_calcHepTotalFlowTimer->isActive())
        {   //停止累计转数
            m_calcHepTotalFlowTimer->stop();
        }
    }
}

void AntiSystemSimulation::slotCalcHepFlowTimeout()
{
    if(g_ss.machineType == SWS4000 &&
            (((g_mbd.md4.hep.wr0.cmd & HEPUMP_WR0_M1) && !(g_mbd.md4.hep.wr0.cmd & HEPUMP_WR0_M0))
            || (!(g_mbd.md4.hep.wr0.cmd & HEPUMP_WR0_M1) && (g_mbd.md4.hep.wr0.cmd & HEPUMP_WR0_M0))))
    {   //4000型，正向或反向快速移动时，不计算流量（正常推注或追加模式才计算）
        return;
    }

    //开始追加前，记录下追加前的已推注总量
    if(m_isAppend && m_beforeAppendVolume < 0)
    {
        m_beforeAppendVolume = m_hepTotalFlow;
    }

    //累计肝素推注总量
    m_hepTotalFlow += g_simDa.antiSys.hepRealFlow.value/3600.0;

    //计算追加完成
    if(m_isAppend)
    {
        if((m_hepTotalFlow - m_beforeAppendVolume) >= (g_mbd.md6.hpd.wr1.volume/10.0))
        {
            m_isAppend = false;
            m_beforeAppendVolume = -1;
        }
    }
}
