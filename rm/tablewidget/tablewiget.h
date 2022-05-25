#ifndef TABLEWIGET_H
#define TABLEWIGET_H

#include <QMainWindow>
#include <QStringListModel>

#include <spinboxdelegate.h>

QT_BEGIN_NAMESPACE
namespace Ui { class tableWiget; }
QT_END_NAMESPACE

class tableWiget : public QMainWindow
{
    Q_OBJECT

public:
    tableWiget(QWidget *parent = nullptr);
    ~tableWiget();

private slots:
    void on_treeView_clicked(const QModelIndex &index);
    void removerow();

private:
    Ui::tableWiget *ui;
    spinboxdelegate sbd;





};
#endif // TABLEWIGET_H
