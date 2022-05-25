#include "customlinklabel.h"

CustomLinkLabel::CustomLinkLabel(QWidget *parent) : QLabel(parent)
{
    //设置手型
    this->setCursor(Qt::PointingHandCursor);
    this->setAttribute(Qt::WA_TransparentForMouseEvents, false);

    //设置下划线
    QFont font = this->font();
    font.setUnderline(true);
    this->setFont(font);

    //设置字体颜色
    setTextColor(m_enableColor);
}

void CustomLinkLabel::setEnableColor(bool enable, QColor color)
{
    if(enable)
    {
        m_enableColor = color;
    }
    else
    {
        m_disableColor = color;
    }

    this->setEnabled(this->isEnabled()); //重新设置使能（更新颜色）
}

void CustomLinkLabel::setTextColor(QColor color)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::WindowText, QColor(color));
    this->setPalette(palette);
}

void CustomLinkLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
    }

    QLabel::mouseReleaseEvent(event);
}

void CustomLinkLabel::setEnabled(bool enable)
{
    if(enable)
    {
        this->setCursor(Qt::PointingHandCursor);
        setTextColor(m_enableColor);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
        setTextColor(m_disableColor);
    }

    QLabel::setEnabled(enable);
}

void CustomLinkLabel::setDisabled(bool disable)
{
    setEnabled(!disable);
}
