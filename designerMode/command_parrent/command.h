#ifndef COMMAND_H
#define COMMAND_H

#include <QString>

class Command
{
public:
    virtual QString exe() const = 0;
};

class simpleCommand:public Command
{
public:
    QString simple;
    explicit simpleCommand(QString* sim):simple(*sim){}
    QString exe() const override{return simple;}
};

class Reciver
{
public:
    static QString exeA(QString a){return a;}
    static QString exeB(QString b){return b;}
};

class ComPlexCommand: public Command
{
public:
    Reciver* r;
    QString a;
    QString b;

    ComPlexCommand(Reciver* r,QString* a,QString* b):r(r),a(*a),b(*b){}
    QString exe()const override{return this->r->exeA(a) + this->r->exeB(b);}
};

class Send
{
public:
    Command* start;
    Command* end;

    Send() = default;
    void setSimpleCommand(Command* start){this->start = start;}
    void setComplexCommand(Command* end){this->end = end;}

    QString doSomeSimpleThing() const{if(this->start)return this->start->exe();else return QString("");}
    QString doSomeComplexThing() const{if(this->start)return this->end->exe();else return QString("");}
};

#endif // COMMAND_H
