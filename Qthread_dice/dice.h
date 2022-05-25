#ifndef DICE_H
#define DICE_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
typedef enum
{
    no=0,
    yes=1,
}pk;

class dice : public QThread
{
    Q_OBJECT
public:
    explicit dice(QThread *parent = nullptr);
    void run();
    void dicestart();
    void dicepause();
    void dicestop();
//    void init();

    pk threadpk;

private:
    bool dice_stop=false;
    bool dice_pause=true;
    int dice_count=0;
    int dice_view=0;
    QMutex mute;


signals:
    void newdicecreate(int dice_count,int dice_view,QString Qthreadid);

};


#endif // DICE_H
