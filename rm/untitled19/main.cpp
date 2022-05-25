#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    Dialog *d=new Dialog(this);
    QObject::connect(d,&Dialog::useragechange,this,&MainWindow::setuserage);
    d->show();

    w.show();


    return a.exec();
}
void setusreage(int age)
{
    userage=age;
}
