/****************************************************************************
Copyright (c) 2022 dilipa All rights reserved.

fileName:   startinterface.cpp
    info:	System Startup interface
******************************************************************************/

#include "startinterface.h"
#include "ui_startinterface.h"

QPointer<StartInterface> StartInterface::s_startInterface = nullptr;
QMutex *StartInterface::s_mutexLocker = nullptr;

/****************************************************************************
接口描述: 创建启动界面实例
输   入: /
输   出: /
******************************************************************************/
StartInterface &StartInterface::initStartInterface()
{
    if(nullptr == s_startInterface)
    {
        QMutexLocker locker(s_mutexLocker);
        if(nullptr == s_startInterface)
        {
            s_startInterface = new StartInterface();
            s_startInterface->show();
        }
    }

    return *s_startInterface;
}

/****************************************************************************
接口描述: 鼠标按下
输   入: event---鼠标事件
输   出: /
******************************************************************************/
void StartInterface::mousePressEvent(QMouseEvent *event)
{
    m_prePoint = event->pos();
}

/****************************************************************************
接口描述: 鼠标释放
输   入: event---鼠标事件
输   出: /
******************************************************************************/
void StartInterface::mouseReleaseEvent(QMouseEvent *event)
{
    if(600 < event->pos().x() - m_prePoint.x() || -600 > event->pos().x() - m_prePoint.x()
       || 400 < event->pos().y() - m_prePoint.y() || -400 > event->pos().y() - m_prePoint.y())
    {
        m_startTimer->stop();
        emit signal_switchMainInterface(DebugPage);
    }
}

/****************************************************************************
接口描述: 启动界面构造函数
输   入: parent---父窗口
输   出: /
******************************************************************************/
StartInterface::StartInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartInterface)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);

    setSystemAddSoftVersion();

    m_startTimer = new QTimer(this);
    connect(m_startTimer, &QTimer::timeout, this, &StartInterface::slot_startTimerOut);
    m_startTimer->start(5);
}

/****************************************************************************
接口描述: 启动界面析构函数
输   入: /
输   出: /
******************************************************************************/
StartInterface::~StartInterface()
{
    delete ui;
    qdebug << "start析构";
    if(true == m_startTimer->isActive())
    {
        m_startTimer->stop();
    }

    if(nullptr != m_startTimer)
    {
        delete m_startTimer;
        m_startTimer = nullptr;
    }
}

/****************************************************************************
接口描述: 设置系统和软件版本
输   入: /
输   出: /
******************************************************************************/
void StartInterface::setSystemAddSoftVersion()
{
    QString system_version(tr("SYSTEM_VERSION   "));
    ui->system_version->setText(system_version.append("0.0"));

    QString soft_version(tr("SOFT_VERSION   "));
    ui->soft_version->setText(soft_version.append(VSERSION));
}

/****************************************************************************
接口描述: 启动界面定时器超时
输   入: /
输   出: /
******************************************************************************/
void StartInterface::slot_startTimerOut()
{
    switch(ui->startProgress->value())
    {
        case 98:
            m_startTimer->stop();
            m_startTimer->disconnect();
            emit signal_switchMainInterface(MainPage);
            break;
        default :
            ui->startProgress->setValue(ui->startProgress->value() + 1);
            break;
    }
}
