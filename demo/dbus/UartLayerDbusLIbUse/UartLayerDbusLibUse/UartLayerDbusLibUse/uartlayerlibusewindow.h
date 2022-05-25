#ifndef UARTLAYERLIBUSEWINDOW_H
#define UARTLAYERLIBUSEWINDOW_H

#include <QMainWindow>
#include "uartlayerdbus.h"
#include <QByteArray>

namespace Ui {
class UartLayerLibUseWindow;
}

class UartLayerLibUseWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit UartLayerLibUseWindow(QWidget *parent = 0);
    ~UartLayerLibUseWindow();
signals:
    void SIGNALSendData(QByteArray data);
private slots:
    void SLOTReceive(QByteArray data);
    void SLOTDbusError(mDBusError error,QString errorMsg);
    void on_btnSend_clicked();
    void SLOTSendNextData(bool ok);
private:
    Ui::UartLayerLibUseWindow *ui;

    UartLayerDbus *mUartLayerDbus;

    void sendData();
};

#endif // UARTLAYERLIBUSEWINDOW_H
