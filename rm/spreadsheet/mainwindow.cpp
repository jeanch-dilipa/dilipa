#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSplashScreen"
#include "QThread"
#include "QTextEdit"
#include "form.h"

#include <QFileDialog>
#include <QMdiArea>
#include <qmdiarea.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    Form *f=new Form;
    ui->mdiArea->addSubWindow(f);
    f->show();
    f->defaultfile(":/new/prefix1/txt/readme.txt");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionnew_triggered()
{
    Form *m=new Form;
    ui->mdiArea->addSubWindow(m);
    m->show();
}

void MainWindow::on_actionopen_triggered()
{
    QString curpath=QDir::currentPath();
    QString filetype="文本文件(*.txt)::所有文件(*.*)";
    QString filename=QFileDialog::getOpenFileName(this,tr("打开一个文件"),curpath,filetype);
    if(filename.isEmpty())
        return;
    Form *f=new Form;
    ui->mdiArea->addSubWindow((f));
    f->show();
    f->open(filename);
}

void MainWindow::on_actioncut_triggered()
{
    Form *m;
    m=(Form*)ui->mdiArea->activeSubWindow();
    m->cut();
}

void MainWindow::on_actionpaste_triggered()
{
    Form *m=(Form*)ui->mdiArea->activeSubWindow();
    m->paste();
}
