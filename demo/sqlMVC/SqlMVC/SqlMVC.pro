#-------------------------------------------------
#
# Project created by QtCreator 2014-12-17T08:55:14
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SqlMVC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sqlthreadfirst.cpp \
    sqlthreadsecond.cpp

HEADERS  += mainwindow.h \
    sqlthreadfirst.h \
    sqlthreadsecond.h

FORMS    += mainwindow.ui
