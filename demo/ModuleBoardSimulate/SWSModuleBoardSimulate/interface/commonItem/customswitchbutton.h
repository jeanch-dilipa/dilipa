#ifndef CUSTOMSWITCHBUTTON_H
#define CUSTOMSWITCHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QPropertyAnimation>

class CustomSwitchButton : public QWidget
{
    Q_OBJECT

public:
    explicit CustomSwitchButton(QWidget *parent = 0);
    ~CustomSwitchButton();
    void setChecked(bool checked);
    bool isChecked();

signals:
    void toggled(bool isChecked);

private slots:
    void slotBtnToggled(bool isChecked);
    void setCheckedStyleSheet(bool isChecked);

private:
    QPushButton *m_pannelBtn;
    QPushButton *m_handleBtn;
    QPropertyAnimation *m_animation;
};

#endif // CUSTOMSWITCHBUTTON_H
