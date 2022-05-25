#include "spinboxdelegate.h"

#include <QSpinBox>

spinboxdelegate::spinboxdelegate()
{

}

QWidget *spinboxdelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    QSpinBox *editor=new QSpinBox(parent);
    editor->setFrame(false);
    editor->setMaximum(2000);
    editor->setMinimum(30);
    return  editor;
}

void spinboxdelegate::setEditorData(QWidget *editor, const QModelIndex &index)
{
    int value=index.model()->data(index,Qt::EditRole).toInt();
    QSpinBox *spinbox= static_cast<QSpinBox*>(editor);
    spinbox->setValue(value);
}

void spinboxdelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index)
{
    QSpinBox *spinbox=static_cast<QSpinBox*>(editor);
    spinbox->interpretText();
    int value=spinbox->value();
    model->setData(index,value,Qt::EditRole);
}

void spinboxdelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    editor->setGeometry(option.rect);
}
