#include "DataLayerDbusSend.h"
#include <QThread>
#include <sys/types.h>
#include <unistd.h>
#include <QDebug>
#include <QTime>

DataLayerDbusSend::DataLayerDbusSend(QObject *parent) :
    QObject(parent)
{
    //初始化
    iface = NULL;
}

void DataLayerDbusSend::SLOTDataSend(QByteArray data)
{
    if(NULL == iface)
    {
        // 创建QDBusInterface
        iface = new QDBusInterface( "com.dbus.uartlayer", "/uartlayerDbus/registry",
                              "com.dbus.uartlayer.registry", QDBusConnection::sessionBus());
    }
    if (!iface->isValid())//如果连接出错，发出出错信号
    {
        emit SIGNALDataLayerError(DBusInterfaceConnectionError,QDBusConnection::sessionBus().lastError().message());
        return;
    }
    // 呼叫远程的SLOTUartLayerReceiveData，参数为recData
    QDBusReply<void> reply = iface->call(QDBus::NoBlock,"SLOTUartLayerReceiveFun",data);

//    reply.waitForFinished();
    if (!reply.isValid()) //如果调用出错
    {
        emit SIGNALReturnValue(false);
    }
    else
    {
        emit SIGNALReturnValue(true);
    }
}
