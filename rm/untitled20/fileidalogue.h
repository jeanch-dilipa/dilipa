#ifndef FILEIDALOGUE_H
#define FILEIDALOGUE_H

#include <QWidget>

class fileidalogue : public QWidget
{
    Q_OBJECT

public:
    fileidalogue(QWidget *parent = nullptr);
    ~fileidalogue();

    void read(QString str);
    void write(QString str);
};
#endif // FILEIDALOGUE_H
