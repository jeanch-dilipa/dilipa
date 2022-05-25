/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   mainwidgetmanager.cpp
    info:	Handle main interface scheduling
******************************************************************************/

#include "widgetmanager.h"

QPointer<WidgetManager> WidgetManager::s_widget = nullptr;
QMutex *WidgetManager::s_mutexLocker = nullptr;

/****************************************************************************
接口描述: 创建界面管理类实例
输   入: /
输   出: /
******************************************************************************/
WidgetManager &WidgetManager::initWidgetManager()
{
    if(nullptr == s_widget)
    {
        QMutexLocker locker(s_mutexLocker);
        if(nullptr == s_widget)
        {
            s_widget = new WidgetManager();
        }
    }

    return *s_widget;
}

/****************************************************************************
接口描述: 主界面管理器构造函数
输   入: /
输   出: /
******************************************************************************/
WidgetManager::WidgetManager()
{
    qdebug << "WidgetManager" << QThread::currentThreadId();
    m_currentPage = DefaultPage;
    slot_switchMainInterface(StartPage);
}

/****************************************************************************
接口描述: 主界面管理器构造函数
输   入: /
输   出: /
******************************************************************************/
WidgetManager::~WidgetManager()
{
    if(nullptr != m_start)
    {
        m_start->disconnect();
        m_start->deleteLater();
    }

    if(nullptr != m_main)
    {
        m_main->disconnect();
        m_main->deleteLater();
    }

    if(nullptr != m_debug)
    {
        m_debug->disconnect();
        m_debug->deleteLater();
    }
}

/****************************************************************************
接口描述: 销毁当前主界面
输   入: /
输   出: /
******************************************************************************/
void WidgetManager::deleterCurrentInterface()
{
    switch(m_currentPage)
    {
        case StartPage:
            m_start->disconnect();
            m_start->deleteLater();
            break;
        case DebugPage:
            m_debug->disconnect();
            m_debug->deleteLater();
            break;
        default:
            break;
    }
}

/****************************************************************************
接口描述: 主界面切换
输   入: /
输   出: /
******************************************************************************/
void WidgetManager::slot_switchMainInterface(const PageType mainPage)
{
    deleterCurrentInterface();
    m_currentPage = mainPage;
    switch(mainPage)
    {
        case StartPage:
            m_start = &StartInterface::initStartInterface();
            connect(m_start, &StartInterface::signal_switchMainInterface, this, &WidgetManager::slot_switchMainInterface);
            break;
        case MainPage:
            m_main = &MainInterface::initMainInterface();
//            connect(m_main, &StartInterface::signal_switchMainInterface, this, &WidgetManager::slot_switchMainInterface);
            break;
        case DebugPage:
            m_debug = &DebugInterface::initDebugInterface();
//            connect(m_debug, &StartInterface::signal_switchMainInterface, this, &WidgetManager::slot_switchMainInterface);
            break;
        default:
            break;
    }
}
