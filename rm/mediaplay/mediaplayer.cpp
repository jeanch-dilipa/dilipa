#include "mediaplayer.h"
#include "ui_mediaplayer.h"

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>

mediaplayer::mediaplayer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mediaplayer)
{
    ui->setupUi(this);
    play=new QMediaPlayer(this);
    playlist=new QMediaPlaylist(this);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);    //循环播放
    play->setPlaylist(playlist);
//    void(mediaplayer::*statech)(QMediaPlayer::State)=&mediaplayer::statechange;     //带参信号传递QT5
    connect(play,&QMediaPlayer::stateChanged,this,&mediaplayer::statechange);       //播放状态
    connect(play,&QMediaPlayer::durationChanged,this,&mediaplayer::durationchange);     //播放总时长
    connect(play,&QMediaPlayer::positionChanged,this,&mediaplayer::positionchange);     //当前播放位置
    connect(playlist,&QMediaPlaylist::currentIndexChanged,this,&mediaplayer::playlistchange);       //播放列表
}

mediaplayer::~mediaplayer()
{
    delete ui;
}

void mediaplayer::statechange(QMediaPlayer::State state)
{
    ui->play->setEnabled(!(state==QMediaPlayer::PlayingState));
    ui->puase->setEnabled(state==QMediaPlayer::PlayingState);
    ui->stop->setEnabled(state==QMediaPlayer::PlayingState);
}

void mediaplayer::playlistchange(int position)
{
    Q_UNUSED(position);
}

void mediaplayer::durationchange(quint64 duration)
{
    durationtime=duration;
    ui->time->setText(QString("%1:%2/%3:%4").arg(positiontime/60000).arg((positiontime/60000)%60).arg(durationtime/60000).arg((durationtime/60000)%60));
}

void mediaplayer::positionchange(quint64 position)
{
    positiontime=position;
    ui->time->setText(QString("%1:%2/%3:%4").arg(positiontime/60000).arg((positiontime/60000)%60).arg(durationtime/60000).arg((durationtime/60000)%60));
}


void mediaplayer::on_add_clicked()
{
    QStringList filelist=QFileDialog::getOpenFileNames(this,tr("选择音频文件"),"f:","*.*");
    foreach(QString str,filelist)
    {
        if(colornum+10>=255)
            colornum=0;
        playlist->addMedia(QUrl::fromLocalFile(str));
        QFileInfo info(str);
        ui->listWidget->addItem(info.fileName());

        QListWidgetItem *lwi=ui->listWidget->item(ui->listWidget->count()-1);
        lwi->setBackgroundColor(qRgb(colornum+10,255-colornum,colornum/2+15));
        colornum+=10;
    }
}

void mediaplayer::on_remove_clicked()
{
    QListWidgetItem *lwi=ui->listWidget->takeItem(ui->listWidget->currentRow());
    delete lwi;
//    ui->listWidget->removeItemWidget(lwi);
    playlist->removeMedia(ui->listWidget->currentRow());

}

void mediaplayer::on_close_clicked()
{
    ui->listWidget->clear();
    playlist->clear();
    play->stop();
}

void mediaplayer::on_listWidget_doubleClicked(const QModelIndex &index)
{
    QListWidgetItem *lwi=ui->listWidget->item(index.row());
    ui->playname->setText(lwi->text());
    playlist->setCurrentIndex(index.row());
    play->play();
}

void mediaplayer::on_play_clicked()
{
    play->play();
}

void mediaplayer::on_puase_clicked()
{
    play->pause();
}

void mediaplayer::on_stop_clicked()
{
    play->stop();
}

void mediaplayer::on_last_clicked()
{
    playlist->previous();
}

void mediaplayer::on_next_clicked()
{
    playlist->next();
}

void mediaplayer::on_horizontalSlider_valueChanged(int value)
{
    play->setVolume(value);
}
