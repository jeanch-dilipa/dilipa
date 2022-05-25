import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

ApplicationWindow
{
    id:rootwindow
    width: 450
    height: 400
    visible: true

    property var version: 0.1

    title: qsTr("tetris_"+version+"_rough")

    opacity: 0.5

//    flags: Qt.WindowSystemMenuHint

    /*Diamond*/
    Diamond
    {
        id:diamond
        anchors.left: rootwindow.left
    }

    /*Integral*/
    Integral
    {
        id:integral
        anchors.left: diamond.right
    }

}
