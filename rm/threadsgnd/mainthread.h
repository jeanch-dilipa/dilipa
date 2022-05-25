#ifndef MAINTHREAD_H
#define MAINTHREAD_H

#include <QDialog>
#include "readwritethread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainthread; }
QT_END_NAMESPACE

class mainthread : public QDialog
{
    Q_OBJECT

public:
    mainthread(QWidget *parent = nullptr);
    ~mainthread();

private slots:
    void on_start_clicked();

    void on_stop_clicked();
    void showtext(int *data,int size,int num);

private:
    Ui::mainthread *ui;
    readthread readthread;
    writethread writethread;
};
#endif // MAINTHREAD_H
