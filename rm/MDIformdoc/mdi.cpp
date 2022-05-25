#include "mdi.h"
#include "ui_mdi.h"

#include <QMouseEvent>
#include <QPlainTextEdit>
#include <QMenuBar>
#include <QFile>
#include <QFileDialog>

MDI::MDI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MDI)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    connect(ui->menuNEW,&QMenu::aboutToShow,this,&MDI::slot_new);
    connect(ui->menuOPEN,&QMenu::aboutToShow,this,&MDI::slot_open);
//    connect(ui->menuCLOSE,&QMenu::triggered,this,&MDI::slot_close);
    connect(ui->menuEXIT,&QMenu::aboutToShow,this,&MDI::slot_exit);
//    connect(ui->menuCUT,&QMenu::triggered,this,&MDI::slot_cut);
//    connect(ui->menuCOPY,&QMenu::triggered,this,&MDI::slot_copy);
//    connect(ui->menuTAG,&QMenu::triggered,this,&MDI::slot_tag);
    ui->mdiArea->setViewMode(QMdiArea::TabbedView); //多页模式
//    ui->mdiArea->setViewMode(QMdiArea::SubWindowView); //子窗口模式
    ui->mdiArea->setTabsClosable(true); //可关闭
}

MDI::~MDI()
{
    delete ui;
}

void MDI::mouseMoveEvent(QMouseEvent *event)
{
    if(isPress)
        move(event->pos()-mousep+this->pos());
}

void MDI::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
        isPress=true;
    mousep=event->pos();
}

void MDI::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    isPress=false;
}

void MDI::slot_new()
{
    QPlainTextEdit *pte=new QPlainTextEdit(this);
    ui->mdiArea->addSubWindow(pte);
    pte->show();
    pte->setWindowTitle("new");
}

void MDI::slot_open()
{
    QPlainTextEdit *pte=new QPlainTextEdit(this);
    ui->mdiArea->addSubWindow(pte);
    pte->show();
    QString filestr=QFileDialog::getOpenFileName(this,tr("open_file"),"/d:",tr("*.*"));
    if(!filestr.isEmpty())
    {
        QFile file(filestr);
        if(file.open(QIODevice::ReadWrite))
        {
            QString str=file.readAll();
            pte->setPlainText(str);
            pte->setWindowTitle(filestr.mid(filestr.lastIndexOf("/")+1));
            pte->setFocus();
        }
    }

}

void MDI::slot_exit()
{
    this->close();
}

