#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialogue; }
QT_END_NAMESPACE

class Dialogue : public QWidget
{
    Q_OBJECT

public:
    Dialogue(QWidget *parent = nullptr);
    ~Dialogue();

private slots:
    void on_lineEdit_returnPressed();

    void on_pushButton_clicked();

    void slot_readreturn();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Dialogue *ui;
    QTcpSocket *socket;
    QTcpSocket *socketfile;
};
#endif // DIALOGUE_H
