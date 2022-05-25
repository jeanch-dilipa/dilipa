#include "customswitchbutton.h"

CustomSwitchButton::CustomSwitchButton(QWidget *parent) : QWidget(parent)
{
    this->resize(60, 30);

    m_pannelBtn = new QPushButton(this);
    m_pannelBtn->resize(this->size());
    m_pannelBtn->setCheckable(true);

    m_handleBtn = new QPushButton(this);
    m_handleBtn->resize(m_pannelBtn->height(), m_pannelBtn->height());
    m_handleBtn->move(0, 0);

    m_animation = new QPropertyAnimation(m_handleBtn, "geometry", this);
    m_animation->setEasingCurve(QEasingCurve::OutCubic);
    m_animation->setDuration(500);

    connect(m_pannelBtn, &QPushButton::toggled, this, &CustomSwitchButton::slotBtnToggled);
    connect(m_handleBtn, &QPushButton::clicked, this, [this](){
        m_pannelBtn->setChecked(!m_pannelBtn->isChecked());
    });
    connect(m_pannelBtn, &QPushButton::toggled, this, &CustomSwitchButton::toggled);

    setCheckedStyleSheet(m_pannelBtn->isChecked());
}

CustomSwitchButton::~CustomSwitchButton()
{
}

void CustomSwitchButton::setChecked(bool checked)
{
    m_pannelBtn->setChecked(checked);
}

bool CustomSwitchButton::isChecked()
{
    return m_pannelBtn->isChecked();
}

void CustomSwitchButton::slotBtnToggled(bool isChecked)
{
    if(isChecked)
    {
        m_animation->setStartValue(m_handleBtn->geometry());
        m_animation->setEndValue(QRect(m_pannelBtn->width() - m_handleBtn->width(), 0, m_handleBtn->width(), m_handleBtn->height()));
        m_animation->start();
    }
    else
    {
        m_animation->setStartValue(m_handleBtn->geometry());
        m_animation->setEndValue(QRect(0, 0, m_handleBtn->width(), m_handleBtn->height()));
        m_animation->start();
    }
    setCheckedStyleSheet(isChecked);
}

void CustomSwitchButton::setCheckedStyleSheet(bool isChecked)
{
    if(isChecked)
    {
        m_pannelBtn->setStyleSheet("QPushButton{border: 2px solid rgb(77, 166, 252); border-radius: 15px;"
                                   "background: rgba(191, 239, 255, 180);}");
        m_handleBtn->setStyleSheet("QPushButton{border: none; border-radius: 15px; background: rgb(77, 166, 252);}");
    }
    else
    {
        m_pannelBtn->setStyleSheet("QPushButton{border: 2px solid rgb(180, 180, 180); border-radius: 15px;"
                                   "background: rgba(220, 220, 220, 80);}");
        m_handleBtn->setStyleSheet("QPushButton{border: none; border-radius: 15px; background: rgb(180, 180, 180);}");
    }
}
