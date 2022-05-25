#ifndef TEXTURETEST_H
#define TEXTURETEST_H

#include <QWidget>

namespace Ui {
class TextureTest;
}

class TextureTest : public QWidget
{
    Q_OBJECT

public:
    explicit TextureTest(QWidget *parent = 0);
    ~TextureTest();

private:
    Ui::TextureTest *ui;
};

#endif // TEXTURETEST_H
