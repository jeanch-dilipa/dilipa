import QtQuick 2.11
import QtQuick.Controls 2.4

Popup {
    width: centerText.width + 20;
    height: centerText.height + 20;
    property var fileArray;
    property string dialogTitle;
    property color backColor;

    background: Rectangle {
        id: backgroundRec;
        color: backColor;
        radius: 5;
    }

    Text{
        id: centerText;
        font.pixelSize: 14;
    }

    onFileArrayChanged: {
        var s = "[" + dialogTitle + "] " + qsTr("文件列表：") + "\n";
        s += fileArray.join("\n");
        centerText.text = s;
    }

    enter: Transition {
        NumberAnimation { duration: 300; property: "opacity"; from: 0.0; to: 1.0; easing.type: Easing.OutCubic; }
    }

    exit: Transition {
        NumberAnimation { duration: 300; property: "opacity"; from: 1.0; to: 0.0; easing.type: Easing.OutCubic; }
    }
}
