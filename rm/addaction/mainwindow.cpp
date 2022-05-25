#include "mainwindow.h"

#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QMessageBox>
#include <QDialog>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("main windows"));

    action=new QAction(QIcon(":/images/file"),tr("&open"),this);
    action->setShortcuts(QKeySequence::Open);
    action->setStatusTip(tr("open an existing file"));
    connect(action,&QAction::triggered,this,&MainWindow::open);

    QMenu *m=menuBar()->addMenu(tr("&File"));
    m->addAction(action);

    QToolBar *t=addToolBar(tr("&File"));
    t->addAction(action);

    statusBar();
}

MainWindow::~MainWindow()
{

}

void MainWindow::open()
{
//    QMessageBox::information(this,tr("information"),tr("open"));

//    QDialog d(this);
//    d->setAttribute(Qt::WA_DeleteOnClose);
//    d.setWindowTitle(tr("hello dialog"));
//    d.show();

//    QDialog *d=new QDialog;
//    d->setAttribute(Qt::WA_DeleteOnClose);
//    d->setWindowTitle(tr("hello dialog"));
//    d->show();

    QMessageBox message;
    message.setText(tr("主要信息"));
    message.setInformativeText(tr("提示信息"));
    message.setDetailedText(tr("更多信息"));
    message.setStandardButtons(QMessageBox::Save|
                               QMessageBox::Discard|
                               QMessageBox::Cancel);
    message.setDefaultButton(QMessageBox::Save);

    int ret=message.exec();
    switch (ret)
    {
    case QMessageBox::Save:
        qDebug()<<tr("save");
        QMessageBox::information(this,tr("提示"),tr("save"));
        break;
    case QMessageBox::Discard:
        qDebug()<<tr("discard");
        QMessageBox::information(this,tr("提示"),tr("discard"));
        break;
    case QMessageBox::Cancel:
        qDebug()<<tr("Cancel");
        QMessageBox::information(this,tr("提示"),tr("cancel"));
        break;
    }
}
