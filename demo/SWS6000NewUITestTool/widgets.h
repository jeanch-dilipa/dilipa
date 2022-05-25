#ifndef WIDGETS_H
#define WIDGETS_H

#include <QWidget>

namespace Ui {
class Widgets;
}

class Widgets : public QWidget
{
    Q_OBJECT

public:
    explicit Widgets(QWidget *parent = 0);
    ~Widgets();

private slots:
    void on_toolButton_clicked();

private:
    Ui::Widgets *ui;
};

#endif // WIDGETS_H
