#include "server.h"

#include <QApplication>
#include <QTranslator>
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QDir dir;
//    QTranslator qtranslator;
//    qtranslator.load(dir.absolutePath()+"/english.qm");
//    a.installTranslator(&qtranslator);
    Server w;
    w.show();
    return a.exec();
}
