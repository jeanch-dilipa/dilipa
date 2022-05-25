import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.0   //图形效果

ApplicationWindow
{
    id:mainwindow
    visible: true
    width: 970//1220
    height: 660//820
    flags: Qt.FramelessWindowHint|Qt.Window     //无边框窗口
    color: "#00000000"

    // 左边缘及上边缘阴影
    DropShadow
    {
           anchors.fill: window
           horizontalOffset: -5
           verticalOffset: -5
           radius: 12.0
           samples: 25
           color: "#20000000"
           spread: 0.0
           source: window
    }
    // 右边缘及下边缘阴影
    DropShadow
    {
            anchors.fill: window
            horizontalOffset: 5
            verticalOffset: 5
            radius: 12.0
            samples: 25
            color: "#20000000"
            spread: 0.0
            source: window
    }
    Rectangle
    {
        id:window
        width: parent.width-20
        height: parent.height-20
        color: "red"
        anchors.centerIn: parent

        //移动
        MouseArea
        {
            property point pos: "0,0"
            property bool ismove: false
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
                    mainwindow.setX(mainwindow.x+mouse.x-pos.x)
                    mainwindow.setY(mainwindow.y+mouse.y-pos.y)
                }
            }
        }

        LeftMain
        {
            id:showleftmain
            visible: true
            anchors.left: parent.left
            width: 70
            height: window.height
        }

        TopMain
        {
            id:showtopmain
            visible: true
            anchors.top: parent.top
            width: window.width-showleftmain.width-20
            height: window.height/24*3
            anchors.right: parent.right
            onPleasemin: mainwindow.visibility="Minimized"
            onPleasemax:
            {
                if(ismax===true)
                {
                    mainwindow.visibility="Maximized"
                }
                else
                {
                    mainwindow.visibility="Windowed"
                }
            }
        }

        MeddleMain
        {
            id:showmeddlemain
            visible: true
            anchors.top: showtopmain.bottom
            anchors.right: parent.right
            width: window.width-showleftmain.width-20
            height: window.height/4
            property var app
            onShowapplication:
            {
                app=Qt.createComponent("All_application.qml")
                app.createObject(window)
            }
        }

        BottomMain
        {
            id:showbottommain
            x: 80
            y: 240
            visible: true
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            width: window.width-showleftmain.width-20
            height: window.height/8*5
        }

    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#ffffff"}
}
##^##*/
