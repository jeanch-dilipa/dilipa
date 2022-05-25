#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QQmlContext>
#include <QStringLiteral>

#include "tetris.h"

int main(int argc, char *argv[])
{
    QSystemSemaphore sema("TETRIS_sema",1,QSystemSemaphore::Open);
    sema.acquire();
    QSharedMemory share("TERIS_share");
    bool isactive=share.create(1);
    sema.release();

    if(!isactive)
    {
        return 0;
    }

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    Tetris tetris;
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("TETRIS",&tetris);
    engine.load(QStringLiteral("qrc:/main.qml"));

    return app.exec();
}
