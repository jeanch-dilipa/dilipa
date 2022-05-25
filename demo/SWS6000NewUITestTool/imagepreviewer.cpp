#include "imagepreviewer.h"
#include "ui_imagepreviewer.h"

#include <QDir>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <QTime>



#define AUTO_HIDE_TIME 3*1000

ImagePreviewer::ImagePreviewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImagePreviewer),
    m_index(0),
    m_hideTimer(new QTimer(this))
{
    ui->setupUi(this);
//    ui->quitBtn->hide(); // use doubleClick instead;
    ui->front_btn->raise();
    ui->next_btn->raise();
    hideButton();
    ui->show->installEventFilter(this);

    m_hideTimer->setInterval(AUTO_HIDE_TIME);
    connect(m_hideTimer, &QTimer::timeout, this, &ImagePreviewer::hideButton);
}

ImagePreviewer::~ImagePreviewer()
{
    delete ui;
}

void ImagePreviewer::addImage(const QString &path)
{
    m_pixmaps.append(QPixmap(path).scaledToHeight(768, Qt::SmoothTransformation)); //scale to 1024x768
}

void ImagePreviewer::clearImages()
{
    m_pixmaps.clear();
}

void ImagePreviewer::setPixmaps(const QList<QPixmap> &pixmaps, const QList<QString> &names)
{
    m_pixmaps = pixmaps;
    m_pixmapFileNames = names;
}

void ImagePreviewer::showImage()
{
    setCurrentIndex(0);
    this->show();
    this->raise();
}

void ImagePreviewer::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    this->hide();
}

bool ImagePreviewer::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->show && event->type() == QEvent::MouseButtonDblClick)
    {
        this->hide();
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

void ImagePreviewer::setCurrentIndex(int index)
{
    if(m_pixmaps.isEmpty())
    {
        return;
    }
    else
    {
        if(index < 0)
            m_index = m_pixmaps.size() - 1;
        else if(index >= m_pixmaps.size())
            m_index = 0;
        else
            m_index = index;
        ui->imageLB->setPixmap(m_pixmaps.at(m_index));  //test show that this method is the most fast one,
                                                        //it will be lag if laod image each time when show it.
        ui->fileNameLB->setText(m_pixmapFileNames.at(m_index));
    }
}

void ImagePreviewer::on_front_btn_clicked()
{
    setCurrentIndex(m_index - 1);
    m_hideTimer->start();
}

void ImagePreviewer::on_next_btn_clicked()
{
    setCurrentIndex(m_index + 1);
    m_hideTimer->start();
}

void ImagePreviewer::hideButton()
{
    ui->front_btn->hide();
    ui->next_btn->hide();
    ui->fileNameLB->hide();
}

void ImagePreviewer::showButton()
{
    ui->front_btn->show();
    ui->next_btn->show();
    ui->fileNameLB->show();
    m_hideTimer->start();
}

void ImagePreviewer::on_show_clicked()
{
    showButton();
}

void ImagePreviewer::on_quitBtn_clicked()
{
    this->hide();
}
