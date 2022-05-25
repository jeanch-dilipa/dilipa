#ifndef DIALOGS_H
#define DIALOGS_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class dialogs; }
QT_END_NAMESPACE

class dialogs : public QWidget
{
    Q_OBJECT

public:
    dialogs(QWidget *parent = nullptr);
    ~dialogs();

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
//    void dropEvent(QDropEvent *event);
//    void dragEnterEvent(QDragEnterEvent *event);

private slots:
    void on_close_clicked();
    void on_clear_clicked();
    void on_openfile_clicked();
    void on_openfiles_clicked();
    void on_savefile_clicked();
    void on_existdirectory_clicked();
    void on_openurlfile_clicked();
    void on_getcolor_clicked();

    void on_showtext_customContextMenuRequested(const QPoint &pos);

    void on_getfont_clicked();

    void on_gettext_clicked();

    void on_getint_clicked();

    void on_getdouble_clicked();

    void on_getitem_clicked();

    void on_getmultitext_clicked();

    void on_information_clicked();

    void on_question_clicked();

    void on_warning_clicked();

    void on_critical_clicked();

    void on_about_clicked();

    void on_aboutqt_clicked();

    void on_uidialog_clicked();

private:
    Ui::dialogs *ui;

    bool ismouse=false;
    bool isdrag;

    QPoint point;
};
#endif // DIALOGS_H

