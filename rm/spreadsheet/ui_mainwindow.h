/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionnew;
    QAction *actionopen;
    QAction *actionsave;
    QAction *actionsave_as;
    QAction *action1population;
    QAction *action2report_2006_sp;
    QAction *actionExit;
    QAction *actioncut;
    QAction *actioncopy;
    QAction *actionpaste;
    QAction *actiondelete;
    QAction *actionfind;
    QAction *actiongo_to_cell;
    QAction *actionrecalculate;
    QAction *actionsort;
    QAction *actionrow;
    QAction *actioncolumn;
    QAction *actionall;
    QAction *actionshow_grid;
    QAction *actionauto_recalculate;
    QAction *actionabout;
    QAction *actionabout_qt;
    QAction *action_4;
    QAction *action_5;
    QAction *action_6;
    QWidget *centralwidget;
    QMdiArea *mdiArea;
    QMenuBar *menubar;
    QMenu *menuaas;
    QMenu *menuedit;
    QMenu *menuselect;
    QMenu *menutools;
    QMenu *menuoptions;
    QMenu *menuhelp;
    QStatusBar *statusbar;
    QToolBar *toolBar;
    QToolBar *toolBar_2;
    QToolBar *toolBar_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(619, 423);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        actionnew = new QAction(MainWindow);
        actionnew->setObjectName(QString::fromUtf8("actionnew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/images/test.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actionnew->setIcon(icon);
        actionnew->setAutoRepeat(true);
        actionopen = new QAction(MainWindow);
        actionopen->setObjectName(QString::fromUtf8("actionopen"));
        actionsave = new QAction(MainWindow);
        actionsave->setObjectName(QString::fromUtf8("actionsave"));
        actionsave_as = new QAction(MainWindow);
        actionsave_as->setObjectName(QString::fromUtf8("actionsave_as"));
        action1population = new QAction(MainWindow);
        action1population->setObjectName(QString::fromUtf8("action1population"));
        action2report_2006_sp = new QAction(MainWindow);
        action2report_2006_sp->setObjectName(QString::fromUtf8("action2report_2006_sp"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actioncut = new QAction(MainWindow);
        actioncut->setObjectName(QString::fromUtf8("actioncut"));
        actioncopy = new QAction(MainWindow);
        actioncopy->setObjectName(QString::fromUtf8("actioncopy"));
        actionpaste = new QAction(MainWindow);
        actionpaste->setObjectName(QString::fromUtf8("actionpaste"));
        actiondelete = new QAction(MainWindow);
        actiondelete->setObjectName(QString::fromUtf8("actiondelete"));
        actionfind = new QAction(MainWindow);
        actionfind->setObjectName(QString::fromUtf8("actionfind"));
        actiongo_to_cell = new QAction(MainWindow);
        actiongo_to_cell->setObjectName(QString::fromUtf8("actiongo_to_cell"));
        actionrecalculate = new QAction(MainWindow);
        actionrecalculate->setObjectName(QString::fromUtf8("actionrecalculate"));
        actionsort = new QAction(MainWindow);
        actionsort->setObjectName(QString::fromUtf8("actionsort"));
        actionrow = new QAction(MainWindow);
        actionrow->setObjectName(QString::fromUtf8("actionrow"));
        actioncolumn = new QAction(MainWindow);
        actioncolumn->setObjectName(QString::fromUtf8("actioncolumn"));
        actionall = new QAction(MainWindow);
        actionall->setObjectName(QString::fromUtf8("actionall"));
        actionshow_grid = new QAction(MainWindow);
        actionshow_grid->setObjectName(QString::fromUtf8("actionshow_grid"));
        actionauto_recalculate = new QAction(MainWindow);
        actionauto_recalculate->setObjectName(QString::fromUtf8("actionauto_recalculate"));
        actionabout = new QAction(MainWindow);
        actionabout->setObjectName(QString::fromUtf8("actionabout"));
        actionabout_qt = new QAction(MainWindow);
        actionabout_qt->setObjectName(QString::fromUtf8("actionabout_qt"));
        action_4 = new QAction(MainWindow);
        action_4->setObjectName(QString::fromUtf8("action_4"));
        action_5 = new QAction(MainWindow);
        action_5->setObjectName(QString::fromUtf8("action_5"));
        action_6 = new QAction(MainWindow);
        action_6->setObjectName(QString::fromUtf8("action_6"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        mdiArea = new QMdiArea(centralwidget);
        mdiArea->setObjectName(QString::fromUtf8("mdiArea"));
        mdiArea->setGeometry(QRect(0, 0, 621, 351));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 619, 23));
        menuaas = new QMenu(menubar);
        menuaas->setObjectName(QString::fromUtf8("menuaas"));
        menuedit = new QMenu(menubar);
        menuedit->setObjectName(QString::fromUtf8("menuedit"));
        menuselect = new QMenu(menuedit);
        menuselect->setObjectName(QString::fromUtf8("menuselect"));
        menutools = new QMenu(menubar);
        menutools->setObjectName(QString::fromUtf8("menutools"));
        menuoptions = new QMenu(menubar);
        menuoptions->setObjectName(QString::fromUtf8("menuoptions"));
        menuhelp = new QMenu(menubar);
        menuhelp->setObjectName(QString::fromUtf8("menuhelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        toolBar_2 = new QToolBar(MainWindow);
        toolBar_2->setObjectName(QString::fromUtf8("toolBar_2"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar_2);
        toolBar_3 = new QToolBar(MainWindow);
        toolBar_3->setObjectName(QString::fromUtf8("toolBar_3"));
        MainWindow->addToolBar(Qt::BottomToolBarArea, toolBar_3);

        menubar->addAction(menuaas->menuAction());
        menubar->addAction(menuedit->menuAction());
        menubar->addAction(menutools->menuAction());
        menubar->addAction(menuoptions->menuAction());
        menubar->addAction(menuhelp->menuAction());
        menuaas->addAction(actionnew);
        menuaas->addAction(actionopen);
        menuaas->addAction(actionsave);
        menuaas->addAction(actionsave_as);
        menuaas->addSeparator();
        menuaas->addAction(action1population);
        menuaas->addAction(action2report_2006_sp);
        menuaas->addSeparator();
        menuaas->addAction(actionExit);
        menuedit->addAction(actioncut);
        menuedit->addAction(actioncopy);
        menuedit->addAction(actionpaste);
        menuedit->addAction(actiondelete);
        menuedit->addAction(menuselect->menuAction());
        menuedit->addSeparator();
        menuedit->addAction(actionfind);
        menuedit->addAction(actiongo_to_cell);
        menuselect->addAction(actionrow);
        menuselect->addAction(actioncolumn);
        menuselect->addAction(actionall);
        menutools->addAction(actionrecalculate);
        menutools->addAction(actionsort);
        menuoptions->addAction(actionshow_grid);
        menuoptions->addAction(actionauto_recalculate);
        menuhelp->addAction(actionabout);
        menuhelp->addAction(actionabout_qt);
        toolBar->addAction(action_4);
        toolBar->addAction(action_5);
        toolBar->addAction(action_6);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Spreadsheet", nullptr));
        actionnew->setText(QCoreApplication::translate("MainWindow", "new      CTRL+N", nullptr));
#if QT_CONFIG(shortcut)
        actionnew->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionopen->setText(QCoreApplication::translate("MainWindow", "open      CTRL+N", nullptr));
#if QT_CONFIG(shortcut)
        actionopen->setShortcut(QCoreApplication::translate("MainWindow", "Shift+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionsave->setText(QCoreApplication::translate("MainWindow", "save      CTRL+S", nullptr));
#if QT_CONFIG(shortcut)
        actionsave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionsave_as->setText(QCoreApplication::translate("MainWindow", "save as", nullptr));
        action1population->setText(QCoreApplication::translate("MainWindow", "1population", nullptr));
        action2report_2006_sp->setText(QCoreApplication::translate("MainWindow", "2report 2006.sp", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actioncut->setText(QCoreApplication::translate("MainWindow", "cut", nullptr));
        actioncopy->setText(QCoreApplication::translate("MainWindow", "copy", nullptr));
        actionpaste->setText(QCoreApplication::translate("MainWindow", "paste", nullptr));
        actiondelete->setText(QCoreApplication::translate("MainWindow", "delete", nullptr));
        actionfind->setText(QCoreApplication::translate("MainWindow", "find", nullptr));
        actiongo_to_cell->setText(QCoreApplication::translate("MainWindow", "go to cell", nullptr));
        actionrecalculate->setText(QCoreApplication::translate("MainWindow", "recalculate", nullptr));
        actionsort->setText(QCoreApplication::translate("MainWindow", "sort", nullptr));
        actionrow->setText(QCoreApplication::translate("MainWindow", "row", nullptr));
        actioncolumn->setText(QCoreApplication::translate("MainWindow", "column", nullptr));
        actionall->setText(QCoreApplication::translate("MainWindow", "all", nullptr));
        actionshow_grid->setText(QCoreApplication::translate("MainWindow", "show grid", nullptr));
        actionauto_recalculate->setText(QCoreApplication::translate("MainWindow", "auto-recalculate", nullptr));
        actionabout->setText(QCoreApplication::translate("MainWindow", "about", nullptr));
        actionabout_qt->setText(QCoreApplication::translate("MainWindow", "about qt", nullptr));
        action_4->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
#if QT_CONFIG(tooltip)
        action_4->setToolTip(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        action_4->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        action_5->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
#if QT_CONFIG(tooltip)
        action_5->setToolTip(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        action_5->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        action_6->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
#if QT_CONFIG(tooltip)
        action_6->setToolTip(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        action_6->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        menuaas->setTitle(QCoreApplication::translate("MainWindow", "file", nullptr));
        menuedit->setTitle(QCoreApplication::translate("MainWindow", "edit", nullptr));
        menuselect->setTitle(QCoreApplication::translate("MainWindow", "select", nullptr));
        menutools->setTitle(QCoreApplication::translate("MainWindow", "tools", nullptr));
        menuoptions->setTitle(QCoreApplication::translate("MainWindow", "options", nullptr));
        menuhelp->setTitle(QCoreApplication::translate("MainWindow", "help", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
        toolBar_2->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar_2", nullptr));
        toolBar_3->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar_3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
