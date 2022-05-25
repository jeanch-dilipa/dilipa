#ifndef TIMEROPTION_H
#define TIMEROPTION_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QDebug>



class timeroption : public QWidget
{
    Q_OBJECT
public:
    explicit timeroption(QWidget *parent = nullptr);
    void kk();

signals:

};

#endif // TIMEROPTION_H
