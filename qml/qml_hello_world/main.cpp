#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "helloworld.h"
#include <QQuickView>
#include <QQmlContext>
#include <QQmlComponent>
#include <QDebug>
#include <QQmlProperty>
#include <QMetaMethod>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
//                    //c++类型名    包名       主版本号 次版本号  qml类型名
//    qmlRegisterType<hello_world>("test",1,0,"TEST");        //为qml注册c++类

//    QQmlApplicationEngine engine;

//    QQmlComponent component(&engine,QUrl(QStringLiteral("qrc:/main.qml")));
//    QObject *qmlobject= component.create();     //在c++中实例化qml组件

//    qDebug()<<qmlobject->property("width").toInt();
//    qmlobject->setProperty("width",200);
//    qDebug()<<QQmlProperty::read(qmlobject,"width");
//    QObject *text=qmlobject->findChild<QObject*>("name");
//    if(text)
//        qDebug()<<text->property("text");

//    QVariant returnvalue,property="789";        //调用qml函数，返回值Q_RETURN_ARG，参数Q_ARG
//    QMetaObject::invokeMethod(qmlobject,"qmlfun",Q_RETURN_ARG(QVariant,returnvalue),Q_ARG(QVariant,property));
//    qDebug()<<returnvalue;
//    hello_world hello;
//    QObject::connect(qmlobject,SIGNAL(choose(QString)),&hello,SLOT(cslot(QString)));    //连接qml槽函数

//    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);
//    engine.load(url);       //加载文件，创建对象树

    hello_world hello;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Hello",&hello);
    engine.load(QStringLiteral("qrc:/main.qml"));
    if(engine.rootObjects().isEmpty())
        return  -1;

    return app.exec();
}
