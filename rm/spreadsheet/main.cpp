#include "mainwindow.h"

#include <QApplication>
#include "QSplashScreen"
#include "QThread"
#include "form.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen *splash=new QSplashScreen();
    splash->setPixmap(QPixmap(":/new/prefix1/images/test.bmp"));
    splash->show();
    Qt::Alignment topright=Qt::AlignLeft | Qt::AlignBottom;
    splash->showMessage(QString("loading......"),topright,Qt::red);
    QThread::sleep(3);
    MainWindow w;
    splash->showMessage(QString("connecting......"),topright,Qt::red);
    QThread::sleep(3);
    splash->finish(&w);
    delete splash;

    w.show();
    return a.exec();
}
