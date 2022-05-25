#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "updatefilepacking.h"
#include <QFont>
#include <QSystemSemaphore>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    //------------------------------保证程序只运行一个----------------------------->
    QSystemSemaphore sema("SWSUpgradePackingTool", 1, QSystemSemaphore::Open);

    sema.acquire(); //信号量，用于互斥，保证下面的代码一次只有一个进程在运行
    QSharedMemory mem("SWSUpgradePackingToolMemory");
    bool createRes = mem.create(1); //若已经存在，create会失败并返回false
    sema.release();

    if(!createRes)
    {   //创建失败，表示已有一个进程在运行
        return 0;
    }
    //--------------------------------------------------------------------------<

    QGuiApplication app(argc, argv);
    QFont font = app.font();
    font.setFamily("Microsoft Yahei"); //设置全局字体
    app.setFont(font);

    UpdateFilePacking packing;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("updatePacking", &packing);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
