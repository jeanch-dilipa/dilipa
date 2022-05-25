/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   mainwidget.cpp
    info:	The main interface of the system bears the main therapeutic
            functions of the system
******************************************************************************/

#include "maininterface.h"
#include "ui_maininterface.h"

QPointer<MainInterface> MainInterface::s_main = nullptr;
QMutex *MainInterface::s_mutexLocker = nullptr;

/****************************************************************************
接口描述: 创建主界面类实例
输   入: parent---父窗口
输   出: /
******************************************************************************/
MainInterface& MainInterface::initMainInterface()
{
    if(nullptr == s_main)
    {
        QMutexLocker locker(s_mutexLocker);
        if(nullptr == s_main)
        {
            s_main = new MainInterface();
            s_main->show();
        }
    }

    return *s_main;
}

/****************************************************************************
接口描述: 主界面构造函数
输   入: parent---父窗口
输   出: /
******************************************************************************/
MainInterface::MainInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainInterface)
{
//    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);

    registerAttribute();
}

/****************************************************************************
接口描述: 主界面析构函数
输   入: /
输   出: /
******************************************************************************/
MainInterface::~MainInterface()
{
    delete ui;
    unRegisterAttribute();
}

/****************************************************************************
接口描述: 注册通信数据
输   入: /
输   出: /
******************************************************************************/
void MainInterface::registerAttribute()
{
    g_pd.m_mb->registerDataDeliveryQueue(BLOOD_PUMP_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);           /*血泵板*/
    g_pd.m_mb->registerDataDeliveryQueue(FLUID_INFUSION_PUMP_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);  /*补液泵板*/
    g_pd.m_mb->registerDataDeliveryQueue(ULTRAFILTRATION_PUMP_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0); /*超滤板*/
    g_pd.m_mb->registerDataDeliveryQueue(HEPARIN_PUMP_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_0);       /*肝素板*/
    g_pd.m_mb->registerDataDeliveryQueue(DRIVER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_0);             /*驱动板*/
    g_pd.m_mb->registerDataDeliveryQueue(DRIVER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_1);
    g_pd.m_mb->registerDataDeliveryQueue(DRIVER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_2);
    g_pd.m_mb->registerDataDeliveryQueue(BALANCE_CHAMBER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_0);    /*平衡腔板*/
    g_pd.m_mb->registerDataDeliveryQueue(BALANCE_CHAMBER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_1);
    g_pd.m_mb->registerDataDeliveryQueue(BALANCE_CHAMBER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_2);
    g_pd.m_mb->registerDataDeliveryQueue(BALANCE_CHAMBER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_3);
    g_pd.m_mb->registerDataDeliveryQueue(MIXED_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);                /*配液板*/
    g_pd.m_mb->registerDataDeliveryQueue(MIXED_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_1);
    g_pd.m_mb->registerDataDeliveryQueue(CONDUCTANCE_BOARD_C_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);        /*电导板*/
    g_pd.m_mb->registerDataDeliveryQueue(CONDUCTANCE_BOARD_C_ADDRESS,SYSTEM_BUS_READ_COMMAND_1);
    g_pd.m_mb->registerDataDeliveryQueue(KEYPRESS_BOARD_ADDRESS,SYSTEM_BUS_KEY_PRESSED_COMMAND);        /*按键板*/
    g_pd.m_mb->registerDataDeliveryQueue(HEATER_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);               /*加热板*/
    g_pd.m_mb->registerDataDeliveryQueue(POWER_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);                /*电源板*/
    g_pd.m_mb->registerDataDeliveryQueue(BLOOD_PRESSURE_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);       /*血压计*/
    g_pd.m_mb->registerDataDeliveryQueue(BLOOD_PRESSURE_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_1);
    g_pd.m_mb->registerDataDeliveryQueue(BLOOD_PRESSURE_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_2);
    g_pd.m_mb->registerDataDeliveryQueue(ONLINE_KTV_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);           /*RCM*/
    g_pd.m_mb->registerDataDeliveryQueue(BTBV_BOARD_ADDRESS, SYSTEM_BUS_READ_COMMAND_0);                /*BVM*/
    g_pd.m_mb->registerDataDeliveryQueue(BTBV_BOARD_ADDRESS, SYSTEM_BUS_READ_COMMAND_1);
    g_pd.m_mb->registerDataDeliveryQueue(BTBV_BOARD_ADDRESS, SYSTEM_BUS_READ_COMMAND_2);
    g_pd.m_mb->registerDataDeliveryQueue(BTBV_BOARD_ADDRESS, SYSTEM_BUS_READ_COMMAND_3);
}

/****************************************************************************
接口描述: 注销通信数据
输   入: /
输   出: /
******************************************************************************/
void MainInterface::unRegisterAttribute()
{
    g_pd.m_mb->unRegisterDataDeliveryQueue(BLOOD_PUMP_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);           /*血泵板*/
    g_pd.m_mb->unRegisterDataDeliveryQueue(FLUID_INFUSION_PUMP_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);  /*补液泵板*/
    g_pd.m_mb->unRegisterDataDeliveryQueue(ULTRAFILTRATION_PUMP_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0); /*超滤板*/
    g_pd.m_mb->unRegisterDataDeliveryQueue(HEPARIN_PUMP_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_0);       /*肝素板*/
    g_pd.m_mb->unRegisterDataDeliveryQueue(DRIVER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_0);             /*驱动板*/
    g_pd.m_mb->unRegisterDataDeliveryQueue(DRIVER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_1);
    g_pd.m_mb->unRegisterDataDeliveryQueue(DRIVER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_2);
    g_pd.m_mb->unRegisterDataDeliveryQueue(BALANCE_CHAMBER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_0);    /*平衡腔板*/
    g_pd.m_mb->unRegisterDataDeliveryQueue(BALANCE_CHAMBER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_1);
    g_pd.m_mb->unRegisterDataDeliveryQueue(BALANCE_CHAMBER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_2);
    g_pd.m_mb->unRegisterDataDeliveryQueue(BALANCE_CHAMBER_BOARD_ADDRESS , SYSTEM_BUS_READ_COMMAND_3);
    g_pd.m_mb->unRegisterDataDeliveryQueue(MIXED_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);                /*配液板*/
    g_pd.m_mb->unRegisterDataDeliveryQueue(MIXED_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_1);
    g_pd.m_mb->unRegisterDataDeliveryQueue(CONDUCTANCE_BOARD_C_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);        /*电导板*/
    g_pd.m_mb->unRegisterDataDeliveryQueue(CONDUCTANCE_BOARD_C_ADDRESS,SYSTEM_BUS_READ_COMMAND_1);
    g_pd.m_mb->unRegisterDataDeliveryQueue(KEYPRESS_BOARD_ADDRESS,SYSTEM_BUS_KEY_PRESSED_COMMAND);        /*按键板*/
    g_pd.m_mb->unRegisterDataDeliveryQueue(HEATER_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);               /*加热板*/
    g_pd.m_mb->unRegisterDataDeliveryQueue(POWER_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);                /*电源板*/
    g_pd.m_mb->unRegisterDataDeliveryQueue(BLOOD_PRESSURE_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);       /*血压计*/
    g_pd.m_mb->unRegisterDataDeliveryQueue(BLOOD_PRESSURE_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_1);
    g_pd.m_mb->unRegisterDataDeliveryQueue(BLOOD_PRESSURE_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_2);
    g_pd.m_mb->unRegisterDataDeliveryQueue(ONLINE_KTV_BOARD_ADDRESS,SYSTEM_BUS_READ_COMMAND_0);           /*RCM*/
    g_pd.m_mb->unRegisterDataDeliveryQueue(BTBV_BOARD_ADDRESS, SYSTEM_BUS_READ_COMMAND_0);                /*BVM*/
    g_pd.m_mb->unRegisterDataDeliveryQueue(BTBV_BOARD_ADDRESS, SYSTEM_BUS_READ_COMMAND_1);
    g_pd.m_mb->unRegisterDataDeliveryQueue(BTBV_BOARD_ADDRESS, SYSTEM_BUS_READ_COMMAND_2);
    g_pd.m_mb->unRegisterDataDeliveryQueue(BTBV_BOARD_ADDRESS, SYSTEM_BUS_READ_COMMAND_3);
}
