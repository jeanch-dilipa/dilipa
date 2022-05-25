#ifndef SPINBOXDELEGATE_H
#define SPINBOXDELEGATE_H

#include <QStyledItemDelegate>

class spinboxdelegate : public QStyledItemDelegate
{
public:
    spinboxdelegate();

    QWidget *createEditor(QWidget *parent,const QStyleOptionViewItem &option, const QModelIndex &index);
    void setEditorData(QWidget *editor, const QModelIndex &index);
    void setModelData(QWidget *editor,QAbstractItemModel *model,const QModelIndex &index);
    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,const QModelIndex &index);
};

#endif // SPINBOXDELEGATE_H
