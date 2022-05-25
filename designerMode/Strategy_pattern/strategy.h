#ifndef STRATEGY_H
#define STRATEGY_H

#include <QString>

class Strategy
{
public:
    virtual QString show() const = 0;
};

class Context
{
public:
    explicit Context(Strategy* strategy):m_strategy(strategy){this->SetStrategy(strategy);}
    void SetStrategy(Strategy *strategy){this->m_strategy = strategy;}
    QString DoSomeThing() const{return m_strategy->show();}

private:
    Strategy *m_strategy;
};

class Strategy1: public Strategy
{
public:
    QString show() const override{return QString("strategy1");}
};

class Strategy2: public Strategy
{
public:
    QString show() const override{return QString("strategy2");}
};

class Strategy3: public Strategy
{
public:
    QString show() const override{return QString("strategy3");}
};

#endif // STRATEGY_H
