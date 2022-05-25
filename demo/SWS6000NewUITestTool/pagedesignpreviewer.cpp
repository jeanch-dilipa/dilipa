#include "pagedesignpreviewer.h"
#include "ui_pagedesignpreviewer.h"

#include <QDir>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
//#include <QTest>
#include <QProcess>
#include <QGraphicsDropShadowEffect>
#include "effects/qinnershadow.h"
#include "groupchoosepage.h"

#define IMAGE_PATH "/mnt/UIImages/"
#define UNGROUPED_NAME "Other" //没有分组的图片归类为一个组的组名

PageDesignPreviewer::PageDesignPreviewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageDesignPreviewer),
    m_previewer(new ImagePreviewer(this)),
    m_textureTest(new TextureTest()),
    m_widget(new Widgets()),
    m_groupChoosePage(new GroupChoosePage(this->grab(), m_pixmaps, this))
{
    ui->setupUi(this);

    m_groupChoosePage->hide();
    m_textureTest->hide();
    m_widget->hide();
    m_previewer->hide();
    ui->countLB->hide();
    ui->progressBar->hide();
    ui->noteLB->hide();
    ui->disconnectResultLB->hide();
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(ui->label);
    effect->setColor("#50000000");
    effect->setBlurRadius(12);
    effect->setOffset(0,2);
    ui->label->setGraphicsEffect(effect);

    QGraphicsDropShadowEffect *effect2 = new QGraphicsDropShadowEffect(ui->disconnectUSBBtn);
    effect2->setColor("#30000000");
    effect2->setBlurRadius(6);
    effect2->setOffset(0,2);
    ui->disconnectUSBBtn->setGraphicsEffect(effect2);

    QInnerShadow *innerShadow1 = new QInnerShadow(ui->widget);
    innerShadow1->setColor("#40000000");
    innerShadow1->setOffset(QPoint(2,2));
    innerShadow1->setRadius(2);
    ui->widget->setGraphicsEffect(innerShadow1);

    connect(ui->loadPicsBtn, &QPushButton::clicked, this, &PageDesignPreviewer::readImages);
    connect(ui->showBtn,&QToolButton::clicked, m_previewer, &ImagePreviewer::showImage);

    connect(m_groupChoosePage, &GroupChoosePage::showGroup, this, &PageDesignPreviewer::showGroup);

}

PageDesignPreviewer::~PageDesignPreviewer()
{
    delete ui;
}

void PageDesignPreviewer::readImages()
{
    QProcess process;
    QString source = "/dev/sdb1";
    QString des = "/mnt";
    QStringList arguments;
    arguments<<source<<des;
    process.start("mount", arguments);
    if(process.waitForStarted())
    {
        if(process.waitForFinished()) //wait until mount cmd finished, if not succeed, show "not found xxx" warnning
        {
            ;
        }
        else
        {
            return ;
        }
    }
    else
    {
        ;
    }

    QString path = IMAGE_PATH;
    QDir dir(path);

    if(dir.exists())
    {
        QStringList filter;
        filter<<"*.png"<<"*.jpg";

        m_pixmapsCount = 0;
        m_groupInfo.clear();

        //grouped images
        QStringList groups;
        groups = dir.entryList(QStringList(), QDir::Dirs | QDir::NoDotAndDotDot);
        foreach (QString group, groups) {
            QDir picDir(path+group);
            if(picDir.exists())
            {
                 QStringList paths = picDir.entryList(filter, QDir::Files | QDir::NoDotAndDotDot);
                 if(paths.isEmpty())
                     continue;
                 m_pixmapsCount += paths.length();
                 m_groupInfo.insert(group, paths);
            }
        }
        //ungrouped images
        QStringList paths = dir.entryList(filter, QDir::Files | QDir::NoDotAndDotDot);
        if(paths.length() != 0 )
        {
            m_pixmapsCount += paths.length();
            m_groupInfo.insert(UNGROUPED_NAME, paths);
        }

        QTime start = QTime::currentTime();
        //read as pixmaps
        saveImages(m_groupInfo);
        qDebug()<<"读取用时："<<start.msecsTo(QTime::currentTime())<<"ms" ;
    }
    else
    {
        QMessageBox::warning(this, "Warning", tr("无法找到图片目录，请检查U盘!"), QMessageBox::Ok);
        return;
    }

    if(!m_pixmaps.isEmpty())
    {
//        ui->imageLB->setPixmap(m_pixmaps.first());
    }
    else
    {
        int result = QMessageBox::warning(this, "Warning", tr("无图片"), QMessageBox::Cancel, QMessageBox::Retry);
        if(result == QMessageBox::Retry)
        {
            readImages();
        }
        else if(result == QMessageBox::Cancel)
        {

        }
    }
}

void PageDesignPreviewer::saveImages(const QMap<QString, QStringList> &groupInfo)
{
    ui->loadPicsBtn->setText("读取中...");
    ui->countLB->show();
    ui->progressBar->show();
    ui->noteLB->show();

    m_pixmaps.clear();
    QList<QPixmap> pixs;
    int i = 0;
    foreach (QString group, groupInfo.keys()) {
        pixs.clear();
        foreach (QString pic, groupInfo[group]) {
            QString filePath ;
            if(group == UNGROUPED_NAME)
            {
                filePath = IMAGE_PATH + pic;
            }
            else
            {
                filePath = IMAGE_PATH +group+ "/" + pic;
            }
            pixs.append(QPixmap(filePath).scaledToHeight(768, Qt::SmoothTransformation)); //scale to 1024x768
            setLoadProgress(++i);
        }
        m_pixmaps.insert(group, pixs);
    }


    ui->loadPicsBtn->setText("读取图片");
    ui->noteLB->hide();

    m_groupChoosePage->setBackgroundPixmap(this->grab());
    m_groupChoosePage->setPixmaps(m_pixmaps);
}

void PageDesignPreviewer::setLoadProgress(int num)
{
    if(m_pixmapsCount>0)
    {
        ui->progressBar->setValue(num*1.0/m_pixmapsCount*100);
        ui->countLB->setText(QString::number(num) + "/"+QString::number(m_pixmapsCount));
        qApp->processEvents(); //force update progress bar
    }
}

void PageDesignPreviewer::on_disconnectUSBBtn_clicked()
{
    QProcess pro ;
    pro.start("umount", QStringList("/dev/sdb1"));
    pro.waitForStarted();
    pro.waitForFinished();
    pro.start("sync");
    pro.waitForStarted();
    pro.waitForFinished();
    ui->disconnectResultLB->show();
    QTimer::singleShot(3000, ui->disconnectResultLB, &QLabel::hide);
}

void PageDesignPreviewer::on_shutdownBtn_clicked()
{
    QProcess pro ;
    pro.start("poweroff");
    pro.waitForStarted();
    pro.waitForFinished();
}


void PageDesignPreviewer::on_pushButton_clicked()
{
    qDebug()<<"show---------------------------";
    m_widget->show();
    qDebug()<<"show---------------------------";
    m_widget->raise();
}

void PageDesignPreviewer::on_rebootBtn_clicked()
{
    QProcess pro ;
    pro.start("reboot");
    pro.waitForStarted();
    pro.waitForFinished();
}

void PageDesignPreviewer::on_showBtn_clicked()
{
    QList<QPixmap> ps;
    QStringList psNames;
    foreach (QList<QPixmap> p, m_pixmaps.values()) {
        ps += p;
    }
    foreach (QStringList names, m_groupInfo.values()) {
        psNames+= names;
    }
    m_previewer->setPixmaps(ps, psNames);
    m_previewer->showImage();
//    m_previewer->raise();
}

void PageDesignPreviewer::on_viewByGroupBtn_clicked()
{
     m_groupChoosePage->show();
     m_groupChoosePage->raise();
//     QWidget *widget = new QWidget(nullptr);
//     widget->setFixedSize(300,300);
//     widget->setWindowFlags(widget->windowFlags()|Qt::Drawer);
//     widget->show();

}

void PageDesignPreviewer::showGroup(QString name)
{
    m_previewer->setPixmaps(m_pixmaps[name], m_groupInfo[name]);
    m_previewer->showImage();
}
