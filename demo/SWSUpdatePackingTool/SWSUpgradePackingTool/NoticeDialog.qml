import QtQuick 2.0
import QtQuick.Controls 2.4

Popup {
    id: rootPopup;
    width: 350;
    height: 150;
    modal: true;
    closePolicy: Popup.NoAutoClose;
    x: (parent.width - width)/2;
    y: (parent.height - height)/2;

    property string message;
    property string button0Text: qsTr("确定");
    property string button1Text: qsTr("取消");
    property int result: 1;
    signal finished(var result);

    background: Rectangle{
        id: noticeRec;
        color: Qt.rgba(1.0, 1.0, 1.0, 1.0);
        radius: 10;

        NormalButton{
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 15;
            anchors.left: parent.left;
            anchors.leftMargin: 40;
            text: button0Text;

            onClicked: {
                rootPopup.visible = false;
                result = 0;
                finished(result);
            }
        }
        NormalButton{
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 15;
            anchors.right: parent.right;
            anchors.rightMargin: 40;
            text: button1Text;

            onClicked: {
                rootPopup.visible = false;
                result = 1;
                finished(result);
            }
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: parent.top;
            anchors.topMargin: 30;
            id: centerText;
            text: message;
            width: 320;
            wrapMode: Text.WordWrap;
            font.pixelSize: 14;
        }
    }

    enter: Transition {
        NumberAnimation { duration: 300; property: "opacity"; from: 0.0; to: 1.0; easing.type: Easing.OutCubic; }
    }

    exit: Transition {
        NumberAnimation { duration: 300; property: "opacity"; from: 1.0; to: 0.0; easing.type: Easing.OutCubic; }
    }
}
