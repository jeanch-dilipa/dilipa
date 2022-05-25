#ifndef MAINQTHREAD_H
#define MAINQTHREAD_H

#include <QWidget>
#include "dice.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainQthread; }
QT_END_NAMESPACE

class MainQthread : public QWidget
{
    Q_OBJECT

public:
    MainQthread(QWidget *parent = nullptr);
    ~MainQthread();

private slots:
    void on_startthread_clicked();

    void on_stopthread_clicked();

    void on_start_clicked();

    void on_exit_clicked();

    void on_pause_clicked();

    void on_clear_clicked();
    void newdicevalue(int dicecount,int diceview,QString Qthreadid);

private:
    Ui::MainQthread *ui;
    dice diceQthread1;
    dice diceQthread2;
    bool ispause=false;

};
#endif // MAINQTHREAD_H
