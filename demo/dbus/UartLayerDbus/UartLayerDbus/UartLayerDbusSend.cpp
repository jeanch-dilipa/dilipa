#include "UartLayerDbusSend.h"
#include <QThread>
#include <sys/types.h>
#include <unistd.h>
#include <QDebug>
#include <QDateTime>


UartLayerDbusSend::UartLayerDbusSend(QObject *parent) :
    QObject(parent)
{
    //初始化
    iface = NULL;
}

void UartLayerDbusSend::SLOTDataSend(QByteArray data)
{
    //    qDebug()<<"sub process id:"<<getpid();

    // 创建QDBusInterface
    if(NULL == iface)
    {
        // 创建QDBusInterface
        iface = new QDBusInterface( "com.dbus.datalayer", "/datalayerDbus/registry",
                                    "com.dbus.datalayer.registry", QDBusConnection::sessionBus());
    }
    if (!iface->isValid())//如果连接出错，发出出错信号
    {
        emit SIGNALUartLayerError(DBusInterfaceConnectionError,QDBusConnection::sessionBus().lastError().message());
        return;
    }
    // 呼叫远程的SLOTUartLayerReceiveData，参数为recData
    QDBusReply<void> reply = iface->call(QDBus::NoBlock,"SLOTDataLayerReceiveFun", data);
    //    reply.waitForFinished();
    if (!reply.isValid())//如果调用出错
    {
        emit SIGNALSendReturnValue(false);
    }
    else
    {
        emit SIGNALSendReturnValue(true);
    }
}
