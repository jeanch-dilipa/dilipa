/********************************************************************************
** Form generated from reading UI file 'tablewiget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLEWIGET_H
#define UI_TABLEWIGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QColumnView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QUndoView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tableWiget
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QTreeView *treeView;
    QListView *listView;
    QColumnView *columnView;
    QTableView *tableView;
    QUndoView *undoView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *tableWiget)
    {
        if (tableWiget->objectName().isEmpty())
            tableWiget->setObjectName(QString::fromUtf8("tableWiget"));
        tableWiget->resize(824, 459);
        centralwidget = new QWidget(tableWiget);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        gridLayout->addWidget(treeView, 0, 0, 2, 1);

        listView = new QListView(centralwidget);
        listView->setObjectName(QString::fromUtf8("listView"));

        gridLayout->addWidget(listView, 0, 1, 1, 1);

        columnView = new QColumnView(centralwidget);
        columnView->setObjectName(QString::fromUtf8("columnView"));

        gridLayout->addWidget(columnView, 0, 2, 1, 1);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout->addWidget(tableView, 1, 1, 1, 1);

        undoView = new QUndoView(centralwidget);
        undoView->setObjectName(QString::fromUtf8("undoView"));

        gridLayout->addWidget(undoView, 1, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        tableWiget->setCentralWidget(centralwidget);
        menubar = new QMenuBar(tableWiget);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 824, 23));
        tableWiget->setMenuBar(menubar);
        statusbar = new QStatusBar(tableWiget);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        tableWiget->setStatusBar(statusbar);

        retranslateUi(tableWiget);

        QMetaObject::connectSlotsByName(tableWiget);
    } // setupUi

    void retranslateUi(QMainWindow *tableWiget)
    {
        tableWiget->setWindowTitle(QApplication::translate("tableWiget", "tableWiget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tableWiget: public Ui_tableWiget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLEWIGET_H
