#ifndef MYDBUSSEND_H
#define MYDBUSSEND_H

#include <QObject>
#include <QByteArray>
#include <QDBusInterface>
#include <QDBusReply>
#include "DataLayerDbusReceive.h"

class DataLayerDbusSend : public QObject
{
    Q_OBJECT
public:
    explicit DataLayerDbusSend(QObject *parent = 0);
    QDBusInterface *iface;
signals:
    void SIGNALReturnValue(bool ok);
    void SIGNALDataLayerError(mDBusError error,QString errorMsg);
public slots:
    void SLOTDataSend(QByteArray data);

};

#endif // MYDBUSSEND_H
