#ifndef DATALAYERDBUSWINDOW_H
#define DATALAYERDBUSWINDOW_H

#include <QMainWindow>
#include "datalayerdbus.h"
#include <QByteArray>

namespace Ui {
class DataLayerDbusWindow;
}

class DataLayerDbusWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit DataLayerDbusWindow(QWidget *parent = 0);
    ~DataLayerDbusWindow();
signals:
    void SIGNALSendData(QByteArray data);
private slots:
    void SLOTReceive(QByteArray data);
    void SLOTDbusError(mDBusError error,QString errorMsg);
    void on_btnSend_clicked();
    void SLOTSendNextData(bool ok);
private:
    Ui::DataLayerDbusWindow *ui;

    DataLayerDbus *mDataLayerDbus;

    void sendData();
};

#endif // DATALAYERDBUSWINDOW_H
