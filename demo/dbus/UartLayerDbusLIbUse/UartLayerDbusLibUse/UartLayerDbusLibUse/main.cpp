#include <QtGui/QApplication>
#include "uartlayerlibusewindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UartLayerLibUseWindow w;
    w.show();
    
    return a.exec();
}
