import QtQuick 2.12
import QtQuick.Controls 2.5
import "callfun.js" as Callfun

ApplicationWindow
{
    id:window
    visible: true
    width: 640
    height: 480
//    flags: Qt.WindowSystemMenuHint
    title: qsTr("demo")
    opacity: 0.5
    property var app

    RoundButton
    {
        width: parent.width/4
        height: 20
        radius: 10
        text: qsTr("close")
        font.pixelSize: 15
        font.family: "微软雅黑"
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 2.5
        onClicked:
        {
            settimeparameter(-1,0)
            app.destroy()
            show.height+=limit
            window.title=qsTr("demo")
        }
        background: Rectangle
        {
            radius:10
            color: Qt.rgba(Math.random(),Math.random(),Math.random())
        }
    }
    Rectangle
    {
        id:show
        width: parent.width
        height: parent.height
        clip: true

        Rectangle
        {
            id:scrol
            width: 60
            height: 20
            radius: 6
            color: Qt.rgba(Math.random(),Math.random(),Math.random())
            anchors.margins: 10
            anchors.top: show.top
            anchors.left: show.left
            Text
            {
                text: qsTr("scroll")
                anchors.centerIn: parent
//                horizontalAlignment: Text.AlignHCenter
//                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 10
                font.family: "微软雅黑"
            }
            MouseArea
            {
                anchors.fill:parent
                onClicked:
                {
                    window.title=qsTr("scroll")
                    settimeparameter(1,25)
                    show.height-=limit
                    app=Callfun.createqml("scroll.qml",show)
                }
            }
        }

        RoundButton
        {
            id:annulus
            width: 60
            height: 20
            radius: 6
            anchors.left: scrol.right
            anchors.top: show.top
            anchors.margins: 10
            text: qsTr("annulus")
            font.pixelSize: 10
            font.family: "微软雅黑"
            background: Rectangle
            {
                radius:6
                color:Qt.rgba(Math.random(),Math.random(),Math.random())
            }
            onClicked:
            {
                window.title=qsTr("annulus")
                settimeparameter(1,25)
                show.height-=limit
                app=Callfun.createqml("Annulus.qml",show)
            }
        }

        RoundButton
        {
            id:sender
            width: 60
            height: 20
            radius: 6
            anchors.left: annulus.right
            anchors.top: show.top
            anchors.margins: 10
            text: qsTr("sender")
            font.pixelSize: 10
            font.family: "微软雅黑"
            background: Rectangle
            {
                radius:6
                color:Qt.rgba(Math.random(),Math.random(),Math.random())
            }
            onClicked:
            {
                window.title=qsTr("sender")
                settimeparameter(1,25)
                show.height-=limit
                app=Callfun.createqml("Sender.qml",show)
            }
        }

        RoundButton
        {
            id:windmill
            width: 60
            height: 20
            radius: 6
            anchors.left: sender.right
            anchors.top: show.top
            anchors.margins: 10
            text: qsTr("windmill")
            font.pixelSize: 10
            font.family: "微软雅黑"
            background: Rectangle
            {
                radius:6
                color:Qt.rgba(Math.random(),Math.random(),Math.random())
            }
            onClicked:
            {
                window.title=qsTr("windmill")
                settimeparameter(1,25)
                show.height-=limit
                app=Callfun.createqml("Windmill.qml",show)
            }
        }

        RoundButton
        {
            id:custom_rectangle
            width: 60
            height: 20
            radius: 6
            anchors.left: windmill.right
            anchors.top: show.top
            anchors.margins: 10
            text: qsTr("custom_rectangle")
            font.pixelSize: 10
            font.family: "微软雅黑"
            background: Rectangle
            {
                radius:6
                color:Qt.rgba(Math.random(),Math.random(),Math.random())
            }
            onClicked:
            {
                window.title=qsTr("custom_rectangle")
                settimeparameter(1,25)
                show.height-=limit
                app=Callfun.createqml("Custom_rectangle.qml",show)
            }
        }

        RoundButton
        {
            id:animation
            width: 60
            height: 20
            radius: 6
            anchors.left: custom_rectangle.right
            anchors.top: show.top
            anchors.margins: 10
            text: qsTr("animation")
            font.pixelSize: 10
            font.family: "微软雅黑"
            background: Rectangle
            {
                radius:6
                color:Qt.rgba(Math.random(),Math.random(),Math.random())
            }
            onClicked:
            {
                window.title=qsTr("animation")
                settimeparameter(1,25)
                show.height-=limit
                app=Callfun.createqml("Animation.qml",show)
            }
        }

        RoundButton
        {
            id:model
            width: 60
            height: 20
            radius: 6
            anchors.left: animation.right
            anchors.top: show.top
            anchors.margins: 10
            text: qsTr("model")
            font.pixelSize: 10
            font.family: "微软雅黑"
            background: Rectangle
            {
                radius:6
                color:Qt.rgba(Math.random(),Math.random(),Math.random())
            }
            onClicked:
            {
                window.title=qsTr("model")
                settimeparameter(1,25)
                show.height-=limit
                app=Callfun.createqml("Model.qml",show)
            }
        }

        RoundButton
        {
            id:pathview
            width: 60
            height: 20
            radius: 6
            anchors.left: model.right
            anchors.top: show.top
            anchors.margins: 10
            text: qsTr("pathview")
            font.pixelSize: 10
            font.family: "微软雅黑"
            background: Rectangle
            {
                radius:6
                color:Qt.rgba(Math.random(),Math.random(),Math.random())
            }
            onClicked:
            {
                window.title=qsTr("pathview")
                settimeparameter(1,25)
                show.height-=limit
                app=Callfun.createqml("Pathview.qml",show)
            }
        }

        RoundButton
        {
            id:xmlmodel
            width: 60
            height: 20
            radius: 6
            anchors.left: pathview.right
            anchors.top: show.top
            anchors.margins: 10
            text: qsTr("xmlmodel")
            font.pixelSize: 10
            font.family: "微软雅黑"
            background: Rectangle
            {
                radius:6
                color:Qt.rgba(Math.random(),Math.random(),Math.random())
            }
            onClicked:
            {
                window.title=qsTr("xmlmodel")
                settimeparameter(1,25)
                show.height-=limit
                app=Callfun.createqml("Xmlmodel.qml",show)
            }
        }

        RoundButton
        {
            id:canvas_element
            width: 60
            height: 20
            radius: 6
            anchors.left: show.left
            anchors.top: scrol.bottom
            anchors.margins: 10
            text: qsTr("canvas_element")
            font.pixelSize: 10
            font.family: "微软雅黑"
            background: Rectangle
            {
                radius:6
                color:Qt.rgba(Math.random(),Math.random(),Math.random())
            }
            onClicked:
            {
                window.title=qsTr("canvas_element")
                settimeparameter(1,25)
                show.height-=limit
                app=Callfun.createqml("Canvas_Element.qml",show)
            }
        }

        RoundButton
        {
            id:canvas_paint
            width: 60
            height: 20
            radius: 6
            anchors.left: canvas_element.right
            anchors.top: scrol.bottom
            anchors.margins: 10
            text: qsTr("canvas_paint")
            font.pixelSize: 10
            font.family: "微软雅黑"
            background: Rectangle
            {
                radius:6
                color:Qt.rgba(Math.random(),Math.random(),Math.random())
            }
            onClicked:
            {
                window.title=qsTr("canvas_paint")
                settimeparameter(1,25)
                show.height-=limit
                app=Callfun.createqml("Canvas_paint.qml",show)
            }
        }

        RoundButton
        {
            id:particlesystem
            width: 60
            height: 20
            radius: 6
            anchors.left: canvas_paint.right
            anchors.top: scrol.bottom
            anchors.margins: 10
            text: qsTr("particlesystem")
            font.pixelSize: 10
            font.family: "微软雅黑"
            background: Rectangle
            {
                radius:6
                color:Qt.rgba(Math.random(),Math.random(),Math.random())
            }
            onClicked:
            {
                window.title=qsTr("particlesystem")
                settimeparameter(1,25)
                show.height-=limit
                app=Callfun.createqml("Particlesystem.qml",show)
            }
        }

        RoundButton
        {
            id:particlegroup
            width: 60
            height: 20
            radius: 6
            anchors.left: particlesystem.right
            anchors.top: scrol.bottom
            anchors.margins: 10
            text: qsTr("particlegroup")
            font.pixelSize: 10
            font.family: "微软雅黑"
            background: Rectangle
            {
                radius:6
                color:Qt.rgba(Math.random(),Math.random(),Math.random())
            }
            onClicked:
            {
                window.title=qsTr("particlegroup")
                settimeparameter(1,25)
                show.height-=limit
                app=Callfun.createqml("Particlegroup.qml",show)
            }
        }

        RoundButton
        {
            id:epi_leather
            width: 60
            height: 20
            radius: 6
            anchors.left: particlegroup.right
            anchors.top: scrol.bottom
            anchors.margins: 10
            text: qsTr("epi_leather")
            font.pixelSize: 10
            font.family: "微软雅黑"
            background: Rectangle
            {
                radius:6
                color:Qt.rgba(Math.random(),Math.random(),Math.random())
            }
            onClicked:
            {
                window.title=qsTr("epi_leather")
                settimeparameter(1,25)
                show.height-=limit
                app=Callfun.createqml("Epileather.qml",show)
            }
        }

        RoundButton
        {
            id: curve
            width: 60
            height: 20
            radius: 6
            anchors.left: epi_leather.right
            anchors.top: scrol.bottom
            anchors.margins: 10
            text: qsTr("curve")
            font.pixelSize: 10
            font.family: "微软雅黑"
            background: Rectangle
            {
                radius:6
                color:Qt.rgba(Math.random(),Math.random(),Math.random())
            }
            onClicked:
            {
                window.title=qsTr("curve")
                settimeparameter(1,25)
                show.height-=limit
                app=Callfun.createqml("Curve.qml",show)
            }
        }
    }

    Timer
    {
        id:time
        interval: 20
        repeat: true
        onTriggered:
        {
            show.y+=window.sep
            if(show.y===window.limit)
                stop()
        }
    }
    property var sep
    property var limit
    function settimeparameter(sep,limit)
    {
        window.sep=sep
        window.limit=limit
        time.start()
    }
}
