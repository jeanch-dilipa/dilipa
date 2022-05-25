#include "mp4.h"
#include "ui_mp4.h"

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>
#include <QMovie>

Mp4::Mp4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mp4)
{
    ui->setupUi(this);


    QMovie * movie = new QMovie("F:\\dilipa\\qt\\test\\6000UITest\\20211206_sws6000测试动画.gif");
    ui->label->setMovie(movie);
    ui->label->setScaledContents(true);//用来自适应label大小，图片填充label空间
    movie->start();
}

Mp4::~Mp4()
{
    delete ui;
}
