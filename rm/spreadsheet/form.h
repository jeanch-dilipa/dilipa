#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    void defaultfile(QString filename);
    void cut();
    void copy();
    void paste();
    void open(QString filename);

private:
    Ui::Form *ui;
};

#endif // FORM_H
