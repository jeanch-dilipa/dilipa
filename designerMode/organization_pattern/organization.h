#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include <QString>
#include <QVector>

class Organization
{
private:
    Organization *org;
public:
    Organization() = default;
    virtual ~Organization() = default;

    void setParent(Organization *org){this->org = org;}
    const Organization* getParent() const{return this->org;}

    virtual void addItem(Organization *org){Q_UNUSED(org)}
    virtual void removeItem(Organization *org){Q_UNUSED(org)}

    virtual bool isLeaf(){return false;}

    virtual QString Operation() const = 0;
};

class Leaf:public Organization
{
private:
    QString m_name;
public:
    explicit Leaf(QString* name):m_name(*name){}
    bool isLeaf() override{return true;}

    QString Operation() const override{return QString(this->m_name);}
};

class Continer:public Organization
{
private:
    QVector<Organization*> org_vector;
public:
    bool isLeaf() override{return false;}

    void addItem(Organization *org) override{this->org_vector.push_back(org);org->setParent(this);}
    void removeItem(Organization *org) override{this->org_vector.removeOne(org);org->setParent(nullptr);}

    QString Operation() const override
    {
        QString result("");
        for(const Organization *org : org_vector)
        {
            if(org == org_vector.back())/*检查是否是最后一项*/
            {
                result += org->Operation();
            }
            else
            {
                result += org->Operation() + QString("+");
            }
        }
        return "Branch(" + result + ")";
    }
};

#endif // ORGANIZATION_H
