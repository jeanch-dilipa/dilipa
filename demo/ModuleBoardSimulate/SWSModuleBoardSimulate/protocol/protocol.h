#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <QHash>
#include "common/common.h"
#include "sws4000/protoPacket4000.h"
#include "sws6000/protoPacket6000.h"

//--------------------------模块地址定义-----------------------------<
typedef enum
{
    MODULE_BOARD_ADDR_DEFAULT           = 0x00,

    //SWS4000
    BLOOD_PUMP_BOARD_ADDR4              = 0x01,   //血泵板地址
    FLUID_INFUSION_PUMP_BOARD_ADDR4     = 0x02,   //补液泵板地址
    ULTRAFILTRATION_PUMP_BOARD_ADDR4    = 0x03,   //超滤板地址
    HEPARIN_PUMP_BOARD_ADDR4            = 0x04,   //肝素板地址
    DRIVER_BOARD_ADDR4                  = 0x05,   //驱动板地址
    BALANCE_CHAMBER_BOARD_ADDR4         = 0x06,   //平衡腔板地址
    MIXED_BOARD_ADDR4                   = 0x07,   //配液板地址
    ///MONITOR_BOARD_ADDR4              = 0x09,   //监控板地址 --> 貌似没用
    CONDUCTANCE_BOARD_ADDR4             = 0x25,   //电导板地址
    BLOOD_PRESSURE_BOARD_ADDR4          = 0x27,   //血压计模块地址
    HEATER_BOARD_ADDR4                  = 0x0A,   //加热板地址
    ///WEIGHT_BOARD_ADDR4               = 0x0B,   //称重板地址 --> 没用
    POWER_BOARD_ADDR4                   = 0x0C,   //电源板地址
    KEYPRESS_BOARD_ADDR4                = 0x41,   //按键地址
    PILOT_LAMP_BOARD_ADDR4              = 0x42,   //指示灯地址
    ///MAIN_CONTROL_BOARD_ADDR4         = 0x55,   //主控板地址 --> 貌似没用

    //SWS6000
    MONITOR_BOARD_ADDR6                 = 0x10,   //主控板地址485
    KEY_LAMP_BOARD_ADDR6                = 0x11,   //主控板地址232,按键指示灯
    BLOOD_TRAIL_BOARD_ADDR6             = 0x12,   //血路驱动板地址
    HEPARIN_BOARD_ADDR6                 = 0x13,   //肝素板地址
    LIQUID_DRIVER_BOARD_ADDR6           = 0x14,   //水路驱动板地址
    MIX_ULTRA_BOARD_ADDR6               = 0x15,   //配液超滤板地址
    POWER_BOARD_ADDR6                   = 0x16,   //电源板地址
    BLOOD_PRESSURE_BOARD_ADDR6          = 0x17,   //血压计板地址
    AIR_DETECTOR_BOARD_ADDR6            = 0x26,   //空气监测板地址
    IC_CARD_READER_MODULE_ADDR6         = 0x27,   ///IC卡读卡器模块地址 --> 与4000血压计地址冲突，但为单独的串口，地址实际无多大意义
    UREA_SENSORE_MODULE_ADDR            = 0x28,   //实时清除率监测模块地址，4000，6000通用
    BLOOD_TEMP_VOLUME_MODULE_ADDR       = 0x29,   //血温血容量模块地址，4000，6000通用
}ModuleBoardAddrType;

//--------------------------读写命令定义-----------------------------<
typedef enum
{
    //写命令
    WRITE_COMMAND_0  =  0x30,     //WR0
    WRITE_COMMAND_1  =  0x31,     //WR1
    WRITE_COMMAND_2  =  0x32,     //WR2
    WRITE_COMMAND_3  =  0x33,     //WR3
    WRITE_COMMAND_4  =  0x34,     //WR4
    WRITE_COMMAND_5  =  0x35,     //WR5
    WRITE_COMMAND_6  =  0x36,     //WR6
    WRITE_COMMAND_7  =  0x37,     //WR7
    WRITE_COMMAND_8  =  0x38,     //WR8
    WRITE_COMMAND_9  =  0x39,     //WR9

    //读命令
    READ_COMMAND_0   =  0x40,     //RD0
    READ_COMMAND_1   =  0x41,     //RD1
    READ_COMMAND_2   =  0x42,     //RD2
    READ_COMMAND_3   =  0x43,     //RD3
    READ_COMMAND_4   =  0x44,     //RD4
    READ_COMMAND_5   =  0x45,     //RD5
    READ_COMMAND_6   =  0x46,     //RD6
    READ_COMMAND_7   =  0x47,     //RD7
    READ_COMMAND_8   =  0x48,     //RD8
}SystemBusCommandType;

//--------------------------定义模块板数据---------------------------<
//用于保存模块数据指针及数据大小
struct BoardDataPointer
{
    BoardDataPointer(){}
    BoardDataPointer(void *ptr, size_t size)
    {
        this->ptr = ptr;
        this->size = size;
    }

    void *ptr = NULL;
    size_t size = 0;
};

struct ModuleBoardData
{
    ModuleBoardData()
    {
        //数据清空
        memset(&md4, 0, sizeof(md4));
        memset(&md6, 0, sizeof(md6));

        QHash<int, BoardDataPointer> cmdhash;
        //--------------------------------插入4000型RD数据----------------------------------<
        //血泵板
        cmdhash.insert(READ_COMMAND_0, BoardDataPointer(&md4.blood.rd0, sizeof(md4.blood.rd0)));
        cmdhash.insert(READ_COMMAND_7, BoardDataPointer(&md4.blood.rd7, sizeof(md4.blood.rd7)));
        m_rdPtrHash.insert(BLOOD_PUMP_BOARD_ADDR4, cmdhash);

        //置换液泵板
        cmdhash.clear();
        cmdhash.insert(READ_COMMAND_0, BoardDataPointer(&md4.sub.rd0, sizeof(md4.sub.rd0)));
        cmdhash.insert(READ_COMMAND_7, BoardDataPointer(&md4.sub.rd7, sizeof(md4.sub.rd7)));
        m_rdPtrHash.insert(FLUID_INFUSION_PUMP_BOARD_ADDR4, cmdhash);

        //超滤板
        cmdhash.clear();
        cmdhash.insert(READ_COMMAND_0, BoardDataPointer(&md4.uf.rd0, sizeof(md4.uf.rd0)));
        cmdhash.insert(READ_COMMAND_7, BoardDataPointer(&md4.uf.rd7, sizeof(md4.uf.rd7)));
        m_rdPtrHash.insert(ULTRAFILTRATION_PUMP_BOARD_ADDR4, cmdhash);

        //肝素板
        cmdhash.clear();
        cmdhash.insert(READ_COMMAND_0, BoardDataPointer(&md4.hep.rd0, sizeof(md4.hep.rd0)));
        cmdhash.insert(READ_COMMAND_7, BoardDataPointer(&md4.hep.rd7, sizeof(md4.hep.rd7)));
        m_rdPtrHash.insert(HEPARIN_PUMP_BOARD_ADDR4, cmdhash);

        //驱动板
        cmdhash.clear();
        cmdhash.insert(READ_COMMAND_0, BoardDataPointer(&md4.drive.rd0, sizeof(md4.drive.rd0)));
        cmdhash.insert(READ_COMMAND_1, BoardDataPointer(&md4.drive.rd1, sizeof(md4.drive.rd1)));
        cmdhash.insert(READ_COMMAND_2, BoardDataPointer(&md4.drive.rd2, sizeof(md4.drive.rd2)));
        cmdhash.insert(READ_COMMAND_7, BoardDataPointer(&md4.drive.rd7, sizeof(md4.drive.rd7)));
        m_rdPtrHash.insert(DRIVER_BOARD_ADDR4, cmdhash);

        //平衡腔板
        cmdhash.clear();
        cmdhash.insert(READ_COMMAND_0, BoardDataPointer(&md4.balance.rd0, sizeof(md4.balance.rd0)));
        cmdhash.insert(READ_COMMAND_1, BoardDataPointer(&md4.balance.rd1, sizeof(md4.balance.rd1)));
        cmdhash.insert(READ_COMMAND_2, BoardDataPointer(&md4.balance.rd2, sizeof(md4.balance.rd2)));
        cmdhash.insert(READ_COMMAND_3, BoardDataPointer(&md4.balance.rd3, sizeof(md4.balance.rd3)));
        cmdhash.insert(READ_COMMAND_7, BoardDataPointer(&md4.balance.rd7, sizeof(md4.balance.rd7)));
        m_rdPtrHash.insert(BALANCE_CHAMBER_BOARD_ADDR4, cmdhash);

        //配液板
        cmdhash.clear();
        cmdhash.insert(READ_COMMAND_0, BoardDataPointer(&md4.mix.rd0, sizeof(md4.mix.rd0)));
        cmdhash.insert(READ_COMMAND_1, BoardDataPointer(&md4.mix.rd1, sizeof(md4.mix.rd1)));
        cmdhash.insert(READ_COMMAND_7, BoardDataPointer(&md4.mix.rd7, sizeof(md4.mix.rd7)));
        m_rdPtrHash.insert(MIXED_BOARD_ADDR4, cmdhash);

        //电导板
        cmdhash.clear();
        cmdhash.insert(READ_COMMAND_0, BoardDataPointer(&md4.cond.rd0, sizeof(md4.cond.rd0)));
        cmdhash.insert(READ_COMMAND_1, BoardDataPointer(&md4.cond.rd1, sizeof(md4.cond.rd1)));
        cmdhash.insert(READ_COMMAND_7, BoardDataPointer(&md4.mix.rd7, sizeof(md4.mix.rd7)));
        m_rdPtrHash.insert(CONDUCTANCE_BOARD_ADDR4, cmdhash);

        //加热板
        cmdhash.clear();
        cmdhash.insert(READ_COMMAND_0, BoardDataPointer(&md4.heat.rd0, sizeof(md4.heat.rd0)));
        cmdhash.insert(READ_COMMAND_7, BoardDataPointer(&md4.heat.rd7, sizeof(md4.heat.rd7)));
        m_rdPtrHash.insert(HEATER_BOARD_ADDR4, cmdhash);

        //电源板
        cmdhash.clear();
        cmdhash.insert(READ_COMMAND_0, BoardDataPointer(&md4.power.rd0, sizeof(md4.power.rd0)));
        cmdhash.insert(READ_COMMAND_7, BoardDataPointer(&md4.power.rd7, sizeof(md4.power.rd7)));
        m_rdPtrHash.insert(POWER_BOARD_ADDR4, cmdhash);

        //--------------------------------插入6000型RD数据----------------------------------<
        //血路板
        cmdhash.clear();
        cmdhash.insert(READ_COMMAND_0, BoardDataPointer(&md6.btd.rd0, sizeof(md6.btd.rd0)));
        cmdhash.insert(READ_COMMAND_1, BoardDataPointer(&md6.btd.rd1, sizeof(md6.btd.rd1)));
        cmdhash.insert(READ_COMMAND_2, BoardDataPointer(&md6.btd.rd2, sizeof(md6.btd.rd2)));
        cmdhash.insert(READ_COMMAND_3, BoardDataPointer(&md6.btd.rd3, sizeof(md6.btd.rd3)));
        cmdhash.insert(READ_COMMAND_4, BoardDataPointer(&md6.btd.rd4, sizeof(md6.btd.rd4)));
        cmdhash.insert(READ_COMMAND_5, BoardDataPointer(&md6.btd.rd5, sizeof(md6.btd.rd5)));
        cmdhash.insert(READ_COMMAND_7, BoardDataPointer(&md6.btd.rd7, sizeof(md6.btd.rd7)));
        cmdhash.insert(READ_COMMAND_8, BoardDataPointer(&md6.btd.rd8, sizeof(md6.btd.rd8)));
        m_rdPtrHash.insert(BLOOD_TRAIL_BOARD_ADDR6, cmdhash);

        //水路驱动板
        cmdhash.clear();
        cmdhash.insert(READ_COMMAND_0, BoardDataPointer(&md6.ldd.rd0, sizeof(md6.ldd.rd0)));
        cmdhash.insert(READ_COMMAND_1, BoardDataPointer(&md6.ldd.rd1, sizeof(md6.ldd.rd1)));
        cmdhash.insert(READ_COMMAND_2, BoardDataPointer(&md6.ldd.rd2, sizeof(md6.ldd.rd2)));
        cmdhash.insert(READ_COMMAND_3, BoardDataPointer(&md6.ldd.rd3, sizeof(md6.ldd.rd3)));
        cmdhash.insert(READ_COMMAND_4, BoardDataPointer(&md6.ldd.rd4, sizeof(md6.ldd.rd4)));
        cmdhash.insert(READ_COMMAND_7, BoardDataPointer(&md6.ldd.rd7, sizeof(md6.ldd.rd7)));
        cmdhash.insert(READ_COMMAND_8, BoardDataPointer(&md6.ldd.rd8, sizeof(md6.ldd.rd8)));
        m_rdPtrHash.insert(LIQUID_DRIVER_BOARD_ADDR6, cmdhash);

        //配液超滤板
        cmdhash.clear();
        cmdhash.insert(READ_COMMAND_0, BoardDataPointer(&md6.cpd.rd0, sizeof(md6.cpd.rd0)));
        cmdhash.insert(READ_COMMAND_1, BoardDataPointer(&md6.cpd.rd1, sizeof(md6.cpd.rd1)));
        cmdhash.insert(READ_COMMAND_2, BoardDataPointer(&md6.cpd.rd2, sizeof(md6.cpd.rd2)));
        cmdhash.insert(READ_COMMAND_3, BoardDataPointer(&md6.cpd.rd3, sizeof(md6.cpd.rd3)));
        cmdhash.insert(READ_COMMAND_4, BoardDataPointer(&md6.cpd.rd4, sizeof(md6.cpd.rd4)));
        cmdhash.insert(READ_COMMAND_5, BoardDataPointer(&md6.cpd.rd5, sizeof(md6.cpd.rd5)));
        cmdhash.insert(READ_COMMAND_6, BoardDataPointer(&md6.cpd.rd6, sizeof(md6.cpd.rd6)));
        cmdhash.insert(READ_COMMAND_7, BoardDataPointer(&md6.cpd.rd7, sizeof(md6.cpd.rd7)));
        cmdhash.insert(READ_COMMAND_8, BoardDataPointer(&md6.cpd.rd8, sizeof(md6.cpd.rd8)));
        m_rdPtrHash.insert(MIX_ULTRA_BOARD_ADDR6, cmdhash);

        //肝素板
        cmdhash.clear();
        cmdhash.insert(READ_COMMAND_0, BoardDataPointer(&md6.hpd.rd0, sizeof(md6.hpd.rd0)));
        cmdhash.insert(READ_COMMAND_1, BoardDataPointer(&md6.hpd.rd1, sizeof(md6.hpd.rd1)));
        cmdhash.insert(READ_COMMAND_7, BoardDataPointer(&md6.hpd.rd7, sizeof(md6.hpd.rd7)));
        cmdhash.insert(READ_COMMAND_8, BoardDataPointer(&md6.hpd.rd8, sizeof(md6.hpd.rd8)));
        m_rdPtrHash.insert(HEPARIN_BOARD_ADDR6, cmdhash);

        //电源板
        cmdhash.clear();
        cmdhash.insert(READ_COMMAND_0, BoardDataPointer(&md6.pbd.rd0, sizeof(md6.pbd.rd0)));
        cmdhash.insert(READ_COMMAND_7, BoardDataPointer(&md6.pbd.rd7, sizeof(md6.pbd.rd7)));
        cmdhash.insert(READ_COMMAND_8, BoardDataPointer(&md6.pbd.rd8, sizeof(md6.pbd.rd8)));
        m_rdPtrHash.insert(POWER_BOARD_ADDR6, cmdhash);

        //监控板
        cmdhash.clear();
        cmdhash.insert(READ_COMMAND_7, BoardDataPointer(&md6.mbd.rd7, sizeof(md6.mbd.rd7)));
        cmdhash.insert(READ_COMMAND_8, BoardDataPointer(&md6.mbd.rd8, sizeof(md6.mbd.rd8)));
        m_rdPtrHash.insert(MONITOR_BOARD_ADDR6, cmdhash);

        //空气监测板
        cmdhash.clear();
        cmdhash.insert(READ_COMMAND_0, BoardDataPointer(&md6.add.rd0, sizeof(md6.add.rd0)));
        cmdhash.insert(READ_COMMAND_7, BoardDataPointer(&md6.add.rd7, sizeof(md6.add.rd7)));
        m_rdPtrHash.insert(AIR_DETECTOR_BOARD_ADDR6, cmdhash);

        //-----------------------------------插入通用数据------------------------------------<
        //血温血容量板
        cmdhash.clear();
        cmdhash.insert(READ_COMMAND_0, BoardDataPointer(&btv.rd0, sizeof(btv.rd0)));
        cmdhash.insert(READ_COMMAND_1, BoardDataPointer(&btv.rd1, sizeof(btv.rd1)));
        cmdhash.insert(READ_COMMAND_2, BoardDataPointer(&btv.rd2, sizeof(btv.rd2)));
        cmdhash.insert(READ_COMMAND_3, BoardDataPointer(&btv.rd3, sizeof(btv.rd3)));
        cmdhash.insert(READ_COMMAND_7, BoardDataPointer(&btv.rd7, sizeof(btv.rd7)));
        cmdhash.insert(READ_COMMAND_8, BoardDataPointer(&btv.rd8, sizeof(btv.rd8)));
        m_rdPtrHash.insert(BLOOD_TEMP_VOLUME_MODULE_ADDR, cmdhash);

        //实时清除率监测板
        cmdhash.clear();
        cmdhash.insert(READ_COMMAND_0, BoardDataPointer(&rcm.rd0, sizeof(rcm.rd0)));
        cmdhash.insert(READ_COMMAND_7, BoardDataPointer(&rcm.rd7, sizeof(rcm.rd7)));
        cmdhash.insert(READ_COMMAND_8, BoardDataPointer(&rcm.rd8, sizeof(rcm.rd8)));
        m_rdPtrHash.insert(UREA_SENSORE_MODULE_ADDR, cmdhash);
    }

    BoardDataPointer rdPtr(int board, int cmd)
    {
        return m_rdPtrHash.value(board).value(cmd);
    }

    ModuleData4000           md4;     //模块数据_SWS4000
    ModuleData6000           md6;     //模块数据_SWS6000
    BloodTempVolumeBoardData btv;     //血温血容量_通用
    UreaSensorBoardData      rcm;     //实时清除率监测数据_通用

private:
    QHash<int, QHash<int, BoardDataPointer>> m_rdPtrHash; //保存RD命令的指针
};

#endif // PROTOCOL_H
