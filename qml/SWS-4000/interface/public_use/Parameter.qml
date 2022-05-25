import QtQuick 2.5
import QtQuick.Controls 2.5
import QtQuick.Window 2.3
import QtGraphicalEffects 1.0
import QtQuick.LocalStorage 2.12
import QtQml 2.3

import "../Custom_model"
import "SqliteSet.js" as DB

Window
{
    id:rootw
    width: 1024
    height: 608

    flags: Qt.FramelessWindowHint
    opacity: 0.9
    color: "#00000000"

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

    property IntelligentKeyboard keyview
    property CustomButton currentbutton
    property var buttonlist: []

    Component.onCompleted:
    {
        /*初始化列表*/
        buttonlist[0] = dislysateTemp

        loadParameterValue()
    }

    Connections
    {
        target: rootw.keyview
        onResultChanged:
        {
            rootw.currentbutton.value = rootw.keyview.result
            rootw.currentbutton.snap_value = rootw.keyview.result
            var cmd = "update param_table set snapvalue = " + rootw.currentbutton.snap_value * rootw.currentbutton.gain + ",value = " + rootw.currentbutton.value * rootw.currentbutton.gain + " where description = '" + rootw.currentbutton.description + "'"
            DB.loadSqliteData(cmd)
        }
    }

    Rectangle
    {
        id:root
        width: rootw.width-20
        height: rootw.height-20
        anchors.centerIn: parent
        radius: 10

        Row
        {
            id:r1
            Rectangle
            {
                id:dislysateTempRect
                width: root.width/3
                height: root.height/8
                radius: 10
                Row
                {
                    anchors.fill: parent
                    Rectangle
                    {
                        width: parent.width*0.4
                        height: parent.height
                        Text
                        {
                            anchors.fill: parent
                            anchors.centerIn: parent
                            font.pointSize: 12
                            text: qsTr("透析液温度:")
    //                        wrapMode: Text.WordWrap
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideLeft
                        }
                    }
                    Rectangle
                    {
                        width: parent.width*0.4
                        height: parent.height
                        CustomButton
                        {
                            id:dislysateTemp
                            width: parent.width*0.8
                            height: parent.height/2
                            anchors.centerIn: parent
                            backgroundradius: width/8
                            textfontpointsize: 20
                            value: 37.0
                            snap_value: 37.0
                            def_value: 37.0
                            max_value: 40.0
                            min_value: 33.0
                            gain: 10
                            description: qsTr("透析液温度")
                            text: value

                            onClicked:
                            {
                                setParameterValue(description,max_value,min_value,gain.toString().length - 1)
                                rootw.currentbutton = this
                            }
                        }
                    }
                    Rectangle
                    {
                        width: parent.width*0.2
                        height: parent.height
                        Text
                        {
                            anchors.fill: parent
                            anchors.centerIn: parent
                            font.pointSize: 12
                            horizontalAlignment: Text.AlignLeft
                            verticalAlignment: Text.AlignVCenter
                            text: qsTr("℃")
                        }
                    }
                }
            }

            Rectangle
            {
                id:t1
                width: root.width/3
                height: root.height/8
                radius: 10
                Row
                {
                    anchors.fill: parent
                    Rectangle
                    {
                        width: parent.width*0.4
                        height: parent.height
                        Text
                        {
                            anchors.fill: parent
                            anchors.centerIn: parent
                            font.pointSize: 12
                            text: qsTr("透析液温度:")
    //                        wrapMode: Text.WordWrap
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideLeft
                        }
                    }
                    Rectangle
                    {
                        width: parent.width*0.4
                        height: parent.height
                        CustomButton
                        {
                            width: parent.width*0.8
                            height: parent.height/2
                            anchors.centerIn: parent
                            backgroundradius: width/8
                            textfontpointsize: 20
                            text: qsTr("37")
                        }
                    }
                    Rectangle
                    {
                        width: parent.width*0.2
                        height: parent.height
                        Text
                        {
                            anchors.fill: parent
                            anchors.centerIn: parent
                            font.pointSize: 12
                            horizontalAlignment: Text.AlignLeft
                            verticalAlignment: Text.AlignVCenter
                            text: qsTr("℃")
                        }
                    }
                }
            }

            Rectangle
            {
                id:t2
                width: root.width/3
                height: root.height/8
                radius: 10
                Row
                {
                    anchors.fill: parent
                    Rectangle
                    {
                        width: parent.width*0.4
                        height: parent.height
                        Text
                        {
                            anchors.fill: parent
                            anchors.centerIn: parent
                            font.pointSize: 12
                            text: qsTr("透析液温度:")
    //                        wrapMode: Text.WordWrap
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideLeft
                        }
                    }
                    Rectangle
                    {
                        width: parent.width*0.4
                        height: parent.height
                        CustomButton
                        {
                            width: parent.width*0.8
                            height: parent.height/2
                            anchors.centerIn: parent
                            backgroundradius: width/8
                            textfontpointsize: 20
                            text: qsTr("37")
                        }
                    }
                    Rectangle
                    {
                        width: parent.width*0.2
                        height: parent.height
                        Text
                        {
                            anchors.fill: parent
                            anchors.centerIn: parent
                            font.pointSize: 12
                            horizontalAlignment: Text.AlignLeft
                            verticalAlignment: Text.AlignVCenter
                            text: qsTr("℃")
                        }
                    }
                }
            }
        }

        Row
        {
            id:r2
            anchors.top: r1.bottom
            Rectangle
            {
                id:t3
                width: root.width/3
                height: root.height/8
                radius: 10
                Row
                {
                    anchors.fill: parent
                    Rectangle
                    {
                        width: parent.width*0.4
                        height: parent.height
                        Text
                        {
                            anchors.fill: parent
                            anchors.centerIn: parent
                            font.pointSize: 12
                            text: qsTr("透析液温度:")
    //                        wrapMode: Text.WordWrap
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideLeft
                        }
                    }
                    Rectangle
                    {
                        width: parent.width*0.4
                        height: parent.height
                        CustomButton
                        {
                            width: parent.width*0.8
                            height: parent.height/2
                            anchors.centerIn: parent
                            backgroundradius: width/8
                            textfontpointsize: 20
                            text: qsTr("37")
                        }
                    }
                    Rectangle
                    {
                        width: parent.width*0.2
                        height: parent.height
                        Text
                        {
                            anchors.fill: parent
                            anchors.centerIn: parent
                            font.pointSize: 12
                            horizontalAlignment: Text.AlignLeft
                            verticalAlignment: Text.AlignVCenter
                            text: qsTr("℃")
                        }
                    }
                }
            }

            Rectangle
            {
                id:t4
                width: root.width/3
                height: root.height/8
                radius: 10
                Row
                {
                    anchors.fill: parent
                    Rectangle
                    {
                        width: parent.width*0.4
                        height: parent.height
                        Text
                        {
                            anchors.fill: parent
                            anchors.centerIn: parent
                            font.pointSize: 12
                            text: qsTr("透析液温度:")
    //                        wrapMode: Text.WordWrap
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideLeft
                        }
                    }
                    Rectangle
                    {
                        width: parent.width*0.4
                        height: parent.height
                        CustomButton
                        {
                            width: parent.width*0.8
                            height: parent.height/2
                            anchors.centerIn: parent
                            backgroundradius: width/8
                            textfontpointsize: 20
                            text: qsTr("37")
                        }
                    }
                    Rectangle
                    {
                        width: parent.width*0.2
                        height: parent.height
                        Text
                        {
                            anchors.fill: parent
                            anchors.centerIn: parent
                            font.pointSize: 12
                            horizontalAlignment: Text.AlignLeft
                            verticalAlignment: Text.AlignVCenter
                            text: qsTr("℃")
                        }
                    }
                }
            }

            Rectangle
            {
                id:t5
                width: root.width/3
                height: root.height/8
                radius: 10
                Row
                {
                    anchors.fill: parent
                    Rectangle
                    {
                        width: parent.width*0.4
                        height: parent.height
                        Text
                        {
                            anchors.fill: parent
                            anchors.centerIn: parent
                            font.pointSize: 12
                            text: qsTr("透析液温度:")
    //                        wrapMode: Text.WordWrap
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideLeft
                        }
                    }
                    Rectangle
                    {
                        width: parent.width*0.4
                        height: parent.height
                        CustomButton
                        {
                            width: parent.width*0.8
                            height: parent.height/2
                            anchors.centerIn: parent
                            backgroundradius: width/8
                            textfontpointsize: 20
                            text: qsTr("37")
                        }
                    }
                    Rectangle
                    {
                        width: parent.width*0.2
                        height: parent.height
                        Text
                        {
                            anchors.fill: parent
                            anchors.centerIn: parent
                            font.pointSize: 12
                            horizontalAlignment: Text.AlignLeft
                            verticalAlignment: Text.AlignVCenter
                            text: qsTr("℃")
                        }
                    }
                }
            }
        }

    }

    function loadParameterValue()
    {
        var cmd = "select * from param_table"
        var rs = DB.loadSqliteData(cmd)
        var currentindex = 0
        while(currentindex < rs.rows.length)
        {
            var currentItem = rs.rows.item(currentindex)
            buttonlist[currentindex].value = Number(currentItem.value/currentItem.gain).toFixed(currentItem.gain.toString().length-1)
            buttonlist[currentindex].snap_value = Number(currentItem.snapvalue/currentItem.gain).toFixed(currentItem.gain.toString().length-1)
            buttonlist[currentindex].def_value = Number(currentItem.defvalue/currentItem.gain).toFixed(currentItem.gain.toString().length-1)
            buttonlist[currentindex].max_value = Number(currentItem.upvalue/currentItem.gain).toFixed(currentItem.gain.toString().length-1)
            buttonlist[currentindex].min_value = Number(currentItem.lowvalue/currentItem.gain).toFixed(currentItem.gain.toString().length-1)
            buttonlist[currentindex].gain = Number(currentItem.gain)
            buttonlist[currentindex].description = currentItem.description
            currentindex++
        }
    }

    function setParameterValue(itemName,itemmaxLimit,itemminLimit,itemdigit)
    {
        if(rootw.keyview)
        {
            rootw.keyview.destroy()
        }
        var view = Qt.createComponent("qrc:/interface/public_use/IntelligentKeyboard.qml")
        rootw.keyview = view.createObject(root)
        rootw.keyview.itemName = itemName
        rootw.keyview.itemmaxLimit = itemmaxLimit
        rootw.keyview.itemminLimit = itemminLimit
        rootw.keyview.itemdigit = itemdigit
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/

