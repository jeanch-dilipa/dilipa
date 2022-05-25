#ifndef SQLITEMAKE_H
#define SQLITEMAKE_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QItemSelectionModel>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui { class sqlitemake; }
QT_END_NAMESPACE

class sqlitemake : public QWidget
{
    Q_OBJECT

public:
    sqlitemake(QWidget *parent = nullptr);
    ~sqlitemake();

private:
    Ui::sqlitemake *ui;

    QSqlDatabase db;
//    QSqlRecord record;
    QString dbfile;
    QSqlQueryModel *querymodel;
    QItemSelectionModel *section;
    QSqlTableModel *tablemodel;
};
#endif // SQLITEMAKE_H
