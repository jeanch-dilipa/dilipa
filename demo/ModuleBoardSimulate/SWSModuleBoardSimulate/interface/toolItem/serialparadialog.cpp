#include "serialparadialog.h"
#include "uart/uart485.h"
#include <QSerialPort>
#include <QEvent>
#include <QMouseEvent>
#include <QSerialPortInfo>

SerialParaDialog::SerialParaDialog(QWidget *parent) : QDialog(parent)
{
    initUI();

    connect(Uart485App, &UART485::signalConnectSate, this, &SerialParaDialog::slotConnectSate);
}

SerialParaDialog::~SerialParaDialog()
{
}

void SerialParaDialog::initUI()
{
    this->setWindowTitle(tr("连接参数"));
    this->setFixedSize(230, 220);

    m_stackWidget = new QStackedWidget(this);
    m_stackWidget->addWidget(new QWidget(m_stackWidget));
    m_stackWidget->addWidget(new QWidget(m_stackWidget));

    m_commuWayLbl = new QLabel(this);
    m_baudRateLbl = new QLabel(this);
    m_parityBitsLbl = new QLabel(this);
    m_dataBitsLbl = new QLabel(this);
    m_stopBitsLbl = new QLabel(this);
    m_portNameLbl = new QLabel(this);
    m_portNameLbl2 = new QLabel(this);
    m_msgLbl = new CustomMessageLabel(this);

    m_commuWayLbl->setText(tr("通讯方式："));
    m_baudRateLbl->setText(tr("波特率："));
    m_parityBitsLbl->setText(tr("校验位："));
    m_dataBitsLbl->setText(tr("数据位："));
    m_stopBitsLbl->setText(tr("停止位："));
    m_portNameLbl->setText(tr("端口名："));
    m_portNameLbl2->setText(tr("端口名："));

    m_commuWayCbx = new QComboBox(this);
    m_baudRateCbx = new QComboBox(this);
    m_parityBitsCbx = new QComboBox(this);
    m_dataBitsCbx = new QComboBox(this);
    m_stopBitsCbx = new QComboBox(this);
    m_portNameCbx = new QComboBox(this);
    m_portNameEdit = new QLineEdit(this);

    m_portNameCbx->installEventFilter(this);

    m_commuWayCbx->addItems({tr("串口"), tr("命名管道")});
    connect(m_commuWayCbx, (void (QComboBox:: *)(int))&QComboBox::currentIndexChanged, this, &SerialParaDialog::slotCommuWayCbxChanged);

#ifdef Q_OS_WIN
    m_portNameEdit->setText("\\\\.\\pipe\\com_1");
#else
    m_portNameEdit->setText("/dev/pts/12");
#endif

    m_baudRateCbx->addItems({"1200","2400","4800","9600","19200","38400","57600","115200"});
    m_baudRateCbx->setCurrentText("115200");

    m_parityBitsCbx->addItem("No", QSerialPort::NoParity);
    m_parityBitsCbx->addItem("Even", QSerialPort::EvenParity);
    m_parityBitsCbx->addItem("Odd", QSerialPort::OddParity);
    m_parityBitsCbx->addItem("Space", QSerialPort::SpaceParity);
    m_parityBitsCbx->addItem("Mark", QSerialPort::MarkParity);

    m_dataBitsCbx->addItems({"5","6","7","8"});
    m_dataBitsCbx->setCurrentText("8");

    m_stopBitsCbx->addItem("1", QSerialPort::OneStop);
    m_stopBitsCbx->addItem("1.5", QSerialPort::OneAndHalfStop);
    m_stopBitsCbx->addItem("2", QSerialPort::TwoStop);
    m_stopBitsCbx->setCurrentText("1");

    m_connectBtn = new QPushButton(this);
    m_connectBtn->setText(tr("连接"));
    connect(m_connectBtn, &QPushButton::clicked, this, &SerialParaDialog::slotConnectBtnClicked);

    m_vLayout = new QVBoxLayout(this);
    m_gridLayout = new QGridLayout(m_stackWidget->widget(0));
    m_hLayout = new QHBoxLayout();
    m_hLayout1 = new QHBoxLayout();
    m_hLayout2 = new QHBoxLayout(m_stackWidget->widget(1));

    m_hLayout1->addWidget(m_commuWayLbl);
    m_hLayout1->addWidget(m_commuWayCbx);

    m_hLayout2->addWidget(m_portNameLbl2);

    m_gridLayout->addWidget(m_baudRateLbl, 0, 0);
    m_gridLayout->addWidget(m_parityBitsLbl, 1, 0);
    m_gridLayout->addWidget(m_dataBitsLbl, 2, 0);
    m_gridLayout->addWidget(m_stopBitsLbl, 3, 0);
    m_gridLayout->addWidget(m_portNameLbl, 4, 0);

    m_gridLayout->addWidget(m_baudRateCbx, 0, 1);
    m_gridLayout->addWidget(m_parityBitsCbx, 1, 1);
    m_gridLayout->addWidget(m_dataBitsCbx, 2, 1);
    m_gridLayout->addWidget(m_stopBitsCbx, 3, 1);

#ifdef Q_OS_WIN
    m_gridLayout->addWidget(m_portNameCbx, 4, 1);
    m_hLayout2->addWidget(m_portNameEdit);
#else
    m_gridLayout->addWidget(m_portNameEdit, 4, 1);
    m_portNameCbx->hide();
    m_commuWayLbl->hide();
    m_commuWayCbx->hide();
#endif

    m_gridLayout->setMargin(0);
    m_hLayout2->setMargin(0);

    m_hLayout->addWidget(m_msgLbl);
    m_hLayout->addStretch();
    m_hLayout->addWidget(m_connectBtn);
    m_vLayout->addLayout(m_hLayout1);
    m_vLayout->addWidget(m_stackWidget);
    m_vLayout->addLayout(m_hLayout);

#ifdef Q_OS_WIN
    m_commuWayCbx->setCurrentIndex(1); //windows下默认管道方式连接
    updatePortName();
#endif
}

void SerialParaDialog::updatePortName()
{
    QList<QSerialPortInfo> infoList = QSerialPortInfo::availablePorts();
    QStringList portList;
    foreach (QSerialPortInfo info, infoList)
    {
        portList << info.portName();
    }

    if(portList != m_portNameList)
    {
        if(!portList.isEmpty())
        {
            m_portNameList = portList;

            QString selectedPort = m_portNameCbx->currentText();
            m_portNameCbx->clear();
            m_portNameCbx->addItems(m_portNameList);
            if(m_portNameList.contains(selectedPort))
            {
                m_portNameCbx->setCurrentText(selectedPort);
            }
            m_connectBtn->setEnabled(true);
        }
        else
        {
            m_portNameCbx->clear();
            m_portNameCbx->addItem(tr("无可用串口"));
            m_connectBtn->setEnabled(false);
        }
    }
}

bool SerialParaDialog::eventFilter(QObject *obj, QEvent *event)
{
    //鼠标点击串口名下拉框，自动更新可用串口
    if(obj == m_portNameCbx)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                updatePortName();
            }
        }
    }

    return QDialog::eventFilter(obj, event);
}

void SerialParaDialog::slotConnectBtnClicked()
{
    if(m_connectState == 0)
    {
        SerialParaType para;
        para.pipeCom = (bool)m_commuWayCbx->currentIndex();
        para.baud = (QSerialPort::BaudRate)m_baudRateCbx->currentText().toInt();
        para.parity = (QSerialPort::Parity)m_parityBitsCbx->currentData().toInt();
        para.dataBits = (QSerialPort::DataBits)m_dataBitsCbx->currentText().toInt();
        para.stopBits = (QSerialPort::StopBits)m_stopBitsCbx->currentData().toInt();
#ifdef Q_OS_WIN
        para.portName = para.pipeCom ? m_portNameEdit->text().trimmed() : m_portNameCbx->currentText();
#else
        para.portName = m_portNameEdit->text().trimmed();
#endif
        Uart485App->connectToSerial(para);

        m_connectBtn->setText(tr("连接中"));
        m_connectBtn->setEnabled(false);
        m_connectState = 1;
    }
    else if(m_connectState == 3)
    {
        Uart485App->disconnectFromSerial();
    }
}

void SerialParaDialog::slotConnectSate(bool isConnect)
{
    m_connectBtn->setEnabled(true);

    if(isConnect)
    {
        m_connectBtn->setText(tr("断开"));
        m_msgLbl->showSuccessMessage(tr("连接成功！"));
        m_connectState = 3;
        this->close(); //连接成功自动关闭窗口
    }
    else
    {
        m_connectBtn->setText(tr("连接"));
        if(m_connectState == 1)
        {
            m_msgLbl->showErrorMessage(tr("连接失败！"));
        }
        else if(m_connectState == 3)
        {
            m_msgLbl->showErrorMessage(tr("连接已断开！"));
        }
        m_connectState = 0;
    }
}

void SerialParaDialog::slotCommuWayCbxChanged(int index)
{
    if(m_stackWidget->currentIndex() != index)
    {
        if(index == 0)
        {
            this->setFixedSize(230, 220);
        }
        else
        {
            this->setFixedSize(230, 120);
        }

        m_stackWidget->setCurrentIndex(index);
    }
}
