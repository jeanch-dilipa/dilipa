#-------------------------------------------------
#
# Project created by QtCreator 2021-05-28T08:39:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SWS6000UITest
TEMPLATE = app


SOURCES += main.cpp\
    imagepreviewer.cpp \
    pagedesignpreviewer.cpp \
    effects/qinnershadow.cpp \
    texturetest.cpp \
    widgets.cpp \
    effects/qcustompushbutton.cpp \
    groupchoosepage.cpp

HEADERS  += \
    imagepreviewer.h \
    pagedesignpreviewer.h \
    effects/qinnershadow.h \
    texturetest.h \
    widgets.h \
    effects/qcustompushbutton.h \
    groupchoosepage.h

FORMS    += \
    imagepreviewer.ui \
    pagedesignpreviewer.ui \
    texturetest.ui \
    widgets.ui \
    groupchoosepage.ui

RESOURCES += \
    icons.qrc \
    textures.qrc
