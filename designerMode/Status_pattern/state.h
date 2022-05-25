#ifndef STATE_H
#define STATE_H

#include <QString>

class Context;
class State
{
public:
    State() = default;

    void SetContext(Context *contetx){this->m_context = contetx;};
    virtual QString Do1() const = 0;
    virtual void Do2() = 0;

protected:
    Context *m_context;
};

class Context
{
public:
    explicit Context(State *state):m_state(state){this->SetState(state);}

    void SetState(State *state) {this->m_state = state;this->m_state->SetContext(this);}
    QString SetState1() const{return this->m_state->Do1();}
    void SetState2() const{this->m_state->Do2();}

private:
    State *m_state;
};

class State3;
class State1:public State
{
public:
    explicit State1(QString *str):m_name(*str){}
    QString Do1() const override{return this->m_name;}
    void Do2() override;
private:
    QString m_name;
};

class State2:public State
{
public:
    explicit State2(QString *str):m_name(*str){}
    QString Do1() const override{return m_name;}
    void Do2() override{m_context->SetState(new State1(new QString("state1")));}
private:
    QString m_name;
};

class State3:public State
{
public:
    explicit State3(QString *str):m_name(*str){}
    QString Do1() const override{return m_name;}
    void Do2() override{m_context->SetState(new State2(new QString("state2")));}
private:
    QString m_name;
};



#endif // STATE_H
