#ifndef DATALAYERDBUS_H
#define DATALAYERDBUS_H

#include <QObject>
#include "DataLayerDbusReceive.h"
#include "DataLayerDbusSend.h"
#include <QByteArray>
#include <QThread>
#include <QTimer>
#include <QVector>

class DataLayerDbus : public QObject
{
    Q_OBJECT
private:
    QVector<QByteArray> sendDataList;
    QTimer *m_sendTimer;
public:
    explicit DataLayerDbus(QObject *parent = 0);

    DataLayerDbusReceive *m_DataLayerDbusReceive;
    DataLayerDbusSend *m_DataLayerDbusSend;

    QThread *m_ReceiveThread;
    QThread *m_SendThread;
    
signals:
    void SIGNALReceData(QByteArray data);
    void SIGNALSendData(QByteArray data);
    void SIGNALSendRetValue(bool ok);
    void SIGNALDataLayerError(mDBusError error,QString errorMsg);
public slots:
    void SLOTaddSendDataToList(QByteArray data);
private slots:
    void SLOTSendDataTimerFun();
    
};

#endif // DATALAYERDBUS_H
