/*******************************************************************************
Copyright (c) 2022, dilipa
All rights reserved
文件：    adapter.h
作者：    dilipa
版本：    V1.0
日期：    2022-03-31
摘要：    适配器类头文件
********************************************************************************/

#ifndef ADAPTER_H
#define ADAPTER_H

#include <QString>

class Target
{
public:
    Target() = default;
    virtual ~Target() = default;
    virtual QString show_target() const{return QString("A:123456");}
};

class adapted
{
public:
    static QString show_adapted(){return QString("4896546");}
};

class adapter:public Target
{
public:
    adapted *ad;
    explicit adapter(adapted* ad):ad(ad){}
//    QString show_adapter(){return QString("%1%2").arg(QString("A:")).arg(ad->show_adapted());}
    QString show_target() const override{QString str = ad->show_adapted();std::reverse(str.begin(), str.end());return  QString("A:") + str;}
};

class superAdapter:public Target,public adapted
{
public:
    static QString show_superaddapter(){return QString("%1%2").arg(QString("A:")).arg(show_adapted());}
};

#endif // ADAPTER_H
