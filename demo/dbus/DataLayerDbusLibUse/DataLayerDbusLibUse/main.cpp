#include <QtGui/QApplication>
#include "datalayerdbuswindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataLayerDbusWindow w;
    w.show();
    
    return a.exec();
}
