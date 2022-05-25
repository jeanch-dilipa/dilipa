#ifndef MYDBUSSEND_H
#define MYDBUSSEND_H

#include <QObject>
#include <QByteArray>
#include <QDBusInterface>
#include <QDBusReply>
#include "UartLayerDbusReceive.h"

class UartLayerDbusSend : public QObject
{
    Q_OBJECT
public:
    explicit UartLayerDbusSend(QObject *parent = 0);
    QDBusInterface *iface;
signals:
    void SIGNALSendReturnValue(bool ok);
    void SIGNALUartLayerError(mDBusError error,QString errorMsg);
public slots:
    void SLOTDataSend(QByteArray data);
    
};

#endif // MYDBUSSEND_H
