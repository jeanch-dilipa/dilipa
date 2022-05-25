/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   functioninterface.h
    info:	Function module setting interface
******************************************************************************/

#ifndef FUNCTIONINTERFACE_H
#define FUNCTIONINTERFACE_H

#include <QWidget>

namespace Ui
{
    class FunctionInterface;
}

class FunctionInterface : public QWidget
{
    Q_OBJECT

public:
    explicit FunctionInterface(QWidget *parent = nullptr);
    ~FunctionInterface();

private:
    Ui::FunctionInterface                       *ui;
};

#endif // FUNCTIONINTERFACE_H
