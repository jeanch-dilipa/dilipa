#ifndef GROUPCHOOSEPAGE_H
#define GROUPCHOOSEPAGE_H

#include <QWidget>
#include <QListWidget>

namespace Ui {
class GroupChoosePage;
}

class GroupChoosePage : public QWidget
{
    Q_OBJECT

public:
    explicit GroupChoosePage(const QPixmap &background, const QMap<QString, QList<QPixmap>> &pixmaps, QWidget *parent = 0);
    ~GroupChoosePage();

    void setBackgroundPixmap(const QPixmap &pix);
    void setPixmaps(const QMap<QString, QList<QPixmap>> &pixmaps);
signals:
    void showGroup(QString name);

private slots:
    void on_mask_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_toolButton_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

private:
    Ui::GroupChoosePage *ui;
    QList<QString> m_groupNames;
};

#endif // GROUPCHOOSEPAGE_H
