import QtQuick 2.0
import QtQuick.Controls 2.5

import "../Custom_model"

Rectangle
{
    id:root
    width: 1024/10*9-20
    height: 588
    radius: 10

    Rectangle
    {
        id:ap_on_off_model
        width: root.width/5
        height: root.height/8
        Text
        {
            id:ap_on_off_text
            height: ap_on_off_model.height/3
            anchors.horizontalCenter: ap_on_off_model.horizontalCenter
            text: qsTr("ap_switch")
            font.pointSize: ap_on_off_model.width/10
        }
        CustomSwitch
        {
            id:ap_on_off
            anchors.top: ap_on_off_text.bottom
            anchors.topMargin: 12
            anchors.horizontalCenter: ap_on_off_model.horizontalCenter
        }
    }
    Rectangle
    {
        id:vp_on_off_model
        width: root.width/5
        height: root.height/8
        anchors.left: ap_on_off_model.right
        anchors.leftMargin: width/3
        Text
        {
            id:vp_on_off_text
            height: vp_on_off_model.height/3
            anchors.horizontalCenter: vp_on_off_model.horizontalCenter
            text: qsTr("vp_switch")
            font.pointSize: vp_on_off_model.width/10
        }
        CustomSwitch
        {
            id:vp_on_off
            anchors.top: vp_on_off_text.bottom
            anchors.topMargin: 12
            anchors.horizontalCenter: vp_on_off_model.horizontalCenter
        }
    }
    Rectangle
    {
        id:tmp_on_off_model
        width: root.width/5
        height: root.height/8
        anchors.left: vp_on_off_model.right
        anchors.leftMargin: width/3
        Text
        {
            id:tmp_on_off_text
            height: tmp_on_off_model.height/3
            anchors.horizontalCenter: tmp_on_off_model.horizontalCenter
            text: qsTr("tmp_switch")
            font.pointSize: tmp_on_off_model.width/10
        }
        CustomSwitch
        {
            id:tmp_on_off
            anchors.top: tmp_on_off_text.bottom
            anchors.topMargin: 12
            anchors.horizontalCenter: tmp_on_off_model.horizontalCenter
        }
    }
    Rectangle
    {
        id:cond_on_off_model
        width: root.width/5
        height: root.height/8
        anchors.left: tmp_on_off_model.right
        anchors.leftMargin: width/3
        Text
        {
            id:cond_on_off_text
            height: cond_on_off_model.height/3
            anchors.horizontalCenter: cond_on_off_model.horizontalCenter
            text: qsTr("cond_switch")
            font.pointSize: cond_on_off_model.width/10
        }
        CustomSwitch
        {
            id:cond_on_off
            anchors.top: cond_on_off_text.bottom
            anchors.topMargin: 12
            anchors.horizontalCenter: cond_on_off_model.horizontalCenter
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
