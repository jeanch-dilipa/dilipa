import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

ApplicationWindow
{
    id:rootwindow
    visible: true
    width: 300
    height: 300
    flags: Qt.FramelessWindowHint|Qt.Window     //无边框窗口
    color: "#00000000"
    property var version: 0.1
    opacity: 0.5
//    title: qsTr("Simple_Manger_"+version+"_rough")

    /*阴影*/
    DropShadow
    {
        anchors.fill: loginwindow
        anchors.centerIn: loginwindow
        horizontalOffset: 3
        verticalOffset: 3
        radius: 10
        samples: 21
        color: "#80000000"
        source: loginwindow
    }
    DropShadow
    {
        anchors.fill: loginwindow
        horizontalOffset: -3
        verticalOffset: -3
        radius: 10
        samples: 21
        color: "#80000000"
        source: loginwindow
    }

    Rectangle
    {
        id:loginwindow
        width: rootwindow.width-20
        height: rootwindow.height-20
        anchors.centerIn: parent
        radius: width/2
        color: "white"
        /*移动*/
        MouseArea
        {
            property point pos: "0,0"
            property var ismove: false
            anchors.fill: parent
            onPressed:
            {
                if(mouse.button===Qt.LeftButton)
                    ismove=true
                pos=Qt.point(mouse.x,mouse.y)
            }
            onPositionChanged:
            {
                if(ismove)
                {
                    rootwindow.setX(rootwindow.x+mouse.x-pos.x)
                    rootwindow.setY(rootwindow.y+mouse.y-pos.y)
                }
            }
        }

        Label
        {
            anchors.top: loginwindow.top
            anchors.topMargin: text.length
            anchors.horizontalCenter: parent.horizontalCenter
            text:qsTr("Simple_Manger_"+version+"_rough")
        }

        RoundButton
        {
            id:login
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -height/2
            width: text.length*10
            height: parent.width*0.1
            text: qsTr("login")
            onClicked:
            {
                var c=Qt.createComponent("Simple_Manger.qml")
                var app=c.createObject(rootwindow)
                rootwindow.width=app.width
                rootwindow.height=app.height
            }
        }
        RoundButton
        {
            id:logout
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 10
            anchors.top: login.bottom
            width: text.length*10
            height: parent.width*0.1
            text: qsTr("logout")
            onClicked:
            {
                Qt.quit()
            }
        }
    }
}
