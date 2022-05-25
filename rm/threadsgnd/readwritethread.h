#ifndef READWRITETHREAD_H
#define READWRITETHREAD_H
#include <QThread>
#include <QSemaphore>


class readthread : public QThread
{
    Q_OBJECT
public:
    readthread();
    void run() override;
    void threadstop();

    bool over=false;

signals:
    void readbuffsignal(int *buff,int buggsize,int buffnum);
};


class writethread : public QThread
{
public:
    writethread();
    void run() override;
    void threadstop();

    bool over=false;

};
#endif // READWRITETHREAD_H
