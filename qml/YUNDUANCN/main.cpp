#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QDebug>
#include <QStringLiteral>
#include <QQmlContext>
#include <QQuickView>

#include "yunduancn.h"

int main(int argc, char *argv[])
{

    QSystemSemaphore sema("yunduancn",1,QSystemSemaphore::Open);    //系统信号量+共享内存保证只运行一个程序
    sema.acquire();
    QSharedMemory sharm("yunduancnMemory");
    bool isactive=sharm.create(1);
    sema.release();

    if(!isactive)
    {
        return 0;
    }

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQuickView view;
    yunduancn yunduancn;
    QQmlApplicationEngine engine;
    view.setFlags(Qt::FramelessWindowHint);
    engine.rootContext()->setContextProperty("YunDuanCN",&yunduancn);
    engine.load(QStringLiteral("qrc:/main.qml"));

    return app.exec();
}
