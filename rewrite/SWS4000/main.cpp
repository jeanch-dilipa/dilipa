#include <QApplication>
#include <QSystemSemaphore>
#include <QSharedMemory>

#include "common/debug.h"
#include "systemmanager.h"

int main(int argc, char *argv[])
{
    QSystemSemaphore systemSema("SWS4000_sema", 1, QSystemSemaphore::Open);
    systemSema.acquire();
    QSharedMemory shareMemory("SWS4000_memory");
    bool isActive = shareMemory.create(1);
    systemSema.release();
    if(false == isActive)
    {
        return 0;
    }

    QApplication a(argc, argv);
    qInstallMessageHandler(customMessageHandler);

    qRegisterMetaType<DataAttributeType>("DataAttributeType");

    SystemManager sysmanager;
    return a.exec();
}
