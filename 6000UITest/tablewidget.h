#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class tableWidget;
}

class tableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit tableWidget(QWidget *parent = nullptr);
    ~tableWidget();

private:
    Ui::tableWidget *ui;
    QPointer<QStandardItemModel> m_model ;//历史报警表
    QStringList m_header;//历史报警表头内容
};

#endif // TABLEWIDGET_H
