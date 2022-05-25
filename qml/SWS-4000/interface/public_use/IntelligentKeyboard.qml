import QtQuick 2.0
import QtGraphicalEffects 1.0

import "../Custom_model"

Rectangle
{
    id:rootw
    width: 420
    height: 320
    anchors.centerIn: parent
    color: "#00000000"

    property var itemName:qsTr("")
    property var itemmaxLimit:qsTr("")
    property var itemminLimit:qsTr("")
    property var result
    property var itemdigit

    DropShadow
    {
        anchors.fill: root
        horizontalOffset: 5
        verticalOffset: 5
        source: root
        color: "#a8a8a8a8"
        samples: 5
        radius: 5
    }
    DropShadow
    {
        anchors.fill: root
        horizontalOffset: -5
        verticalOffset: 5
        source: root
        color: "#a8a8a8a8"
        samples: 5
        radius: 5
    }
    DropShadow
    {
        anchors.fill: root
        horizontalOffset: -5
        verticalOffset: -5
        source: root
        color: "#a8a8a8a8"
        samples: 5
        radius: 5
    }
    DropShadow
    {
        anchors.fill: root
        horizontalOffset: 5
        verticalOffset: -5
        source: root
        color: "#a8a8a8a8"
        samples: 5
        radius: 5
    }

    Rectangle
    {
        id:root
        width: 400
        height: 300
        anchors.centerIn: parent
        Rectangle
        {
            id:showarea
            width: parent.width
            height: parent.height*0.4

            Row
            {
                anchors.fill: parent
                Rectangle
                {
                    width: parent.width*0.3
                    height: parent.height
                    radius: 15
                    color: "#0acf97"
                    Text
                    {
                        id:itemname
                        width: parent.width
                        height: parent.height/2
                        font.pointSize: 12
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        wrapMode: Text.WordWrap
                        text: rootw.itemName
                    }
                    Text
                    {
                        id:itemlimit
                        width: parent.width
                        height: parent.height/2
                        anchors.top: itemname.bottom
                        font.pointSize: 12
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        wrapMode: Text.WordWrap
                        text: rootw.itemmaxLimit + "～" + rootw.itemminLimit
                    }
                }
                spacing: parent.width*0.1
                Rectangle
                {
                    width: parent.width*0.6
                    height: parent.height
                    radius: 15
                    color: "#0acf97";
                    Text
                    {
                        id:itemvalue
                        width: parent.width*0.8
                        height: parent.height
                        anchors.centerIn: parent
                        font.pointSize: 15
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignRight
                        wrapMode: Text.WordWrap
                        text: qsTr("")
                    }
                }
            }
        }

        Rectangle
        {
            id:keyarea
            width: parent.width
            height: parent.height*0.6
            anchors.top: showarea.bottom

            Column
            {
                anchors.fill: parent
                Row
                {
                    width: parent.width
                    height: parent.height/4
                    CustomButton
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width/4
                        height: parent.height*0.8
                        backgroundradius: 20
                        text: qsTr("7")
                        onClicked:
                        {
                            itemvalue.text += text
                        }
                    }
                    CustomButton
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width/4
                        height: parent.height*0.8
                        backgroundradius: 20
                        text: qsTr("8")
                        onClicked:
                        {
                            itemvalue.text += text
                        }
                    }
                    CustomButton
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width/4
                        height: parent.height*0.8
                        backgroundradius: 20
                        text: qsTr("9")
                        onClicked:
                        {
                            itemvalue.text += text
                        }
                    }
                    CustomButton
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width/4
                        height: parent.height*0.8
                        backgroundradius: 20
                        text: qsTr("<")
                        onClicked:
                        {
                            itemvalue.text = itemvalue.text.slice(0,itemvalue.text.length-1)
                        }
                    }
                }

                Row
                {
                    width: parent.width
                    height: parent.height/4
                    CustomButton
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width/4
                        height: parent.height*0.8
                        backgroundradius: 20
                        text: qsTr("4")
                        onClicked:
                        {
                            itemvalue.text += text
                        }
                    }
                    CustomButton
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width/4
                        height: parent.height*0.8
                        backgroundradius: 20
                        text: qsTr("5")
                        onClicked:
                        {
                            itemvalue.text += text
                        }
                    }
                    CustomButton
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width/4
                        height: parent.height*0.8
                        backgroundradius: 20
                        text: qsTr("6")
                        onClicked:
                        {
                            itemvalue.text += text
                        }
                    }
                    CustomButton
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width/4
                        height: parent.height*0.8
                        backgroundradius: 20
                        text: qsTr("clear")
                        onClicked:
                        {
                            itemvalue.text = qsTr("")
                        }
                    }
                }

                Row
                {
                    width: parent.width
                    height: parent.height/4
                    CustomButton
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width/4
                        height: parent.height*0.8
                        backgroundradius: 20
                        text: qsTr("1")
                        onClicked:
                        {
                            itemvalue.text += text
                        }
                    }
                    CustomButton
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width/4
                        height: parent.height*0.8
                        backgroundradius: 20
                        text: qsTr("2")
                        onClicked:
                        {
                            itemvalue.text += text
                        }
                    }
                    CustomButton
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width/4
                        height: parent.height*0.8
                        backgroundradius: 20
                        text: qsTr("3")
                        onClicked:
                        {
                            itemvalue.text += text
                        }
                    }
                    CustomButton
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width/4
                        height: parent.height*0.8
                        backgroundradius: 20
                        text: qsTr("close")
                        onClicked:
                        {
                            rootw.destroy()
                        }
                    }
                }

                Row
                {
                    width: parent.width
                    height: parent.height/4
                    CustomButton
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width/4
                        height: parent.height*0.8
                        backgroundradius: 20
                        text: qsTr("-/+")
                        onClicked:
                        {
                            if(itemvalue.text.slice(0,1) === "-")
                            {
                                itemvalue.text = itemvalue.text.slice(1,itemvalue.text.length)
                            }
                            else
                            {
                                itemvalue.text = "-" + itemvalue.text
                            }
                        }
                    }
                    CustomButton
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width/4
                        height: parent.height*0.8
                        backgroundradius: 20
                        text: qsTr("0")
                        onClicked:
                        {
                            itemvalue.text += text
                        }
                    }
                    CustomButton
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width/4
                        height: parent.height*0.8
                        backgroundradius: 20
                        text: qsTr(".")
                        onClicked:
                        {
                            itemvalue.text += text
                        }
                    }
                    CustomButton
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width/4
                        height: parent.height*0.8
                        backgroundradius: 20
                        text: qsTr("ok")
                        onClicked:
                        {
                            crossLineDetection()
                        }
                    }
                }
            }
        }
    }

    function crossLineDetection()
    {
        var crossline = true

        if(Number(itemvalue.text) <= Number(rootw.itemmaxLimit) && Number(itemvalue.text) >= Number(rootw.itemminLimit))
        {
            crossline = false
        }

        if(crossline)
        {
            itemvalue.text = qsTr("error")
        }
        else
        {
            rootw.result = Number(itemvalue.text).toFixed(rootw.itemdigit)
            rootw.destroy()
        }
    }
}
