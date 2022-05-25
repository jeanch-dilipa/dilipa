import QtQuick 2.11
import QtQuick.Controls 2.4

TextField{
    implicitHeight: 30;
    font.pixelSize: 14;
    selectByMouse: true;

    background: Rectangle {
        radius: 4;
        border.color: parent.focus ? "#44CF16" : (parent.hovered ? "#44CF16" : "#0DA7F9");
        border.width: 2;
        Behavior on border.color {
            ColorAnimation {duration: 300}
        }
    }
}
