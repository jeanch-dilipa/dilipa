QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_tgui.cpp \
    ../untitled8/main.cpp \
    ../untitled8/widget.cpp

SUBDIRS += \
    ../untitled8/untitled8.pro

FORMS += \
    ../untitled8/widget.ui

HEADERS += \
    ../untitled8/widget.h
