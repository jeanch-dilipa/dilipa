#include "mainwidget.h"
#include "pressuremonitor.h"
#include "center.h"
#include "heteroideus.h"
#include "curve.h"
#include "mp4.h"
#include "tablewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tableWidget w(nullptr);
    w.show();
    return a.exec();
}
