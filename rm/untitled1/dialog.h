#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    int row();
    int column();
    void setrowcolumn(int row,int column);
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
