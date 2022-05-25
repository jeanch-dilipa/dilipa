import QtQuick 2.0
import QtQuick.Controls 2.5

import "../public_use"
import "../Custom_model"

Rectangle
{
    id:root
    width: 1024
    height: 608
    anchors.top: parent.top
    anchors.topMargin: 96

    BloodControl
    {
        id:bloodControl
        anchors.horizontalCenter: root.horizontalCenter
        anchors.top: root.top
        anchors.topMargin: 5
    }
    CustomButton
    {
        id:hd
        width: parent.width/4
        height: parent.height/4
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: -300
        anchors.verticalCenterOffset: -120
        backgroundradius: width/6
        text: qsTr("HD")
        textfontpointsize: 40
    }
    CustomButton
    {
        id:iuf
        width: parent.width/4
        height: parent.height/4
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: 300
        anchors.verticalCenterOffset: -120
        backgroundradius: width/6
        text: qsTr("IUF")
        textfontpointsize: 40
    }
    CustomButton
    {
        id:hf
        width: parent.width/4
        height: parent.height/4
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: -300
        anchors.verticalCenterOffset: 120
        backgroundradius: width/6
        text: qsTr("HF")
        textfontpointsize: 40
    }
    CustomButton
    {
        id:hdf
        width: parent.width/4
        height: parent.height/4
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: 300
        anchors.verticalCenterOffset: 120
        backgroundradius: width/6
        text: qsTr("HDF")
        textfontpointsize: 40
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
