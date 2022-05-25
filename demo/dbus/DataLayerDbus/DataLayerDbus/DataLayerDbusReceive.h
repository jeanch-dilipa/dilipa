#ifndef MYDBUS_H
#define MYDBUS_H

#include <QObject>
#include <QtDBus/QDBusConnection>
#include <QDebug>
#include <QDBusError>
#include <QDBusReply>
#include <QDBusInterface>
#include <QByteArray>


enum mDBusError
{
    DBuRegisterServiceError,                            //注册服务时发生错误
    DBusInterfaceConnectionError                       //Interface连接到服务时发生错误
};


class DataLayerDbusReceive : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.dbus.datalayer.registry")
public:
    explicit DataLayerDbusReceive(QObject *parent = 0);

signals:
    void SIGNALReceivedData(QByteArray data);
    void SIGNALDataLayerError(mDBusError error,QString errorMsg);
public slots:
    void SLOTDataLayerReceiveFun(QByteArray data);
};

#endif // MYDBUS_H
