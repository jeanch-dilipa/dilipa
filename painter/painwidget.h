#ifndef PAINWIDGET_H
#define PAINWIDGET_H

#include <QWidget>
#include <QPoint>

QT_BEGIN_NAMESPACE
namespace Ui { class painwidget; }
QT_END_NAMESPACE

class painwidget : public QWidget
{
    Q_OBJECT

public:
    painwidget(QWidget *parent = nullptr);
    ~painwidget();
    void paintEvent(QPaintEvent *event);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);


private:
    Ui::painwidget *ui;
    bool isleftmousepress=false;
    QPoint p;
};
#endif // PAINWIDGET_H
