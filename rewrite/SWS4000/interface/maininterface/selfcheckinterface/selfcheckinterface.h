/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   selfcheckinterface.h
    info:	System self-check control interface
******************************************************************************/

#ifndef SELFCHECKINTERFACE_H
#define SELFCHECKINTERFACE_H

#include <QWidget>
#include <QPointer>
#include <QMutex>
#include <QMutexLocker>

namespace Ui
{
    class SelfCheckInterface;
}

class SelfCheckInterface : public QWidget
{
    Q_OBJECT

public:
    static SelfCheckInterface& initSelfCheckInterface();

private:
    explicit SelfCheckInterface(QWidget *parent = nullptr);
    ~SelfCheckInterface();

private:
    Ui::SelfCheckInterface                         *ui;
    static QPointer<SelfCheckInterface>             s_selfCheck;
    static QMutex                                  *s_mutexLocker;
};

#endif // SELFCHECKINTERFACE_H
