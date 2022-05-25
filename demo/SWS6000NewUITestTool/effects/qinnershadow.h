/*******************************
 *
 *  InnerShadow by custom QGraphicsEffect
 *
 * ****************************/

#ifndef QINNERSHADOW_H
#define QINNERSHADOW_H

#include <QGraphicsEffect>

class QInnerShadow : public QGraphicsEffect
{
    Q_OBJECT
    Q_PROPERTY(int radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QPoint offset READ offset WRITE setOffset NOTIFY offsetChanged)

public:
    explicit QInnerShadow(QObject *parent = nullptr);

    int radius() const;
    void setRadius(int newAlphaGaussBlurRadius);

    const QColor &color() const;
    void setColor(const QColor &newColor);

    QPoint offset() const;
    void setOffset(QPoint newOffset);

signals:
    void radiusChanged();
    void timeUse(int ms);
    void colorChanged();

    void offsetChanged();

protected:
    void draw(QPainter *painter) override;

private:
    QImage alphaGaussBlur(const QImage &src); //对给定图像的alpha通道进行高斯模糊

private:
    int m_radius; //用于alpha通道高斯模糊的模糊半径
    QList<double> m_alphaGaussBlurKernel; //用于alpha通道高斯模糊的卷积核

    QList<int> boxForGauss(int sigma, int n);
    void boxBlurH(QImage &src, QImage &des, int radius);
    void boxBlur(QImage &src, QImage &des, int radius);
    void boxBlurH(uchar *src, uchar* des, int width, int height, int format, int radius);
    void boxBlurV(uchar *src, uchar* des, int width, int height, int format, int radius);
    QColor m_color;
    QPoint m_offset;
};

#endif // QINNERSHADOW_H
