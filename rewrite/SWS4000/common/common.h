/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   common.h
    info:	The system supports file interfaces
******************************************************************************/

#ifndef COMMON_H
#define COMMON_H

#include <QDebug>

#define VSERSION                    "V0.0.01 A"                         /*系统版本*/

#define EXHIBITION                  0                                   /*参展模式*/

#define qdebug                      qDebug()                            /*系统调试*/
#define qinfo                       qInfo()
#define qwarning                    qWarning()
#define qcritical                   qCritical()
#define qfatal                      qFatal()

#endif // COMMON_H
