import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQml 2.3

import "../Custom_model"
import "SqliteSet.js" as DB

Rectangle
{
    id:root
    width: 1024/10*9-20
    height: 588

    property var sliderlist: []
    property IntelligentKeyboard keyview
    property CustomSlider currentslider

    Component.onCompleted:
    {
        sliderlist[0] = temp_max_limit
        sliderlist[1] = temp_min_limit
        sliderlist[2] = ap_max_limit
        sliderlist[3] = ap_min_limit
        sliderlist[4] = vp_max_limit
        sliderlist[5] = vp_min_limit
        sliderlist[6] = tmp_max_limit
        sliderlist[7] = tmp_min_limit

        loadParameterValue()
    }

    Connections
    {
        target: root.keyview
        onResultChanged:
        {
            currentslider.value = root.keyview.result
            var cmd = "update alarm_table set snapvalue = " + root.currentslider.snap_value * root.currentslider.gain + ",value = " + root.currentslider.value * root.currentslider.gain + " where description = '" + root.currentslider.description + "'"
            DB.loadSqliteData(cmd)
        }
    }


    Rectangle
    {
        id:ap_max_limit_model
        width: root.width/3
        height: root.height/6
        anchors.top: root.top
        Text
        {
            id:ap_max_limit_text
            width: parent.width
            height: ap_max_limit_model.height/3
            anchors.horizontalCenter: ap_max_limit_model.horizontalCenter
            text: qsTr("ap_max_limit")
            font.pointSize: ap_max_limit_model.width/20
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    root.currentslider = ap_max_limit
                    setParameterValue(ap_max_limit.description,Math.floor(ap_max_limit.max_value).toFixed(ap_max_limit.gain.toString().length - 1),Math.floor(ap_min_limit.value).toFixed(ap_max_limit.gain.toString().length - 1),ap_max_limit.gain)
                }
            }
        }
        CustomSlider
        {
            id:ap_max_limit
            width: ap_max_limit_model.width*0.9
            anchors.top: ap_max_limit_text.bottom
            anchors.horizontalCenter: ap_max_limit_model.horizontalCenter
            from:Math.floor(ap_min_limit.value)
            to:max_value
        }
        Label
        {
            id:ap_max_limit_min
            anchors.top: ap_max_limit.bottom
            anchors.left: ap_max_limit_model.left
            anchors.leftMargin: 23
            text: ap_max_limit.from
        }
        Label
        {
            id:ap_max_limit_value
            anchors.top: ap_max_limit.bottom
            anchors.horizontalCenter: ap_max_limit_model.horizontalCenter
            text: Math.floor(ap_max_limit.value)
        }
        Label
        {
            id:ap_max_limit_max
            anchors.top: ap_max_limit.bottom
            anchors.right: ap_max_limit_model.right
            anchors.rightMargin: 23
            text: ap_max_limit.to
        }
    }
    Rectangle
    {
        id:ap_min_limit_model
        width: root.width/3
        height: root.height/6
        anchors.top: ap_max_limit_model.bottom
        Text
        {
            id:ap_min_limit_text
            width: parent.width
            height: ap_min_limit_model.height/3
            anchors.horizontalCenter: ap_min_limit_model.horizontalCenter
            text: qsTr("ap_min_limit")
            font.pointSize: ap_min_limit_model.width/20
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    root.currentslider = ap_min_limit
                    setParameterValue(ap_min_limit.description,Math.floor(ap_max_limit.value).toFixed(ap_min_limit.gain.toString().length - 1),Math.floor(ap_min_limit.min_value).toFixed(ap_min_limit.gain.toString().length - 1),ap_min_limit.gain)
                }
            }
        }
        CustomSlider
        {
            id:ap_min_limit
            width: ap_min_limit_model.width*0.9
            anchors.top: ap_min_limit_text.bottom
            anchors.horizontalCenter: ap_min_limit_model.horizontalCenter
            from:min_value
            to:Math.floor(ap_max_limit.value)
        }
        Label
        {
            id:ap_min_limit_min
            anchors.top: ap_min_limit.bottom
            anchors.left: ap_min_limit_model.left
            anchors.leftMargin: 23
            text: ap_min_limit.from
        }
        Label
        {
            id:ap_min_limit_value
            anchors.top: ap_min_limit.bottom
            anchors.horizontalCenter: ap_min_limit_model.horizontalCenter
            text: Math.floor(ap_min_limit.value)
        }
        Label
        {
            id:ap_min_limit_max
            anchors.top: ap_min_limit.bottom
            anchors.right: ap_min_limit_model.right
            anchors.rightMargin: 23
            text: ap_min_limit.to
        }
    }

    Rectangle
    {
        id:vp_max_limit_model
        width: root.width/3
        height: root.height/6
        anchors.left: ap_max_limit_model.right
        anchors.top: root.top
        Text
        {
            id:vp_max_limit_text
            width: parent.width
            height: vp_max_limit_model.height/3
            anchors.horizontalCenter: vp_max_limit_model.horizontalCenter
            text: qsTr("vp_max_limit")
            font.pointSize: vp_max_limit_model.width/20
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    root.currentslider = vp_max_limit
                    setParameterValue(vp_max_limit.description,Math.floor(vp_max_limit.max_value).toFixed(vp_max_limit.gain.toString().length - 1),Math.floor(vp_min_limit.value).toFixed(vp_max_limit.gain.toString().length - 1),vp_max_limit.gain)
                }
            }
        }
        CustomSlider
        {
            id:vp_max_limit
            width: vp_max_limit_model.width*0.9
            anchors.top: vp_max_limit_text.bottom
            anchors.horizontalCenter: vp_max_limit_model.horizontalCenter
            from:Math.floor(vp_min_limit.value)
            to:max_value
        }
        Label
        {
            id:vp_max_limit_min
            anchors.top: vp_max_limit.bottom
            anchors.left: vp_max_limit_model.left
            anchors.leftMargin: 23
            text: vp_max_limit.from
        }
        Label
        {
            id:vp_max_limit_value
            anchors.top: vp_max_limit.bottom
            anchors.horizontalCenter: vp_max_limit_model.horizontalCenter
            text: Math.floor(vp_max_limit.value)
        }
        Label
        {
            id:vp_max_limit_max
            anchors.top: vp_max_limit.bottom
            anchors.right: vp_max_limit_model.right
            anchors.rightMargin: 23
            text: vp_max_limit.to
        }
    }
    Rectangle
    {
        id:vp_min_limit_model
        width: root.width/3
        height: root.height/6
        anchors.left: ap_min_limit_model.right
        anchors.top: vp_max_limit_model.bottom
        Text
        {
            id:vp_min_limit_text
            width: parent.width
            height: vp_min_limit_model.height/3
            anchors.horizontalCenter: vp_min_limit_model.horizontalCenter
            text: qsTr("vp_min_limit")
            font.pointSize: vp_min_limit_model.width/20
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    root.currentslider = vp_min_limit
                    setParameterValue(vp_min_limit.description,Math.floor(vp_max_limit.value).toFixed(vp_min_limit.gain.toString().length - 1),Math.floor(vp_min_limit.min_value).toFixed(vp_min_limit.gain.toString().length - 1),vp_min_limit.gain)
                }
            }
        }
        CustomSlider
        {
            id:vp_min_limit
            width: vp_min_limit_model.width*0.9
            anchors.top: vp_min_limit_text.bottom
            anchors.horizontalCenter: vp_min_limit_model.horizontalCenter
            from:min_value
            to:Math.floor(vp_max_limit.value)
        }
        Label
        {
            id:vp_min_limit_min
            anchors.top: vp_min_limit.bottom
            anchors.left: vp_min_limit_model.left
            anchors.leftMargin: 23
            text: vp_min_limit.from
        }
        Label
        {
            id:vp_min_limit_value
            anchors.top: vp_min_limit.bottom
            anchors.horizontalCenter: vp_min_limit_model.horizontalCenter
            text: Math.floor(vp_min_limit.value)
        }
        Label
        {
            id:vp_min_limit_max
            anchors.top: vp_min_limit.bottom
            anchors.right: vp_min_limit_model.right
            anchors.rightMargin: 23
            text: vp_min_limit.to
        }
    }

    Rectangle
    {
        id:tmp_max_limit_model
        width: root.width/3
        height: root.height/6
        anchors.left: vp_max_limit_model.right
        anchors.top: root.top
        Text
        {
            id:tmp_max_limit_text
            width: parent.width
            height: tmp_max_limit_model.height/3
            anchors.horizontalCenter: tmp_max_limit_model.horizontalCenter
            text: qsTr("tmp_max_limit")
            font.pointSize: tmp_max_limit_model.width/20
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    root.currentslider = tmp_max_limit
                    setParameterValue(tmp_max_limit.description,Math.floor(tmp_max_limit.max_value).toFixed(tmp_max_limit.gain.toString().length - 1),Math.floor(tmp_min_limit.value).toFixed(tmp_max_limit.gain.toString().length - 1),tmp_max_limit.gain)
                }
            }
        }
        CustomSlider
        {
            id:tmp_max_limit
            width: tmp_max_limit_model.width*0.9
            anchors.top: tmp_max_limit_text.bottom
            anchors.horizontalCenter: tmp_max_limit_model.horizontalCenter
            from:Math.floor(tmp_min_limit.value)
            to:max_value
        }
        Label
        {
            id:tmp_max_limit_min
            anchors.top: tmp_max_limit.bottom
            anchors.left: tmp_max_limit_model.left
            anchors.leftMargin: 23
            text: tmp_max_limit.from
        }
        Label
        {
            id:tmp_max_limit_value
            anchors.top: tmp_max_limit.bottom
            anchors.horizontalCenter: tmp_max_limit_model.horizontalCenter
            text: Math.floor(tmp_max_limit.value)
        }
        Label
        {
            id:tmp_max_limit_max
            anchors.top: tmp_max_limit.bottom
            anchors.right: tmp_max_limit_model.right
            anchors.rightMargin: 23
            text: tmp_max_limit.to
        }
    }
    Rectangle
    {
        id:tmp_min_limit_model
        width: root.width/3
        height: root.height/6
        anchors.left: vp_min_limit_model.right
        anchors.top: tmp_max_limit_model.bottom
        Text
        {
            id:tmp_min_limit_text
            width: parent.width
            height: tmp_min_limit_model.height/3
            anchors.horizontalCenter: tmp_min_limit_model.horizontalCenter
            text: qsTr("tmp_min_limit")
            font.pointSize: tmp_min_limit_model.width/20
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    root.currentslider = tmp_min_limit
                    setParameterValue(tmp_min_limit.description,Math.floor(tmp_max_limit.value).toFixed(tmp_min_limit.gain.toString().length - 1),Math.floor(tmp_min_limit.min_value).toFixed(tmp_min_limit.gain.toString().length - 1),tmp_min_limit.gain)
                }
            }
        }
        CustomSlider
        {
            id:tmp_min_limit
            width: tmp_min_limit_model.width*0.9
            anchors.top: tmp_min_limit_text.bottom
            anchors.horizontalCenter: tmp_min_limit_model.horizontalCenter
            from:min_value
            to:Math.floor(tmp_max_limit.value)
        }
        Label
        {
            id:tmp_min_limit_min
            anchors.top: tmp_min_limit.bottom
            anchors.left: tmp_min_limit_model.left
            anchors.leftMargin: 23
            text: tmp_min_limit.from
        }
        Label
        {
            id:tmp_min_limit_value
            anchors.top: tmp_min_limit.bottom
            anchors.horizontalCenter: tmp_min_limit_model.horizontalCenter
            text: Math.floor(tmp_min_limit.value)
        }
        Label
        {
            id:tmp_min_limit_max
            anchors.top: tmp_min_limit.bottom
            anchors.right: tmp_min_limit_model.right
            anchors.rightMargin: 23
            text: tmp_min_limit.to
        }
    }

    Rectangle
    {
        id:temp_max_limit_model
        width: root.width/3
        height: root.height/6
        anchors.top: ap_min_limit_model.bottom
        Text
        {
            id:temp_max_limit_text
            width: parent.width
            height: temp_max_limit_model.height/3
            anchors.horizontalCenter: temp_max_limit_model.horizontalCenter
            text: qsTr("temp_max_limit")
            font.pointSize: temp_max_limit_model.width/20
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    root.currentslider = temp_max_limit
                    setParameterValue(temp_max_limit.description,Math.floor(temp_max_limit.max_value).toFixed(temp_max_limit.gain.toString().length - 1),Math.floor(temp_min_limit.value).toFixed(temp_max_limit.gain.toString().length - 1),temp_max_limit.gain)
                }
            }
        }
        CustomSlider
        {
            id:temp_max_limit
            width: temp_max_limit_model.width*0.9
            anchors.top: temp_max_limit_text.bottom
            anchors.horizontalCenter: temp_max_limit_model.horizontalCenter
            from:Math.floor(temp_min_limit.value)
            to:max_value
        }
        Label
        {
            id:temp_max_limit_min
            anchors.top: temp_max_limit.bottom
            anchors.left: temp_max_limit_model.left
            anchors.leftMargin: 23
            text: temp_max_limit.from
        }
        Label
        {
            id:temp_max_limit_value
            anchors.top: temp_max_limit.bottom
            anchors.horizontalCenter: temp_max_limit_model.horizontalCenter
            text: Math.floor(temp_max_limit.value)
        }
        Label
        {
            id:temp_max_limit_max
            anchors.top: temp_max_limit.bottom
            anchors.right: temp_max_limit_model.right
            anchors.rightMargin: 23
            text: temp_max_limit.to
        }
    }
    Rectangle
    {
        id:temp_min_limit_model
        width: root.width/3
        height: root.height/6
        anchors.top: temp_max_limit_model.bottom
        Text
        {
            id:temp_min_limit_text
            width: parent.width
            height: temp_min_limit_model.height/3
            anchors.horizontalCenter: temp_min_limit_model.horizontalCenter
            text: qsTr("temp_min_limit")
            font.pointSize: temp_min_limit_model.width/20
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    root.currentslider = temp_min_limit
                    setParameterValue(temp_min_limit.description,Math.floor(temp_max_limit.value).toFixed(temp_min_limit.gain.toString().length - 1),Math.floor(temp_min_limit.min_value).toFixed(temp_min_limit.gain.toString().length - 1),temp_min_limit.gain)
                }
            }
        }
        CustomSlider
        {
            id:temp_min_limit
            width: temp_min_limit_model.width*0.9
            anchors.top: temp_min_limit_text.bottom
            anchors.horizontalCenter: temp_min_limit_model.horizontalCenter
            from:min_value
            to:Math.floor(temp_max_limit.value)
        }
        Label
        {
            id:temp_min_limit_min
            anchors.top: temp_min_limit.bottom
            anchors.left: temp_min_limit_model.left
            anchors.leftMargin: 23
            text: temp_min_limit.from
        }
        Label
        {
            id:temp_min_limit_value
            anchors.top: temp_min_limit.bottom
            anchors.horizontalCenter: temp_min_limit_model.horizontalCenter
            text: Math.floor(temp_min_limit.value)
        }
        Label
        {
            id:temp_min_limit_max
            anchors.top: temp_min_limit.bottom
            anchors.right: temp_min_limit_model.right
            anchors.rightMargin: 23
            text: temp_min_limit.to
        }
    }

    function loadParameterValue()
    {
        var cmd = "select * from alarm_table"
        var rs = DB.loadSqliteData(cmd)
        var currentindex = 0
        while(currentindex < rs.rows.length)
        {
            var currentItem = rs.rows.item(currentindex)
            sliderlist[currentindex].value = Number(currentItem.value/currentItem.gain).toFixed(currentItem.gain.toString().length-1)
            sliderlist[currentindex].snap_value = Number(currentItem.snapvalue/currentItem.gain).toFixed(currentItem.gain.toString().length-1)
            sliderlist[currentindex].def_value = Number(currentItem.defvalue/currentItem.gain).toFixed(currentItem.gain.toString().length-1)
            sliderlist[currentindex].max_value = Number(currentItem.upvalue/currentItem.gain).toFixed(currentItem.gain.toString().length-1)
            sliderlist[currentindex].min_value = Number(currentItem.lowvalue/currentItem.gain).toFixed(currentItem.gain.toString().length-1)
            sliderlist[currentindex].gain = Number(currentItem.gain)
            sliderlist[currentindex].description = currentItem.description
            currentindex++
        }
    }

    function setParameterValue(itemName,itemmaxLimit,itemminLimit,itemdigit)
    {
        if(root.keyview)
        {
            root.keyview.destroy()
        }
        var view = Qt.createComponent("qrc:/interface/public_use/IntelligentKeyboard.qml")
        root.keyview = view.createObject(root)
        root.keyview.itemName = itemName
        root.keyview.itemmaxLimit = itemmaxLimit
        root.keyview.itemminLimit = itemminLimit
        root.keyview.itemdigit = itemdigit
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
