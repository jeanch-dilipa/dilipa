#ifndef MDI_H
#define MDI_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MDI; }
QT_END_NAMESPACE

class MDI : public QMainWindow
{
    Q_OBJECT

public:
    MDI(QWidget *parent = nullptr);
    ~MDI();

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public slots:
    void slot_new();
    void slot_open();
//    void slot_close();
    void slot_exit();
//    void slot_cut();
//    void slot_copy();
//    void slot_tag();


private:
    Ui::MDI *ui;

    QPoint mousep;
    bool isPress;
};
#endif // MDI_H
