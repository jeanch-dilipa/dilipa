/********************************************************************************
** Form generated from reading UI file 'dialogs.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGS_H
#define UI_DIALOGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dialogs
{
public:
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QPlainTextEdit *showtext;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QPushButton *getfont;
    QPushButton *getitem;
    QPushButton *openurlfile;
    QPushButton *warning;
    QPushButton *savefile;
    QPushButton *getint;
    QPushButton *information;
    QPushButton *about;
    QPushButton *openfile;
    QPushButton *uidialog;
    QGridLayout *gridLayout_2;
    QPushButton *getmultitext;
    QPushButton *aboutqt;
    QPushButton *getdouble;
    QPushButton *existdirectory;
    QPushButton *critical;
    QPushButton *getcolor;
    QPushButton *question;
    QPushButton *openfiles;
    QPushButton *gettext;
    QPushButton *pushButton_2;
    QVBoxLayout *verticalLayout;
    QPushButton *clear;
    QPushButton *close;

    void setupUi(QWidget *dialogs)
    {
        if (dialogs->objectName().isEmpty())
            dialogs->setObjectName(QString::fromUtf8("dialogs"));
        dialogs->resize(714, 426);
        dialogs->setMouseTracking(true);
        gridLayout_4 = new QGridLayout(dialogs);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        showtext = new QPlainTextEdit(dialogs);
        showtext->setObjectName(QString::fromUtf8("showtext"));

        gridLayout_3->addWidget(showtext, 0, 3, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        getfont = new QPushButton(dialogs);
        getfont->setObjectName(QString::fromUtf8("getfont"));

        gridLayout->addWidget(getfont, 3, 0, 1, 1);

        getitem = new QPushButton(dialogs);
        getitem->setObjectName(QString::fromUtf8("getitem"));

        gridLayout->addWidget(getitem, 5, 0, 1, 1);

        openurlfile = new QPushButton(dialogs);
        openurlfile->setObjectName(QString::fromUtf8("openurlfile"));

        gridLayout->addWidget(openurlfile, 2, 0, 1, 1);

        warning = new QPushButton(dialogs);
        warning->setObjectName(QString::fromUtf8("warning"));

        gridLayout->addWidget(warning, 7, 0, 1, 1);

        savefile = new QPushButton(dialogs);
        savefile->setObjectName(QString::fromUtf8("savefile"));

        gridLayout->addWidget(savefile, 1, 0, 1, 1);

        getint = new QPushButton(dialogs);
        getint->setObjectName(QString::fromUtf8("getint"));

        gridLayout->addWidget(getint, 4, 0, 1, 1);

        information = new QPushButton(dialogs);
        information->setObjectName(QString::fromUtf8("information"));

        gridLayout->addWidget(information, 6, 0, 1, 1);

        about = new QPushButton(dialogs);
        about->setObjectName(QString::fromUtf8("about"));

        gridLayout->addWidget(about, 8, 0, 1, 1);

        openfile = new QPushButton(dialogs);
        openfile->setObjectName(QString::fromUtf8("openfile"));

        gridLayout->addWidget(openfile, 0, 0, 1, 1);

        uidialog = new QPushButton(dialogs);
        uidialog->setObjectName(QString::fromUtf8("uidialog"));

        gridLayout->addWidget(uidialog, 9, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        getmultitext = new QPushButton(dialogs);
        getmultitext->setObjectName(QString::fromUtf8("getmultitext"));

        gridLayout_2->addWidget(getmultitext, 5, 0, 1, 1);

        aboutqt = new QPushButton(dialogs);
        aboutqt->setObjectName(QString::fromUtf8("aboutqt"));

        gridLayout_2->addWidget(aboutqt, 8, 0, 1, 1);

        getdouble = new QPushButton(dialogs);
        getdouble->setObjectName(QString::fromUtf8("getdouble"));

        gridLayout_2->addWidget(getdouble, 4, 0, 1, 1);

        existdirectory = new QPushButton(dialogs);
        existdirectory->setObjectName(QString::fromUtf8("existdirectory"));

        gridLayout_2->addWidget(existdirectory, 1, 0, 1, 1);

        critical = new QPushButton(dialogs);
        critical->setObjectName(QString::fromUtf8("critical"));

        gridLayout_2->addWidget(critical, 7, 0, 1, 1);

        getcolor = new QPushButton(dialogs);
        getcolor->setObjectName(QString::fromUtf8("getcolor"));

        gridLayout_2->addWidget(getcolor, 2, 0, 1, 1);

        question = new QPushButton(dialogs);
        question->setObjectName(QString::fromUtf8("question"));

        gridLayout_2->addWidget(question, 6, 0, 1, 1);

        openfiles = new QPushButton(dialogs);
        openfiles->setObjectName(QString::fromUtf8("openfiles"));

        gridLayout_2->addWidget(openfiles, 0, 0, 1, 1);

        gettext = new QPushButton(dialogs);
        gettext->setObjectName(QString::fromUtf8("gettext"));

        gridLayout_2->addWidget(gettext, 3, 0, 1, 1);

        pushButton_2 = new QPushButton(dialogs);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout_2->addWidget(pushButton_2, 9, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout_2);


        gridLayout_3->addLayout(horizontalLayout, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        clear = new QPushButton(dialogs);
        clear->setObjectName(QString::fromUtf8("clear"));
        clear->setAutoDefault(false);

        verticalLayout->addWidget(clear);

        close = new QPushButton(dialogs);
        close->setObjectName(QString::fromUtf8("close"));

        verticalLayout->addWidget(close);


        gridLayout_3->addLayout(verticalLayout, 0, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);


        retranslateUi(dialogs);

        QMetaObject::connectSlotsByName(dialogs);
    } // setupUi

    void retranslateUi(QWidget *dialogs)
    {
        dialogs->setWindowTitle(QApplication::translate("dialogs", "dialogs", nullptr));
        getfont->setText(QApplication::translate("dialogs", "getfont", nullptr));
        getitem->setText(QApplication::translate("dialogs", "getitem", nullptr));
        openurlfile->setText(QApplication::translate("dialogs", "openurlfile", nullptr));
        warning->setText(QApplication::translate("dialogs", "warning", nullptr));
        savefile->setText(QApplication::translate("dialogs", "savefile", nullptr));
        getint->setText(QApplication::translate("dialogs", "getint", nullptr));
        information->setText(QApplication::translate("dialogs", "information", nullptr));
        about->setText(QApplication::translate("dialogs", "about", nullptr));
        openfile->setText(QApplication::translate("dialogs", "openfile", nullptr));
        uidialog->setText(QApplication::translate("dialogs", "uidialog", nullptr));
        getmultitext->setText(QApplication::translate("dialogs", "getmultitext", nullptr));
        aboutqt->setText(QApplication::translate("dialogs", "aboutqt", nullptr));
        getdouble->setText(QApplication::translate("dialogs", "getdouble", nullptr));
        existdirectory->setText(QApplication::translate("dialogs", "existdirectory", nullptr));
        critical->setText(QApplication::translate("dialogs", "critical", nullptr));
        getcolor->setText(QApplication::translate("dialogs", "getcolor", nullptr));
        question->setText(QApplication::translate("dialogs", "question", nullptr));
        openfiles->setText(QApplication::translate("dialogs", "openfiles", nullptr));
        gettext->setText(QApplication::translate("dialogs", "gettext", nullptr));
        pushButton_2->setText(QApplication::translate("dialogs", "PushButton", nullptr));
        clear->setText(QApplication::translate("dialogs", "clear", nullptr));
        close->setText(QApplication::translate("dialogs", "close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dialogs: public Ui_dialogs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGS_H
