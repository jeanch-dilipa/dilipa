#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QDir>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QWidget
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

    QString languagecombox;
signals:
    void language(QString str);

public slots:
    void slot_connect();
    void slot_read();
//    void slot_disconnect();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_3_returnPressed();

    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::Server *ui;
    QDir dir;
    QTranslator qtranslator;
};
#endif // SERVER_H
