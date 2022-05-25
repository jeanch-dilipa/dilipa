#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QStringLiteral>
#include <QQmlContext>

#include "repeater.h"

int main(int argc, char *argv[])
{
    QSystemSemaphore sema("IC_CARD_sema",1,QSystemSemaphore::Open);
    sema.acquire();
    QSharedMemory share("IC_CARD_share");
    bool share_check=share.create(1);
    sema.release();

    if(!share_check)return 0;

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    repeater repeater;

    engine.rootContext()->setContextProperty("REPEATER",&repeater);
    engine.load(QStringLiteral("qrc:/main.qml"));

    return app.exec();
}
