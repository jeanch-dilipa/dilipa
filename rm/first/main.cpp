#include "head.h"
#include <QLabel>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLabel *label=new QLabel("hello word!");
    label->show();
    return a.exec();
}
