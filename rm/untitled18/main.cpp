#include <QSlider>
#include <QSpinBox>
#include <QApplication>
#include <QHBoxLayout>\

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget w;
    w.setWindowTitle("enter your eye");

    QSpinBox *sp=new QSpinBox(&w);
    QSlider *sl=new QSlider(Qt::Horizontal,&w);
    sp->setRange(0,130);
    sl->setRange(0,130);

    QObject::connect(sl,&QSlider::valueChanged,sp,&QSpinBox::setValue);
    void(QSpinBox::*spinBoxSingal)(int)=&QSpinBox::valueChanged;
    QObject::connect(sp,spinBoxSingal,sl,&QSlider::setValue);
    sp->setValue(35);

    QHBoxLayout *l=new QHBoxLayout;
    l->addWidget(sp);
    l->addWidget(sl);
    w.setLayout(l);

    w.show();

    return a.exec();
}
