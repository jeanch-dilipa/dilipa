#include "mainwindow.h"

#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMaximumSize(200,200);

    QMenuBar *mbar=menuBar();
    QMenu *m=mbar->addMenu("文件");

    QAction *a=m->addAction("new");
    a->setToolTip("new");
    connect(a,&QAction::triggered,[=]()
                                        {
                                            qDebug()<<"new";
                                        });

    QAction *a0=m->addAction("open");
    a0->setToolTip("open");
    connect(a0,&QAction::triggered,[=]()
                                        {
                                            qDebug()<<"open";
                                        });

    QToolBar *tbar=addToolBar("tool");
    tbar->addAction("new");
    tbar->setToolTip("new");

    QStatusBar *sbar=statusBar();
    QPushButton *l=new QPushButton(this);
    l->setText("status");
    sbar->addWidget(l);

    QPushButton *p=new QPushButton(this);
    p->setStyleSheet("color:red;background-color:green;");
    p->setText("open");
    tbar->addWidget(p);
    //p->setToolTip("open");
    connect(p,&QPushButton::clicked,[=]()
                                        {
                                            qDebug()<<"tool open";
//                                            l->setStatusTip("open");
                                        });

    QDockWidget *dw=new QDockWidget();
    dw->resize(200,200);
    connect(l,&QPushButton::clicked,dw,&QDockWidget::show);

    QTextEdit *te=new QTextEdit(this);
    QMainWindow::setCentralWidget(te);

}

MainWindow::~MainWindow()
{
}

