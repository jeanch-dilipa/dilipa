#include "sqlitemake.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sqlitemake w;
    w.show();
    return a.exec();
}
