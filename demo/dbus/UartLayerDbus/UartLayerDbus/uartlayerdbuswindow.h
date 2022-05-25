#ifndef UARTLAYERDBUSWINDOW_H
#define UARTLAYERDBUSWINDOW_H

#include <QMainWindow>
#include "uartlayerdbus.h"

namespace Ui {
class UartLayerDbusWindow;
}

class UartLayerDbusWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit UartLayerDbusWindow(QWidget *parent = 0);
    ~UartLayerDbusWindow();
    
    void sendData();
signals:
    void SIGNALSendData(QByteArray data);
private slots:
    void on_btnSend_clicked();
    void SLOTReceData(QByteArray data);
    void SLOTSendNextData(bool ok);
    void SLOTDbusError(mDBusError error,QString errorMsg);
private:
    Ui::UartLayerDbusWindow *ui;
    UartLayerDbus *m_uartLayerDbus;
};

#endif // UARTLAYERDBUSWINDOW_H
