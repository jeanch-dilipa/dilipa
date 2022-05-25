import QtQuick 2.11
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.0

CheckBox{
    id: cbx;
    implicitHeight: 30;
    indicator: Rectangle {
        id: idc;
        height: parent.height*0.6;
        width: height;
        anchors.verticalCenter: parent.verticalCenter;
        border.color: cbx.enabled ? (cbx.pressed ? "#1C628D" : (cbx.hovered ? "#44CF16" : "#03A9F4")) : "lightGray";

        Item{   //这个Item用于给Image定位及大小的，目的是实现Image进入和退出的动画以中心为原点
            id: idcImgItem;
            anchors.left: parent.left;
            anchors.bottom: parent.bottom;
            width: parent.width*1.2;
            height: width;

            Image {
                id: idcImg;
                source: "qrc:/checkIcon.png"; //图片比例：17:15
                anchors.centerIn: parent;
                visible: false;
                layer.enabled: true;
                layer.effect: ColorOverlay{
                    color: cbx.indicator.border.color;
                    Behavior on color { ColorAnimation{ duration: 500; easing.type: Easing.OutCubic } }
                }

                PropertyAnimation {
                    id: enterAni;
                    target: idcImg;
                    properties: "width,height";
                    duration: 200;
                    from: 0;
                    to: idcImgItem.width;
                    easing.type: Easing.OutCubic;
                }
                PropertyAnimation {
                    id: exitAni;
                    target: idcImg;
                    properties: "width,height";
                    duration: 200;
                    to: 0;
                    easing.type: Easing.OutCubic;
                    onStopped: {
                        idcImg.visible = false;
                    }
                }
            }
        }
    }

    onCheckedChanged: {
        if(checked)
        {
            idcImg.visible = true;
            enterAni.start();
        }
        else
        {
            exitAni.start();
        }
    }
}
