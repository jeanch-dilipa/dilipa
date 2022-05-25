#include "systeminterfacebase.h"
#include "uart/uart485.h"
#include <QRegExpValidator>

#define UPDATE_INTERFACE_TIME 500 /*装载设置数据周期 ms*/

SystemInterfaceBase::SystemInterfaceBase(QWidget *parent) : QWidget(parent)
{
    //按钮组
    m_btnGroup = new QButtonGroup(this);
    m_btnGroup->setExclusive(false);
    connect(m_btnGroup, (void (QButtonGroup:: *)(QAbstractButton *, bool))&QButtonGroup::buttonToggled, this, &SystemInterfaceBase::slotButtonToggled);

    //更新界面定时器
    m_updateTimer = new QTimer(this);
    connect(m_updateTimer, &QTimer::timeout, this, &SystemInterfaceBase::slotUpdateInterface);
    m_updateTimer->start(UPDATE_INTERFACE_TIME);

    //初始化按钮与数据绑定（父类构造时，子类还没有构造，需要延迟调用此函数）
    QTimer::singleShot(0, this, [this](){
        initBtnBind();
    });
}

void SystemInterfaceBase::updateBoardVersionToEdit()
{
    foreach(BindVersionListItem item, m_bindBoardVerItemList)
    {
        item.edit->setText(verNumToStr(*item.version, item.isSoft));
    }
}

void SystemInterfaceBase::slotUpdateInterface()
{
    int size = m_bindBtnItemList.size();
    for(int i = 0; i < size; i++)
    {
        BindBtnListItem *item = &m_bindBtnItemList[i];
        ValueType type = item->data->set.valueType;
        if(type <= BinaryValueWithAuto)
        {   //二值型
            item->btn->setText((bool)item->data->value ? item->valueStr1 : item->valueStr0);
            if(item->btnOpen != (bool)item->data->value)
            {
                item->btnOpen = (bool)item->data->value;
                setButtonStyleSheet(item->btn, item->btnOpen);
            }
        }
        else if(type >= NumericValue && type <= NumericValueWithAutoRange)
        {   //数值型
            if(item->data->set.decimals == 0)
            {   //整数
                item->btn->setText(QString::number((int)item->data->value));
            }
            else
            {   //小数
                item->btn->setText(QString::number(item->data->value, 'f', item->data->set.decimals));
            }
        }
    }

    //枚举型
    foreach(BindEnumBtnListItem item, m_bindEnumBtnItemList)
    {
        item.btn->setText(item.enumStrList.value(item.data->value));
    }
}

void SystemInterfaceBase::addBtnBindItem(QPushButton *btn, SimDataSt *data, QString title, QString valueStr0, QString valueStr1)
{
    m_bindBtnItemList.append(BindBtnListItem(btn, data, title, valueStr0, valueStr1));
    m_btnGroup->addButton(btn);
}

void SystemInterfaceBase::addBtnBindItem(QPushButton *btn, SimDataSt *data, const QString &title, const QStringList &enumStrList)
{
    m_bindEnumBtnItemList.append(BindEnumBtnListItem(btn, data, title, enumStrList));
    m_btnGroup->addButton(btn);
}

void SystemInterfaceBase::initVersionLineEdit(QLineEdit *lineEdit, ushort *ver, bool isSoft)
{
    if(lineEdit)
    {
        if(isSoft)
        {   //软件版本
            lineEdit->setValidator(new QRegExpValidator(QRegExp("S-V[0-9]\\.[0-9]{2}")));
            lineEdit->setPlaceholderText("S-V0.00");
        }
        else
        {   //硬件版本
            lineEdit->setValidator(new QRegExpValidator(QRegExp("H-V[0-9]\\.[0-9]{2}")));
            lineEdit->setPlaceholderText("H-V0.00");
        }
        connect(lineEdit, &QLineEdit::editingFinished, this, &SystemInterfaceBase::slotLineEditEditingFinished, Qt::UniqueConnection);
        m_bindBoardVerItemList.append(BindVersionListItem(lineEdit, ver, isSoft));
        lineEdit->editingFinished(); //先刷新一次
    }
}

ushort SystemInterfaceBase::verStrToNum(QString verStr)
{   //例如："S-V6.03"
    ushort ver = 0;

    if(verStr.size() == 7)
    {
        QStringList verStrList = verStr.mid(3).split('.');
        if(verStrList.size() == 2)
        {
            uchar verHigh = verStrList.at(0).toInt();
            uchar verLow = verStrList.at(1).toInt();
            ver = (verHigh << 8) | verLow;
        }
    }

    return ver;
}

QString SystemInterfaceBase::verNumToStr(ushort verNum, bool isSoft)
{
    return QString("%1-V%2.%3")
            .arg(isSoft ? "S" : "H").arg(verNum >> 8, 0, 10, QChar('0')).arg(verNum & 0x00FF, 2, 10, QChar('0'));
}

void SystemInterfaceBase::initVerStackedWidget(QStackedWidget *w)
{
    if(w)
    {
        m_verStackedWidget = w;
        //连接机器型号改变信号
        connect(Uart485App, &UART485::signalMachineTypeChanged, this, [this](){
            m_verStackedWidget->setCurrentIndex(g_ss.machineType == SWS4000);
        }, Qt::UniqueConnection);

        ///zf_test 默认6000
        m_verStackedWidget->setCurrentIndex(0);
    }
}

void SystemInterfaceBase::slotButtonToggled(QAbstractButton *btn, bool checked)
{
    if(checked)
    {
        int index = m_bindBtnItemList.indexOf(BindBtnListItem((QPushButton *)btn));
        if(index >= 0)
        {
            BindBtnListItem item = m_bindBtnItemList.value(index);
            ValueModeSelectDialog dialog(this);
            dialog.setCurrentSetting(item.data->set, item.valueStr0, item.valueStr1);
            getSettingFromDialog(item, dialog);
        }
        else
        {   //尝试是否为枚举类型
            index = m_bindEnumBtnItemList.indexOf(BindEnumBtnListItem((QPushButton *)btn));
            if(index >= 0)
            {
                BindEnumBtnListItem item = m_bindEnumBtnItemList.value(index);
                ValueModeSelectDialog dialog(this);
                dialog.setCurrentSetting(item.data->set, item.enumStrList);
                getSettingFromDialog(item, dialog);
            }
        }

        btn->setChecked(false);
    }
}

void SystemInterfaceBase::slotLineEditEditingFinished()
{
    QLineEdit *editSender = qobject_cast<QLineEdit *>(sender());
    int index = m_bindBoardVerItemList.indexOf(BindVersionListItem(editSender));
    if(index >= 0)
    {   //装载版本信息
        BindVersionListItem item = m_bindBoardVerItemList.at(index);
        *item.version = verStrToNum(item.edit->text());
    }
}

void SystemInterfaceBase::setButtonStyleSheet(QPushButton *btn, bool isOpen)
{
    if(btn == Q_NULLPTR)
    {
        return;
    }

    if(isOpen)
    {
        btn->setStyleSheet("QPushButton{background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(165, 245, 226, 200), stop:1 rgba(0, 255, 255, 200));}"
                           "QPushButton:hover{background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(165, 245, 226, 255), stop:1 rgba(0, 255, 255, 255));}"
                           "QPushButton:pressed{background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(150, 230, 211, 200), stop:1 rgba(0, 240, 240, 200));}"
                           "QPushButton:checked{background: rgba(153, 255, 204, 100);}");
    }
    else
    {
        btn->setStyleSheet("QPushButton{background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(234, 255, 255, 200), stop:1 rgba(253, 231, 231, 150));}"
                           "QPushButton:hover{background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(234, 255, 255, 255), stop:1 rgba(253, 231, 231, 255));}"
                           "QPushButton:pressed{background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(214, 235, 235, 200), stop:1 rgba(243, 211, 211, 150));}"
                           "QPushButton:checked{background: rgba(153, 255, 204, 100);}");
    }
}

template<typename T>
void SystemInterfaceBase::getSettingFromDialog(T &item, ValueModeSelectDialog &dialog)
{
    dialog.setTitle(item.title);
    dialog.move(QCursor::pos());
    dialog.exec();
    item.data->set = dialog.currentSetting();

    if(item.data->set.mode == FixSimMode)
    {   //模拟固定值，直接装载数据
        item.data->value = item.data->set.fixValue;
    }
    item.data->set.changed = true;
}
