import QtQuick 2.0

Rectangle
{
    id:root
    width: 500
    height: 500
    anchors.centerIn: parent

    property int thunder        //列数
    property int thundernum     //雷数
    property var thunderposition:0
//    MouseArea
//    {
//        anchors.fill: parent
//        onClicked:
//        {
//            rootwindow.width=rootwidth
//            rootwindow.height=rootheight
//            win.destroy()
//        }
//    }
    onThunderChanged:
    {
        console.log(thundernum)
        PARAVANE.signal_createthunder(thunder,thundernum)
    }

    Connections
    {
        target: PARAVANE
        onSignal_showthunder:thunderposition=thundercount
    }

    Grid
    {
        anchors.fill: parent
        rows: thunder
        columns: thunder
        spacing: width/Math.pow(thunder+1,2)
        Repeater
        {
            model: Math.pow(thunder,2)
            Rectangle
            {
                width: root.width/(thunder+1)
                height: width
                radius: width/4
                color: Qt.rgba(Math.random()*1,Math.random()*1,Math.random()*1,Math.random()*1)
                Text
                {
                    id:thundertxt
                    anchors.centerIn: parent
                    text:index
                    font.pointSize: parent.width
                    opacity: 0
                }
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        PARAVANE.signal_judgethunder(index)
                        thundertxt.text=thunderposition
                        thundertxt.opacity=1
                    }
                }
            }
        }
    }
}
