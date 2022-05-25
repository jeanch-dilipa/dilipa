import QtQuick 2.5
import QtQuick.Controls 2.5
import QtQuick.Window 2.3
import QtGraphicalEffects 1.0

import "../Custom_model"

Window
{
    id:rootw
    width: 1024
    height: 608

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
        clip: true

        Rectangle
        {
            id:funtion
            width: root.width/10
            height: root.height
            anchors.left: root.left
            radius: 10

            ListView
            {
                id:listview
                anchors.fill: parent
                model: listmodel
                spacing: 10
                delegate:CustomButton
                {
                    width: 100
                    height: 60
                    text: qsTr(name)
                    textfontpointsize: 15
                    backgroundradius: 15
                    backgroundDefaultColor: "#0acf97"
                    spreadColor:"#a8a8a8a8"
                    onClicked:
                    {
                        judgePageCreate(index)
                    }
                }
            }
            ListModel
            {
                id:listmodel
                ListElement{name:"alarm_on_off"}
                ListElement{name:"alarm_limit"}
                ListElement{name:"alarm_list"}
                ListElement{name:"开关"}
                ListElement{name:"开关";}
                ListElement{name:"开关"}
                ListElement{name:"开关"}
            }
        }

        SwipeView
        {
            id:view
            width: root.width/10*9
            height: root.height
            anchors.left: funtion.right
            orientation: Qt.Vertical

            Page
            {
                AlarmOnOffPage
                {
                    id:on_off
                }
            }
            Page
            {
                AlarmLimitPage
                {
                    id:limit
                }
            }
            Page
            {
                AlarmList
                {
                    id:list
                }
            }
            Page
            {
                Rectangle
                {
                    anchors.fill: parent
                    color: "red"
                    Text
                    {
                        text: qsTr("开发中......")
                    }
                }
            }
            Page
            {
                Rectangle
                {
                    anchors.fill: parent
                    color: "blue"
                    Text
                    {
                        text: qsTr("开发中......")
                    }
                }
            }
            Page
            {
                Rectangle
                {
                    anchors.fill: parent
                    color: "yellow"
                    Text
                    {
                        text: qsTr("开发中......")
                    }
                }
            }
        }
    }

    function judgePageCreate(Index)
    {
        view.currentIndex = Index
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
