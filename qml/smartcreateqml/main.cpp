#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTextStream>
#include <QFile>
#include <QtGui>

//QTextStream cout(stdout,QIODevice::WriteOnly);  //文本流操作

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();

//    QList<QString> list;
//    list<<"jkdf"<<"kshd";
//    QListIterator<QString> iter(list);
//    while (iter.hasNext())
//    {
//        cout<<iter.next();
//        if(iter.hasNext())
//            cout<<" ";
//    }
//    cout<<"!"<<endl;

//    QStringList strlist;
//    strlist<<"jshd"<<"kshd"<<"jksd";
//    QString str= strlist.join(" ij ")+"!";      //在链表节点中添加字符
//    cout<<str<<endl;

//    QList<QStringList> data;
//    QFile file("E:\\新建 XLS 工作表.xls");
//    if(file.open(QIODevice::ReadOnly))
//    {
//        QTextStream stream(&file);
//        forever
//        {
//            QString line=stream.readLine();
//            cout<<line<<endl;
//            if(line.isEmpty())
//                continue;
//            if(line.isNull())
//                break;
//            QStringList row;
//            foreach(const QString& cell,line.split(","))
//                row.append(cell.trimmed());
//            line=row.join("1");
//            cout<<line<<endl;

//            data.append(row);
//        }
//    }

}
