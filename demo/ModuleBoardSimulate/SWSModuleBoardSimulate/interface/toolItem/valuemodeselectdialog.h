#ifndef VALUEMODESELECTDIALOG_H
#define VALUEMODESELECTDIALOG_H

#include <QDialog>
#include "common/publicdata.h"

namespace Ui {
class ValueModeSelectDialog;
}

class ValueModeSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ValueModeSelectDialog(QWidget *parent = 0);
    ~ValueModeSelectDialog();

    void setTitle(const QString &title);
    void setDecimals(int dec);
    void setCurrentSetting(const DataSimModeSt &dsm, const QString &valueStr0, const QString &valueStr1); //设置当前设置，以及二值时的文字
    void setCurrentSetting(const DataSimModeSt &dsm, const QStringList &enumStrList); //设置当前设置，枚举类型
    DataSimModeSt currentSetting();

private slots:
    void on_randomMinSpinBox_valueChanged(double arg1);
    void on_randomMaxSpinBox_valueChanged(double arg1);

private:
    void setValueType(ValueType type, const QString &valueStr0 = "", const QString &valueStr1 = ""); //设置数据类型，若为二值时，还设置文字
    void setEnumValueType(ValueType type, const QStringList &enumStrList); //设定为枚举类型

private:
    Ui::ValueModeSelectDialog *ui;
    DataSimModeSt m_currentSetting;
};

#endif // VALUEMODESELECTDIALOG_H
