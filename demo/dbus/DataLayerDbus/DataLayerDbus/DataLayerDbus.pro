#-------------------------------------------------
#
# Project created by QtCreator 2014-02-19T14:49:44
#
#-------------------------------------------------

QT       += core gui
QT       += dbus

TARGET = DataLayerDbus
TEMPLATE = app


SOURCES += main.cpp\
        datalaywindow.cpp \
    DataLayerDbusReceive.cpp \
    DataLayerDbusSend.cpp \
    datalayerdbus.cpp

HEADERS  += datalaywindow.h \
    DataLayerDbusReceive.h \
    DataLayerDbusSend.h \
    datalayerdbus.h

FORMS    += datalaywindow.ui
