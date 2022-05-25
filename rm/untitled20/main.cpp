#include "fileidalogue.h"

#include <QApplication>
#include <QFileDialog>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    fileidalogue w;
    w.show();
    return a.exec();
}
