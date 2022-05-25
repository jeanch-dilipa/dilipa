#ifndef HETEROIDEUS_H
#define HETEROIDEUS_H

#include <QWidget>
#include <QPainter>
#include <QBitmap>
#include <QPaintEvent>

namespace Ui {
class Heteroideus;
}

class Heteroideus : public QWidget
{
    Q_OBJECT

public:
    explicit Heteroideus(QWidget *parent = nullptr);
    ~Heteroideus();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::Heteroideus *ui;
    QImage           image;
};

#endif // HETEROIDEUS_H
