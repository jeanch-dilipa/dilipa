#include "mixultrasystemsimulation.h"

MixUltraSystemSimulation::MixUltraSystemSimulation(QObject *parent) : BoardSimulationBase(parent)
{
    //创建累计转数定时器
    m_calcRotNumTimer = new QTimer(this);
    m_calcRotNumTimer->setInterval(1000);
    connect(m_calcRotNumTimer, &QTimer::timeout, this, &MixUltraSystemSimulation::slotCalcRotationNum);
}

MixUltraSystemSimulation::~MixUltraSystemSimulation()
{
    if(m_calcRotNumTimer->isActive())
    {
        m_calcRotNumTimer->stop();
    }
}

void MixUltraSystemSimulation::recvWriteCmd4000(ModuleBoardAddrType addr, SystemBusCommandType cmd, const QByteArray &data)
{
    if(addr == MIXED_BOARD_ADDR4)
    {   //配液板
        switch(cmd)
        {
        case WRITE_COMMAND_0: //配液控制命令
            memcpy(&g_mbd.md4.mix.wr0, data.data(), sizeof(g_mbd.md4.mix.wr0));
            break;
        case WRITE_COMMAND_1: //电导校正命令
            memcpy(&g_mbd.md4.mix.wr1, data.data(), sizeof(g_mbd.md4.mix.wr1));
            break;
        default:
            break;
        }
    }
    else if(addr == ULTRAFILTRATION_PUMP_BOARD_ADDR4)
    {   //超滤板
        switch(cmd)
        {
        case WRITE_COMMAND_0: //超滤泵控制命令
            memcpy(&g_mbd.md4.uf.wr0, data.data(), sizeof(g_mbd.md4.uf.wr0));

            if(g_mbd.md4.uf.wr0.cmd & UFPUMP_WR0_Z)
            {   //超滤泵转数清零
                m_ufPumpRolls = 0;
            }
            break;
        default:
            break;
        }
    }
    else if(addr == CONDUCTANCE_BOARD_ADDR4)
    {   //电导板
        switch(cmd)
        {
        case WRITE_COMMAND_1: //电导标定命令
            memcpy(&g_mbd.md4.cond.wr1, data.data(), sizeof(g_mbd.md4.cond.wr1));
            break;
        default:
            break;
        }
    }
}

void MixUltraSystemSimulation::recvWriteCmd6000(ModuleBoardAddrType /*addr*/, SystemBusCommandType cmd, const QByteArray &data)
{
    switch(cmd)
    {
    case WRITE_COMMAND_0: //配液控制命令
        memcpy(&g_mbd.md6.cpd.wr0, data.data(), sizeof(g_mbd.md6.cpd.wr0));

        if(g_mbd.md6.cpd.wr0.p_cmd & CPB_WR0_AF)
        {   //A泵转数清零
            m_APumpRolls = 0;
        }
        if(g_mbd.md6.cpd.wr0.p_cmd & CPB_WR0_BF)
        {   //B泵转数清零
            m_BPumpRolls = 0;
        }
        break;
    case WRITE_COMMAND_1: //超滤泵控制命令
        memcpy(&g_mbd.md6.cpd.wr1, data.data(), sizeof(g_mbd.md6.cpd.wr1));

        if(g_mbd.md6.cpd.wr1.cmd & CPB_WR1_FLOW)
        {   //超滤泵转数清零
            m_ufPumpRolls = 0;
        }
        break;
    case WRITE_COMMAND_2: //电导校正控制命令
        ///预留
        break;
    case WRITE_COMMAND_9: //升级命令信息
        ///预留
        break;
    default:
        break;
    }
}

void MixUltraSystemSimulation::initSimData()
{
    addSimDataInit(C_MixSW, &g_simDa.mixUltraSys.mixSW, BinaryValueWithAuto);                                  //配液开关
    addSimDataInit(C_BCond, &g_simDa.mixUltraSys.BCond, NumericValueWithAutoRange, 3);                         //B电导
    addSimDataInit(C_ACond, &g_simDa.mixUltraSys.ACond, NumericValueWithAutoRange, 3);                         //A电导
    addSimDataInit(C_CCond, &g_simDa.mixUltraSys.CCond, NumericValueWithAutoRange, 3);                         //C电导
    addSimDataInit(C_AdjustRange, &g_simDa.mixUltraSys.adjustRange, NumericValueWithAuto);                     //配液调整范围
    addSimDataInit(C_WG2, &g_simDa.mixUltraSys.WG2, NumericValueWithAutoRange, 2);                             //WG2
    addSimDataInit(C_WG3, &g_simDa.mixUltraSys.WG3, NumericValueWithAutoRange, 2);                             //WG3
    addSimDataInit(C_WG4, &g_simDa.mixUltraSys.WG4, NumericValueWithAutoRange, 2);                             //WG4
    addSimDataInit(C_APumpSW, &g_simDa.mixUltraSys.APumpSW, BinaryValueWithAuto);                              //A泵开关
    addSimDataInit(C_APumpDirec, &g_simDa.mixUltraSys.APumpDirec, BinaryValueWithAuto);                        //A泵方向
    addSimDataInit(C_APumpBlock, &g_simDa.mixUltraSys.APumpBlock, BinaryValue);                                //A泵堵转
    addSimDataInit(C_APumpPhaseLoss, &g_simDa.mixUltraSys.APumpPhaseLoss, BinaryValue);                        //A泵缺相
    addSimDataInit(C_APumpTargetSpeed, &g_simDa.mixUltraSys.APumpTargetSpeed, NumericValueWithAutoRange, 1);   //A泵目标转速
    addSimDataInit(C_APumpRealSpeed, &g_simDa.mixUltraSys.APumpRealSpeed, NumericValueWithAutoRange, 1);       //A泵实际转速
    addSimDataInit(C_APumpRolls, &g_simDa.mixUltraSys.APumpRolls, NumericValueWithAutoRange, 2);               //A泵累计转数
    addSimDataInit(C_BPumpSW, &g_simDa.mixUltraSys.BPumpSW, BinaryValueWithAuto);                              //B泵开关
    addSimDataInit(C_BPumpDirec, &g_simDa.mixUltraSys.BPumpDirec, BinaryValueWithAuto);                        //B泵方向
    addSimDataInit(C_BPumpBlock, &g_simDa.mixUltraSys.BPumpBlock, BinaryValue);                                //B泵堵转
    addSimDataInit(C_BPumpPhaseLoss, &g_simDa.mixUltraSys.BPumpPhaseLoss, BinaryValue);                        //B泵缺相
    addSimDataInit(C_BPumpTargetSpeed, &g_simDa.mixUltraSys.BPumpTargetSpeed, NumericValueWithAutoRange, 1);   //B泵目标转速
    addSimDataInit(C_BPumpRealSpeed, &g_simDa.mixUltraSys.BPumpRealSpeed, NumericValueWithAutoRange, 1);       //B泵实际转速
    addSimDataInit(C_BPumpRolls, &g_simDa.mixUltraSys.BPumpRolls, NumericValueWithAutoRange, 2);               //B泵累计转数
    addSimDataInit(C_UfPumpSW, &g_simDa.mixUltraSys.ufPumpSW, BinaryValueWithAuto);                            //超滤泵开关
    addSimDataInit(C_UfPumpDirec, &g_simDa.mixUltraSys.ufPumpDirec, BinaryValueWithAuto);                      //超滤泵方向
    addSimDataInit(C_UfPumpBlock, &g_simDa.mixUltraSys.ufPumpBlock, BinaryValue);                              //超滤泵堵转
    addSimDataInit(C_UfPumpPhaseLoss, &g_simDa.mixUltraSys.ufPumpPhaseLoss, BinaryValue);                      //超滤泵缺相
    addSimDataInit(C_UfPumpTargetSpeed, &g_simDa.mixUltraSys.ufPumpTargetSpeed, NumericValueWithAutoRange, 1); //超滤泵目标转速
    addSimDataInit(C_UfPumpRealSpeed, &g_simDa.mixUltraSys.ufPumpRealSpeed, NumericValueWithAutoRange, 1);     //超滤泵实际转速
    addSimDataInit(C_UfPumpRolls, &g_simDa.mixUltraSys.ufPumpRolls, NumericValueWithAutoRange, 2);             //超滤泵累计转数

    //插入模块板版本信息
    m_boardVersionCode = C_MixUfSysBoardVersion;
    m_boardVersionList << &g_simDa.mixUltraSys.mixUfBoardSoftVer << &g_simDa.mixUltraSys.mixUfBoardHardVer
                       << &g_simDa.mixUltraSys.mixBoardSoftVer << &g_simDa.mixUltraSys.mixBoardHardVer
                       << &g_simDa.mixUltraSys.ufBoardSoftVer << &g_simDa.mixUltraSys.ufBoardHardVer
                       << &g_simDa.mixUltraSys.condBoardSoftVer << &g_simDa.mixUltraSys.condBoardHardVer;
}

void MixUltraSystemSimulation::loadData4000()
{
    //--------------------------配液板软硬件版本----------------------------------<
    g_mbd.md4.mix.rd7.ver_s = g_simDa.mixUltraSys.mixBoardSoftVer;
    g_mbd.md4.mix.rd7.ver_h = g_simDa.mixUltraSys.mixBoardHardVer;

    //--------------------------超滤板软硬件版本----------------------------------<
    g_mbd.md4.uf.rd7.ver_s = g_simDa.mixUltraSys.ufBoardSoftVer;
    g_mbd.md4.uf.rd7.ver_h = g_simDa.mixUltraSys.ufBoardHardVer;

    //--------------------------电导板软硬件版本----------------------------------<
    g_mbd.md4.cond.rd7.ver_s = g_simDa.mixUltraSys.condBoardSoftVer;
    g_mbd.md4.cond.rd7.ver_h = g_simDa.mixUltraSys.condBoardHardVer;

    //---------------------------配液工作模式------------------------------------<
    if(g_simDa.mixUltraSys.mixSW.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.mixSW.value = !(g_mbd.md4.mix.wr0.cmd == MIXTURE_WR0_WORK_MOD_STOP);
    }

    //-------------------------A电导（放大10倍）----------------------------------<
    if(g_simDa.mixUltraSys.ACond.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.ACond.value = g_mbd.md4.mix.wr0.Acond/10.0 + g_simDa.mixUltraSys.ACond.fluctValue;
    }
    g_mbd.md4.mix.rd0.Acond = g_mbd.md4.mix.wr0.Acond;
    g_mbd.md4.mix.rd0.rtAcond = g_simDa.mixUltraSys.ACond.value*10;

    //-------------------------B电导（放大10倍）----------------------------------<
    if(g_simDa.mixUltraSys.BCond.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.BCond.value = g_mbd.md4.mix.wr0.Bcond/10.0 + g_simDa.mixUltraSys.BCond.fluctValue;
    }
    g_mbd.md4.mix.rd0.Bcond = g_mbd.md4.mix.wr0.Bcond;
    g_mbd.md4.mix.rd0.rtBcond = g_simDa.mixUltraSys.BCond.value*10;

    //-------------------------C电导（放大10倍）----------------------------------<
    if(g_simDa.mixUltraSys.CCond.set.mode == AutoSimMode)
    {   //4000理论B导与C导相同
        g_simDa.mixUltraSys.CCond.value = g_mbd.md4.mix.wr0.Bcond/10.0 + g_simDa.mixUltraSys.CCond.fluctValue;
    }
    g_mbd.md4.cond.rd0.cond_a = g_simDa.mixUltraSys.CCond.value*10;

    //-------------------------WG2（放大10倍）----------------------------------<
    if(g_simDa.mixUltraSys.WG2.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.WG2.value = g_mbd.md4.heat.wr0.temp/10.0 + g_simDa.mixUltraSys.WG2.fluctValue;
    }
    g_mbd.md4.mix.rd0.rtAtemp = g_simDa.mixUltraSys.WG2.value*10;

    //-------------------------WG3（放大10倍）----------------------------------<
    if(g_simDa.mixUltraSys.WG3.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.WG3.value = g_mbd.md4.heat.wr0.temp/10.0 + g_simDa.mixUltraSys.WG3.fluctValue;
    }
    g_mbd.md4.mix.rd0.rtBtemp = g_simDa.mixUltraSys.WG3.value*10;

    //-------------------------WG4（放大10倍）----------------------------------<
    if(g_simDa.mixUltraSys.WG4.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.WG4.value = g_mbd.md4.heat.wr0.temp/10.0 + g_simDa.mixUltraSys.WG4.fluctValue;
    }
    quint16 temp = g_simDa.mixUltraSys.WG4.value*10;
    g_mbd.md4.cond.rd0.m_temp_a = (temp >> 8 | temp << 8); //转为大端模式

    //-----------------------------A泵开关---------------------------------------<
    if(g_simDa.mixUltraSys.APumpSW.set.mode == AutoSimMode)
    {   //配液开则A泵开
        g_simDa.mixUltraSys.APumpSW.value = g_simDa.mixUltraSys.mixSW.value;
    }
    setBitInByte(g_mbd.md4.mix.rd0.status, MIXTURE_RD0_A_SR, g_simDa.mixUltraSys.APumpSW.value);

    //-----------------------------A泵堵转---------------------------------------<
    setBitInByte(g_mbd.md4.mix.rd0.status, MIXTURE_RD0_A_ND, g_simDa.mixUltraSys.APumpBlock.value);

    //-----------------------------A泵缺相---------------------------------------<
    setBitInByte(g_mbd.md4.mix.rd0.status, MIXTURE_RD0_A_NP, g_simDa.mixUltraSys.APumpPhaseLoss.value);

    //----------------------------A泵目标转速------------------------------------<
    if(g_simDa.mixUltraSys.APumpTargetSpeed.set.mode == AutoSimMode)
    {
        if(g_mbd.md4.mix.wr0.Afpr != 0)
        {
            g_simDa.mixUltraSys.APumpTargetSpeed.value = g_mbd.md4.mix.wr0.Afpm/(float)g_mbd.md4.mix.wr0.Afpr*100.0 + g_simDa.mixUltraSys.APumpTargetSpeed.fluctValue;
        }
    }
    g_mbd.md4.mix.rd0.Arpm = g_simDa.mixUltraSys.APumpTargetSpeed.value;

    //-----------------------------A泵实际转速-----------------------------------<
    if(g_simDa.mixUltraSys.APumpRealSpeed.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.APumpRealSpeed.value = g_simDa.mixUltraSys.APumpTargetSpeed.value + g_simDa.mixUltraSys.APumpRealSpeed.fluctValue;
    }
    g_mbd.md4.mix.rd0.rtArpm = g_simDa.mixUltraSys.APumpRealSpeed.value;

    //-----------------------------B泵开关---------------------------------------<
    if(g_simDa.mixUltraSys.BPumpSW.set.mode == AutoSimMode)
    {   //配液开则B泵开
        g_simDa.mixUltraSys.BPumpSW.value = g_simDa.mixUltraSys.mixSW.value;
    }
    setBitInByte(g_mbd.md4.mix.rd0.status, MIXTURE_RD0_B_SR, g_simDa.mixUltraSys.BPumpSW.value);

    //-----------------------------B泵堵转---------------------------------------<
    setBitInByte(g_mbd.md4.mix.rd0.status, MIXTURE_RD0_B_ND, g_simDa.mixUltraSys.BPumpBlock.value);

    //-----------------------------B泵缺相---------------------------------------<
    setBitInByte(g_mbd.md4.mix.rd0.status, MIXTURE_RD0_B_NP, g_simDa.mixUltraSys.BPumpPhaseLoss.value);

    //----------------------------B泵目标转速------------------------------------<
    if(g_simDa.mixUltraSys.BPumpTargetSpeed.set.mode == AutoSimMode)
    {
        if(g_mbd.md4.mix.wr0.Bfpr != 0)
        {
            g_simDa.mixUltraSys.BPumpTargetSpeed.value = g_mbd.md4.mix.wr0.Bfpm/(float)g_mbd.md4.mix.wr0.Bfpr*100.0 + g_simDa.mixUltraSys.BPumpTargetSpeed.fluctValue;
        }
    }
    g_mbd.md4.mix.rd0.Brpm = g_simDa.mixUltraSys.BPumpTargetSpeed.value;

    //-----------------------------B泵实际转速-----------------------------------<
    if(g_simDa.mixUltraSys.BPumpRealSpeed.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.BPumpRealSpeed.value = g_simDa.mixUltraSys.BPumpTargetSpeed.value + g_simDa.mixUltraSys.BPumpRealSpeed.fluctValue;
    }
    g_mbd.md4.mix.rd0.rtBrpm = g_simDa.mixUltraSys.BPumpRealSpeed.value;

    //----------------------------超滤泵开关-------------------------------------<
    if(g_simDa.mixUltraSys.ufPumpSW.set.mode == AutoSimMode)
    {   //配液开则B泵开
        g_simDa.mixUltraSys.ufPumpSW.value = !!(g_mbd.md4.uf.wr0.cmd & UFPUMP_WR0_SR);
    }
    setBitInByte(g_mbd.md4.uf.rd0.status, UFPUMP_RD0_SR, g_simDa.mixUltraSys.ufPumpSW.value);

    //----------------------------超滤泵堵转-------------------------------------<
    setBitInByte(g_mbd.md4.uf.rd0.status, UFPUMP_RD0_ND, g_simDa.mixUltraSys.ufPumpBlock.value);

    //----------------------------超滤泵缺相-------------------------------------<
    setBitInByte(g_mbd.md4.uf.rd0.status, UFPUMP_RD0_NP, g_simDa.mixUltraSys.ufPumpPhaseLoss.value);

    //---------------------------超滤泵目标转速-----------------------------------<
    if(g_simDa.mixUltraSys.ufPumpTargetSpeed.set.mode == AutoSimMode)
    {
        if(g_mbd.md4.uf.wr0.fpr != 0)
        {
            g_simDa.mixUltraSys.ufPumpTargetSpeed.value = g_mbd.md4.uf.wr0.fph/60.0/(float)g_mbd.md4.uf.wr0.fpr*1000.0 + g_simDa.mixUltraSys.ufPumpTargetSpeed.fluctValue;
        }
    }
    g_mbd.md4.uf.rd0.fpm_set = g_simDa.mixUltraSys.ufPumpTargetSpeed.value*g_mbd.md4.uf.wr0.fpr*60/1000.0;

    //-----------------------超滤泵实际转速（放大10倍）-----------------------------<
    if(g_simDa.mixUltraSys.ufPumpRealSpeed.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.ufPumpRealSpeed.value = g_simDa.mixUltraSys.ufPumpTargetSpeed.value + g_simDa.mixUltraSys.ufPumpRealSpeed.fluctValue;
    }
    g_mbd.md4.uf.rd0.rpm = g_simDa.mixUltraSys.ufPumpRealSpeed.value*10;
    g_mbd.md4.uf.rd0.fpm_real = g_simDa.mixUltraSys.ufPumpRealSpeed.value*g_mbd.md4.uf.wr0.fpr*60/1000.0;

    //------------------------==-超滤泵累计流量------------=========--------------<
    if(g_simDa.mixUltraSys.ufPumpRolls.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.ufPumpRolls.value = m_ufPumpRolls;
    }
    g_mbd.md4.uf.rd0.flow = g_simDa.mixUltraSys.ufPumpRolls.value*g_mbd.md4.uf.wr0.fpr/1000.0;

    ctrlCalcRotationTimer(); //自动控制累计转数定时器
}

void MixUltraSystemSimulation::loadData6000()
{
    //----------------------------软硬件版本-------------------------------------<
    g_mbd.md6.cpd.rd7.sv = g_simDa.mixUltraSys.mixUfBoardSoftVer;
    g_mbd.md6.cpd.rd7.hv = g_simDa.mixUltraSys.mixUfBoardHardVer;

    //---------------------------配液工作模式------------------------------------<
    if(g_simDa.mixUltraSys.mixSW.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.mixSW.value = !!g_mbd.md6.cpd.wr0.mode;
    }
    g_mbd.md6.cpd.rd0.mode = g_simDa.mixUltraSys.mixSW.value;

    //-------------------------B电导（放大1000倍）--------------------------------<
    if(g_simDa.mixUltraSys.BCond.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.BCond.value = g_mbd.md6.cpd.wr0.cond_B/1000.0 + g_simDa.mixUltraSys.BCond.fluctValue;
    }
    g_mbd.md6.cpd.rd0.cond_B = g_simDa.mixUltraSys.BCond.value*1000;

    //-------------------------A电导（放大1000倍）--------------------------------<
    if(g_simDa.mixUltraSys.ACond.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.ACond.value = g_mbd.md6.cpd.wr0.cond_A/1000.0 + g_simDa.mixUltraSys.ACond.fluctValue;
    }
    g_mbd.md6.cpd.rd0.cond_A = g_simDa.mixUltraSys.ACond.value*1000;

    //-------------------------C电导（放大1000倍）--------------------------------<
    if(g_simDa.mixUltraSys.CCond.set.mode == AutoSimMode)
    {   //6000理论A导与C导相同
        g_simDa.mixUltraSys.CCond.value = g_mbd.md6.cpd.wr0.cond_A/1000.0 + g_simDa.mixUltraSys.CCond.fluctValue;
    }
    g_mbd.md6.cpd.rd0.cond_C = g_simDa.mixUltraSys.CCond.value*1000;

    //--------------------------配液调整范围-------------------------------------<
    if(g_simDa.mixUltraSys.adjustRange.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.adjustRange.value = g_mbd.md6.cpd.wr0.limits + g_simDa.mixUltraSys.adjustRange.fluctValue;
    }
    g_mbd.md6.cpd.rd0.limits = g_simDa.mixUltraSys.adjustRange.value;

    //-------------------------WG2（放大100倍）----------------------------------<
    if(g_simDa.mixUltraSys.WG2.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.WG2.value = (g_mbd.md6.ldd.wr1.temp + g_mbd.md6.ldd.wr1.temp_Offset)/100.0 + g_simDa.mixUltraSys.WG2.fluctValue;
    }
    g_mbd.md6.cpd.rd0.temp_B = g_simDa.mixUltraSys.WG2.value*100;

    //-------------------------WG3（放大100倍）----------------------------------<
    if(g_simDa.mixUltraSys.WG3.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.WG3.value = (g_mbd.md6.ldd.wr1.temp + g_mbd.md6.ldd.wr1.temp_Offset)/100.0 + g_simDa.mixUltraSys.WG3.fluctValue;
    }
    g_mbd.md6.cpd.rd0.temp_A = g_simDa.mixUltraSys.WG3.value*100;

    //-------------------------WG4（放大100倍）----------------------------------<
    if(g_simDa.mixUltraSys.WG4.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.WG4.value = (g_mbd.md6.ldd.wr1.temp + g_mbd.md6.ldd.wr1.temp_Offset)/100.0 + g_simDa.mixUltraSys.WG4.fluctValue;
    }
    g_mbd.md6.cpd.rd0.temp_C = g_simDa.mixUltraSys.WG4.value*100;

    //-----------------------------A泵开关---------------------------------------<
    if(g_simDa.mixUltraSys.APumpSW.set.mode == AutoSimMode)
    {   //配液开则A泵开
        g_simDa.mixUltraSys.APumpSW.value = g_simDa.mixUltraSys.mixSW.value;
    }
    setBitInByte(g_mbd.md6.cpd.rd1.a_st1, CPB_RD1_AP_OFF_ON, g_simDa.mixUltraSys.APumpSW.value);

    //-----------------------------A泵方向---------------------------------------<
    if(g_simDa.mixUltraSys.APumpDirec.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.APumpDirec.value = !!(g_mbd.md6.cpd.wr0.p_cmd & CPB_WR0_A);
    }
    setBitInByte(g_mbd.md6.cpd.rd1.a_st1, CPB_RD1_AP_CWR, g_simDa.mixUltraSys.APumpDirec.value);

    //-----------------------------A泵堵转---------------------------------------<
    setBitInByte(g_mbd.md6.cpd.rd1.a_st1, CPB_RD1_AP_MOTOR, g_simDa.mixUltraSys.APumpBlock.value);

    //-------------------------A泵目标转速（放大10倍）-----------------------------<
    if(g_simDa.mixUltraSys.APumpTargetSpeed.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.APumpTargetSpeed.value = g_mbd.md6.cpd.wr0.rpm_A/10.0 + g_simDa.mixUltraSys.APumpTargetSpeed.fluctValue;
    }
    g_mbd.md6.cpd.rd1.a_rpm_tt = g_simDa.mixUltraSys.APumpTargetSpeed.value*10;

    //-------------------------A泵实际转速（放大10倍）-----------------------------<
    if(g_simDa.mixUltraSys.APumpRealSpeed.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.APumpRealSpeed.value = g_simDa.mixUltraSys.APumpTargetSpeed.value + g_simDa.mixUltraSys.APumpRealSpeed.fluctValue;
    }
    g_mbd.md6.cpd.rd1.a_rpm_rt = g_simDa.mixUltraSys.APumpRealSpeed.value*10;

    //-------------------------A泵累计转数（放大100倍）----------------------------<
    if(g_simDa.mixUltraSys.APumpRolls.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.APumpRolls.value = m_APumpRolls;
    }
    g_mbd.md6.cpd.rd1.a_tr = g_simDa.mixUltraSys.APumpRolls.value*100;

    //-----------------------------B泵开关---------------------------------------<
    if(g_simDa.mixUltraSys.BPumpSW.set.mode == AutoSimMode)
    {   //配液开则B泵开
        g_simDa.mixUltraSys.BPumpSW.value = g_simDa.mixUltraSys.mixSW.value;
    }
    setBitInByte(g_mbd.md6.cpd.rd1.b_st1, CPB_RD1_BP_OFF_ON, g_simDa.mixUltraSys.BPumpSW.value);

    //-----------------------------B泵方向---------------------------------------<
    if(g_simDa.mixUltraSys.BPumpDirec.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.BPumpDirec.value = !!(g_mbd.md6.cpd.wr0.p_cmd & CPB_WR0_B);
    }
    setBitInByte(g_mbd.md6.cpd.rd1.b_st1, CPB_RD1_BP_CWR, g_simDa.mixUltraSys.BPumpDirec.value);

    //-----------------------------B泵堵转---------------------------------------<
    setBitInByte(g_mbd.md6.cpd.rd1.b_st1, CPB_RD1_BP_MOTOR, g_simDa.mixUltraSys.BPumpBlock.value);

    //-------------------------B泵目标转速（放大10倍）-----------------------------<
    if(g_simDa.mixUltraSys.BPumpTargetSpeed.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.BPumpTargetSpeed.value = g_mbd.md6.cpd.wr0.rpm_B/10.0 + g_simDa.mixUltraSys.BPumpTargetSpeed.fluctValue;
    }
    g_mbd.md6.cpd.rd1.b_rpm_tt = g_simDa.mixUltraSys.BPumpTargetSpeed.value*10;

    //-------------------------B泵实际转速（放大10倍）-----------------------------<
    if(g_simDa.mixUltraSys.BPumpRealSpeed.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.BPumpRealSpeed.value = g_simDa.mixUltraSys.BPumpTargetSpeed.value + g_simDa.mixUltraSys.BPumpRealSpeed.fluctValue;
    }
    g_mbd.md6.cpd.rd1.b_rpm_rt = g_simDa.mixUltraSys.BPumpRealSpeed.value*10;

    //-------------------------B泵累计转数（放大100倍）----------------------------<
    if(g_simDa.mixUltraSys.BPumpRolls.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.BPumpRolls.value = m_BPumpRolls;
    }
    g_mbd.md6.cpd.rd1.b_tr = g_simDa.mixUltraSys.BPumpRolls.value*100;

    //-----------------------------超滤开关--------------------------------------<
    if(g_simDa.mixUltraSys.ufPumpSW.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.ufPumpSW.value = !!(g_mbd.md6.cpd.wr1.cmd & CPB_WR1_OFF_ON);
    }
    setBitInByte(g_mbd.md6.cpd.rd2.st1, CPB_RD2_UF_OFF_ON, g_simDa.mixUltraSys.ufPumpSW.value);

    //-----------------------------超滤泵方向-------------------------------------<
    if(g_simDa.mixUltraSys.ufPumpDirec.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.ufPumpDirec.value = !!(g_mbd.md6.cpd.wr1.cmd & CPB_WR1_CWR);
    }
    setBitInByte(g_mbd.md6.cpd.rd2.st1, CPB_RD2_UF_CWR, g_simDa.mixUltraSys.ufPumpDirec.value);

    //-----------------------------超滤泵堵转-------------------------------------<
    setBitInByte(g_mbd.md6.cpd.rd2.st1, CPB_RD2_UF_MOTOR, g_simDa.mixUltraSys.ufPumpBlock.value);

    //-------------------------超滤泵目标转速（放大10倍）---------------------------<
    if(g_simDa.mixUltraSys.ufPumpTargetSpeed.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.ufPumpTargetSpeed.value = g_mbd.md6.cpd.wr1.rpm/10.0 + g_simDa.mixUltraSys.ufPumpTargetSpeed.fluctValue;
    }
    g_mbd.md6.cpd.rd2.rpm_tt = g_simDa.mixUltraSys.ufPumpTargetSpeed.value*10;

    //-------------------------超滤泵实际转速（放大10倍）---------------------------<
    if(g_simDa.mixUltraSys.ufPumpRealSpeed.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.ufPumpRealSpeed.value = g_simDa.mixUltraSys.ufPumpTargetSpeed.value + g_simDa.mixUltraSys.ufPumpRealSpeed.fluctValue;
    }
    g_mbd.md6.cpd.rd2.rpm_rt = g_simDa.mixUltraSys.ufPumpRealSpeed.value*10;

    //-------------------------超滤泵累计转数（放大100倍）--------------------------<
    if(g_simDa.mixUltraSys.ufPumpRolls.set.mode == AutoSimMode)
    {
        g_simDa.mixUltraSys.ufPumpRolls.value = m_ufPumpRolls;
    }
    g_mbd.md6.cpd.rd2.tr = g_simDa.mixUltraSys.ufPumpRolls.value*100;

    ctrlCalcRotationTimer(); //自动控制累计转数定时器
}

void MixUltraSystemSimulation::slotCalcRotationNum()
{
    if((bool)g_simDa.mixUltraSys.APumpSW.value)
    {
        m_APumpRolls += g_simDa.mixUltraSys.APumpRealSpeed.value/60.0;   //A泵累计转数
    }

    if((bool)g_simDa.mixUltraSys.BPumpSW.value)
    {
        m_BPumpRolls += g_simDa.mixUltraSys.BPumpRealSpeed.value/60.0;   //B泵累计转数
    }

    if((bool)g_simDa.mixUltraSys.ufPumpSW.value)
    {
        m_ufPumpRolls += g_simDa.mixUltraSys.ufPumpRealSpeed.value/60.0; //超滤泵累计转数
    }
}

void MixUltraSystemSimulation::ctrlCalcRotationTimer()
{
    if((bool)g_simDa.mixUltraSys.APumpSW.value || (bool)g_simDa.mixUltraSys.BPumpSW.value || (bool)g_simDa.mixUltraSys.ufPumpSW.value)
    {   //A、B泵或超滤泵有一个运行，打开累计转数定时器
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
