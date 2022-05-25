#include <QtGui/QApplication>
#include "datalaywindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataLayWindow w;
    w.show();
    
    return a.exec();
}
