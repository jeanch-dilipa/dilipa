#-------------------------------------------------
#
# Project created by QtCreator 2020-06-30T14:53:30
#
#-------------------------------------------------

QT       += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SWSModuleBoardSimulator
TEMPLATE = app


SOURCES += main.cpp\
    simulation/boardsimulation/antisystemsimulation.cpp \
    simulation/boardsimulation/powersystemsimulation.cpp \
    interface/mainwindow.cpp \
    uart/uart485.cpp \
    interface/commonItem/customlinklabel.cpp \
    interface/toolItem/serialparadialog.cpp \
    uart/crc.cpp \
    common/publicdata.cpp \
    simulation/simulationmanager.cpp \
    simulation/randomdatagenerator.cpp \
    interface/centerInterface/bloodsysteminterface.cpp \
    interface/commonItem/customswitchbutton.cpp \
    interface/toolItem/valuemodeselectdialog.cpp \
    simulation/boardsimulation/bloodsystemsimulation.cpp \
    simulation/boardsimulation/boardsimulationbase.cpp \
    simulation/boardsimulation/liquidsystemsimulation.cpp \
    interface/centerInterface/liquidsysteminterface.cpp \
    interface/centerInterface/systeminterfacebase.cpp \
    simulation/boardsimulation/mixultrasystemsimulation.cpp \
    interface/centerInterface/antisysteminterface.cpp \
    interface/centerInterface/mixultrasysteminterface.cpp \
    interface/centerInterface/powersysteminterface.cpp \
    interface/centerInterface/keylampinterface.cpp \
    simulation/boardsimulation/keylampsimulation.cpp \
    interface/centerInterface/btvrcminterface.cpp \
    simulation/boardsimulation/btvrcmsimulation.cpp

HEADERS  += \
    simulation/boardsimulation/antisystemsimulation.h \
    simulation/boardsimulation/powersystemsimulation.h \
    common/common.h \
    interface/mainwindow.h \
    uart/uart485.h \
    protocol/protocol.h \
    interface/commonItem/customlinklabel.h \
    interface/toolItem/serialparadialog.h \
    interface/commonItem/custommessagelabel.h \
    uart/crc.h \
    common/publicdata.h \
    simulation/simulationmanager.h \
    protocol/sws6000/bloodtrailboardprotocol.h \
    protocol/sws4000/protoPacket4000.h \
    protocol/sws6000/protoPacket6000.h \
    protocol/sws6000/ureasensorboardprotocol.h \
    simulation/randomdatagenerator.h \
    interface/centerInterface/bloodsysteminterface.h \
    interface/commonItem/customswitchbutton.h \
    interface/toolItem/valuemodeselectdialog.h \
    simulation/simulationsetdata.h \
    simulation/boardsimulation/bloodsystemsimulation.h \
    simulation/boardsimulation/boardsimulationbase.h \
    protocol/sws6000/liquiddriverboarprotocol.h \
    protocol/sws6000/mixultraboardprotocol.h \
    protocol/sws6000/heparinpumpboardprotocol.h \
    protocol/sws6000/powerboardprotocol.h \
    protocol/sws6000/monitoringboardprotocol.h \
    simulation/boardsimulation/liquidsystemsimulation.h \
    interface/centerInterface/liquidsysteminterface.h \
    interface/centerInterface/systeminterfacebase.h \
    simulation/boardsimulation/mixultrasystemsimulation.h \
    interface/centerInterface/antisysteminterface.h \
    interface/centerInterface/mixultrasysteminterface.h \
    interface/centerInterface/powersysteminterface.h \
    interface/centerInterface/keylampinterface.h \
    common/simulationdatacode.h \
    simulation/boardsimulation/keylampsimulation.h \
    interface/centerInterface/btvrcminterface.h \
    simulation/boardsimulation/btvrcmsimulation.h \
    protocol/sws6000/bloodtempvolumeboardprotocol.h \
    protocol/sws6000/airdetectormoduletypes.h

FORMS += \
    interface/mainwindow.ui \
    interface/centerInterface/bloodsysteminterface.ui \
    interface/toolItem/valuemodeselectdialog.ui \
    interface/centerInterface/liquidsysteminterface.ui \
    interface/centerInterface/antisysteminterface.ui \
    interface/centerInterface/mixultrasysteminterface.ui \
    interface/centerInterface/powersysteminterface.ui \
    interface/centerInterface/keylampinterface.ui \
    interface/centerInterface/btvrcminterface.ui

RESOURCES += \
    images/images.qrc

RC_FILE += \
    images/app_icon.rc

TRANSLATIONS += SWSModuleBoardSimulator_English.ts
