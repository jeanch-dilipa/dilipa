#ifndef PROXY_H
#define PROXY_H

#include <QString>

class Server
{
public:
    virtual QString show() const = 0;
};

class RealServer:Server
{
public:
    QString show() const override{return QString("This is product");}
};

class Proxy:Server
{
public:
    explicit Proxy(RealServer* ser):m_ser(ser){};

    static QString before() {return QString("before");}
    static QString after() {return QString("after");}
    QString show() const override{return this->before() + this->m_ser->show() + this->after();}

private:
    RealServer* m_ser;
};

#endif // PROXY_H
