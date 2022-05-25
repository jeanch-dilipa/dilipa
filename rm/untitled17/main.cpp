#include "mainwindow.h"
#include <QApplication>
#include <QLineEdit>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    QLineEdit line("hello word");
//    line.show();
    QPushButton button("quit");
    QObject::connect(&button,&QPushButton::clicked,&QApplication::quit);
    button.show();
    return a.exec();
}
