#include "painwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    painwidget w;
    w.show();
    return a.exec();
}
