#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QQmlContext>
#include <QStringLiteral>
#include <QFont>
#include <QFile>
#include <QTextStream>
#include <QtGlobal>
#include <QTextCodec>
#include <QDebug>
#include <QDir>

#include "common/DebugLog.h"
#include "dispatcher.h"
#include "global/publicdata.h"



/*自定义消息处理器*/
void customMessageHandler(const QtMsgType type,const QMessageLogContext &context,const QString &msg)
{
    QString info = QString("");

    switch (type)
    {
        case QtDebugMsg:
            info = QString("DEBUG:%1  %2  %3  %4").arg(context.file).arg(context.function).arg(context.line).arg(msg);
            break;
        case QtWarningMsg:
            info = QString("WARNING:%1  %2  %3  %4").arg(context.file).arg(context.function).arg(context.line).arg(msg);
            break;
        case QtCriticalMsg:
            info = QString("CRITICAL:%1  %2  %3  %4").arg(context.file).arg(context.function).arg(context.line).arg(msg);
            break;
        case QtFatalMsg:
            info = QString("FATAL:%1  %2  %3  %4").arg(context.file).arg(context.function).arg(context.line).arg(msg);
            break;
        case QtInfoMsg:
            info = QString("INFO:%1  %2  %3  %4").arg(context.file).arg(context.function).arg(context.line).arg(msg);
            break;
    }

    initLog(QDir::currentPath() + "/Log",100);
    loadingLogs(QDir::currentPath() + "/Log",type,info);
}

int main(int argc, char *argv[])
{
    /*只运行一个程序*/
    QSystemSemaphore sema("SWS-4000_SEMA",1,QSystemSemaphore::Open);
    sema.acquire();
    QSharedMemory memory("SWS-4000_MEMORY");
    bool isActive = memory.create(1);
    sema.release();

    if(isActive != true)return 0;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    /*指定字体*/
    QFont font;
    font.setFamily("DejaVu Sans Mono");
    app.setFont(font);

    /*指定字符格式*/
//    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//    QTextCodec::setCodecForLocale(codec);

    qInstallMessageHandler(customMessageHandler);

    Dispatcher dispather;
    QQmlApplicationEngine engine;

    engine.setOfflineStoragePath("F:\\dilipa\\qt\\qml\\SWS-4000");
    engine.rootContext()->setContextProperty("$G_DATA",&g_data);
    engine.rootContext()->setContextProperty("DISPATHER",&dispather);
    engine.load(QStringLiteral("qrc:/main.qml"));

    return app.exec();
}
