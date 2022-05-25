#include "mdi.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MDI w;
    w.show();

    return a.exec();
}
