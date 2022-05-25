#include "texturetest.h"
#include "ui_texturetest.h"
#include "widgets.h"

TextureTest::TextureTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextureTest)
{
    ui->setupUi(this);

}

TextureTest::~TextureTest()
{
    delete ui;
}
