#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    QTextCodec *textcode=QTextCodec::codecForName("utf-8"); //全局文字编码设置
//    QTextCodec::setCodecForLocale(textcode);

//    QString filepath=QFileDialog::getOpenFileName();
//    QFile file(filepath);
//    file.open(QIODevice::ReadOnly);
//    QTextStream ts(&file);
//    while(!ts.atEnd())
//        qDebug()<<ts.readLine();
//    file.close();

    return a.exec();
}
