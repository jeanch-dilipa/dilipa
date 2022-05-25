QT       += core gui serialport sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    datadeal/common/publicdata.cpp \
    datadeal/datadeal.cpp \
    datadeal/modelboard/moduleboard.cpp \
    datadeal/modelboard/moduleboardbase.cpp \
    datadeal/sqlbase/sqlbase.cpp \
    interface/debuginterface/debuginterface.cpp \
    interface/maininterface/functioninterface/functioninterface.cpp \
    interface/maininterface/maininterface.cpp \
    interface/maininterface/selfcheckinterface/selfcheckinterface.cpp \
    interface/startinterface/startinterface.cpp \
    interface/tool/pushButton/pushbuttonbase.cpp \
    interface/widgetmanager.cpp \
    main.cpp \
    network/network.cpp \
    systemmanager.cpp \
    uart/crc/crc.cpp \
    uart/port/uart485.cpp \
    uart/uart.cpp

HEADERS += \
    common/common.h \
    common/debug.h \
    datadeal/common/functioncode.h \
    datadeal/common/modulecommon.h \
    datadeal/common/modulestruct.h \
    datadeal/common/moduletype.h \
    datadeal/common/publicdata.h \
    datadeal/datadeal.h \
    datadeal/modelboard/moduleboard.h \
    datadeal/modelboard/moduleboardbase.h \
    datadeal/sqlbase/sqlbase.h \
    interface/common/interfacedata.h \
    interface/debuginterface/debuginterface.h \
    interface/maininterface/functioninterface/functioninterface.h \
    interface/maininterface/maininterface.h \
    interface/maininterface/selfcheckinterface/selfcheckinterface.h \
    interface/startinterface/startinterface.h \
    interface/tool/pushButton/pushbuttonbase.h \
    interface/widgetmanager.h \
    network/network.h \
    systemmanager.h \
    uart/crc/crc.h \
    uart/port/uart485.h \
    uart/uart.h

FORMS += \
    interface/debuginterface/debuginterface.ui \
    interface/maininterface/functioninterface/functioninterface.ui \
    interface/maininterface/maininterface.ui \
    interface/maininterface/selfcheckinterface/selfcheckinterface.ui \
    interface/startinterface/startinterface.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
