/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   moduleboard.cpp
    info:	Module board communication interface
******************************************************************************/

#include "moduleboard.h"
#include "datadeal/common/publicdata.h"

QPointer<ModuleBoard> ModuleBoard::s_mb = nullptr;
QMutex *ModuleBoard::s_mutexLocker = nullptr;

/****************************************************************************
接口描述: 创建模块板通信处理类实例
输   入: /
输   出: /
******************************************************************************/
ModuleBoard &ModuleBoard::initModuleBoard()
{
    if(nullptr == s_mb)
    {
        QMutexLocker locker(s_mutexLocker);
        if(nullptr == s_mb)
        {
            s_mb = new ModuleBoard();
        }
    }

    return *s_mb;
}

/****************************************************************************
接口描述: 模块板通信注册
输   入: addr---模块板地址, command---指令
输   出: /
******************************************************************************/
void ModuleBoard::registerDataDeliveryQueue(const ModuleBoardAddrType addr, const SystemBusCommandType command)
{
    QPointer<ModuleBoardBase> board = m_moduleBoardMap.value(addr, nullptr);
    if(nullptr != board)
    {
        DataAttributeType attr = board->getAttribute(command);
        attr.m_dataType = REGISTER_TYPE_DATA;
        emit signal_sendUartData(attr, QByteArray());
    }
}

/****************************************************************************
接口描述: 模块板通信注销
输   入: addr---模块板地址, aommand---指令
输   出: /
******************************************************************************/
void ModuleBoard::unRegisterDataDeliveryQueue(const ModuleBoardAddrType addr, const SystemBusCommandType command)
{
    QPointer<ModuleBoardBase> board = m_moduleBoardMap.value(addr, nullptr);
    if(nullptr != board)
    {
        DataAttributeType attr = board->getAttribute(command);
        attr.m_dataType = UNREGISTER_TYPE_DATA;
        emit signal_sendUartData(attr, QByteArray());
    }
}

/****************************************************************************
接口描述: 设置模块板数据属性
输   入: attribute---数据属性
输   出: /
******************************************************************************/
void ModuleBoard::setModuleBoardDataAttribute(const DataAttributeType attribute)
{
    m_moduleBoardMap.value(attribute.m_module.m_boardAddr)->setAttribute(attribute);
}

/****************************************************************************
接口描述: 指令下发
输   入: tag---待下发模块板
输   出: /
******************************************************************************/
void ModuleBoard::sync(SyncTag tag)
{

}

/****************************************************************************
接口描述: 模块板通信管理类构造函数
输   入: /
输   出: /
******************************************************************************/
ModuleBoard::ModuleBoard()
{
    QMultiMap<SystemBusCommandType, void*> dataMap = {};
    QPointer<ModuleBoardBase> board = nullptr;

    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_0, &g_pd.m_mdb.bp.wr0);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_9, &g_pd.m_mdb.bp.wr9);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_0, &g_pd.m_mdb.bp.rd0);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_7, &g_pd.m_mdb.bp.rd7);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_8, &g_pd.m_mdb.bp.rd8);
    board = new ModuleBoardBase(dataMap);
    m_moduleBoardMap.insert(BLOOD_PUMP_BOARD_ADDRESS, board);               //血泵

    dataMap.clear();
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_0, &g_pd.m_mdb.fp.wr0);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_9, &g_pd.m_mdb.fp.wr9);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_0, &g_pd.m_mdb.fp.rd0);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_7, &g_pd.m_mdb.fp.rd7);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_8, &g_pd.m_mdb.fp.rd8);
    board = new ModuleBoardBase(dataMap);
    m_moduleBoardMap.insert(FLUID_INFUSION_PUMP_BOARD_ADDRESS, board);      //补液泵

    dataMap.clear();
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_0, &g_pd.m_mdb.ufp.wr0);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_9, &g_pd.m_mdb.ufp.wr9);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_0, &g_pd.m_mdb.ufp.rd0);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_7, &g_pd.m_mdb.ufp.rd7);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_8, &g_pd.m_mdb.ufp.rd8);
    board = new ModuleBoardBase(dataMap);
    m_moduleBoardMap.insert(ULTRAFILTRATION_PUMP_BOARD_ADDRESS, board);     //超滤泵

    dataMap.clear();
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_0, &g_pd.m_mdb.hp.wr0);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_9, &g_pd.m_mdb.hp.wr9);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_0, &g_pd.m_mdb.hp.rd0);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_7, &g_pd.m_mdb.hp.rd7);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_8, &g_pd.m_mdb.hp.rd8);
    board = new ModuleBoardBase(dataMap);
    m_moduleBoardMap.insert(HEPARIN_PUMP_BOARD_ADDRESS, board);             //肝素泵

    dataMap.clear();
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_0, &g_pd.m_mdb.drive.wr0);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_1, &g_pd.m_mdb.drive.wr1);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_9, &g_pd.m_mdb.drive.wr9);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_0, &g_pd.m_mdb.drive.rd0);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_1, &g_pd.m_mdb.drive.rd1);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_2, &g_pd.m_mdb.drive.rd2);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_3, &g_pd.m_mdb.drive.rd3);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_7, &g_pd.m_mdb.drive.rd7);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_8, &g_pd.m_mdb.drive.rd8);
    board = new ModuleBoardBase(dataMap);
    m_moduleBoardMap.insert(DRIVER_BOARD_ADDRESS, board);                   //驱动板

    dataMap.clear();
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_0, &g_pd.m_mdb.balance.wr0);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_1, &g_pd.m_mdb.balance.wr1);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_2, &g_pd.m_mdb.balance.wr2);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_3, &g_pd.m_mdb.balance.wr3);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_9, &g_pd.m_mdb.balance.wr9);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_0, &g_pd.m_mdb.balance.rd0);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_1, &g_pd.m_mdb.balance.rd1);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_2, &g_pd.m_mdb.balance.rd2);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_3, &g_pd.m_mdb.balance.rd3);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_7, &g_pd.m_mdb.balance.rd7);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_8, &g_pd.m_mdb.balance.rd8);
    board = new ModuleBoardBase(dataMap);
    m_moduleBoardMap.insert(BALANCE_CHAMBER_BOARD_ADDRESS, board);          //平衡腔板

    dataMap.clear();
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_0, &g_pd.m_mdb.mixture.wr0);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_1, &g_pd.m_mdb.mixture.wr1);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_9, &g_pd.m_mdb.mixture.wr9);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_0, &g_pd.m_mdb.mixture.rd0);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_1, &g_pd.m_mdb.mixture.rd1);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_7, &g_pd.m_mdb.mixture.rd7);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_8, &g_pd.m_mdb.mixture.rd8);
    board = new ModuleBoardBase(dataMap);
    m_moduleBoardMap.insert(MIXED_BOARD_ADDRESS, board);                    //配液板

    dataMap.clear();
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_9, &g_pd.m_mdb.monitor.wr9);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_7, &g_pd.m_mdb.monitor.rd7);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_8, &g_pd.m_mdb.monitor.rd8);
    board = new ModuleBoardBase(dataMap);
    m_moduleBoardMap.insert(MONITOR_BOARD_ADDRESS, board);                  //监控板

    dataMap.clear();
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_0, &g_pd.m_mdb.heat.wr0);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_1, &g_pd.m_mdb.heat.wr1);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_9, &g_pd.m_mdb.heat.wr9);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_0, &g_pd.m_mdb.heat.rd0);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_7, &g_pd.m_mdb.heat.rd7);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_8, &g_pd.m_mdb.heat.rd8);
    board = new ModuleBoardBase(dataMap);
    m_moduleBoardMap.insert(HEATER_BOARD_ADDRESS, board);                   //加热板

    dataMap.clear();
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_0, &g_pd.m_mdb.power.wr0);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_1, &g_pd.m_mdb.power.wr1);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_9, &g_pd.m_mdb.power.wr9);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_0, &g_pd.m_mdb.power.rd0);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_7, &g_pd.m_mdb.power.rd7);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_8, &g_pd.m_mdb.power.rd8);
    board = new ModuleBoardBase(dataMap);
    m_moduleBoardMap.insert(POWER_BOARD_ADDRESS, board);                    //电源板

    dataMap.clear();
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_0, &g_pd.m_mdb.cond.wr0);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_9, &g_pd.m_mdb.cond.wr9);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_0, &g_pd.m_mdb.cond.rd0);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_1, &g_pd.m_mdb.cond.rd1);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_7, &g_pd.m_mdb.cond.rd7);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_8, &g_pd.m_mdb.cond.rd8);
    board = new ModuleBoardBase(dataMap);
    m_moduleBoardMap.insert(CONDUCTANCE_BOARD_C_ADDRESS, board);            //电导板

    dataMap.clear();
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_0, &g_pd.m_mdb.bpm.wr0);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_1, &g_pd.m_mdb.bpm.wr1);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_0, &g_pd.m_mdb.bpm.rd0);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_1, &g_pd.m_mdb.bpm.rd1);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_2, &g_pd.m_mdb.bpm.rd2);
    board = new ModuleBoardBase(dataMap);
    m_moduleBoardMap.insert(BLOOD_PRESSURE_BOARD_ADDRESS, board);           //血压计

    dataMap.clear();
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_0, &g_pd.m_mdb.rcm.wr0);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_9, &g_pd.m_mdb.rcm.wr9);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_0, &g_pd.m_mdb.rcm.rd0);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_7, &g_pd.m_mdb.rcm.rd7);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_8, &g_pd.m_mdb.rcm.rd8);
    board = new ModuleBoardBase(dataMap);
    m_moduleBoardMap.insert(ONLINE_KTV_BOARD_ADDRESS, board);               //实时清除率

    dataMap.clear();
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_0, &g_pd.m_mdb.btbv.wr0);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_1, &g_pd.m_mdb.btbv.wr1);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_2, &g_pd.m_mdb.btbv.wr2);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_7, &g_pd.m_mdb.btbv.wr7);
    dataMap.insert(SYSTEM_BUS_WRITE_COMMAND_9, &g_pd.m_mdb.btbv.wr9);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_0, &g_pd.m_mdb.btbv.rd0);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_1, &g_pd.m_mdb.btbv.rd1);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_2, &g_pd.m_mdb.btbv.rd2);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_3, &g_pd.m_mdb.btbv.rd3);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_7, &g_pd.m_mdb.btbv.rd7);
    dataMap.insert(SYSTEM_BUS_READ_COMMAND_8, &g_pd.m_mdb.btbv.rd8);
    board = new ModuleBoardBase(dataMap);
    m_moduleBoardMap.insert(BTBV_BOARD_ADDRESS, board);                     //血温血容

    dataMap.clear();
    dataMap.insert(SYSTEM_BUS_KEY_PRESSED_COMMAND, &g_pd.m_mdb.monitor.rd0);
    board = new ModuleBoardBase(dataMap);
    m_moduleBoardMap.insert(KEYPRESS_BOARD_ADDRESS, board);                 //按键板

    dataMap.clear();
    dataMap.insert(SYSTEM_BUS_PILOT_LAMP_COMMAND , &g_pd.m_mdb.monitor.wr0);
    board = new ModuleBoardBase(dataMap);
    m_moduleBoardMap.insert(PILOT_LAMP_BOARD_ADDRESS, board);               //指示灯
}

/****************************************************************************
接口描述: 模块板通信管理类析构函数
输   入: /
输   出: /
******************************************************************************/
ModuleBoard::~ModuleBoard()
{

}
