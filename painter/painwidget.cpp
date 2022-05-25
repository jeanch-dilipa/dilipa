#include "painwidget.h"
#include "ui_painwidget.h"

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QRect>
#include <QMouseEvent>

painwidget::painwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::painwidget)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    setWindowOpacity(0.5);
    setWindowFlag(Qt::FramelessWindowHint);
}

painwidget::~painwidget()
{
    delete ui;
}

void painwidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter pain(this);    //记得添加绘图设备
    pain.setRenderHint(QPainter::Antialiasing);
    pain.setRenderHint(QPainter::TextAntialiasing);

    QRect rec(0,0,this->width(),this->height());

    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);   //端点样式
    pen.setJoinStyle(Qt::BevelJoin);    //连接点样式
    pain.setPen(pen);

    QBrush brush;
    brush.setColor(Qt::red);            //  不填充             单一填充            水平填充            垂直线填充           线性渐变                    圆锥渐变                        辐射渐变                        材质填充
    brush.setStyle(Qt::SolidPattern);   //    Qt::NoBrush    Qt::SolidPattern    Qt::HorPattern    Qt::VerPattern   Qt::LinearGradientPattern    Qt::ConicalGradientPattern    Qt::RadialGradientPattern    Qt::TexturePattern

    QRadialGradient rg(this->width()/2,this->height()/2,this->width()/8,this->width()/4,this->height()/4);
    rg.setColorAt(0,Qt::green);
    rg.setColorAt(1,Qt::blue);
    rg.setSpread(QGradient::ReflectSpread);
//    brush.setTexture(QPixmap pm);   //图片做画刷pixmap
//    brush.setTextureImage(QImage im);   //图片做画刷image
//    pain.setBrush(brush);
    pain.setBrush(rg);

//    pain.translate(100,200);    //坐标平移
//    pain.rotate(90);    //坐标旋转
//    pain.scale(10,0.5); //缩放
//    pain.save();    //保存坐标
//    pain.restore();     //回滚
//    pain.resetTransform();      //重置

    pain.drawRect(rec);
    pain.translate(this->width()/2,this->height()/2);
    QLinearGradient lg(0,0,this->width(),this->height());
    lg.setColorAt(0,Qt::yellow);
    lg.setColorAt(1,Qt::red);
    lg.setSpread(QGradient::PadSpread);
    pain.setBrush(lg);
//    pain.setCompositionMode(QPainter::RasterOp_NotSourceXorDestination);      //复合模式
    pain.setCompositionMode(QPainter::RasterOp_SourceXorDestination);


    for(int i=1;i<40;i++)
    {
        pain.drawEllipse(QPoint(this->width()/4,this->height()/4),this->width()/10,this->height()/6);
        pain.rotate(10);
    }
}

void painwidget::mouseMoveEvent(QMouseEvent *event)
{
    if(isleftmousepress)
        this->move(event->pos()-p+this->pos());
}

void painwidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
        isleftmousepress=true;
    p=event->pos();
}

void painwidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    isleftmousepress=false;
}

void painwidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    this->close();
}

