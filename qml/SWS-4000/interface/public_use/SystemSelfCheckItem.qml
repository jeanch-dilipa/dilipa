import QtQuick 2.0
import QtQml 2.3
import QtQuick.Controls 2.5

import "qrc:/common/"

Rectangle
{
    id:root
    width: 1024/14//parent.width/14
    height: 608/3*2//parent.height/3*2
    radius: width/4
    border.width: 1
    border.color: "red"

    property bool stratCheck: false
    property var changeNum: 1
    property var checkname: ""
    property var rectColor: 0
    property var selfCheckItem
    property bool reSelfCheck: false
    property bool showRefresh: false
    property bool correctState: false

    property var rangeValue: 90;
    property var nowRange: 0;

    //Sin曲线
    property int sX: 0;
    property int sY: root.height / 2;
    property int axisLength: root.width;        //轴长
    property double waveWidth: 0.015;   //波浪宽度,数越小越宽
    property double waveHeight: 6;      //波浪高度,数越大越高
    property double speed: 0.09;        //波浪速度，数越大速度越快
    property double xOffset: 0;         //波浪x偏移量

    onCorrectStateChanged:
    {
        showRefresh = false
        rectColor = 0
    }

    onStratCheckChanged:
    {
        timer.start()
    }
    onChecknameChanged:
    {
        checkName.text = checkname
    }
    onShowRefreshChanged:
    {
        if(showRefresh === true)
        {
            refresh.visible = true
        }
        else
        {
            refresh.visible = false
        }
    }

    Canvas
    {
        id: canvas
        height: root.height
        width: root.width
        anchors.centerIn: root
        onPaint:
        {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, canvas.width, canvas.height);

            ctx.beginPath()
            ctx.arc(canvas.x + root.radius,canvas.y + root.radius,root.radius,Math.PI,Math.PI*1.5)
            ctx.lineTo(canvas.width-root.radius,0)
            ctx.arc(canvas.width-root.radius,canvas.y + root.radius,root.radius,Math.PI*1.5,0)
            ctx.lineTo(canvas.width,canvas.height - root.radius)
            ctx.arc(canvas.width-root.radius,canvas.height - root.radius,root.radius,0,Math.PI*0.5)
            ctx.lineTo(canvas.x + root.radius,canvas.height)
            ctx.arc(canvas.x + root.radius,canvas.height - root.radius,root.radius,Math.PI*0.5,Math.PI)
            ctx.lineTo(0,canvas.y + root.radius)
            ctx.stroke()
            ctx.clip()

            //sin曲线
            ctx.save();
            var points=[];
            ctx.beginPath();
            for(var x = root.sX; x < root.sX + root.axisLength; x += 20 / root.axisLength)
            {
                var y = -Math.sin((root.sX + x) * root.waveWidth + root.xOffset);
                var dY = canvas.height * (1 - root.nowRange / 100 );
                points.push([x, dY + y * root.waveHeight]);
                ctx.lineTo(x, dY + y * root.waveHeight);
            }

            //显示波浪
            ctx.lineTo(root.axisLength, canvas.height);
            ctx.lineTo(root.sX, canvas.height);
            ctx.lineTo(points[0][0],points[0][1]);
            ctx.fillStyle = root.rectColor ? "#cc0066" : '#00bfff';
            ctx.fill();
            ctx.restore();

            //增加Rang值
            if(root.nowRange <= root.rangeValue)
            {
                root.nowRange += root.changeNum;
            }

            if(root.nowRange > root.rangeValue)
            {
                root.nowRange -= root.changeNum;
                root.changeNum = 0
            }
            root.xOffset += root.speed;
        }

        Timer
        {
            id: timer
            running: false
            repeat: true
            interval: 10
            onTriggered:
            {
                canvas.requestPaint();
            }
        }
    }

    Text
    {
        id:checkName
        anchors.centerIn: root
        text: qsTr(checkname)
        font.pointSize: root.width/4
        width: root.width/4
        height: checkname.length*font.pointSize
        wrapMode: Text.WordWrap
    }

    Image
    {
        id: refresh
        width: 50
        height: 50
        visible: false
        anchors.top: root.top
        anchors.topMargin: 15
        anchors.horizontalCenter: parent.horizontalCenter
        source: "qrc:/new/prefix1/image/selfCheck_refresh.png"

    }
    onReSelfCheckChanged:
    {
        if(root.selfCheckItem < 0x4000)
        {
            root.nowRange = 0
        }
        root.rangeValue = 90
        root.correctState = root.correctState ? false :true
        DISPATHER.signal_reSelfCheck(selfCheckItem)
    }

    MouseArea
    {
        anchors.fill: refresh
        onClicked:
        {
            root.reSelfCheck = root.reSelfCheck ? false : true
        }
    }

    onSelfCheckItemChanged:
    {
        switch(selfCheckItem)
        {
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_11:
                checkitem.text = qsTr("11")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_21:
                checkitem.text = qsTr("21")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_21_1:
                checkitem.text = qsTr("21_1")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_21_2:
                checkitem.text = qsTr("21_2")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_22:
                checkitem.text = qsTr("22")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_22_1:
                checkitem.text = qsTr("22_1")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_22_2:
                checkitem.text = qsTr("22_2")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_31:
                checkitem.text = qsTr("31")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32:
                checkitem.text = qsTr("32")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_1:
                checkitem.text = qsTr("32_1")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_2:
                checkitem.text = qsTr("32_2")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_3:
                checkitem.text = qsTr("32_3")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_4:
                checkitem.text = qsTr("32_4")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_5:
                checkitem.text = qsTr("32_5")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_6:
                checkitem.text = qsTr("32_6")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33:
                checkitem.text = qsTr("33")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_1:
                checkitem.text = qsTr("33_1")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_2:
                checkitem.text = qsTr("33_2")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_3:
                checkitem.text = qsTr("33_3")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_4:
                checkitem.text = qsTr("33_4")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_5:
                checkitem.text = qsTr("33_5")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_6:
                checkitem.text = qsTr("33_6")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_36:
                checkitem.text = qsTr("36")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_36_1:
                checkitem.text = qsTr("36_1")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_36_2:
                checkitem.text = qsTr("36_2")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_11:
                checkitem.text = qsTr("11")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_1:
                checkitem.text = qsTr("12_1")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_2:
                checkitem.text = qsTr("12_2")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_3:
                checkitem.text = qsTr("12_3")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_4:
                checkitem.text = qsTr("12_4")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_5:
                checkitem.text = qsTr("12_5")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_13:
                checkitem.text = qsTr("13")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_14:
                checkitem.text = qsTr("14")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_15_1:
                checkitem.text = qsTr("15_1")
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_15_2:
                checkitem.text = qsTr("15_2")
                break
            default:
                checkitem.text = qsTr("")
                break
        }
    }

    Text
    {
        id: checkitem
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        text: qsTr("")
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.3300000429153442}D{i:1;invisible:true}D{i:3;invisible:true}
D{i:4;invisible:true}D{i:5;invisible:true}D{i:6;invisible:true}
}
##^##*/
