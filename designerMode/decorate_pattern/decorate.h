#ifndef DECORATE_H
#define DECORATE_H

#include <QString>

class Product
{
public:
    virtual QString show() const = 0;
};

class ProductA:public Product
{
public:
    QString show() const override{return QString("A");}
};

class Decorate:public Product
{
private:
    Product* pro;
public:
    explicit Decorate(Product* pro):pro(pro){};
    QString show() const override{return this->pro->show();};
};

class DecorateA:public Decorate
{
public:
    explicit DecorateA(Product* pro):Decorate(pro){}
    QString show() const override{return QString("a+") + Decorate::show();}
};

class DecorateB:public Decorate
{
public:
    explicit DecorateB(Product* pro):Decorate(pro){}
    QString show() const override{return QString("b+") + Decorate::show();}
};

#endif // DECORATE_H
