#include "valuemodeselectdialog.h"
#include "ui_valuemodeselectdialog.h"
#include <QDebug> ///#include <QDebug>

ValueModeSelectDialog::ValueModeSelectDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ValueModeSelectDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);

    connect(ui->closeBtn, &QPushButton::clicked, this, &QDialog::close);
    ui->closeBtn->hide(); //隐藏关闭按钮（貌似有点多余）
}

ValueModeSelectDialog::~ValueModeSelectDialog()
{
    delete ui;
}

void ValueModeSelectDialog::setValueType(ValueType type, const QString &valueStr0, const QString &valueStr1)
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->firstRadioBtn->setText(tr("固定值"));
    ui->secondRadioBtn->setText(tr("随机值"));

    switch(type)
    {
    case BinaryValue:
        ui->fixValueWidget->hide();
        ui->randomRangeWidget->hide();
        ui->flucRangeWidget->hide();
        ui->thirdRadioBtn->hide();
        ui->line_two->hide();
        ui->firstRadioBtn->setText(valueStr0);
        ui->secondRadioBtn->setText(valueStr1);
        this->setFixedSize(190, 170);
        break;
    case BinaryValueWithAuto:
        ui->fixValueWidget->hide();
        ui->randomRangeWidget->hide();
        ui->flucRangeWidget->hide();
        ui->thirdRadioBtn->show();
        ui->line_two->show();
        ui->firstRadioBtn->setText(valueStr0);
        ui->secondRadioBtn->setText(valueStr1);
        this->setFixedSize(190, 170);
        break;
    case NumericValue:
        ui->fixValueWidget->show();
        ui->randomRangeWidget->show();
        ui->flucRangeWidget->hide();
        ui->thirdRadioBtn->hide();
        ui->line_two->hide();
        this->setFixedSize(250, 220);
        break;
    case NumericValueWithAuto:
        ui->fixValueWidget->show();
        ui->randomRangeWidget->show();
        ui->flucRangeWidget->hide();
        ui->thirdRadioBtn->show();
        ui->line_two->show();
        this->setFixedSize(250, 240);
        break;
    case NumericValueWithAutoRange:
        ui->fixValueWidget->show();
        ui->randomRangeWidget->show();
        ui->flucRangeWidget->show();
        ui->thirdRadioBtn->show();
        ui->line_two->show();
        this->setFixedSize(300, 270);
        break;
    default:
        break;
    }
}

void ValueModeSelectDialog::setEnumValueType(ValueType type, const QStringList &enumStrList)
{
    ui->stackedWidget->setCurrentIndex(1);

    ui->fixComboBox_page2->clear();
    ui->fixComboBox_page2->addItems(enumStrList);

    ui->autoRadioBtn_page2->setVisible(type == EnumValueWithAuto);

    this->setFixedSize(190, 170);
}

void ValueModeSelectDialog::setTitle(const QString &title)
{
    ui->titleLabel->setText(title);
}

void ValueModeSelectDialog::setDecimals(int dec)
{
    ui->fixSpinBox->setDecimals(dec);
    ui->randomMinSpinBox->setDecimals(dec);
    ui->randomMaxSpinBox->setDecimals(dec);
    ui->autoSubSpinBox->setDecimals(dec);
    ui->autoAddSpinBox->setDecimals(dec);
}

void ValueModeSelectDialog::setCurrentSetting(const DataSimModeSt &dsm, const QString &valueStr0, const QString &valueStr1)
{
    m_currentSetting = dsm;
    setValueType(dsm.valueType, valueStr0, valueStr1);

    if(dsm.valueType <= BinaryValueWithAuto)
    {   //二值的数据类型（只有固定和自动两种模式）
        if(dsm.mode == FixSimMode)
        {   //固定模式
            if(dsm.fixValue == 0)
            {
                ui->firstRadioBtn->setChecked(true);
            }
            else
            {
                ui->secondRadioBtn->setChecked(true);
            }
        }
        else
        {   //自动模式
            ui->thirdRadioBtn->setChecked(true);
        }
    }
    else
    {   //数值型的数据类型
        setDecimals(dsm.decimals);
        switch(dsm.mode)
        {
        case FixSimMode:
            ui->firstRadioBtn->setChecked(true);
            break;
        case RandomSimMode:
            ui->secondRadioBtn->setChecked(true);
            break;
        case AutoSimMode:
            ui->thirdRadioBtn->setChecked(true);
            break;
        default:
            break;
        }

        ui->fixSpinBox->setValue(dsm.fixValue);
        ui->randomMinSpinBox->setValue(dsm.randomMinValue);
        ui->randomMaxSpinBox->setValue(dsm.randomMaxValue);
        ui->autoSubSpinBox->setValue(dsm.autoSubValue);
        ui->autoAddSpinBox->setValue(dsm.autoAddValue);
    }
}

void ValueModeSelectDialog::setCurrentSetting(const DataSimModeSt &dsm, const QStringList &enumStrList)
{
    m_currentSetting = dsm;
    setEnumValueType(dsm.valueType, enumStrList);

    if(dsm.mode == FixSimMode)
    {
        ui->fixRadioBtn_page2->setChecked(true);
    }
    else if(dsm.mode == AutoSimMode)
    {
        ui->autoRadioBtn_page2->setChecked(true);
    }

    ui->fixComboBox_page2->setCurrentIndex((int)dsm.fixValue);
}

DataSimModeSt ValueModeSelectDialog::currentSetting()
{
    if(m_currentSetting.valueType <= BinaryValueWithAuto)
    {   //二值的数据类型（只有固定和自动两种模式）
        if(ui->firstRadioBtn->isChecked())
        {
            m_currentSetting.mode = FixSimMode;
            m_currentSetting.fixValue = 0;
        }
        else if(ui->secondRadioBtn->isChecked())
        {
            m_currentSetting.mode = FixSimMode;
            m_currentSetting.fixValue = 1;
        }
        else if(ui->thirdRadioBtn->isChecked())
        {
            m_currentSetting.mode = AutoSimMode;
        }
    }
    else if(m_currentSetting.valueType >= NumericValue && m_currentSetting.valueType <= NumericValueWithAutoRange)
    {   //数值型的数据类型
        if(ui->firstRadioBtn->isChecked())
        {
            m_currentSetting.mode = FixSimMode;
        }
        else if(ui->secondRadioBtn->isChecked())
        {
            m_currentSetting.mode = RandomSimMode;
        }
        else if(ui->thirdRadioBtn->isChecked())
        {
            m_currentSetting.mode = AutoSimMode;
        }

        m_currentSetting.fixValue = ui->fixSpinBox->value();
        m_currentSetting.randomMinValue = ui->randomMinSpinBox->value();
        m_currentSetting.randomMaxValue = ui->randomMaxSpinBox->value();
        m_currentSetting.autoSubValue = ui->autoSubSpinBox->value();
        m_currentSetting.autoAddValue = ui->autoAddSpinBox->value();
    }
    else if(m_currentSetting.valueType >= EnumValue && m_currentSetting.valueType <= EnumValueWithAuto)
    {   //枚举类型
        if(ui->fixRadioBtn_page2->isChecked())
        {
            m_currentSetting.mode = FixSimMode;
        }
        else if(ui->autoRadioBtn_page2->isChecked())
        {
            m_currentSetting.mode = AutoSimMode;
        }

        m_currentSetting.fixValue = ui->fixComboBox_page2->currentIndex();
    }

    return m_currentSetting;
}

void ValueModeSelectDialog::on_randomMinSpinBox_valueChanged(double arg1)
{
    ui->randomMaxSpinBox->setMinimum(arg1);
}

void ValueModeSelectDialog::on_randomMaxSpinBox_valueChanged(double arg1)
{
    ui->randomMinSpinBox->setMaximum(arg1);
}
