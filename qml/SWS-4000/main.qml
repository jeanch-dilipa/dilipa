import QtQuick.Controls 2.5
import QtQuick 2.9
import QtQml 2.3

import "./interface/public_use/"

ApplicationWindow
{
    id:rootWindow
    width: 1024//$G_DATA.m_rootWindowWidth
    height: 768//$G_DATA.m_rootWindowHeight
    visible: false

    /*无边框窗口*/
//    flags: Qt.FramelessWindowHint

    property var currentview

    Connections
    {
        target: DISPATHER
        onSignal_createStartInterface:
        {
            var view = Qt.createComponent("qrc:/interface/StartInterface.qml")
            currentview = view.createObject(rootWindow)
            rootWindow.visible = true
        }
        onSignal_createSystemSelfCheck:
        {
            currentview.destroy()
            var view = Qt.createComponent("qrc:/interface/systemselfcheck/SystemSelfCheck.qml")
            currentview = view.createObject(rootWindow)
        }
        onSignal_createSchema:
        {
            currentview.destroy()
            var view = Qt.createComponent("qrc:/interface/schema/Schema.qml")
            currentview = view.createObject(rootWindow)
        }
        onSignal_createDetectInterface:
        {
            currentview.destroy()
            var view = Qt.createComponent("qrc:/interface/detect/Detect.qml")
            currentview = view.createObject(rootWindow)
        }
        onSignal_createCorrectInterface:
        {
            currentview.destroy()
            var view = Qt.createComponent("qrc:/interface/correct/Correct.qml")
            currentview = view.createObject(rootWindow)
        }
    }

    Top_toolBar
    {
        id:topToolBar
    }

    AlarmInfoPop_Up
    {
        id:alarmInfo
        visible: false
    }

    Bottom_toolBar
    {
        id:bottomToolBar
        anchors.bottom: parent.bottom
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
