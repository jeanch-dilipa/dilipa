#ifndef FACADE_H
#define FACADE_H

#include <QString>

class Interface1
{
public:
    static QString show1(){return QString("interface11");}
    static QString show2(){return QString("interface12");}
};
class Interface2
{
public:
    static QString show1(){return QString("interface21");}
    static QString show2(){return QString("interface22");}
};

class Facade
{
private:
    const Interface1* i1;
    const Interface2* i2;
public:
    Facade(const Interface1* i1 = nullptr,const Interface2* i2 = nullptr)
    {
        this->i1 = i1 ?: new Interface1();
        this->i2 = i2 ?: new Interface2();
    };

    QString show()
    {
        QString result("");
        result += this->i1->show1();
        result += this->i1->show2();
        result += this->i2->show1();
        result += this->i2->show2();
        return result;
    }
};

#endif // FACADE_H
