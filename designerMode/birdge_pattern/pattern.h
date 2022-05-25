#ifndef PATTERN_H
#define PATTERN_H

#include <QString>

class Device
{
public:
    virtual QString port() const = 0;
};

class DeviceA:public Device
{
public:
    QString port() const override{return QString("DeviceA");}
};

class DeviceB:public Device
{
public:
    QString port() const override{return QString("DeviceB");}
};

class control
{
public:
    Device* device;
    explicit control(Device *device){this->device = device;}
    QString control_p() const{return device->port();}
};

class controlExpand
{
public:
    Device* device;
    explicit controlExpand(Device *device){this->device = device;}
    QString control_p(){return QString("%1%2").arg(QString("Expand:")).arg(device->port());}
};

#endif // PATTERN_H
