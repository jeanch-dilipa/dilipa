#ifndef CHAIN_H
#define CHAIN_H

#include <QString>

class Decision
{
public:
    virtual Decision* next_decision(Decision* dec) = 0;
    virtual QString dec(QString str) = 0;
};

class AbstractDecidion:public Decision
{
public:
    AbstractDecidion():decision(nullptr){}
    ~AbstractDecidion(){}

    Decision* decision;
    Decision* next_decision(Decision *dec) override{this->decision = dec;return dec;}
    QString dec(QString str) override
    {
        if(this->decision)
        {
            return this->decision->dec(str);
        }
        else
        {
            return QString("");
        }
    }
};

class DecisionA:public AbstractDecidion
{
public:
    QString dec(QString str) override
    {
        if(str == QString("A"))
        {
            return QString("This is A;");
        }
        else
        {
            return AbstractDecidion::dec(str);
        }
    }
};

class DecisionB:public AbstractDecidion
{
public:
    QString dec(QString str) override
    {
        if(str == QString("B"))
        {
            return QString("This is B;");
        }
        else
        {
            return AbstractDecidion::dec(str);
        }
    }
};

class DecisionC:public AbstractDecidion
{
public:
    QString dec(QString str) override
    {
        if(str == QString("C"))
        {
            return QString("This is C;");
        }
        else
        {
            return AbstractDecidion::dec(str);
        }
    }
};

#endif // CHAIN_H
