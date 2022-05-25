#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sqlthreadfirst.h"
#include "sqlthreadsecond.h"
#include "QtSql/QSqlTableModel"
#include "QTimer"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void TimeOut();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    SqlthreadFirst *mySqlFirst;
    SqlthreadSecond *mySqlSecond;
    QSqlTableModel *myTableModel;
    QTimer *myTick;
};

#endif // MAINWINDOW_H
