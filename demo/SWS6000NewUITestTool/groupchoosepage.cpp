#include "groupchoosepage.h"
#include "ui_groupchoosepage.h"
#include <QGraphicsBlurEffect>
#include <QGraphicsDropShadowEffect>

#include <QtDebug>

GroupChoosePage::GroupChoosePage(const QPixmap &background, const QMap<QString, QList<QPixmap>> &pixmaps,  QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupChoosePage)
{
    ui->setupUi(this);

    QSize size = background.size();
    this->setFixedSize(size);
    ui->background->setFixedSize(size);
    ui->mask->setFixedSize(size);

    setBackgroundPixmap(background);
//    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(ui->listWidget);
//    shadow->setBlurRadius(38);
//    shadow->setOffset(0,2);
//    shadow->setColor("#80308cc6");
//    ui->listWidget->setGraphicsEffect(shadow);
    setPixmaps(pixmaps);
}

GroupChoosePage::~GroupChoosePage()
{
    delete ui;
}

void GroupChoosePage::setBackgroundPixmap(const QPixmap &pix)
{
    ui->background->setPixmap(pix);
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect(ui->background);
    blur->setBlurRadius(20);
    ui->background->setGraphicsEffect(blur);
    ui->background->setPixmap(ui->background->grab());
    ui->background->setGraphicsEffect(Q_NULLPTR);
}

void GroupChoosePage::setPixmaps(const QMap<QString, QList<QPixmap> > &pixmaps)
{
    ui->listWidget->clear();
    int i = 0;
    m_groupNames = pixmaps.keys();
    foreach (QString groupName, pixmaps.keys()) {
        ui->listWidget->addItem(groupName.toLocal8Bit());
        ui->listWidget->item(i)->setIcon(QIcon(pixmaps.value(groupName).first()));
        ++i;
        qDebug()<<groupName;
    }
}

void GroupChoosePage::on_mask_clicked()
{
    this->hide();
}

void GroupChoosePage::on_listWidget_itemClicked(QListWidgetItem *item)
{
//    ui->listWidget->indexFromItem(item);
//    emit showGroup(item->text());
}

void GroupChoosePage::on_toolButton_clicked()
{
    this->hide();
}

void GroupChoosePage::on_listWidget_clicked(const QModelIndex &index)
{
    emit showGroup(m_groupNames.at(index.row()));
}
