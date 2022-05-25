/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   startinterface.h
    info:	System Startup interface
******************************************************************************/

#ifndef STARTINTERFACE_H
#define STARTINTERFACE_H

#include <QWidget>
#include <QMutex>
#include <QMutexLocker>
#include <QPointer>
#include <QTimer>
#include <QMouseEvent>

#include "common/common.h"
#include "interface/common/interfacedata.h"

namespace Ui
{
    class StartInterface;
}

class StartInterface : public QWidget
{
    Q_OBJECT

public:
    static StartInterface& initStartInterface();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    explicit StartInterface(QWidget *parent = nullptr);
    ~StartInterface();

    void setSystemAddSoftVersion();                                                 //设置系统和软件版本

private slots:
    void slot_startTimerOut();                                                      //启动定时器超时处理

signals:
    void signal_switchMainInterface(const PageType);                                //切换主界面

private:
    Ui::StartInterface                     *ui;
    static QPointer<StartInterface>         s_startInterface;
    static QMutex                          *s_mutexLocker;

    QPointer<QTimer>                        m_startTimer;                           //启动定时器

    QPoint                                  m_prePoint;                             //触摸点
};

#endif // STARTINTERFACE_H
