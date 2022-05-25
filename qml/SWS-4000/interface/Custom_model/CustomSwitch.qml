import QtQuick 2.0
import QtQuick.Controls 2.0

Switch
{
    id: root
    property color checkedColor: "#0ACF97"

    indicator: Rectangle
    {
        width: 64
        height: 34
        radius: height / 2
        anchors.verticalCenter:parent.verticalCenter
        color: root.checked ? checkedColor : "white"
        border.width: 2
        border.color: root.checked ? checkedColor : "#E5E5E5"

        Rectangle
        {
            x: root.checked ? parent.width - width - 2 : 1
            width: root.checked ? parent.height - 4 : parent.height - 2
            height: width
            anchors.verticalCenter: parent.verticalCenter
            radius: width / 2
            color: "white"
            border.color: "#D5D5D5"

            Behavior on x
            {
                NumberAnimation { duration: 200 }
            }
        }
    }
}
