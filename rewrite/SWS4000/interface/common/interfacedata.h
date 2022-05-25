/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   interfacedata.h
    info:	Interface Type of a public interface
******************************************************************************/

#ifndef INTERFACEDATA_H
#define INTERFACEDATA_H

typedef enum
{
    DefaultPage                                     = 0,
    StartPage                                       = 1,            //启动界面
    MainPage                                        = 2,            //主界面
    DebugPage                                       = 3,            //工程师界面
}PageType;

#endif // INTERFACEDATA_H
