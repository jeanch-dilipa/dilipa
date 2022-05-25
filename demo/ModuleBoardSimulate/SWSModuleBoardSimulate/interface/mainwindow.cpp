#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "interface/toolItem/serialparadialog.h"
#include "uart/uart485.h"
#include "common/publicdata.h"
#include <QPushButton>
#include <QAction>
#include <QMouseEvent>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("SWS模块板模拟工具"));
    ui->versionLabel->setText(SOFT_VERSION);
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    ui->mainTabWidget->setCurrentIndex(0);
    this->setFixedSize(980, 700);

    //最小化按钮
    connect(ui->minimizeBtn, &QPushButton::clicked, this, [this](){
        this->setWindowState(Qt::WindowMinimized);
    });

    //关闭按钮（隐藏主界面）
    connect(ui->closeBtn, &QPushButton::clicked, this, &MainWindow::hide);

    //初始化系统托盘
    m_sysTrayIcon = new QSystemTrayIcon(this);
    m_sysTrayIcon->setIcon(QIcon(":/appicon.ico"));
    m_sysTrayIcon->setToolTip(tr("SWS模块板模拟工具"));
    connect(m_sysTrayIcon, &QSystemTrayIcon::activated, this, [this](QSystemTrayIcon::ActivationReason reason){
        if(reason == QSystemTrayIcon::Trigger)
        {
            this->show();
        }
    });

    m_sysTrayMenu = new QMenu(this);
    m_sysTrayMenu->setStyleSheet("font-size: 9pt;");

    QAction *action = new QAction(tr("显示主界面"), this);
    connect(action, &QAction::triggered, this, &QMainWindow::show);
    m_sysTrayMenu->addAction(action);

    action = new QAction(tr("退出"), this);
    connect(action, &QAction::triggered, this, &MainWindow::slotCloseWindow);
    m_sysTrayMenu->addAction(action);

    m_sysTrayIcon->setContextMenu(m_sysTrayMenu);
    m_sysTrayIcon->show();

    ui->centralWidget->installEventFilter(this);

    //连接状态按钮，可点击
    connect(ui->connectStateLabel, &CustomLinkLabel::clicked, this, &MainWindow::slotConnectStateLabelClicked);
    connect(Uart485App, &UART485::signalConnectSate, this, &MainWindow::slotConnectSate);
    connect(Uart485App, &UART485::signalMachineTypeChanged, this, &MainWindow::slotMachineTypeChanged);

    slotConnectSate(false, "");

    //连接机型按钮，可点击
    connect(ui->machineType, &CustomLinkLabel::clicked, this, &MainWindow::slotMachineTypeClicked);

    //初始化机型设置菜单
    m_machineSetMenu = new QMenu(this);
    QActionGroup *actionGroup = new QActionGroup(m_machineSetMenu);
    actionGroup->addAction(tr("自动检测"))->setData(AutoDetectMachine);
    actionGroup->addAction(tr("SWS-4000"))->setData(SWS4000);
    actionGroup->addAction(tr("SWS-6000"))->setData(SWS6000);
    actionGroup->actions()[0]->setCheckable(true);
    actionGroup->actions()[1]->setCheckable(true);
    actionGroup->actions()[2]->setCheckable(true);
    actionGroup->actions()[0]->setChecked(true);
    m_machineSetMenu->addActions(actionGroup->actions());
    connect(actionGroup, &QActionGroup::triggered, this, &MainWindow::slotActionGroupTriggered);

    //初始化设置菜单
    m_setMenu = new QMenu(this);
    action = new QAction(tr("保存设置"), this);
    m_setMenu->addAction(action);
    connect(action, &QAction::triggered, this, &MainWindow::slotSaveActionTriggered);
    action = new QAction(tr("清除设置"), this);
    m_setMenu->addAction(action);
    connect(action, &QAction::triggered, this, &MainWindow::slotClearActionTriggered);
    action = new QAction(tr("导入设置"), this);
    m_setMenu->addAction(action);
    connect(action, &QAction::triggered, this, &MainWindow::slotImportActionTriggered);
    action = new QAction(tr("导出设置"), this);
    m_setMenu->addAction(action);
    connect(action, &QAction::triggered, this, &MainWindow::slotExportActionTriggered);
}

MainWindow::~MainWindow()
{
    delete ui;
    UART485::deInstance();  //删除485串口线程
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{   //实现空白处点击拖动使主窗口拖动，双击最大化
    static QPoint pressePoint;
    static bool isMove = false;
    if(obj == ui->centralWidget)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {   //鼠标按下事件
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                pressePoint = mouseEvent->pos();
                isMove = true;
            }
        }
        else if(event->type() == QEvent::MouseMove)
        {   //鼠标移动事件
            if(isMove)
            {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
                int changedX = mouseEvent->pos().x() - pressePoint.x();
                int changedY = mouseEvent->pos().y() - pressePoint.y();
                this->move(this->x() + changedX, this->y() + changedY);
            }
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {   //鼠标释放事件
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                isMove = false;
            }
        }
#if 0   /*暂时不要最大化功能（没什么卵用）*/
        else if(event->type() == QEvent::MouseButtonDblClick)
#else
        else if(false)
#endif
        {   //鼠标双击事件（实现左键双击最大化/还原）
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                if(this->windowState() == Qt::WindowMaximized)
                {
                    this->setWindowState(Qt::WindowNoState);
                }
                else
                {
                    this->setWindowState(Qt::WindowMaximized);
                }
            }
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::slotActionGroupTriggered(QAction *action)
{
    g_ss.machineSetType = (MachineType)action->data().toInt();
    if(g_ss.machineSetType != AutoDetectMachine)
    {   //如果不是自动识别型号，强制设置型号
        g_ss.machineType = g_ss.machineSetType;
    }
    emit Uart485App->signalMachineTypeChanged();
}

void MainWindow::slotLoadSetFileFinished()
{
    ui->bloodSystemTab->updateBoardVersionToEdit();
    ui->liquidSystemTab->updateBoardVersionToEdit();
    ui->mixUltraSystemTab->updateBoardVersionToEdit();
    ui->antiSystemTab->updateBoardVersionToEdit();
    ui->powerSystemTab->updateBoardVersionToEdit();
    ui->keyLampTab->updateBoardVersionToEdit();
    ui->BtvRCMTab->updateBoardVersionToEdit();

    QAction *action = m_machineSetMenu->actions().value(g_ss.machineSetType);
    action->setChecked(true);
    slotActionGroupTriggered(action);
}

void MainWindow::slotCloseWindow()
{
    //关机自动保存设置（没有清除的情况下）
    if(!m_clearSetFlag)
    {
        emit signalSaveSetToFile();
    }

    this->close();
}

void MainWindow::slotConnectStateLabelClicked()
{
    if(!m_serialParaDialog)
    {
        m_serialParaDialog = new SerialParaDialog(this);
    }

    m_serialParaDialog->exec();
}

void MainWindow::slotConnectSate(bool isConnect, QString portName)
{
    if(isConnect)
    {
        ui->connectStateLabel->setText("<font color='green'>" + tr("已连接：") + portName + "</font>");
    }
    else
    {
        ui->connectStateLabel->setText("<font color='red'>" + tr("未连接") + "</font>");
    }
}

void MainWindow::slotMachineTypeChanged()
{
    switch(g_ss.machineType)
    {
    case NoneMachine:
        ui->machineType->setText(tr("未检测到机型"));
        break;
    case SWS4000:
        ui->machineType->setText("<font color='brown'>" + QString("SWS-4000") + "</font>");
        break;
    case SWS6000:
        ui->machineType->setText("<font color='#0011FF'>" + QString("SWS-6000") + "</font>");
        break;
    default:
        break;
    }
}

void MainWindow::slotMachineTypeClicked()
{
    m_machineSetMenu->exec(ui->machineType->mapToGlobal(QPoint(ui->machineType->width()/2, ui->machineType->height())));
}

void MainWindow::on_menuBtn_clicked(bool checked)
{
    if(checked)
    {
        m_setMenu->exec(ui->menuBtn->mapToGlobal(QPoint(0, ui->menuBtn->height())));
        ui->menuBtn->setChecked(false);
    }
}

void MainWindow::slotSaveActionTriggered()
{
    m_clearSetFlag = false;
    emit signalSaveSetToFile();
}

void MainWindow::slotClearActionTriggered()
{
    m_clearSetFlag = true;
    emit signalRemoveSetFile();

    QMessageBox::information(this, tr("提示"), tr("已清除设置，重启后生效！"), tr("确定"));
}

void MainWindow::slotImportActionTriggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("选择文件"), "", "*.sds");
    if(!fileName.isEmpty())
    {
        emit signalLoadSetFromFile(fileName);
    }
}

void MainWindow::slotExportActionTriggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("选择文件"), "", "*.sds");
    if(!fileName.isEmpty())
    {
        emit signalSaveSetToFile(fileName);
    }
}
