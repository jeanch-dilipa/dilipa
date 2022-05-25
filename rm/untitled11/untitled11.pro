QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_test.cpp \
    win.cpp

FORMS +=

HEADERS += \
    win.h
