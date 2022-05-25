#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QQmlContext>
#include <QStringLiteral>
#include <QThread>
#include <QDebug>
#include <QSettings>
#include <QFile>

#include "file_io.h"
#include "crc.h"

int main(int argc, char *argv[])
{
    QSystemSemaphore sema("Md5_Upk_tool_sema",1,QSystemSemaphore::Open);
    sema.acquire();
    QSharedMemory share("Md5_Upk_tool");
    bool isavtive=share.create(1);
    sema.release();

    if(!isavtive)
    {
        return 0;
    }

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    File_io file_io;
    engine.rootContext()->setContextProperty("fileio",&file_io);
    engine.load(QStringLiteral("qrc:/main.qml"));

    return app.exec();
}
