import QtQuick 2.0
import QtQml 2.3
import QtQuick.Controls 2.5

import "../Custom_model"

Rectangle
{
    id:root
    width: 182
    height: width

    property var bloodfprvalue: 200

    Rectangle
    {
        id:bloodcontrolvalue
        width: 182
        height: width/2
        anchors.horizontalCenter: root.horizontalCenter
        clip: true
        CustomButton
        {
            id:bloodfprvaluebtn
            width: 183
            height: width
            anchors.top: bloodcontrolvalue.top
            backgroundradius: width
            doNotHint: true
            text: qsTr("")
            textfontpointsize: 35

            Label
            {
                id:bloodfprvaluetext
                anchors.centerIn: parent
                font.family: "Arial"
                font.weight: Font.Thin
                anchors.verticalCenterOffset: -35
                text: root.bloodfprvalue
                font.pointSize: 35
                color: "white"
            }
        }
    }

    Rectangle
    {
        id:bloodcontroladd
        width: height
        height: 91
        anchors.horizontalCenter: root.horizontalCenter
        anchors.top: bloodcontrolvalue.bottom
        anchors.horizontalCenterOffset: -182/4
        clip: true
        CustomButton
        {
            id:bloodfpraddbtn
            width: 183
            height: width
            anchors.left: bloodcontroladd.left
            anchors.bottom: bloodcontroladd.bottom
            backgroundradius: width
            doNotHint: true
            text: qsTr("")
            onClicked:
            {
                if(root.bloodfprvalue < 650)
                {
                    root.bloodfprvalue += 10
                }
            }
            onPressed:
            {
                icon_add1.color = "red"
                icon_add2.color = "red"
            }
            onReleased:
            {
                icon_add1.color = "#5ffe5f"
                icon_add2.color = "#5ffe5f"
            }
        }
        Rectangle
        {
            id:icon_add1
            width: bloodcontroladd.width/5*3
            height: bloodcontroladd.height/15
            anchors.centerIn: bloodcontroladd
            anchors.verticalCenterOffset: -10
            anchors.horizontalCenterOffset: 10
            radius: width/2
            color: "#5ffe5f"
        }
        Rectangle
        {
            id:icon_add2
            width: bloodcontroladd.width/5*3
            height: bloodcontroladd.height/15
            anchors.centerIn: bloodcontroladd
            anchors.verticalCenterOffset: -10
            anchors.horizontalCenterOffset: 10
            radius: width/2
            rotation: -90
            color: "#5ffe5f"
        }
    }
    Rectangle
    {
        id:bloodcontrolsub
        width: height
        height: 91
        anchors.horizontalCenter: root.horizontalCenter
        anchors.top: bloodcontrolvalue.bottom
        anchors.horizontalCenterOffset: 182/4
        clip: true
        CustomButton
        {
            id:bloodfprsubbtn
            width: 183
            height: width
            anchors.right: bloodcontrolsub.right
            anchors.bottom: bloodcontrolsub.bottom
            backgroundradius: width
            doNotHint: true
            text: qsTr("")
            onClicked:
            {
                if(root.bloodfprvalue > 0)
                {
                    root.bloodfprvalue -= 10
                }
            }
            onPressed:
            {
                icon_sub.color = "red"
            }
            onReleased:
            {
                icon_sub.color = "#5ffe5f"
            }
        }

        Rectangle
        {
            id:icon_sub
            width: bloodcontrolsub.width/5*3
            height: bloodcontrolsub.height/15
            anchors.centerIn: bloodcontrolsub
            anchors.verticalCenterOffset: -10
            anchors.horizontalCenterOffset: -10
            radius: width/2
            color: "#5ffe5f"
        }
    }
}


