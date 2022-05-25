import QtQuick.Controls 2.5
import QtQuick.Window 2.3
import QtQuick 2.9

Window
{
    id:root
    width: 200
    height: 100
    property var messagelabeltext
    property bool isresetcard:false

    onMessagelabeltextChanged: messagelabel.text=messagelabeltext

    Text
    {
        id:messagelabel
        y: 22
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
        font.pointSize: 10
        text: qsTr("message")
    }
    RoundButton
    {
        id:messagebtnclose
        width: parent.width*0.4
        height: width*0.2
        text:qsTr("取消")
        font.pointSize: 10
        anchors.margins: 15
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: -(width+7.5)/2
        background: Rectangle
        {
            radius:parent.height
            color:Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
        }
        onClicked:
        {
            message.visible=false
        }
    }
    RoundButton
    {
        id:messagebtnok
        width: parent.width*0.4
        height: width*0.2
        text:qsTr("确认")
        anchors.margins: 15
        font.pointSize: 10
        anchors.bottom: parent.bottom
        anchors.left: messagebtnclose.right
        background: Rectangle
        {
            radius:parent.height
            color:Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
        }
        onClicked:
        {
            message.visible=false
            if(isresetcard)
                REPEATER.signalwriteuserbasicinfo(Propertydefine.Card_type.Unopencard,qsTr("name"),Propertydefine.Gender_type.Unknown,qsTr("2020-01-01"),180,65,65)
            isresetcard=false
        }
    }

}
