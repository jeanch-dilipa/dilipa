import QtQuick 2.11
import QtQuick.Controls 2.4

Popup {
    width: centerText.width + 20;
    height: centerText.height + 20;
    x: (parent.width - width)/2; //位置一直处于父窗口中间
    y: (parent.height - height)/2;
    property string filePath;
    property color backColor: Qt.rgba(0.01, 0.44, 0.7, 0.6);

    background: Rectangle {
        id: backgroundRec;
        color: backColor;
        radius: 5;
    }

    Text{
        id: centerText;
        font.pixelSize: 14;
        color: "white";
        font.bold: true;
    }

    onFilePathChanged: {
        centerText.text = filePath;
    }

    enter: Transition {
        NumberAnimation { duration: 300; property: "opacity"; from: 0.0; to: 1.0; easing.type: Easing.OutCubic; }
    }

    exit: Transition {
        NumberAnimation { duration: 300; property: "opacity"; from: 1.0; to: 0.0; easing.type: Easing.OutCubic; }
    }

    onClosed: { //关闭自动销毁
        destroy();
    }
}
