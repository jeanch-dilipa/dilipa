#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QStringLiteral>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QSystemSemaphore sema("ImageView_sema",1,QSystemSemaphore::Open);
    sema.acquire();
    QSharedMemory share("IMAGEVIEW_SHARE");
    bool isactive=share.create(1);
    sema.release();
    if(!isactive)return 0;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

//    engine.rootContext()->setContextProperty("","");
    engine.load(QStringLiteral("qrc:/main.qml"));

    return app.exec();
}
