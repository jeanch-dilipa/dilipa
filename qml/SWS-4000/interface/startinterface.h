#ifndef STARTINTERFACE_H
#define STARTINTERFACE_H

#include <QObject>
#include <QTimer>
#include <QMutex>
#include <QMutexLocker>

#include "common/common.h"

#define INITStartInterface (startInterface::initStartInterface())

class startInterface : public QObject
{
    Q_OBJECT
public:
    explicit startInterface(QObject *parent = nullptr);
    ~ startInterface();

    static startInterface *initStartInterface();
    static void deStartInterface();

signals:
    void signal_createStartInterface();                                                                                                 //创建启动界面


private:
    static startInterface                                 *s_startInterface;
    static QMutex                                          s_mutexLocker;
};

#endif // STARTINTERFACE_H
