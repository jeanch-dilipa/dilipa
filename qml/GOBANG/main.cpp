#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QQmlContext>
#include <QStringLiteral>

#include "gobang.h"

int main(int argc, char *argv[])
{
    QSystemSemaphore sema("GOBANG_sema",1,QSystemSemaphore::Open);
    sema.acquire();
    QSharedMemory share("GOBANG_share");
    bool isactive=share.create(1);
    sema.release();
     if(!isactive)
         return 0;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    gobang gobang;
    engine.rootContext()->setContextProperty("GOBANG",&gobang);
    engine.load(QStringLiteral("qrc:/main.qml"));

    return app.exec();
}
