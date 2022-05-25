#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <QString>

class Template
{
public:
    QString TemplateMothd() const
    {
        QString str = QString("");
        str.append(this->A());
        str.append(this->T1());
        str.append(this->K1());
        str.append(this->B());
        str.append(this->T2());
        str.append(this->K2());
        str.append(this->C());
        return str;
    }

    static QString A(){return QString("A");}
    static QString B(){return QString("B");}
    static QString C(){return QString("C");}

    virtual QString T1() const{return QString("");};
    virtual QString T2() const{return QString("");};

    virtual QString K1() const{return QString("");};
    virtual QString K2() const{return QString("");};
};

class TemplateT:public Template
{
public:
    QString T1() const override{return QString("T1");}
    QString T2() const override{return QString("T2");}
};

class TemplateK:public Template
{
public:
    QString K1() const override{return QString("k1");}
    QString K2() const override{return QString("k2");}
};

#endif // TEMPLATE_H
