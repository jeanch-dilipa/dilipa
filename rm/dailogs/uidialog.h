#ifndef UIDIALOG_H
#define UIDIALOG_H

#include <QDialog>

namespace Ui {
class uiDialog;
}

class uiDialog : public QDialog
{
    Q_OBJECT

public:
    explicit uiDialog(QWidget *parent = nullptr);
    ~uiDialog();

    QString str;

private slots:
    void on_cancel_clicked();

    void on_ok_clicked();

private:
    Ui::uiDialog *ui;
};

#endif // UIDIALOG_H
