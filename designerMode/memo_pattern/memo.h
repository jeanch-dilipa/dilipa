#ifndef MEMO_H
#define MEMO_H

#include <QString>
#include <QTime>
#include <QRandomGenerator>
#include <qrandom.h>
#include <QVector>

class BaseMemo
{
public:
    virtual QString state() const = 0;
    virtual QTime dateTime() const = 0;
    virtual QString getName() const = 0;
};

class Memo:public BaseMemo
{
public:
    explicit Memo(QString* state):m_state(*state),m_dateTime(QTime::currentTime()){}

    QString state() const override{return this->m_state;}
    QTime dateTime() const override{return this->m_dateTime;}
    QString getName() const override{return this->dateTime().toString("hh:mm:ss zzz") + this->m_state;}
private:
    QString m_state;
    QTime m_dateTime;
};

template <typename T>
class Send
{
public:
    explicit Send(QString* state):m_state(*state){}

    void doSomeThing()
    {
        QRandomGenerator(QTime::currentTime().msec());
        this->m_state = QString(QRandomGenerator::global()->bounded(256));
    }

    T* save(){return new Memo(&this->m_state);}
    void restore(T* memo){this->m_state = memo->state();}
    QString showSate() const{return this->m_state;}


    const QString& show(QString &m_state) const
    {
        return m_state;
    }

    QString& show(QString &m_state)
    {
        return const_cast<QString&>(static_cast<const QString&>(*this->m_state));
//        return m_state;
    }

private:
    QString m_state;
};

static QString operator+(QString str,BaseMemo* memo)
{
    str += memo->state();
    return str;
}

template <typename U,typename T>
class Manager
{
public:
    explicit Manager(U* send):m_send(send){}

    void backUp(){this->m_memoList.push_back(this->m_send->save());}
    void unDo()
    {
        T* memo = m_memoList.back();
        m_memoList.pop_back();
        this->m_send->restore(memo);
    }
    QString history()
    {
        QString str = "";
        return std::accumulate(m_memoList.begin(),m_memoList.end(),str);
//        foreach (T *m, m_memoList)
//        {
//            str.append(m->state());
//        }
//        return str;
    }

private:
    U* m_send;
    QVector<T*> m_memoList;
};

#endif // MEMO_H
