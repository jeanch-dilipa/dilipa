import QtQuick 2.0
import QtQuick.Controls 2.3

Rectangle
{
    id: meddlemain
    x: 0
    y: 0
    //    color: "red"
    visible: false

    signal showapplication()


    Button {
        id: button
        x: 323
        y: 49
        width: 136
        height: 41
        text: qsTr("Button")

        onClicked: showapplication()

    }



}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
