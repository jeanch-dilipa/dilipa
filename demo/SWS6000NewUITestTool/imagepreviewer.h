#ifndef MAINWIDGET_H
#define MAINWIDGET_H


#include <QWidget>

namespace Ui {
class ImagePreviewer;
}

class ImagePreviewer : public QWidget
{
    Q_OBJECT

public:
    explicit ImagePreviewer(QWidget *parent = 0);
    ~ImagePreviewer();

    void addImage(const QString &path);
    void clearImages();

    void setPixmaps(const QList<QPixmap> &pixmaps, const QList<QString> &names);

public slots:
    void showImage();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void setCurrentIndex(int index);

private slots:
    void on_front_btn_clicked();
    void on_next_btn_clicked();

    void hideButton();
    void showButton();

    void on_show_clicked();
    void on_quitBtn_clicked();

private:
    Ui::ImagePreviewer *ui;
    int m_index;
    QTimer *m_hideTimer;
    QList<QPixmap> m_pixmaps;
    QList<QString> m_pixmapFileNames;
};

#endif // MAINWIDGET_H
