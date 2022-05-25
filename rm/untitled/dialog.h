#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:


//    void on_checkBox_2_clicked(bool checked);

//    void on_checkBox_clicked(bool checked);

//    void on_checkBox_3_clicked(bool checked);

//    void on_radioButton_clicked(bool checked);

//    void on_radioButton_2_clicked(bool checked);

//    void on_radioButton_3_clicked(bool checked);

//    void on_js_clicked();

//    void on_pushButton_clicked();

    void on_red_valueChanged(int value);

    void on_dial_valueChanged(int value);

    void on_horizontalScrollBar_valueChanged(int value);

    void on_verticalSlider_valueChanged(int value);

    void on_dec_clicked(bool checked);

    void on_oct_clicked();

    void on_bin_clicked();

    void on_hex_clicked();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
