#include <QtGui/QApplication>
#include "uartlayerdbuswindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UartLayerDbusWindow w;
    w.show();
    
    return a.exec();
}
