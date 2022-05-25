import QtQuick 2.0
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import QtQuick.Window 2.3
import QtQml 2.3

import "qrc:/common/"
import "../Custom_model"

Window
{
    id:root
    width: 640
    height: 470

    flags: Qt.FramelessWindowHint
    color: "#00000000"

    DropShadow
    {
        anchors.fill: alarm_root
        horizontalOffset: 5
        verticalOffset: 5
        source: alarm_root
        color: "#a8a8a8a8"
        samples: 5
        radius: 5
    }
//    DropShadow
//    {
//        anchors.fill: alarm_root
//        horizontalOffset: -5
//        verticalOffset: 5
//        source: alarm_root
//        color: "#a8a8a8a8"
//        samples: 5
//        radius: 5
//    }
    DropShadow
    {
        anchors.fill: alarm_root
        horizontalOffset: -5
        verticalOffset: -5
        source: alarm_root
        color: "#a8a8a8a8"
        samples: 5
        radius: 5
    }
//    DropShadow
//    {
//        anchors.fill: alarm_root
//        horizontalOffset: 5
//        verticalOffset: -5
//        source: alarm_root
//        color: "#a8a8a8a8"
//        samples: 5
//        radius: 5
//    }

    Rectangle
    {
        id:alarm_root
        width: root.width-20
        height: root.height-20
        anchors.centerIn: parent
        radius: 100
        border.color: "#a8a8a8a8"

        Text
        {
            text: qsTr("AlarmInfo")
            font.pointSize: 25
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
        }

        ListView
        {
            id:listview
            width:560
            height:350
            anchors.centerIn: parent
            model: listmodel
            delegate: Rectangle
            {
                width:parent.width
                height:30
                Rectangle
                {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width:540
                    height:20
                    radius: 100
                    color:ALARMCOLOR === 1 ? "red" : ALARMCOLOR === 4 ? "blue" : "yellow"
                    Text
                    {
                        text:ALARMNAME
                        font.pointSize: 15
                    }
                }
            }
        }
        ListModel
        {
            id:listmodel
        }

        CustomButton
        {
            id:alarm_ok
            width: root.width/8
            height: width/5*2
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 6
            text: "ok"
            backgroundDefaultColor: "#0acf97"
            textfontpointsize: 20
            backgroundradius: 20

            onClicked:
            {
                root.visible = false
                listmodel.clear()
            }
        }

        Connections
        {
            target: DISPATHER
            onSignal_showAlarmToInterface:
            {
                var isExistAlarm = false
                if(alarmEnable)
                {
                    if(listmodel.count !== 0)
                    {
                        for(var i = 0; i < listmodel.count;i++)
                        {
                            if(listmodel.get(i).ALARMCODE === alarmCode)
                            {
                                isExistAlarm = true
                                break
                            }
                        }
                        if(isExistAlarm === false)
                        {
                            listmodel.append({ALARMCODE:alarmCode,ALARMNAME:alarmNameInit(alarmCode,alarmGrade),ALARMCOLOR:alarmGrade})
                        }
                    }
                    else
                    {
                        listmodel.append({ALARMCODE:alarmCode,ALARMNAME:alarmNameInit(alarmCode,alarmGrade),ALARMCOLOR:alarmGrade})
                    }
                    root.visible = true
                    root.show()
                }
                else
                {
                    if(listmodel.count === 0)
                    {
                        root.visible = false
                    }
                    else
                    {
                        for(var j = 0; j < listmodel.count;j++)
                        {
                            if(listmodel.get(j).ALARMCODE === alarmCode)
                                listmodel.remove(j)
                        }
                    }
                }
            }
            onSignal_clearAllAlarm:
            {
                listmodel.clear()
                root.visible = false
            }
        }
    }

    /*alarmNameInit*/
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
