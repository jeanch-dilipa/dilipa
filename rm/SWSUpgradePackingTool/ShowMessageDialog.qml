import QtQuick 2.11
import QtQuick.Controls 2.4

//左下角消息显示对话框
Rectangle {
    id: rootRectangle;
    color: Qt.rgba(0.2, 0.2, 0.2, 0.7);
    radius: 5;
    width: centerText.width < 180 ? 200 : centerText.width + 20;
    height: centerText.height + 20;
    visible: false;
    x: parent.width - width - 20;
    y: parent.height - 140;
    z: 1; //显示在上层

    //显示消息
    function showMessage(message)
    {
        centerText.text = message;
        visible = true;
        holdMsgTimer.stop();
        holdMsgTimer.start();
    }

    //显示时长定时器
    Timer {
        id: holdMsgTimer;
        interval: 2500;
        onTriggered: {
            exitPosAnimation.start();
        }
    }

    Text{
        id: centerText;
        anchors.centerIn: parent;
        color: "white";
        font.pixelSize: 14;
        font.bold: true;
    }

    //进入动画
    PropertyAnimation {
        id: enterPosAnimation;
        target: rootRectangle;
        property: "x";
        from: parent.width;
        to: parent.width - width - 30;
        duration: 300;
        easing.type: Easing.OutCubic;
    }

    //离开动画
    PropertyAnimation {
        id: exitPosAnimation;
        target: rootRectangle;
        property: "x";
        to: parent.width;
        duration: 300;
        easing.type: Easing.InCubic;
        onStopped: {
            visible = false;
        }
    }

    onVisibleChanged: {
        if(visible)
        {
            enterPosAnimation.start();
        }
    }
}
