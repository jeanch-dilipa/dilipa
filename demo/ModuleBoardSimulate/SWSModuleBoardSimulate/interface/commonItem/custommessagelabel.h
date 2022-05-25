#ifndef CUSTOMMESSAGELABEL_H
#define CUSTOMMESSAGELABEL_H

#include <QLabel>
#include <QTimer>

class CustomMessageLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomMessageLabel(QWidget *parent = 0) : QLabel(parent), m_timer(new QTimer(this))
    {
        m_timer->setSingleShot(true);
        m_timer->setInterval(5000);
        connect(m_timer, &QTimer::timeout, this, [this](){
            this->clear();
        });
    }

    void setRelevanceLabel(CustomMessageLabel *label) //设置关联Lalebl
    {
        if(label != this)
        {
            m_relevanceLabel = label;
        }
    }

    void showMessage(const QString &msg, bool autoHide = true)
    {
        this->setText(msg);
        autoHide ? m_timer->start() : m_timer->stop();
        if(m_relevanceLabel)
        {
            m_relevanceLabel->showMessage(msg, autoHide);
        }
    }
    void showErrorMessage(const QString &msg, bool autoHide = true)
    {
        this->setText("<font color='red'>" + msg + "</font>");
        autoHide ? m_timer->start() : m_timer->stop();
        if(m_relevanceLabel)
        {
            m_relevanceLabel->showErrorMessage(msg, autoHide);
        }
    }
    void showSuccessMessage(const QString &msg, bool autoHide = true)
    {
        this->setText("<font color='green'>" + msg + "</font>");
        autoHide ? m_timer->start() : m_timer->stop();
        if(m_relevanceLabel)
        {
            m_relevanceLabel->showSuccessMessage(msg, autoHide);
        }
    }

private:
    QTimer *m_timer;
    CustomMessageLabel *m_relevanceLabel = NULL;
};

#endif // CUSTOMMESSAGELABEL_H
