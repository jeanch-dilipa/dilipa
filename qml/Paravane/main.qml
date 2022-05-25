import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

ApplicationWindow
{
    id:rootwindow
    visible: true
    width: rootwidth
    height: rootheight
    opacity:0.5

    flags: Qt.WindowSystemMenuHint
    title: qsTr("Paravane_"+version+"_rough")

    property var version: 0.1
    property variant win
    property var rootwidth: 300
    property var rootheight: 300

    Image
    {
        id: paravane_image
        width: parent.width/3
        height: parent.height/3
        anchors.topMargin: height/3
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        source: "qrc:/image/paravane.png"
    }

    RoundButton
    {
        id:start_paravane
        width: parent.width/2
        height: parent.height/12
        radius: width/2
        anchors.topMargin: height
        anchors.top: paravane_image.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        background: Rectangle
        {
            color:Qt.rgba(Math.random()*1,Math.random()*1,Math.random()*1,Math.random()*1)
            radius:parent.width/2
        }
        Text {
            id: start_text
            text: qsTr("start")
            font.pointSize: parent.height/2
            anchors.centerIn: parent
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                var c=Qt.createComponent("Paravane.qml")
                win = c.createObject(rootwindow)
                win.thundernum=thundernum_paravane.currentText
                win.thunder=comboBox_paravane.currentText.slice(0,comboBox_paravane.currentText.lastIndexOf("*"))
                if(win.thunder===81)
                {
                    win.width*=1.8
                    win.height*=1.8
                }
                rootwindow.width=win.width
                rootwindow.height=win.height
            }
        }
    }

    ComboBox
    {
        id: comboBox_paravane
        width: parent.width/4
        height: parent.height/12
        anchors.horizontalCenterOffset:-width/2
        anchors.topMargin: 25
        anchors.top:start_paravane.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        editable: false //是否可编辑
        model: ListModel
        {
            id:model
            ListElement{text:"9*9"}
            ListElement{text:"27*27"}
            ListElement{text:"81*81"}
        }
        background: Rectangle
        {
            radius:parent.width/2
            color:Qt.rgba(Math.random()*1,Math.random()*1,Math.random()*1,Math.random()*1)
        }
        onAccepted:
        {
            if(find(editText)===-1)
                model.append({text:editText})
        }
    }
    ComboBox
    {
        id: thundernum_paravane
        width: parent.width/4
        height: parent.height/12
        anchors.topMargin: 25
        anchors.top:start_paravane.bottom
        anchors.left: comboBox_paravane.right
        editable: true //是否可编辑
        model: 6000
        currentIndex:10
        background: Rectangle
        {
            radius:parent.width/2
            color:Qt.rgba(Math.random()*1,Math.random()*1,Math.random()*1,Math.random()*1)
        }
        onAccepted:
        {
            if(find(editText)===-1)
                model.append({text:editText})
        }
    }

    RoundButton
    {
        id:close_paravane
        width: parent.width/2
        height: parent.height/12
        radius: width/2
        anchors.top:comboBox_paravane.bottom
        anchors.topMargin: height
        anchors.horizontalCenter: parent.horizontalCenter
        background: Rectangle
        {
            color:Qt.rgba(Math.random()*1,Math.random()*1,Math.random()*1,Math.random()*1)
            radius:parent.width/2
        }
        Text {
            id: close_text
            text: qsTr("close")
            font.pointSize: parent.height/2
            anchors.centerIn: parent
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                Qt.quit()
            }
        }
    }
}
