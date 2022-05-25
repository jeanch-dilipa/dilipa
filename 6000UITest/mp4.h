#ifndef MP4_H
#define MP4_H

#include <QWidget>

namespace Ui {
class Mp4;
}

class Mp4 : public QWidget
{
    Q_OBJECT

public:
    explicit Mp4(QWidget *parent = nullptr);
    ~Mp4();

private:
    Ui::Mp4 *ui;
};

#endif // MP4_H
