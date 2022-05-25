#ifndef NET_H
#define NET_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>

QT_BEGIN_NAMESPACE
namespace Ui { class net; }
QT_END_NAMESPACE

class net : public QMainWindow
{
    Q_OBJECT

public:
    net(QWidget *parent = nullptr);
    ~net();

private:
    Ui::net *ui;

    QTcpSocket *tcp;
    QTcpServer *tser;
};
#endif // NET_H
