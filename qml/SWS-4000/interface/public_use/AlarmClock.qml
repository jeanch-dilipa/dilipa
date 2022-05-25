import QtQuick 2.0
import QtQuick.Window 2.3
import QtQml 2.3
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.5

import "../Custom_model"

Window
{
    id:rootw
    width: 420
    height: 420
    flags: Qt.FramelessWindowHint
    opacity: 0.9
    color: "#00000000"

    DropShadow
    {
        anchors.fill: root
        horizontalOffset: 5
        verticalOffset: 5
        source: root
        color: "#a8a8a8a8"
        samples: 5
        radius: 5
    }
    DropShadow
    {
        anchors.fill: root
        horizontalOffset: -5
        verticalOffset: 5
        source: root
        color: "#a8a8a8a8"
        samples: 5
        radius: 5
    }
    DropShadow
    {
        anchors.fill: root
        horizontalOffset: -5
        verticalOffset: -5
        source: root
        color: "#a8a8a8a8"
        samples: 5
        radius: 5
    }
    DropShadow
    {
        anchors.fill: root
        horizontalOffset: 5
        verticalOffset: -5
        source: root
        color: "#a8a8a8a8"
        samples: 5
        radius: 5
    }

    Rectangle
    {
        id:root
        width: rootw.width - 20
        height: rootw.height - 20
        anchors.centerIn: parent
        radius: 10

        Rectangle
        {
            id:progress
            width: parent.width
            height: parent.height*0.7
            radius: 10

            property var value: 60
            property var snap_value: 60

            onValueChanged:
            {
                canvas.requestPaint()
            }

            Canvas
            {
                id:canvas
                anchors.fill: parent
                onPaint:
                {
                    var ctx = getContext("2d")
                    ctx.clearRect(0, 0, canvas.width, canvas.height);
                    ctx.strokeStyle =Qt.rgba(1-progress.value/progress.snap_value,progress.value/progress.snap_value,1-progress.value/progress.snap_value,1)
                    ctx.lineWidth = 10
                    ctx.beginPath()
                    ctx.arc(canvas.width/2,canvas.height/2,canvas.width/3-ctx.lineWidth,-Math.PI/2,3/2 * Math.PI - (progress.snap_value - progress.value) / progress.snap_value * 2 * Math.PI,false)
                    ctx.stroke()
                }
            }

            Label
            {
                id:timeclockalarm
                anchors.centerIn: parent
                text: progress.value === 0 ? qsTr("定时时间到！！！") : Math.floor(progress.value / 600).toString() + (Math.floor(progress.value / 60) % 10).toString() + qsTr(":") + Math.floor((progress.value % 60) / 10).toString() + ((progress.value % 60) % 10).toString()
                font.family: "Arial"
                font.weight: Font.Thin
                font.pointSize: 35
            }

            CustomButton
            {
                width: parent.width/7
                height: width
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                backgroundradius: width/2
                text: qsTr("+")
                textfontpointsize: 45

                onClicked:
                {
                    listmodel.append({"time_value": 1})
                }
            }
        }

        Connections
        {
            target: timecontrol.currentTimer
            function onValueChanged()
            {
                progress.value = timecontrol.currentTimer.value
            }
        }
        Connections
        {
            target: timecontrol.keyview
            onResultChanged:
            {
                timecontrol.currentTimer.snap_value = timecontrol.keyview.result * 60
            }
        }

        Rectangle
        {
            id:timecontrol
            width: parent.width
            height: parent.height*0.3
            anchors.top: progress.bottom
            radius: 10

            property CustomButton currentTimer
            property IntelligentKeyboard keyview

            ListView
            {
                id:listview
                anchors.fill: parent
                model:listmodel
                clip: true
                delegate: Rectangle
                {
                    id:delege
                    width: parent.width
                    height: timecontrol.height/3
                    radius: 10
                    CustomButton
                    {
                        id:timeset
                        width: parent.width/3
                        height: parent.height - 10
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 15
                        backgroundradius: 10
                        text: snap_value / 60
                        value: time_value * 60
                        snap_value: time_value * 60
                        textfontpointsize: 12
                        max_value: 59
                        min_value: 1
                        description: qsTr("定时器时间")

                        onSnap_valueChanged:
                        {
                            value = snap_value
                            timecontrol.currentTimer = this
                            progress.value = timeset.value
                            progress.snap_value = timeset.snap_value
                        }
                        onClicked:
                        {
                            timecontrol.currentTimer = this
                            progress.value = timeset.value
                            progress.snap_value = timeset.snap_value
                        }
                        onDoubleClicked:
                        {
                            setTimerValue(description,max_value,min_value)
                        }
                    }
                    Label
                    {
                        text: qsTr("min")
                        font.pointSize: 12
                        anchors.centerIn: parent
                    }
                    CustomSwitch
                    {
                        id:switchcontrol
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 15
                        onPositionChanged:
                        {
                            if(position === 1)
                            {
                                delege.color = "white"
                                timeset.value = timeset.snap_value
                                timer.start()
                                timecontrol.currentTimer = timeset
                                progress.value = timeset.value
                                progress.snap_value = timeset.snap_value
                            }
                            else
                            {
                                timer.stop()
                            }
                        }
                    }
                    Timer
                    {
                        id:timer
                        interval: 1000
                        repeat: true
                        onTriggered:
                        {
                            timeset.value --
                            if(timeset.value <= 0)
                            {
                                if(rootw.visible === false)
                                {
                                    rootw.visible = true
                                }
                                timer.stop()
                                delege.color = "#0acf97"
                                switchcontrol.checked = false
                            }
                        }
                    }
                }
            }
            ListModel
            {
                id:listmodel

                ListElement{time_value:1}
                ListElement{time_value:5}
                ListElement{time_value:10}
                ListElement{time_value:15}
                ListElement{time_value:20}
            }
        }
    }

    function setTimerValue(itemName,itemmaxLimit,itemminLimit)
    {
        if(timecontrol.keyview)
        {
            timecontrol.keyview.destroy()
        }
        var view = Qt.createComponent("qrc:/interface/public_use/IntelligentKeyboard.qml")
        timecontrol.keyview = view.createObject(root)
        timecontrol.keyview.itemName = itemName
        timecontrol.keyview.itemmaxLimit = itemmaxLimit
        timecontrol.keyview.itemminLimit = itemminLimit
    }
}
