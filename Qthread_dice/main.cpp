#include "mainqthread.h"

#include <QApplication>
#include <QTime>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainQthread w;
    w.show();
    return a.exec();
}
