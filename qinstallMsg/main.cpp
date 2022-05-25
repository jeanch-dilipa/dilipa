#include "mainwindow.h"

#include <QApplication>
#include <QtGlobal>
#include <QDebug>
#include <QFile>
#include <QTimer>

void customMsg(QtMsgType type,const QMessageLogContext &context,const QString &strMsg)
{
    QString str=QString("");
    switch(type)
    {
        case QtWarningMsg:
            str=QString("warning:%1%2%3").arg(__FILE__).arg(context.line).arg(strMsg);
            break;
        default:
            break;
    }

    QFile file("log.txt");
    if(!file.open(QIODevice::ReadWrite))
        return;
    QTextStream out(&file);
    out<<str;
    QTextStream ts(stdout, QIODevice::WriteOnly);
    ts << str << endl;
    out.flush();


}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(customMsg);

    MainWindow w;
    w.show();

    qWarning()<<"warn";

    return a.exec();
}
