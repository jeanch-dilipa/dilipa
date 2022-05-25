#-------------------------------------------------
#
# Project created by QtCreator 2014-02-20T10:55:53
#
#-------------------------------------------------

QT       += core gui
QT       += dbus

TARGET = DataLayerDbusLibUse
TEMPLATE = app


SOURCES += main.cpp\
        datalayerdbuswindow.cpp

HEADERS  += datalayerdbuswindow.h

FORMS    += datalayerdbuswindow.ui

unix:!macx:!symbian: LIBS += -L$$PWD/../../../../DbusLib/DataLayerDbus/DataLayerDbusLib-build-desktop-Desktop_Qt_4_8_0_for_GCC__Qt_SDK____/ -lDataLayerDbusLib

INCLUDEPATH += $$PWD/../../../../DbusLib/DataLayerDbus/DataLayerDbusLib-build-desktop-Desktop_Qt_4_8_0_for_GCC__Qt_SDK____
DEPENDPATH += $$PWD/../../../../DbusLib/DataLayerDbus/DataLayerDbusLib-build-desktop-Desktop_Qt_4_8_0_for_GCC__Qt_SDK____
