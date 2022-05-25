import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Rectangle
{
    id:window
    visible: true
    width: 820//1220
    height: 520//820
    color: "#00000000"
    anchors.centerIn: parent

    // 左边缘及上边缘阴影
    DropShadow {
           anchors.fill: all_application
           horizontalOffset: -5
           verticalOffset: -5
           radius: 12.0
           samples: 25
           color: "#20000000"
           spread: 0.0
           source: all_application
    }
    // 右边缘及下边缘阴影
    DropShadow {
            anchors.fill: all_application
            horizontalOffset: 5
            verticalOffset: 5
            radius: 12.0
            samples: 25
            color: "#20000000"
            spread: 0.0
            source: all_application
    }

    Rectangle
    {
        id:all_application
        width: 800
        height: 500
        x:0
        y:0
        signal editor()
        signal editorcancel()

        Rectangle
        {
            id:quit
            width: 20
            height: 20
            anchors.right: all_application.right
            anchors.top: all_application.top
            anchors.topMargin: 15
            anchors.rightMargin: 15
            z:0
//移入变色
            MouseArea
            {
                anchors.fill:quit
                hoverEnabled: true
                onClicked: window.destroy()
                onEntered:
                {
                    quit1.border.color="red"
                    quit2.border.color="red"
                }
                onExited:
                {
                     quit1.border.color="gray"
                     quit2.border.color="gray"
                }
            }

            Rectangle
            {
                id:quit1
                width: 18
                height: 2
                rotation: 45
                border.color: "gray"
                border.width: 2
                anchors.centerIn: quit
            }
            Rectangle
            {
                id:quit2
                width: 18
                height: 2
                rotation: -45   //旋转
                border.color: "gray"
                border.width: 2
                anchors.centerIn: quit
            }
        }
        Rectangle
        {
            id:up
            width: parent.width-40
            height: parent.height-down.height
            anchors.left: parent.left
            clip:true   //超界不显示
            Text
            {
                x:50
                y:25
                text: qsTr("application")
                font.pixelSize: 20
                font.family:"Arial"
            }
            Rectangle
            {
                id:app00
                x: 80
                y: 74
                width: 125
                height: 125
                Rectangle
                {
                    id:app000
                    width: 60
                    height: 80
                    color: Qt.rgba(Math.random(),Math.random(),Math.random())
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text
                {
                    text: qsTr("application")
                    font.pixelSize: 15
                    font.family: "Arial"
                    anchors.top: app000.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Rectangle
            {
                id: app01
                x: app00.x+width
                y: app00.y
                width: 125
                height: 125
                Rectangle
                {
                    id:app001
                    width: 60
                    height: 80
                    color: Qt.rgba(Math.random(),Math.random(),Math.random())
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text
                {
                    text: qsTr("application")
                    font.pixelSize: 15
                    font.family: "Arial"
                    anchors.top: app001.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Rectangle
            {
                id: app02
                x: app01.x+width
                y: app00.y
                width: 125
                height: 125
                Rectangle
                {
                    id:app002
                    width: 60
                    height: 80
                    color: Qt.rgba(Math.random(),Math.random(),Math.random())
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text
                {
                    text: qsTr("application")
                    font.pixelSize: 15
                    font.family: "Arial"
                    anchors.top: app002.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Rectangle
            {
                id: app03
                x: app02.x+width
                y: app00.y
                width: 125
                height: 125
                Rectangle
                {
                    id:app003
                    width: 60
                    height: 80
                    color: Qt.rgba(Math.random(),Math.random(),Math.random())
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text
                {
                    text: qsTr("application")
                    font.pixelSize: 15
                    font.family: "Arial"
                    anchors.top: app003.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Rectangle
            {
                id: app04
                x: app03.x+width
                y: app00.y
                width: 125
                height: 125
                Rectangle
                {
                    id:app004
                    width: 60
                    height: 80
                    color: Qt.rgba(Math.random(),Math.random(),Math.random())
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text
                {
                    text: qsTr("application")
                    font.pixelSize: 15
                    font.family: "Arial"
                    anchors.top: app004.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Rectangle
            {
                id:app10
                x: 80
                y: app00.y+height
                width: 125
                height: 125
                Rectangle
                {
                    id:app005
                    width: 60
                    height: 80
                    color: Qt.rgba(Math.random(),Math.random(),Math.random())
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text
                {
                    text: qsTr("application")
                    font.pixelSize: 15
                    font.family: "Arial"
                    anchors.top: app005.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Rectangle
            {
                id: app11
                x: app10.x+width
                y: app00.y+height
                width: 125
                height: 125
                Rectangle
                {
                    id:app006
                    width: 60
                    height: 80
                    color: Qt.rgba(Math.random(),Math.random(),Math.random())
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text
                {
                    text: qsTr("application")
                    font.pixelSize: 15
                    font.family: "Arial"
                    anchors.top: app006.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Rectangle
            {
                id: app12
                x: app11.x+width
                y: app00.y+height
                width: 125
                height: 125
                Rectangle
                {
                    id:app007
                    width: 60
                    height: 80
                    color: Qt.rgba(Math.random(),Math.random(),Math.random())
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text
                {
                    text: qsTr("application")
                    font.pixelSize: 15
                    font.family: "Arial"
                    anchors.top: app007.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Rectangle
            {
                id: app13
                x: app12.x+width
                y: app00.y+height
                width: 125
                height: 125
                Rectangle
                {
                    id:app008
                    width: 60
                    height: 80
                    color: Qt.rgba(Math.random(),Math.random(),Math.random())
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text
                {
                    text: qsTr("application")
                    font.pixelSize: 15
                    font.family: "Arial"
                    anchors.top: app008.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Rectangle
            {
                id: app14
                x: app13.x+width
                y: app00.y+height
                width: 125
                height: 125
                Rectangle
                {
                    id:app009
                    width: 60
                    height: 80
                    color: Qt.rgba(Math.random(),Math.random(),Math.random())
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text
                {
                    text: qsTr("application")
                    font.pixelSize: 15
                    font.family: "Arial"
                    anchors.top: app009.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
            Rectangle
            {
                id:app20
                x: app00.x
                y: app10.y+height
                width: 125
                height: 125
                Rectangle
                {
                    id:app010
                    width: 60
                    height: 80
                    color: Qt.rgba(Math.random(),Math.random(),Math.random())
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text
                {
                    text: qsTr("application")
                    font.pixelSize: 15
                    font.family: "Arial"
                    anchors.top: app010.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
            Rectangle
            {
                id:app21
                x: app20.x+width
                y: app10.y+height
                width: 125
                height: 125
                Rectangle
                {
                    id:app011
                    width: 60
                    height: 80
                    color: Qt.rgba(Math.random(),Math.random(),Math.random())
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text
                {
                    text: qsTr("application")
                    font.pixelSize: 15
                    font.family: "Arial"
                    anchors.top: app011.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
            Rectangle
            {
                id:app22
                x: app21.x+width
                y: app10.y+height
                width: 125
                height: 125
                Rectangle
                {
                    id:app012
                    width: 60
                    height: 80
                    color: Qt.rgba(Math.random(),Math.random(),Math.random())
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text
                {
                    text: qsTr("application")
                    font.pixelSize: 15
                    font.family: "Arial"
                    anchors.top: app012.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
            Rectangle
            {
                id:app23
                x: app22.x+width
                y: app10.y+height
                width: 125
                height: 125
                Rectangle
                {
                    id:app013
                    width: 60
                    height: 80
                    color: Qt.rgba(Math.random(),Math.random(),Math.random())
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text
                {
                    text: qsTr("application")
                    font.pixelSize: 15
                    font.family: "Arial"
                    anchors.top: app013.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
            Rectangle
            {
                id:app24
                x: app23.x+width
                y: app10.y+height
                width: 125
                height: 125
                Rectangle
                {
                    id:app014
                    width: 60
                    height: 80
                    color: Qt.rgba(Math.random(),Math.random(),Math.random())
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text
                {
                    text: qsTr("application")
                    font.pixelSize: 15
                    font.family: "Arial"
                    anchors.top: app014.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }

        Rectangle
        {
            id:down
            width: parent.width
            height: 60
            x:0
            y:440
            visible: true
            Rectangle
            {
                id:editor
                width: 90
                height: 40
                radius:6
                border.width: 2
                color: Qt.rgba(Math.random(),Math.random(),Math.random())
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottomMargin: 10
                Text
                {
                    text: qsTr("编辑应用")
                    font.pixelSize: 16
                    font.family:"Arial"
                    anchors.centerIn: parent
                }
                MouseArea
                {
                    anchors.fill:parent
                    onClicked:
                    {
                        ok.visible=true
                        cancel.visible=true
                        editor.visible=false
                        editor()
                        time.start()
                    }
                }
            }
            Rectangle
            {
                id:ok
                width: 90
                height: 40
                radius:6
                border.width: 2
                visible: false
                color: Qt.rgba(Math.random(),Math.random(),Math.random())
                anchors.bottom: parent.bottom
                x:down.width/2-width-10
                anchors.bottomMargin: 10
                Text
                {
                    text: qsTr("保存")
                    font.pixelSize: 16
                    font.family:"Arial"
                    anchors.centerIn: parent
                }
                MouseArea
                {
                    anchors.fill:parent
                    onClicked:
                    {
                        ok.visible=false
                        cancel.visible=false
                        editor.visible=true
                        editorcancel()
                    }
                }
            }
            Rectangle
            {
                id:cancel
                width: 90
                height: 40
                radius:6
                border.width: 2
                visible: false
                color: Qt.rgba(Math.random(),Math.random(),Math.random())
                anchors.bottom: parent.bottom
                x:down.width/2+10
                anchors.bottomMargin: 10
                Text
                {
                    text: qsTr("取消")
                    font.pixelSize: 16
                    font.family:"Arial"
                    anchors.centerIn: parent
                }
                MouseArea
                {
                    anchors.fill:parent
                    onClicked:
                    {
                        ok.visible=false
                        cancel.visible=false
                        editor.visible=true
                        editorcancel()
                    }
                }
            }
        }

    }
}

