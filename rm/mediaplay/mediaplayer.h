#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

QT_BEGIN_NAMESPACE
namespace Ui { class mediaplayer; }
QT_END_NAMESPACE

class mediaplayer : public QWidget
{
    Q_OBJECT

public:
    mediaplayer(QWidget *parent = nullptr);
    ~mediaplayer();
private slots:
    void statechange(QMediaPlayer::State state);
    void playlistchange(int position);
    void durationchange(quint64 duration);
    void positionchange(quint64 position);

    void on_add_clicked();

    void on_remove_clicked();

    void on_close_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_play_clicked();

    void on_puase_clicked();

    void on_stop_clicked();

    void on_last_clicked();

    void on_next_clicked();

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::mediaplayer *ui;

    QMediaPlayer *play;
    QMediaPlaylist *playlist;
    int durationtime;
    int positiontime;
    int colornum=0;
};
#endif // MEDIAPLAYER_H
