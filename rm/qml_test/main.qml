import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Text {
        id: element
        x: 198
        y: 150
        text: qsTr("Text")
        font.pixelSize: 40

        anchors.centerIn: parent
        onTextChanged: console.log("change_text")

        property color color_p: "red"
        color: color_p
        onColor_pChanged: console.log("change color_p")

    }

    Button {
        id: button
        x: 280
        y: 294
        text: qsTr("Button")

        onClicked:
        {
            element.text="hello world"
            element.color_p="green"
        }
    }


}
