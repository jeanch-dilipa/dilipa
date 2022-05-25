#ifndef FACTORY_H
#define FACTORY_H

#include <QString>

class Product
{
public:
    virtual QString show() const = 0;
};

class ProductA:public Product
{
public:
    virtual QString show() const override = 0;/*const在函数后，修饰this指针，代表此函数不可操作类数据成员(只读函数)；override标识为重写函数；=0表示函数是虚函数*/
};
class ProductA1:public ProductA
{
public:
    QString show() const override{return QString("A1");}
};

class ProductA2:public ProductA
{
public:
    QString show() const override{return QString("A2");}
};

class ProductB:public Product
{
public:
    virtual QString show() const override= 0;
};

class ProductB1:public ProductB
{
public:
    QString show() const override{return QString("B1");}
};

class ProductB2:public ProductB
{
public:
    QString show() const override{return QString("B2");}
};

class Factory
{
public:
    virtual ProductA *createrA() const = 0;
    virtual ProductB *createrB() const = 0;
};

class Factory1:Factory
{
public:
    inline ProductA *createrA() const override{return new ProductA1();}
    ProductB *createrB() const override{return new ProductB1();}
};

class Factory2:Factory
{
public:
    ProductA *createrA() const override{return new ProductA2();}
    ProductB *createrB() const override{return new ProductB2();}
};
#endif // FACTORY_H
