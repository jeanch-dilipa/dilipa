#ifndef SYSTEMINTERFACEBASE_H
#define SYSTEMINTERFACEBASE_H

#include <QWidget>
#include <QTimer>
#include <QPushButton>
#include <QButtonGroup>
#include <QLineEdit>
#include <QStackedWidget>
#include "common/publicdata.h"
#include "interface/toolItem/valuemodeselectdialog.h"

//用于绑定模拟数据与按钮的基础类
class BindBtnListItemBase
{
public:
    BindBtnListItemBase(QPushButton *btn = Q_NULLPTR)
    {
        this->btn = btn;
    }

    BindBtnListItemBase(QPushButton *btn, SimDataSt *data, QString title)
    {
        this->btn = btn;
        this->data = data;
        this->title = title;
    }

    bool operator ==(BindBtnListItemBase other)
    {
        return (this->btn == other.btn);
    }

    QPushButton   *btn  = Q_NULLPTR;
    SimDataSt     *data = Q_NULLPTR;
    QString        title;
};

class BindBtnListItem : public BindBtnListItemBase
{
public:
    BindBtnListItem(QPushButton *btn = Q_NULLPTR) : BindBtnListItemBase(btn)
    {
    }
    BindBtnListItem(QPushButton *btn, SimDataSt *data, QString title, QString valueStr0 = "", QString valueStr1 = "")
        : BindBtnListItemBase(btn, data, title)
    {
        this->valueStr0 = valueStr0;
        this->valueStr1 = valueStr1;
    }

    QString        valueStr0;
    QString        valueStr1;
    bool           btnOpen = false;  //保存当前按钮的状态（Value为0还是1）
};

class BindEnumBtnListItem : public BindBtnListItemBase
{
public:
    BindEnumBtnListItem(QPushButton *btn = Q_NULLPTR) : BindBtnListItemBase(btn)
    {
    }
    BindEnumBtnListItem(QPushButton *btn, SimDataSt *data, const QString &title, const QStringList &enumStrList)
        : BindBtnListItemBase(btn, data, title)
    {
        this->enumStrList = enumStrList;
    }

    QStringList enumStrList;
};

//用于绑定板子版本信息与编辑控件的基础类
class BindVersionListItem
{
public:
    BindVersionListItem(QLineEdit *edit, ushort *version = Q_NULLPTR, bool isSoft = true)
    {
        this->edit = edit;
        this->version = version;
        this->isSoft = isSoft;
    }
    bool operator ==(BindVersionListItem other)
    {
        return (this->edit == other.edit);
    }

    QLineEdit *edit    = Q_NULLPTR;
    ushort    *version = Q_NULLPTR;
    bool       isSoft  = true;
};

//各个子系统界面基类
class SystemInterfaceBase : public QWidget
{
    Q_OBJECT
public:
    explicit SystemInterfaceBase(QWidget *parent = nullptr);

    void updateBoardVersionToEdit(); //更新板子版本信息到行编辑器（在加载存储设置时使用）

protected:
    virtual void initBtnBind() = 0; //初始化绑定按钮，子类实现
    void addBtnBindItem(QPushButton *btn, SimDataSt *data, QString title, QString valueStr0 = "", QString valueStr1 = ""); //绑定一个按钮
    void addBtnBindItem(QPushButton *btn, SimDataSt *data, const QString &title, const QStringList &enumStrList); //绑定一个按钮，枚举型数据
    void initVersionLineEdit(QLineEdit *lineEdit, ushort *ver, bool isSoft = true); //初始化版本输入框
    ushort verStrToNum(QString verStr);  //版本信息-字符转数字
    QString verNumToStr(ushort verNum, bool isSoft = true);  //版本信息-数字转字符
    void initVerStackedWidget(QStackedWidget *w); //初始化版本显示窗口

private slots:
    void slotUpdateInterface(); //更新界面
    void slotButtonToggled(QAbstractButton *btn, bool checked);  //按钮组中有按钮触发
    void slotLineEditEditingFinished(); //行编辑器编辑完成

private:
    void setButtonStyleSheet(QPushButton *btn, bool isOpen);  //设置按钮的样式

template<typename T>
    void getSettingFromDialog(T &item, ValueModeSelectDialog &dialog); //从对话框中获取设置

private:
    QButtonGroup *m_btnGroup;                          //按钮组
    QList<BindBtnListItem> m_bindBtnItemList;          //已绑定的数据项
    QList<BindEnumBtnListItem> m_bindEnumBtnItemList;  //已绑定的枚举型的数据项
    QList<BindVersionListItem> m_bindBoardVerItemList; //已绑定的模块版本数据项
    QTimer *m_updateTimer;                             //更新界面定时器
    QStackedWidget *m_verStackedWidget = Q_NULLPTR;    //版本显示窗口
};

#endif // SYSTEMINTERFACEBASE_H
