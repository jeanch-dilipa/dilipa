#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <QString>

class prototype
{
public:
    prototype();
    explicit prototype(QString* name):m_name(*name){}

    prototype *clone() const{return new prototype(*this);}//深拷贝（原型）
    QString getM_name() const {return m_name;}
private:
    QString     m_name;
};

#endif // PROTOTYPE_H
