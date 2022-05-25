#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QStringLiteral>
#include <QQmlContext>

#include "simple_manger.h"
#include "sqllitemake.h"


int main(int argc, char *argv[])
{
    QSystemSemaphore sema("Simple_Manger_sema",1,QSystemSemaphore::Open);
    sema.acquire();
    QSharedMemory share("Simple_Manger_share");
    bool isactive=share.create(1);
    sema.release();
    if(!isactive)return 0;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Simple_Manger Simple_Manger;

//    engine.setOfflineStoragePath(DB_FILEPATH);
    engine.rootContext()->setContextProperty("SIMPLE_MANGER",&Simple_Manger);
    engine.load(QStringLiteral("qrc:main.qml"));
    return app.exec();
}
