/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   moduletype.h
    info:	Module board communication data structure
******************************************************************************/

#ifndef MODULETYPE_H
#define MODULETYPE_H

#include <QtGlobal>

//#pragma pack(1)                                                                             //单字节对齐

typedef enum                                                                                //模块板地址
{
    MODULE_BOARD_ADDR_DEFAULT                                   = 0x00,
    BLOOD_PUMP_BOARD_ADDRESS                                    = 0x01,                     //血泵板地址
    FLUID_INFUSION_PUMP_BOARD_ADDRESS                           = 0x02,                     //补液泵板地址
    ULTRAFILTRATION_PUMP_BOARD_ADDRESS                          = 0x03,                     //超滤板地址
    HEPARIN_PUMP_BOARD_ADDRESS                                  = 0x04,                     //肝素板地址
    DRIVER_BOARD_ADDRESS                                        = 0x05,                     //驱动板地址
    BALANCE_CHAMBER_BOARD_ADDRESS                               = 0x06,                     //平衡腔板地址
    MIXED_BOARD_ADDRESS                                         = 0x07,                     //配液板地址
    MONITOR_BOARD_ADDRESS                                       = 0x09,                     //监控板地址
    HEATER_BOARD_ADDRESS                                        = 0x0A,                     //加热板地址
    POWER_BOARD_ADDRESS                                         = 0x0C,                     //电源板地址
    CONDUCTANCE_BOARD_C_ADDRESS                                 = 0x25,                     //电导C地址
    BLOOD_PRESSURE_BOARD_ADDRESS                                = 0x27,                     //血压计模块地址
    ONLINE_KTV_BOARD_ADDRESS                                    = 0x28,                     //实时清除率模块
    BTBV_BOARD_ADDRESS                                          = 0x29,                     //血温血容
    KEYPRESS_BOARD_ADDRESS                                      = 0x41,                     //按键地址
    PILOT_LAMP_BOARD_ADDRESS                                    = 0x42,                     //指示灯地址
    MAIN_CONTROL_BOARD_ADDRESS                                  = 0x55                      //主控板地址
}__attribute__((packed)) ModuleBoardAddrType;

typedef enum                                                                                //读写命令
{
    SYSTEM_BUS_WRITE_COMMAND_0                                  = 0x30,                     //48
    SYSTEM_BUS_WRITE_COMMAND_1                                  = 0x31,                     //49
    SYSTEM_BUS_WRITE_COMMAND_2                                  = 0x32,                     //50
    SYSTEM_BUS_WRITE_COMMAND_3                                  = 0x33,                     //51
    SYSTEM_BUS_WRITE_COMMAND_4                                  = 0x34,                     //52
    SYSTEM_BUS_WRITE_COMMAND_5                                  = 0x35,                     //53
    SYSTEM_BUS_WRITE_COMMAND_6                                  = 0x36,                     //54
    SYSTEM_BUS_WRITE_COMMAND_7                                  = 0x37,                     //55
    SYSTEM_BUS_WRITE_COMMAND_8                                  = 0x38,                     //56
    SYSTEM_BUS_WRITE_COMMAND_9                                  = 0x39,                     //57

    SYSTEM_BUS_READ_COMMAND_0                                   = 0x40,                     //64
    SYSTEM_BUS_READ_COMMAND_1                                   = 0x41,                     //65
    SYSTEM_BUS_READ_COMMAND_2                                   = 0x42,                     //66
    SYSTEM_BUS_READ_COMMAND_3                                   = 0x43,                     //67
    SYSTEM_BUS_READ_COMMAND_4                                   = 0x44,                     //68
    SYSTEM_BUS_READ_COMMAND_5                                   = 0x45,                     //69
    SYSTEM_BUS_READ_COMMAND_6                                   = 0x46,                     //70
    SYSTEM_BUS_READ_COMMAND_7                                   = 0x47,                     //71
    SYSTEM_BUS_READ_COMMAND_8                                   = 0x48,                     //72

    SYSTEM_BUS_PILOT_LAMP_COMMAND                               = 0x50,                     //指示灯命令
    SYSTEM_BUS_KEY_PRESSED_COMMAND                              = 0x51                      //按键指令
}__attribute__((packed))SystemBusCommandType;

typedef enum                                                                                //串口类型
{
    UART_TYPE_NORMAL                                            = 0,
    UART_TYPE_485                                               = 1,                        //485通信串口
    UART_TYPE_232                                               = 2,                        //232通信串口
    UART_TYPE_BP                                                = 3,                        //血压计通信串口
    UART_TYPE_IC                                                = 4,                        //IC卡通信串口
}__attribute__((packed)) UartModelType;

typedef enum
{
    WRITE_TYPE_DATA                                             = 0,                        //写命令数据
    READ_TYPE_DATA                                              = 1,                        //读命令数据
    REGISTER_TYPE_DATA                                          = 2,                        //注册命令数据
    UNREGISTER_TYPE_DATA                                        = 3,                        //注销命令数据
    UPDATE_BOARD_TYPE_DATA                                      = 4,                        //升级命令数据
}__attribute__((packed)) DataType;

typedef enum
{
    TAG_BP_WR0                                                  = 0,                        //血泵
    TAG_FP_WR0                                                  = 10,                       //补液泵
    TAG_UFP_WR0                                                 = 20,                       //超滤泵
    TAG_HP_WR0                                                  = 30,                       //肝素泵
    TAG_DRIVE_WR0                                               = 40,                       //驱动板
    TAG_DRIVE_WR1                                               = 41,
    TAG_BALANCE_WR0                                             = 50,                       //平衡腔板
    TAG_BALANCE_WR1                                             = 51,
    TAG_BALANCE_WR2                                             = 52,
    TAG_BALANCE_WR3                                             = 53,
    TAG_MIXTURE_WR0                                             = 60,                       //配液板
    TAG_MIXTURE_WR1                                             = 61,
    TAG_COND_WR0                                                = 70,                       //电导板
    TAG_HAET_WR0                                                = 80,                       //加热板
    TAG_HAET_WR1                                                = 81,
    TAG_POWER_WR0                                               = 90,                       //电源板
    TAG_POWER_WR1                                               = 91,
    TAG_MONITOR_WR0                                             = 100,                      //监控板
    TAG_BPM_WR0                                                 = 110,                      //血压计板
    TAG_BPM_WR1                                                 = 111,
    TAG_RCM_WR0                                                 = 120,                      //实时清除率板
    TAG_BTBV_WR0                                                = 130,                      //血温血容
    TAG_BTBV_WR1                                                = 131,
    TAG_BTBV_WR2                                                = 132,

}__attribute__((packed)) SyncTag;

struct ModuleBoardAddressAndCommand
{
    explicit ModuleBoardAddressAndCommand(const ModuleBoardAddrType _addr = MODULE_BOARD_ADDR_DEFAULT, const SystemBusCommandType _command = SYSTEM_BUS_READ_COMMAND_0) : m_boardAddr(_addr), m_command(_command){}
    ModuleBoardAddressAndCommand(const ModuleBoardAddressAndCommand &other)
    {
        m_boardAddr = other.m_boardAddr;
        m_command = other.m_command;
    }
    ModuleBoardAddressAndCommand& operator =(const ModuleBoardAddressAndCommand &other)
    {
        m_boardAddr = other.m_boardAddr;
        m_command = other.m_command;
        return *this;
    }

    ModuleBoardAddrType                                         m_boardAddr;
    SystemBusCommandType                                        m_command;
}__attribute__((packed));

struct DataAttributeType
{
    explicit DataAttributeType(const ModuleBoardAddressAndCommand _moduleAttr = ModuleBoardAddressAndCommand(), const UartModelType _type = UART_TYPE_485, const DataType _datatype = READ_TYPE_DATA) : m_module(_moduleAttr), m_uartType(_type), m_dataType(_datatype){}
    DataAtributeType(const DataAttributeType &other)
    {
        m_module = other.m_module;
        m_uartType = other.m_uartType;
        m_dataType = other.m_dataType;
    }

    DataAttributeType& operator =(const DataAttributeType &other)
    {
        m_module = other.m_module;
        m_uartType = other.m_uartType;
        m_dataType = other.m_dataType;
        return *this;
    }

    ModuleBoardAddressAndCommand                                m_module;
    UartModelType                                               m_uartType;
    DataType                                                    m_dataType;
}__attribute__((packed));

#endif // MODULETYPE_H
