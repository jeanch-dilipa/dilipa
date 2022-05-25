#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QQmlContext>
#include <QStringLiteral>

#include "paravane.h"

int main(int argc, char *argv[])
{
    QSystemSemaphore sema("PARAVANE_sema",1,QSystemSemaphore::Open);
    sema.acquire();
    QSharedMemory share("PARAVANE_share");
    bool isactive=share.create(1);
    sema.release();
    if(!isactive)return 0;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    Paravane paravane;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("PARAVANE",&paravane);
    engine.load(QStringLiteral("qrc:/main.qml"));

    return app.exec();
}
