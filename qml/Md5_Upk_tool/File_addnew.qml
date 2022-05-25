import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle
{
    id:root
    width: parent.width
    height: width/8

    Rectangle
    {
        id:md5
        width: root.width/7
        height: root.height/3
        radius: width/2
        anchors.verticalCenter: root.verticalCenter
        anchors.left: root.left
        anchors.margins: root.width/11
        color: Qt.rgba(Math.random(),Math.random(),Math.random(),0.8)
        Text
        {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text:qsTr("md5")
            font.family: "微软雅黑"
            font.pixelSize: width/4
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                fileio.createmd5(file_path.filepathlist)
            }
            hoverEnabled: true
            onEntered: md5.color=Qt.rgba(Math.random(),Math.random(),Math.random())
            onExited: md5.color=Qt.rgba(Math.random(),Math.random(),Math.random())
        }
    }

    Rectangle
    {
        id:upk
        width: root.width/7
        height: root.height/3
        radius: width/2
        anchors.verticalCenter: root.verticalCenter
        anchors.left: md5.right
        anchors.margins: root.width/11
        color: Qt.rgba(Math.random(),Math.random(),Math.random(),0.8)
        Text
        {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text:qsTr("upk")
            font.family: "微软雅黑"
            font.pixelSize: width/4
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                fileio.createupk(file_path.filepathlist,file_path.rootfilepath)
            }
            hoverEnabled: true
            onEntered: upk.color=Qt.rgba(Math.random(),Math.random(),Math.random())
            onExited: upk.color=Qt.rgba(Math.random(),Math.random(),Math.random())
        }
    }
}
