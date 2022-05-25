#ifndef PAGEDESIGNPREVIEWER_H
#define PAGEDESIGNPREVIEWER_H

#include <QMap>
#include <QWidget>
#include "imagepreviewer.h"
#include "effects/qinnershadow.h"
#include "texturetest.h"
#include "widgets.h"
#include "groupchoosepage.h"

namespace Ui {
class PageDesignPreviewer;
}

class PageDesignPreviewer : public QWidget
{
    Q_OBJECT

public:
    explicit PageDesignPreviewer(QWidget *parent = 0);
    ~PageDesignPreviewer();

private slots:
    void readImages();
    void saveImages(const QMap<QString, QStringList> &infos);

    void on_disconnectUSBBtn_clicked();

    void on_shutdownBtn_clicked();

    void on_pushButton_clicked();

    void on_rebootBtn_clicked();

    void on_showBtn_clicked();

    void on_viewByGroupBtn_clicked();

    void showGroup(QString name);

private:
    void setLoadProgress(int num); //update loading progress

private:
    Ui::PageDesignPreviewer *ui;
     QMap<QString, QStringList> m_groupInfo; //<groupname, fileNames>
    int m_pixmapsCount;
    int m_index;
    QMap<QString, QList<QPixmap>> m_pixmaps;//<groupname, pixmaps>
    ImagePreviewer *m_previewer;
    TextureTest *m_textureTest;
    Widgets *m_widget;
    QInnerShadow *shadow;
    GroupChoosePage *m_groupChoosePage;
};

#endif // PAGEDESIGNPREVIEWER_H
