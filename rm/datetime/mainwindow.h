#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_show_clicked();

    void on_set_clicked();

    void on_calendarWidget_selectionChanged();

    void  on_timer_timeout();

    void on_start_clicked();

    void on_stop_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *t1;
    QTime t2;
};
#endif // MAINWINDOW_H
