#ifndef OBSERVER_H
#define OBSERVER_H

#include <QString>
#include <QVector>

class AbstractObserver
{
public:
    virtual QString Update(QString str) const = 0;
};

class AbStractSubject
{
public:
    virtual void subscribe(AbstractObserver *observer) = 0;
    virtual void close(AbstractObserver *observer) = 0;
    virtual QString issue() const = 0;
};

class Observer:public AbstractObserver
{
public:
    explicit Observer(AbStractSubject *subject = nullptr):m_subject(subject){this->m_subject = subject;if(this->m_subject)m_subject->subscribe(this);};
    QString Update(QString str) const override{return str;}

private:
    AbStractSubject *m_subject;
};


class Subject:public AbStractSubject
{
public:
    explicit Subject() = default;
    void subscribe(AbstractObserver *observer) override{this->m_observer.push_back(observer);}
    void close(AbstractObserver *observer) override{this->m_observer.removeOne(observer);}
    QString issue() const override
    {
        QString str = "";
        foreach(AbstractObserver *observer,m_observer)
        {
            str.append(observer->Update(m_message));
        }
        return str;
    }

    void newMessage(const QString message){this->m_message = message;}

private:
    QVector<AbstractObserver*> m_observer;
    QString m_message;
};
#endif // OBSERVER_H
