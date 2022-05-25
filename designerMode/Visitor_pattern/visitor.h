#ifndef VISITOR_H
#define VISITOR_H

#include <QString>

class ProductA;class ProductB;
class Visitor
{
public:
    virtual QString VisitorProductA(const ProductA *A) const = 0;
    virtual QString VisitorProductB(const ProductB *B) const = 0;
};

class Product
{
public:
    virtual QString Accept(Visitor *V) const = 0;
};

class ProductA:public Product
{
public:
    QString Accept(Visitor *V) const override{return V->VisitorProductA(this);}
    static QString DoSomething(){return QString("my name is A");}
};

class ProductB:public Product
{
public:
    QString Accept(Visitor *V) const override{return V->VisitorProductB(this);}
    static QString DoSomething(){return QString("my name is B");}
};

class Visitor1:public Visitor
{
public:
    QString VisitorProductA(const ProductA *A)const override{return A->DoSomething() + QString("-->visitor1");}
    QString VisitorProductB(const ProductB *B)const override{return B->DoSomething() + QString("-->visitor1");}
};

class Visitor2:public Visitor
{
public:
    QString VisitorProductA(const ProductA *A)const override{return A->DoSomething() + QString("-->visitor2");}
    QString VisitorProductB(const ProductB *B)const override{return B->DoSomething() + QString("-->visitor2");}
};

#endif // VISITOR_H
