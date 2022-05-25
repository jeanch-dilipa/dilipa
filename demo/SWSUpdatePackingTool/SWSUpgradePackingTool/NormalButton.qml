import QtQuick 2.11
import QtQuick.Controls 2.4

Button {
    property bool circleStyle: false;     //是否是圆形风格
    property bool hoverRotate: false;     //是否hover时旋转
    property int circleWidth: 36;         //圆的宽度（直径）
    property int fontPixelSize: 14;       //字体大小
    property color hoverColor: "#44CF16"; //定制鼠标悬浮时的颜色

    background: Rectangle {
        id: backgroundRec;
        implicitWidth: circleStyle ? circleWidth : 80;
        implicitHeight: circleStyle ? circleWidth : 30;
        radius: circleStyle ? circleWidth/2 : 5;
        color: parent.enabled ? (parent.checkable ? (parent.checked ? "#03A9F4" : "gray") : (parent.pressed ? "#1C628D" : (parent.hovered ? hoverColor : "#03A9F4"))) : "lightGray";

        Behavior on color {
            ColorAnimation{ duration: 500; easing.type: Easing.OutCubic}
        }
    }

    contentItem: Item{} //这个作用是清除自带的Label

    Label {
        anchors.fill: parent;
        text: parent.text;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
        color: "white";
        font.pixelSize: fontPixelSize;
        font.bold: true;
        rotation: hoverRotate ? (parent.hovered ? 90 : 0) : 0;

        Behavior on rotation {
            NumberAnimation { duration: 200; }
        }
    }
}
