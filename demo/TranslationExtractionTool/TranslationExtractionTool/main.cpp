#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFont>
#include <QQmlContext>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include "extractionthread.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QFont font = app.font();
    font.setFamily("Microsoft Yahei"); //设置全局字体
    app.setFont(font);

    ExtractionSignalHandler signalHandler;
    ExtractionThread extractionThread(&signalHandler);
    extractionThread.start();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("signalHandler", &signalHandler);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
