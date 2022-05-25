#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>

class subwidget : public QWidget
{
    Q_OBJECT
public:
    explicit subwidget(QWidget *parent = nullptr);

public slots:
    void slot_emit();

signals:
    void signal_main();

};

#endif // SUBWIDGET_H
