/********************************************************************************
** Form generated from reading UI file 'uidialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UIDIALOG_H
#define UI_UIDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_uiDialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *ok;
    QPushButton *cancel;
    QLineEdit *lineEdit;

    void setupUi(QDialog *uiDialog)
    {
        if (uiDialog->objectName().isEmpty())
            uiDialog->setObjectName(QString::fromUtf8("uiDialog"));
        uiDialog->resize(400, 76);
        gridLayout = new QGridLayout(uiDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        ok = new QPushButton(uiDialog);
        ok->setObjectName(QString::fromUtf8("ok"));

        gridLayout->addWidget(ok, 1, 0, 1, 1);

        cancel = new QPushButton(uiDialog);
        cancel->setObjectName(QString::fromUtf8("cancel"));

        gridLayout->addWidget(cancel, 1, 1, 1, 1);

        lineEdit = new QLineEdit(uiDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 0, 1, 2);


        retranslateUi(uiDialog);
        QObject::connect(cancel, SIGNAL(clicked()), uiDialog, SLOT(exec()));
        QObject::connect(ok, SIGNAL(clicked()), uiDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(uiDialog);
    } // setupUi

    void retranslateUi(QDialog *uiDialog)
    {
        uiDialog->setWindowTitle(QApplication::translate("uiDialog", "Dialog", nullptr));
        ok->setText(QApplication::translate("uiDialog", "ok", nullptr));
        cancel->setText(QApplication::translate("uiDialog", "cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class uiDialog: public Ui_uiDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UIDIALOG_H
