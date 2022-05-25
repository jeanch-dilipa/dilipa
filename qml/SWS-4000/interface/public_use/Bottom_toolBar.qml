import QtQuick 2.9
import QtQml 2.3
import QtQuick.Controls 2.5

import "../Custom_model"

Rectangle
{
    id:root
    width: 1024
    height: 68

    Rectangle
    {
        id:sysTime
        width: parent.width/8
        height: parent.height
        Text
        {
            id:year
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 5
            text: Qt.formatDateTime(new Date(),"yyyy-MM-dd \n   ddd")
            font.pointSize: 12
        }
        Text
        {
            id:time
            anchors.top: year.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            text: Qt.formatDateTime(new Date(),"hh::mm::ss.zzz")
            font.pointSize: 10
        }

        Timer
        {
            id:brushTime
            running: true
            interval: 10
            repeat: true
            onTriggered:
            {
                year.text = Qt.formatDateTime(new Date(),"yyyy-MM-dd \n   ddd")
                time.text = Qt.formatDateTime(new Date(),"hh::mm::ss.zzz")
            }
        }
    }

    Rectangle
    {
        id:clock
        width: height
        height: parent.height
        anchors.left: sysTime.right
        Image
        {
            id: clockimage
            anchors.fill: parent
            scale: 0.8
            source: "qrc:/new/prefix1/image/clock_off.png"
        }

        property var view

        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                alarmclock.visible = alarmclock.visible ? false : true
            }
        }
    }

    AlarmClock
    {
        id:alarmclock
    }

    Rectangle
    {
        id:theblu
        width: height
        height: parent.height
        anchors.left: clock.right
        Image
        {
            id: thebluimage
            anchors.fill: parent
            scale: 0.8
            source: "qrc:/new/prefix1/image/theblu.png"
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                var view = Qt.createComponent("qrc:/interface/public_use/Screensaver.qml").createObject(rootWindow)
                view.show()
            }
        }
    }

    CustomButton
    {
        id:alarm
        width: root.width/8
        height: root.height/3*2
        anchors.verticalCenter: root.verticalCenter
        anchors.right: real.left
        anchors.rightMargin: width/8
        textfontpointsize: 25
        backgroundradius: width/4
        text: qsTr("alarm");

        property bool distined: false
        property var currentview
        onClicked:
        {
            if(distined === true)
            {
                currentview.destroy()
                distined = false
                alarm.spreadColor = "#a8a8a8a8"
            }
            else
            {
                var view = Qt.createComponent("qrc:/interface/public_use/AlarmSwitch.qml")
                currentview = view.createObject(root)
                currentview.x = rootWindow.x
                currentview.y = rootWindow.y + 90
                currentview.show()
                distined = true
                alarm.spreadColor = "red"
            }
        }
    }
    CustomButton
    {
        id:real
        width: root.width/8
        height: root.height/3*2
        anchors.verticalCenter: root.verticalCenter
        anchors.right: para.left
        anchors.rightMargin: width/8
        textfontpointsize: 20
        backgroundradius: width/4
        text: qsTr("realinfo");

        property bool distined: false
        property var currentview
        onClicked:
        {
            if(distined === true)
            {
                currentview.destroy()
                distined = false
                real.spreadColor = "#a8a8a8a8"
            }
            else
            {
                var view = Qt.createComponent("qrc:/interface/public_use/Realinfo.qml")
                currentview = view.createObject(root)
                currentview.x = rootWindow.x
                currentview.y = rootWindow.y + 90
                currentview.show()
                distined = true
                real.spreadColor = "red"
            }
        }
    }

    CustomButton
    {
        id:para
        width: root.width/8
        height: root.height/3*2
        anchors.verticalCenter: root.verticalCenter
        anchors.right: systempara.left
        anchors.rightMargin: width/8
        backgroundDefaultColor: "#0acf97"
        textfontpointsize: 20
        backgroundradius: width/4
        text: qsTr("parameter")

        property bool distined: false
        property var currentview
        onClicked:
        {
            if(distined === true)
            {
                currentview.destroy()
                distined = false
                para.spreadColor = "#a8a8a8a8"
            }
            else
            {
                var view = Qt.createComponent("qrc:/interface/public_use/Parameter.qml")
                currentview = view.createObject(root)
                currentview.x = rootWindow.x
                currentview.y = rootWindow.y + 90
                currentview.show()
                distined = true
                para.spreadColor = "red"
            }
        }
    }

    CustomButton
    {
        id:systempara
        width: root.width/8
        height: root.height/3*2
        anchors.verticalCenter: root.verticalCenter
        anchors.right: root.right
        anchors.rightMargin: width/8
        textfontpointsize: 20
        backgroundradius: width/4
        text: qsTr("systemparameter")

        property bool distined: false
        property var currentview
        onClicked:
        {
            if(distined === true)
            {
                currentview.destroy()
                distined = false
                systempara.spreadColor = "#a8a8a8a8"
            }
            else
            {
                var view = Qt.createComponent("qrc:/interface/public_use/SystemParamerter.qml")
                currentview = view.createObject(root)
                currentview.x = rootWindow.x
                currentview.y = rootWindow.y + 90
                currentview.show()
                distined = true
                systempara.spreadColor = "red"
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
