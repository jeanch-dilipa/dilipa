#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QQmlContext>
#include <QStringLiteral>

#include "chese.h"

int main(int argc, char *argv[])
{
    QSystemSemaphore sema("CHINESE_CHESS_sema",1,QSystemSemaphore::Open);
    sema.acquire();
    QSharedMemory share("CHINESE_CHESS_share");
    bool isactive=share.create(1);
    sema.release();

    if(!isactive)return 0;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Chese chess;
    engine.rootContext()->setContextProperty("CHESS",&chess);
    engine.load(QStringLiteral("qrc:/main.qml"));

    return app.exec();
}
