import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle
{
    id:root
    width: 1300
    height: 800
    anchors.centerIn: parent

    /*region列表*/
    Rectangle
    {
        id:region_treeview
        width: 300
        height: 800
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        Text
        {
            text: qsTr("Region List")
            font.pointSize: parent.width/20
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Component.onCompleted:
        {
            var c=Qt.createComponent("Region_TreeView.qml")
            var app=c.createObject(root)
        }
    }
    /*分割线*/
    Rectangle
    {
        width: 2
        height: region_treeview.height-30
        anchors.left: region_treeview.right
        anchors.verticalCenter: parent.verticalCenter
        color: "black"
    }
}
