import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle
{
    width: 760
    height: 220
    anchors.top: parent.top
    anchors.left: parent.left
    color:"#00000000"

    DropShadow
    {
            anchors.fill: common
            verticalOffset: 5
            radius: 12.0
            samples: 25
            color: "#20000000"
            spread: 0.0
            source: common
    }
    Rectangle
    {
        id:common
        width: 760
        height: 200

        Text
        {
            x: 32
            y: 16
            text: qsTr("常用")
            font.family:"Arial"
            font.pixelSize: 20
            anchors.top: parent
            anchors.Margin: 10
        }

        Rectangle
        {
            id:app1
            x: 0
            y: 67
            width: 100
            height: 125
            Rectangle
            {
                id:app01
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
                anchors.top: app01.bottom
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#000000";formeditorZoom:0.8999999761581421}
}
##^##*/
