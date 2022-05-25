#-------------------------------------------------
#
# Project created by QtCreator 2014-02-20T11:32:25
#
#-------------------------------------------------

QT       += core gui
QT       += dbus

TARGET = UartLayerDbusLibUse
TEMPLATE = app


SOURCES += main.cpp\
        uartlayerlibusewindow.cpp

HEADERS  += uartlayerlibusewindow.h

FORMS    += uartlayerlibusewindow.ui


unix:!macx:!symbian: LIBS += -L$$PWD/../../../../../DbusLib/UartLayerDbus/UartLayerDbusLib/UartLayerDbusLib-build-desktop-Desktop_Qt_4_8_0_for_GCC__Qt_SDK____/ -lUartLayerDbusLib

INCLUDEPATH += $$PWD/../../../../../DbusLib/UartLayerDbus/UartLayerDbusLib/UartLayerDbusLib-build-desktop-Desktop_Qt_4_8_0_for_GCC__Qt_SDK____
DEPENDPATH += $$PWD/../../../../../DbusLib/UartLayerDbus/UartLayerDbusLib/UartLayerDbusLib-build-desktop-Desktop_Qt_4_8_0_for_GCC__Qt_SDK____
