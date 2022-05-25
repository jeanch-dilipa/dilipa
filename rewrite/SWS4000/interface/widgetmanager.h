/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   mainwidgetmanager.h
    info:	Handle main interface scheduling
******************************************************************************/

#ifndef WIDGETMANAGER_H
#define WIDGETMANAGER_H

#include <QObject>
#include <QPointer>
#include <QTimer>
#include <QThread>

#include "interface/startinterface/startinterface.h"
#include "interface/debuginterface/debuginterface.h"
#include "interface/maininterface/maininterface.h"

class WidgetManager: public QObject
{
    Q_OBJECT

public:
    static WidgetManager& initWidgetManager();

private:
    explicit WidgetManager();
    ~WidgetManager();

    void deleterCurrentInterface();

private slots:
    void slot_switchMainInterface(const PageType mainPage);

private:
    static QPointer<WidgetManager>                  s_widget;
    static QMutex                                  *s_mutexLocker;

    QPointer<StartInterface>                        m_start;                    //启动界面
    QPointer<DebugInterface>                        m_debug;                    //工程师界面
    QPointer<MainInterface>                         m_main;                     //主界面

    quint8                                          m_currentPage;              //当前界面
};

#endif // WIDGETMANAGER_H
