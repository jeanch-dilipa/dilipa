import QtQuick 2.0
import QtQuick.Controls 2.5

Slider
{
    id:slider
    width: 270
    height: 40

    property var butoncolor: "#0acf97"
    property var progresscolor: "#0acf97"
    property var backgroundcolor: "#d5d5d5d5"

    /*parameter*/
    property var snap_value: 200
    property var def_value: 200
    property var max_value: 720
    property var min_value: -500
    property var gain: 10
    property var description: qsTr("")

    onValueChanged:
    {
        snap_value = Math.floor(value)
    }

    handle: Item
    {
        width: 20
        height: width
        anchors.verticalCenter: parent.verticalCenter
        Rectangle
        {
            x: slider.position * (slider.width - width)
            width: 20
            height: width
            radius: width/2
            anchors.verticalCenter: parent.verticalCenter
            color: slider.butoncolor

            NumberAnimation on width {running: slider.pressed;from:20;to:30;duration: 500}
            NumberAnimation on width {running: !slider.pressed;from:30;to:20;duration: 500}
        }
    }
    background:Rectangle
    {
        width: parent.width
        height: 10
        anchors.verticalCenter: parent.verticalCenter
        radius:5
        color: slider.backgroundcolor

        Rectangle
        {
            width: slider.position * parent.width
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            radius: 5
            color: slider.progresscolor
        }
    }
}
