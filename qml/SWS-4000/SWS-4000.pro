QT += quick serialport sql

CONFIG += c++11  #console添加后不支持彩色输出
UI_DIR += ./UI
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        controllayer/alarmcontrol.cpp \
        controllayer/crc.cpp \
        controllayer/datadealthread.cpp \
        controllayer/modelboard.cpp \
        controllayer/serialportcontrol.cpp \
        controllayer/sqlbase.cpp \
        dispatcher.cpp \
        global/publicdata.cpp \
        interface/correct/correct.cpp \
        interface/detect/detect.cpp \
        interface/startinterface.cpp \
        interface/systemselfcheck/systemselfcheck.cpp \
        main.cpp

RESOURCES += qml.qrc \
    resource.qrc

LIBS += -lcrypt32
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    common/DebugLog.h \
    common/common.h \
    common/modulecommon.h \
    common/realInfoItem.h \
    common/systemAlarmCodes.h \
    common/systemSelfCheckItem.h \
    controllayer/alarmcontrol.h \
    controllayer/crc.h \
    controllayer/datadealthread.h \
    controllayer/modelboard.h \
    controllayer/serialportcontrol.h \
    controllayer/sqlbase.h \
    dispatcher.h \
    global/publicdata.h \
    interface/correct/correct.h \
    interface/detect/detect.h \
    interface/startinterface.h \
    interface/systemselfcheck/systemselfcheck.h

DISTFILES +=

FORMS +=
