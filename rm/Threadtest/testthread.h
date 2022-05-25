#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>

#define  MAX 100;

class testthread : public QThread
{
    Q_OBJECT
public:
    explicit testthread(QObject *parent = nullptr);
    ~ testthread();
public slots:
    void fun(int j);

private:
    void run();
    int  j=0;

signals:
    void pubdata(int j);

signals:

};

#endif // TESTTHREAD_H
