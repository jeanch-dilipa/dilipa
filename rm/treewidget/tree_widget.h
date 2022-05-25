#ifndef TREE_WIDGET_H
#define TREE_WIDGET_H

#include <QWidget>
#include <QTreeWidget>

class tree_Widget : public QWidget
{
    Q_OBJECT

public:
    tree_Widget(QWidget *parent = nullptr);
    ~tree_Widget();

    void init();
    void updateitem(QTreeWidgetItem*,int);

public slots:
    void slot_itemchanged(QTreeWidgetItem*,int);

private:
    QTreeWidget *tw;
};
#endif // TREE_WIDGET_H
