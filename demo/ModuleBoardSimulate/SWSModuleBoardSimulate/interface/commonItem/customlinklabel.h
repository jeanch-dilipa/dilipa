#ifndef CUSTOMLINKLABEL_H
#define CUSTOMLINKLABEL_H

/*自定义Label控件，实现超链接效果 — design by Chris Chou*/

#include <QLabel>
#include <QMouseEvent>

class CustomLinkLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLinkLabel(QWidget *parent = nullptr);

    void setEnableColor(bool enable, QColor color);

    //以下函数均为重写
    void mouseReleaseEvent(QMouseEvent *event);
    void setEnabled(bool enable);
    void setDisabled(bool disable);

signals:
    void clicked();

private:
    void setTextColor(QColor color);

    QColor m_enableColor = QColor(0, 118, 201);
    QColor m_disableColor = QColor(Qt::gray);
};

#endif // CUSTOMLINKLABEL_H
