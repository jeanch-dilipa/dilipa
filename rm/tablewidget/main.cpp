#include "tablewiget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tableWiget w;
    w.show();
    return a.exec();
}
