#include "qinnershadow.h"

#include <QPainter>
#include <QtMath>
#include <QDebug>
#include <QTime>
#include <QBitmap>
#include <QRegion>


QInnerShadow::QInnerShadow(QObject *parent) :QGraphicsEffect(parent)
{
    setRadius(0);
    setOffset(QPoint(3,3));
}

void QInnerShadow::draw(QPainter *p)
{
    p->setRenderHint(QPainter::Antialiasing);
    if(radius() <=0 && offset() == QPoint(0,0))
    {
        drawSource(p);
        return;
    }
    QTime start = QTime::currentTime();

    QRect rect = this->sourceBoundingRect(Qt::LogicalCoordinates).toRect();
    QPoint pixOffset ;
    QPixmap srcPix = this->sourcePixmap(Qt::LogicalCoordinates, &pixOffset);
    QImage srcImg = srcPix.toImage();
    srcImg = srcImg.convertToFormat(QImage::Format_ARGB32);

    QImage blurSrc(srcImg.size()+ QSize(2*radius(), 2*radius()), QImage::Format_ARGB32);
    blurSrc.fill(color());

    int top = radius() + offset().y();
    top = top > 0 ? top : 0;
    int bottom = blurSrc.height()-radius() + offset().y();
    bottom = bottom <= blurSrc.height() ? bottom : blurSrc.height();
    for(int y=top; y < bottom; ++y)
    {
        QRgb *line = reinterpret_cast<QRgb *>(blurSrc.scanLine(y));


        const QRgb *line2 = reinterpret_cast<const QRgb *>(srcImg.constScanLine(y-radius()-offset().y()));

        int top2 = radius() + offset().x();
        top2 = top2 > 0 ? top2 : 0;
        int bottom2 = blurSrc.width()-radius() + offset().x();
        bottom2 = bottom2 <= blurSrc.width() ? bottom2 : blurSrc.width();
        for(int x=top2; x<bottom2; ++x)
        {

            line[x] = qRgba(color().red(), color().green(),color().blue(), 255-qAlpha(line2[x-radius()-offset().x()]));

        }
    }


    QImage blured;

    if(radius() <= 0)
    {

        blured = blurSrc;

    }
    else
    {
        blured= alphaGaussBlur(blurSrc);
    }

    QRect rect2 = rect.adjusted(-radius(), -radius(), radius(), radius());

    QPixmap mid = srcPix;
    QPainter pp(&mid);
    pp.setCompositionMode(QPainter::CompositionMode_SourceOver);
    pp.drawImage(rect2,blured);
    QImage img = mid.toImage();
    img = img.convertToFormat(QImage::Format_ARGB32);
    srcImg = srcImg.convertToFormat(QImage::Format_Alpha8);
    img.setAlphaChannel(srcImg);

    p->drawImage(rect,img);

//    qDebug()<<"time use:"<<start.msecsTo(QTime::currentTime())<<m_radius;

}

QImage QInnerShadow::alphaGaussBlur(const QImage &src)
{
    QList<int> bxs = boxForGauss(m_radius, 3);
    QImage expSrc(src);
    expSrc = expSrc.convertToFormat(QImage::Format_ARGB32);

    QTime start = QTime::currentTime();
    QImage resulty(expSrc);
    resulty = resulty.convertToFormat(QImage::Format_ARGB32);

    boxBlur(expSrc, resulty, (bxs.at(0)-1)/2);
    boxBlur(expSrc, resulty, (bxs.at(1)-1)/2);
    boxBlur(expSrc, resulty, (bxs.at(2)-1)/2);
    emit timeUse(start.msecsTo(QTime::currentTime()));
    return expSrc;
}

QList<int> QInnerShadow::boxForGauss(int sigma, int n)
{
    qreal wIdeal = qSqrt((12*sigma*sigma/n)+2);
    int wl = qFloor(wIdeal);
    if(wl % 2 == 0)
        wl--;
    int wu = wl +2;

    qreal mIdeal = (12*sigma*sigma -n*wl*wl - 4*n*wl - 3*n)/(-4*wl-4);
    int m = qRound(mIdeal);

    QList<int> sizes;
    for(int i=0; i<n; ++i)
        sizes.append(i < m ? wl :wu);
    return sizes;
}

void QInnerShadow::boxBlurH(QImage &src, QImage &des, int radius)
{
    int h = des.height();
    int w = des.width();
    boxBlurH(src.bits(), des.bits(), w, h, 4, radius);

//    qreal iarr = 1.0 / (radius+radius+1.0);

//    for(int y=0; y<h; ++y)
//    {
//        QRgb *srcline = (QRgb *) src.constScanLine(y);
//        QRgb *desline = (QRgb *) des.scanLine(y);
//        int val = 0;
//        for(int x=0; x<radius; ++x)
//        {
//            val += qAlpha(srcline[x]);
//        }
//        val += qAlpha(srcline[0])*(radius+1);
//        for(int x=0; x<=radius; ++x)
//        {
//            val += qAlpha(srcline[x+radius])-qAlpha(srcline[0]);
//            desline[x] = qRgba(0,0,0,val*iarr);
//        }

//        for(int x=radius+1; x<w-radius; ++x)
//        {
//            val += (qAlpha(srcline[x+radius]) - qAlpha(srcline[x-1-radius]));
//            desline[x] = qRgba(0,0,0,val*iarr);
//        }
//        for(int x=w-radius; x<w; ++x)
//        {
//            val += qAlpha(srcline[w]) - qAlpha(srcline[x-1-radius]);
//            desline[x] = qRgba(0,0,0,val*iarr);
//        }

//    }
}

void QInnerShadow::boxBlur(QImage &src, QImage &des, int radius)
{
    int h = des.height();
    int w = des.width();
    //默认pixel保存为32位， ARGB格式
    boxBlurH(src.bits(), des.bits(), w, h, 4, radius);
    boxBlurV(des.bits(), src.bits(), w, h, 4, radius);
    //notice that the result img is "src"

//    boxBlurH(src, des, radius);
//    QTransform mtx;
//    mtx.rotate(90);
//    src = des.transformed(mtx);
//    boxBlurH(src, des, radius);
//    mtx.rotate(-90);
//    des = des.transformed(mtx);
}

void QInnerShadow::boxBlurH(uchar *src, uchar* des, int w, int h, int format, int r)
{
    qreal iarr = 1.0 / (r+r+1.0);
    for (int i = 0; i < h; i++) {

            int ti = i*w*format;// middle index
            int li = ti;// left index
            int ri = ti + r*format;// right index
            // in intel cpu (Little Endian)  the pixcel data save as BGRA
            // so the alpha value is at index+3
            uchar fv = src[ti + 3];// first value
            uchar lv = src[ti + (w - 1)*format + 3];// last value
            uint val = fv*(r + 1);// (r+1)/(2r+1)
            for (int j = 0; j < r*format; j += format)
            {
                val += src[ti + j +3];
            }
            for (int j = 0; j <= r*format; j += format)
            {
                val += src[ri+3] - fv;

                des[ti+3] = val*iarr;

                ri += format;
                ti += format;
            }
            for (int j = (r + 1)*format; j < (w - r)*format; j += format)
            {
                val += src[ri+3] - src[li+3];

                des[ti+3] = val*iarr;

                ri += format;
                li += format;
                ti += format;
            }
            for (int j = (w - r)*format; j < w*format; j += format)
            {
                val += lv - src[li+3];

                des[ti+3] = val*iarr;
                li += format;
                ti += format;
            }
    }
}

void QInnerShadow::boxBlurV(uchar *src, uchar *des, int w, int h, int format, int r)
{
    float iarr = 1.0f / (r + r + 1.0f);
    for (int i = 0; i < w*format; i += format) {
        int ti = i;
        int li = ti;
        int ri = ti + r*w*format;
        uchar fv = src[ti + 3];
        uchar lv = src[ti + w*(h - 1)*format + 3];
        uint val = (r + 1)*fv;
        for (int j = 0; j < r; j++)
        {
            val += src[ti + j*w*format + 3];
        }
        for (int j = 0; j <= r; j++)
        {
            val += src[ri +3] - fv;

            des[ti + 3] = val*iarr;

            ri += w*format;
            ti += w*format;
        }
        for (int j = r + 1; j < h - r; j++)
        {
            val += src[ri+3] - src[li+3];

            des[ti+3] = val*iarr;

            li += w*format;
            ri += w*format;
            ti += w*format;
        }
        for (int j = h - r; j < h; j++)
        {
            val += lv - src[li+3];

            des[ti+3] = val*iarr;

            li += w*format;
            ti += w*format;
        }
    }
}

int QInnerShadow::radius() const
{
    return m_radius;
}

void QInnerShadow::setRadius(int newAlphaGaussBlurRadius)
{
    if (m_radius == newAlphaGaussBlurRadius)
        return;
    m_radius = newAlphaGaussBlurRadius;

    m_alphaGaussBlurKernel.clear();
    const int length = m_radius*2+1; //核长度
    const int mid = m_radius+1; //gauss中心位置
    const double sigma = m_radius / 3.0; //sigma

    double sigmap = 1/(qSqrt(2*M_PI)*sigma);
    double sigma2 = 2*sigma*sigma;
    for(int i=0; i<length; ++i)
    {
        m_alphaGaussBlurKernel.append(sigmap * qExp(-qPow((i-mid),2)/ sigma2));
    }
    update();

    emit radiusChanged();
}

const QColor &QInnerShadow::color() const
{
    return m_color;
}

void QInnerShadow::setColor(const QColor &newColor)
{
    if (m_color == newColor)
        return;
    m_color = newColor;
    emit colorChanged();
}

QPoint QInnerShadow::offset() const
{
    return m_offset;
}

void QInnerShadow::setOffset(QPoint newOffset)
{
    if (m_offset == newOffset)
        return;
    m_offset = newOffset;
    emit offsetChanged();
}
