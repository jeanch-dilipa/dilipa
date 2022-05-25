#ifndef UARTLAYERDBUS_H
#define UARTLAYERDBUS_H

#include <QObject>
#include "UartLayerDbusReceive.h"
#include "UartLayerDbusSend.h"
#include <QByteArray>
#include <QThread>
#include <QVector>
#include <QTimer>


class UartLayerDbus : public QObject
{
    Q_OBJECT
private:
    QVector<QByteArray> sendDataList;
    QTimer *m_sendDataTimer;
public:
    explicit UartLayerDbus(QObject *parent = 0);

    UartLayerDbusReceive *m_UartLayerDbusReceice;
    UartLayerDbusSend *m_UartLayerDbusSend;

    QThread *m_SendThread;
    QThread *m_receiceThread;
    
signals:
    void SIGNLASendReturnValue(bool ok);
    void SIGNALSendData(QByteArray data);
    void SIGNALReceivedData(QByteArray data);
    void SIGNALUartLayerError(mDBusError error,QString errorMsg);
public slots:
    void SLOTaddDataToList(QByteArray data);
private slots:
    void SLOTSendDataTimerFun();
    
};

#endif // UARTLAYERDBUS_H
