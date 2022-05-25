QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    center.cpp \
    curve.cpp \
    heteroideus.cpp \
    interface.cpp \
    main.cpp \
    mainwidget.cpp \
    mp4.cpp \
    pressuremonitor.cpp \
    tablewidget.cpp

HEADERS += \
    center.h \
    curve.h \
    heteroideus.h \
    interface.h \
    mainwidget.h \
    mp4.h \
    pressuremonitor.h \
    tablewidget.h

FORMS += \
    center.ui \
    curve.ui \
    heteroideus.ui \
    interface.ui \
    mainwidget.ui \
    mp4.ui \
    pressuremonitor.ui \
    tablewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
