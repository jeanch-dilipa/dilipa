/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   debuginterface.h
    info:	The main debugging interface is used by engineers only for
            system upgrade and engineer maintenance
******************************************************************************/

#ifndef DEBUGINTERFACE_H
#define DEBUGINTERFACE_H

#include <QWidget>
#include <QPointer>
#include <QMutex>
#include <QMutexLocker>

namespace Ui
{
    class DebugInterface;
}

class DebugInterface : public QWidget
{
    Q_OBJECT

public:
    static DebugInterface& initDebugInterface();

private:
    explicit DebugInterface(QWidget *parent = nullptr);
    ~DebugInterface();

private:
    Ui::DebugInterface                         *ui;
    static QPointer<DebugInterface>             s_debug;
    static QMutex                              *s_mutexLocker;
};

#endif // DEBUGINTERFACE_H
