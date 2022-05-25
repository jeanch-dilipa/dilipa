/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   mainwidget.h
    info:	The main interface of the system bears the main therapeutic
            functions of the system
******************************************************************************/

#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include <QWidget>
#include <QMutex>
#include <QMutexLocker>
#include <QPointer>

#include "datadeal/common/publicdata.h"

namespace Ui
{
    class MainInterface;
}

class MainInterface : public QWidget
{
    Q_OBJECT

public:
    static MainInterface& initMainInterface();

public:
    explicit MainInterface(QWidget *parent = nullptr);
    ~MainInterface();

private:
    void registerAttribute();                                           //注册通信数据
    void unRegisterAttribute();                                         //注销通信数据

private:
    Ui::MainInterface                          *ui;
    static QPointer<MainInterface>              s_main;
    static QMutex                              *s_mutexLocker;
};

#endif // MAININTERFACE_H
