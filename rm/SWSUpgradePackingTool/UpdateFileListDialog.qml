import QtQuick 2.11
import QtQuick.Controls 2.4

Dialog {
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

    ColorAnimation {
        id: colorAnimation;
        target: backgroundRec;
        property: "color";
        from: Qt.rgba(1, 1, 1, 0);
        to: backColor;
        duration: 300;
        easing.type: Easing.OutCubic;
    }

    onVisibleChanged: {
        if(visible) {
            colorAnimation.start();
        }
    }
}
