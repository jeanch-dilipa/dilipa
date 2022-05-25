#ifndef MEDIATION_H
#define MEDIATION_H

#include <QString>

class Incident;
class Mediation
{
public:
    virtual QString notify(const Incident* in,QString str) const = 0;
};

class Incident
{
public:
    Mediation* m_media;
    Incident(Mediation* media = nullptr):m_media(media){}

    void setMedai(Mediation* media){this->m_media = media;}
};

class IncidentA:public Incident
{
public:
    QString DoA() const{return this->m_media->notify(this,QString("A"));}
    QString DoB() const{return this->m_media->notify(this,QString("B"));}
};

class IncidentB:public Incident
{
public:
    QString DoC() const{return this->m_media->notify(this,QString("C"));}
    QString DoD() const{return this->m_media->notify(this,QString("D"));}
};

class MediationA:Mediation
{
public:
    IncidentA* m_IA;
    IncidentB* m_IB;

    MediationA(IncidentA* IA,IncidentB* IB):m_IA(IA),m_IB(IB){m_IA->setMedai(this),m_IB->setMedai(this);}
    QString notify(const Incident* in,QString str) const override
    {
        Q_UNUSED(in);
        if(in == m_IA && str == QString("A"))
        {
            return m_IB->DoC() + m_IA->DoB();
        }
        if(in == m_IB && str == QString("D"))
        {
            return m_IA->DoB() + m_IB->DoC();
        }
        return str;
    }
};

#endif // MEDIATION_H
