#ifndef DATALAYWINDOW_H
#define DATALAYWINDOW_H

#include <QMainWindow>
#include "datalayerdbus.h"
#include <QByteArray>

namespace Ui {
class DataLayWindow;
}

class DataLayWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit DataLayWindow(QWidget *parent = 0);
    ~DataLayWindow();
    
    void sendData();
private slots:
    void on_btnSend_clicked();

    void SLOTReceData(QByteArray data);
    void SLOTSendNextData(bool ok);
    void SLOTDbusError(mDBusError error,QString errorMsg);
signals:
    void SIGNALSendData(QByteArray data);
private:
    Ui::DataLayWindow *ui;
    DataLayerDbus *m_dataLayer;
};

#endif // DATALAYWINDOW_H
