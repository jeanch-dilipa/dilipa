#-------------------------------------------------
#
# Project created by QtCreator 2014-02-19T15:47:06
#
#-------------------------------------------------

QT       += core gui
QT       += dbus

TARGET = UartLayerDbus
TEMPLATE = app


SOURCES += main.cpp\
        uartlayerdbuswindow.cpp \
    UartLayerDbusReceive.cpp \
    UartLayerDbusSend.cpp \
    uartlayerdbus.cpp

HEADERS  += uartlayerdbuswindow.h \
    UartLayerDbusReceive.h \
    UartLayerDbusSend.h \
    uartlayerdbus.h

FORMS    += uartlayerdbuswindow.ui
