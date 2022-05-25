#ifndef ITERATOR_H
#define ITERATOR_H

#include <QString>
#include <QVector>

template<typename T,typename U>
class Iterator
{
public:
    typedef typename QVector<T>::iterator iter;
    explicit Iterator(U* container):m_data(container){this->m_iter = container->m_iter.begin();}

    void next(){this->m_iter++;}
    void first(){this->m_iter = m_data->m_iter.begin();}
    bool isend(){return this->m_iter == m_data->m_iter.end();}
    iter current() const{return this->m_iter;}

    U* m_data;
    iter m_iter;
};

template<typename T>
class Container
{
//    friend Iterator<T,Container>;
public:
    void add(T a){m_iter.append(a);}
    Iterator<T,Container>* createIterator(){return new Iterator<T,Container>(this);}

private:
    QVector<T> m_iter;
};

#endif // ITERATOR_H
