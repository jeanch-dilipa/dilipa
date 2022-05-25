#ifndef POLYGON_H
#define POLYGON_H

#include <QMainWindow>
#include <QPaintEvent>

class Polygon : public QMainWindow
{
    Q_OBJECT

public:
    Polygon(QWidget *parent = nullptr);
    ~Polygon();
    void paintEvent(QPaintEvent *event);
};
#endif // POLYGON_H
