import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Controls 1.4
import QtQuick.LocalStorage 2.12
//import QtQml 2.12

import "../Custom_model"
import "qrc:/common/"
import "SqliteSet.js" as DB

Rectangle
{
    id:root
    width: 1024/10*9-20
    height: 588
    radius: 10

    ListModel
    {
        id:pathmodel
    }

    PathView
    {
        id:pathview
        width: root.width
        height: root.height/8*7

        delegate: flipCardDelegate
        model: pathmodel

        path: Path
        {
            startX: root.width/2
            startY: 0

            PathAttribute { name: "itemZ"; value: 0 }           //路径属性层级、角度、缩放
            PathAttribute { name: "itemAngle"; value: -90.0; }
            PathAttribute { name: "itemScale"; value: 0.5; }
            PathLine { x: root.width/2; y: root.height*0.4; }
            PathPercent { value: 0.48; }
            PathLine { x: root.width/2; y: root.height*0.5; }
            PathAttribute { name: "itemAngle"; value: 0.0; }
            PathAttribute { name: "itemScale"; value: 1.0; }
            PathAttribute { name: "itemZ"; value: 100 }
            PathLine { x: root.width/2; y: root.height*0.6; }
            PathPercent { value: 0.52; }
            PathLine { x: root.width/2; y: root.height; }
            PathAttribute { name: "itemAngle"; value: 90.0; }
            PathAttribute { name: "itemScale"; value: 0.5; }
            PathAttribute { name: "itemZ"; value: 0 }
        }

        pathItemCount: 13       //显示数量

        preferredHighlightBegin: 0.5        //可见代理项
        preferredHighlightEnd: 0.5
    }

    Component
    {
        id: flipCardDelegate

        Item
        {
            id: wrapper

            width: root.width - 20
            height: 60

            visible: PathView.onPath

            scale: PathView.itemScale
            z: PathView.itemZ

            property variant rotX: PathView.itemAngle
            transform: Rotation { axis { x: 1; y: 0; z: 0 } angle: wrapper.rotX; origin { x: 32; y: 32; } }

            CustomButton
            {
                id:soleItem
                anchors.fill: wrapper
                smooth: true
                backgroundradius: 30
                text: qsTr("")
                backgroundDefaultColor: alarmGrade === 1 ? "red" : alarmGrade === 4 ? "blue" : "yellow"

                Text
                {
                    id:alarmnum
                    anchors.left: soleItem.left
                    anchors.leftMargin: 10
                    anchors.verticalCenter: soleItem.verticalCenter
                    text: index
                    font.pixelSize: 20
                }

                Text
                {
                    id:alarmtext
                    anchors.horizontalCenter: soleItem.horizontalCenter
                    anchors.verticalCenter: soleItem.verticalCenter
                    text: alarmName
                    font.pixelSize: 20
                }

                Text
                {
                    id:alarmtime
                    anchors.right: soleItem.right
                    anchors.rightMargin: 10
                    anchors.verticalCenter: soleItem.verticalCenter
                    text: alarmDateTime
                    font.pixelSize: 20
                }
            }
        }
    }

    Rectangle
    {
        id:searchTime
        width: root.width
        height: root.height/8
        anchors.top: pathview.bottom
        color: "#00000000"

        CustomButton
        {
            id:last
            width: searchTime.width/10
            height: searchTime.height/2
            anchors.left: searchTime.left
            anchors.leftMargin: 20
            anchors.verticalCenter: searchTime.verticalCenter
            backgroundradius: width/4
            textfontpointsize: 25
            text: qsTr("last")

            onClicked:
            {
                pathmodel.clear()
                calendar.selectedDate = Qt.formatDate(new Date(calendar.selectedDate.getTime() - 86400000),"yyyy-MM-dd")
                alarmtime.text = Qt.formatDate(calendar.selectedDate,"yyyy-MM-dd")
                loadAlarmData()
            }
        }

        Text
        {
            id: alarmtime
            anchors.horizontalCenter: searchTime.horizontalCenter
            anchors.verticalCenter: searchTime.verticalCenter
            font.pointSize: 15
            text: Qt.formatDate(calendar.selectedDate,"yyyy-MM-dd")

            MouseArea
            {
                anchors.fill: alarmtime
                onClicked:
                {
                    calendar.visible = true
                }
            }
        }

        CustomButton
        {
            id:next
            width: searchTime.width/10
            height: searchTime.height/2
            anchors.right: searchTime.right
            anchors.rightMargin: 20
            anchors.verticalCenter: searchTime.verticalCenter
            backgroundradius: width/4
            textfontpointsize: 25
            text: qsTr("next")

            onClicked:
            {
                pathmodel.clear()
                calendar.selectedDate = Qt.formatDate(new Date(calendar.selectedDate.getTime() + 86400000),"yyyy-MM-dd")
                alarmtime.text = Qt.formatDate(calendar.selectedDate,"yyyy-MM-dd")
                loadAlarmData()
            }
        }
    }

    Component.onCompleted:
    {
        loadAlarmData()
    }

    Calendar
    {
        id:calendar
        width: 600
        height: 600
        anchors.fill: root
        anchors.centerIn: root
        visible: false
        minimumDate: new Date(2019,1,1)
        maximumDate: Qt.formatDate(new Date,"yyyy-MM-dd")
        onClicked:
        {
            pathmodel.clear()
            alarmtime.text = Qt.formatDate(calendar.selectedDate,"yyyy-MM-dd")
            loadAlarmData()
            visible = false
        }
    }

    function loadAlarmData()
    {
        var cmd = "select * from historyTest where alarmDateTime like '" + qsTr(alarmtime.text) + "%'"
        var rs = DB.loadSqliteData(cmd)

        var currentAlarmindex = 0
        while(currentAlarmindex < rs.rows.length)
        {
            var currentItem = rs.rows.item(currentAlarmindex)
            var alarmname = alarmNameInit(currentItem.alarmCode,currentItem.alarmGrade)
            pathmodel.append({"alarmDateTime":Qt.formatTime(currentItem.alarmDateTime),"alarmName":alarmname,"alarmGrade":currentItem.alarmGrade})
            currentAlarmindex++;
        }
    }

    function alarmNameInit(alarmCode,alarmGrade)
    {
        var alarmName;

        switch(alarmGrade)
        {
            case 1:
                alarmName = qsTr("!!!")
                break
            case 2:
            case 3:
                alarmName = qsTr("!!")
                break
            case 4:
                alarmName = qsTr("!")
                break
        }

        switch(alarmCode)
        {
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_MODULE_BORD_ERROR:
                alarmName += qsTr("模块板通信错误(ALL)")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_DATABASE_OPEN_ERROR:
                alarmName += qsTr("数据库打开失败")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_DATABASE_READ_ERROR:
                alarmName += qsTr("数据库操作失败")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_LIQUID_A_B_STRAWS_INTO_LIQUID_A_B:
                alarmName += qsTr("请将A、B液吸管插入A、B液中")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_LIQUID_A_STRAWS_INTO_LIQUID_A:
                alarmName += qsTr("请将A液吸管插入A液中")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_LIQUID_B_STRAWS_INTO_LIQUID_B:
                alarmName += qsTr("请将B液吸管插入B液中")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_JQ_YJ1_JK_SELF_CHECK:
                alarmName += qsTr("进水罐故障")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_FEED_WATER_SELF_CHECK:
                alarmName += qsTr("供水不足")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_GAS_SELF_CHECK:
                alarmName += qsTr("空气检测出错")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_BLOOD_LEAK_SELF_CHECK:
                alarmName += qsTr("漏血监测自检出错")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_BLOOD_SELF_CHECK:
                alarmName += qsTr("血液监测自检出错")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_BLOOD_PUMP_SELF_CHECK:
                alarmName += qsTr("血路系统自检出错")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_FLUID_INFUSION_PUMP_SELF_CHECK:
                alarmName += qsTr("补液系统自检出错")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_HEPARIN_PUMP_SELF_CHECK_NOT_BOM:
                alarmName += qsTr("肝素泵自检不能到底")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_HEPARIN_PUMP_SELF_CHECK_NOT_TOP:
                alarmName += qsTr("肝素泵自检不能到顶")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_CHOKED_FLOW_MONITOR_SELF_CHECK:
                alarmName += qsTr("阻流夹自检错误")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP100:
                alarmName += qsTr("YJ2和YJ3常亮，请检查负压罐是否有故障")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_NOTICE_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP100:
                alarmName += qsTr("请可靠连接透析器接头到机器上")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP112:
                alarmName += qsTr("XV1故障")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP114:
                alarmName += qsTr("XV2故障")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP101:
                alarmName += qsTr("请检查齿轮泵DP到电磁阀SV13之间的管路是否堵塞")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP103:
                alarmName += qsTr("请检查电磁阀V1、V5是否堵塞")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP102:
                alarmName += qsTr("请检查机器外部废液管路是否堵塞或折叠")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP105:
                alarmName += qsTr("请检查机器外部废液管路是否堵塞或者折叠")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP107:
                alarmName += qsTr("请检查与透析器接头连接的管路是否折叠")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP106:
                alarmName += qsTr("请检查电磁阀V3、V7是否堵塞")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_PRESSURE_ERR:
                alarmName += qsTr("压力传感器误差大")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP110:
                alarmName += qsTr("齿轮泵DP异常")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP108:
                alarmName += qsTr("V5、V6、V7、V8、SV13、SV14泄漏或周围管路泄漏")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP113:
                alarmName += qsTr("V2、V4泄漏")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP109:
                alarmName += qsTr("齿轮泵YP坏")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP111:
                alarmName += qsTr("V1、V3、SV3、SV5、SV6、SV11或膜片泄漏")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_BALANCE_SYSTEM_SELF_CHECK_ZP116:
                alarmName += qsTr("超滤泵异常")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_ENDOTOXIN_FILTE_SELF_CHECK_ZN120:
                alarmName += qsTr("齿轮泵YP坏")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_ENDOTOXIN_FILTE_SELF_CHECK_ZN121:
                alarmName += qsTr("内毒素滤器或与其连接处泄漏了吗？")
                break
            case SystemAlaemCodes.SystemAlarmCodeType.SYSTEM_ERROR_CODE_DIALYSATE_TEMPERATURE_SELF_CHECK:
                alarmName += qsTr("检查加热系统是否正常工作")
                break

        }
        return alarmName;
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
