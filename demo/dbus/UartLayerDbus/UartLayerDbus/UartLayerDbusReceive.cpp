#include "UartLayerDbusReceive.h"
#include <QMetaType>

UartLayerDbusReceive::UartLayerDbusReceive(QObject *parent) :
    QObject(parent)
{

    qRegisterMetaType<mDBusError>("mDBusError");

    // 用于建立到session bus的连接
    QDBusConnection bus = QDBusConnection::sessionBus();
    // 在session bus上注册名为"com.dbus.datalayer"的service
    if (!bus.registerService("com.dbus.uartlayer"))
    {
        emit SIGNALUartLayerError(DBuRegisterServiceError,bus.lastError().message());
        return;
    }

    // 注册名为"/datalayerDbus/registry"的object。
    // "QDBusConnection::ExportAllSlots"表示把类DbusUartLayer的所有Slot都导出为这个Object的method
    bus.registerObject("/uartlayerDbus/registry", this,
                       QDBusConnection::ExportAllSlots);
}

void UartLayerDbusReceive::SLOTUartLayerReceiveFun(QByteArray data)
{
    emit SIGNALReceivedData(data);
}
