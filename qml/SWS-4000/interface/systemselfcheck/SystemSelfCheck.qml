import QtQuick 2.0
import QtQml 2.3
import QtQuick.Controls 2.5

import "../public_use/"
import "qrc:/common/"

Rectangle
{
    id:root
    width: 1024
    height: 608
    anchors.top: parent.top
    anchors.topMargin: 96

    property bool checkCorrect: false
    property var bloodfprvalue: 0

    onBloodfprvalueChanged:
    {
//        bloodvalue.text = bloodfprvalue
    }

    Connections
    {
        target: DISPATHER
        onSignal_SelfCheckStart:
        {
            switch(checkItem)
            {
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_WATER_SYSTEM:
                num_1.changeNum = 2500 / checkTime
                num_1.stratCheck = true
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_SYSTEM:
                num_2.changeNum = 2500 / checkTime
                num_2.stratCheck = true
                switch(checkSubItem)
                {
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_11:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_11
                        num_2.nowRange = 0
                        num_2.correctState = num_2.correctState ? false : true
                        num_5.nowRange = 0
                        num_5.correctState = num_5.correctState ? false : true
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_21:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_21
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_21_1:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_21_1
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_21_2:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_21_2
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_22:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_22
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_22_1:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_22_1
                        num_2.nowRange = 15
                        num_2.correctState = num_2.correctState ? false : true
                        num_5.nowRange = 15
                        num_5.correctState = num_5.correctState ? false : true
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_22_2:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_22_2
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_31:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_31
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_1:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_1
                        num_2.nowRange = 22
                        num_2.correctState = num_2.correctState ? false : true
                        num_5.nowRange = 22
                        num_5.correctState = num_5.correctState ? false : true
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_2:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_2
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_3:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_3
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_4:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_4
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_5:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_5
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_6:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_32_6
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_1:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_1
                        num_2.nowRange = 58
                        num_2.correctState = num_2.correctState ? false : true
                        num_5.nowRange = 58
                        num_5.correctState = num_5.correctState ? false : true
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_2:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_2
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_3:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_3
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_4:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_4
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_5:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_5
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_6:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_33_6
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_36:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_36
                        num_2.nowRange = 88
                        num_2.correctState = num_2.correctState ? false : true
                        num_5.nowRange = 88
                        num_5.correctState = num_5.correctState ? false : true
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_36_1:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_36_1
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_36_2:
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_CHAMBER_SELF_CHECK_STEP_36_2
                        break
                }
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_HEAT_SYSTEM:
                num_3.changeNum = 2500 / checkTime
                num_3.stratCheck = true
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_MIXED_SYSTEM:
                num_4.changeNum = 2500 / checkTime
                num_4.stratCheck = true
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_SUBPRESSURE_SYSTEM:
                num_5.changeNum = 2500 / checkTime
                num_5.stratCheck = true
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ULTRATILTRATION_SYSTEM:
                num_6.changeNum = 2500 / checkTime
                num_6.stratCheck = true
                break
//            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_WEIGHT_SYSTEM:
//                num_7.changeNum = 2500 / checkTime
//                num_7.stratCheck = true
//                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BLOOD_SYSTEM:
                num_8.changeNum = 2500 / checkTime
                num_8.stratCheck = true
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_HEPARIN_SYSTEM:
                num_9.changeNum = 2500 / checkTime
                num_9.stratCheck = true
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_MONITOR_SYSTEM:
                num_10.changeNum = 2500 / checkTime
                num_10.stratCheck = true
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_CHOKED_FLOW_SYSTEM:
                num_11.changeNum = 2500 / checkTime
                num_11.stratCheck = true
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_FLUID_INFUSION_SYSTEM:
                num_12.changeNum = 2500 / checkTime
                num_12.stratCheck = true
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_SYSTEM:
                num_13.changeNum = 2500 / checkTime
                num_13.stratCheck = true
                switch(checkSubItem)
                {
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_11:
                        num_13.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_11
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_1:
                        num_13.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_1
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_2:
                        num_13.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_2
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_3:
                        num_13.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_3
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_4:
                        num_13.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_4
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_5:
                        num_13.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_12_5
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_13:
                        num_13.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_13
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_14:
                        num_13.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_14
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_15_1:
                        num_13.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_15_1
                        break
                    case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_15_2:
                        num_13.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_FILTER_SELF_CHECK_STEP_15_2
                        break
                }
                break
            }
        }
        onSignal_SelfCheckResult:
        {
            switch(checkItem)
            {
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_WATER_SYSTEM:
                switch(checkResult)
                {
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ON_THE_WAY:
//                        num_1.rangeValue = 90
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_CORRECT:
                        num_1.rangeValue = 100
                        num_1.changeNum = 1
                        num_1.showRefresh = true
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ERROR:
                        num_1.rangeValue = num_1.nowRange
                        num_1.changeNum = 0
                        num_1.rectColor = 1
                        num_1.showRefresh = true
                        break
                }
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_SYSTEM:
                switch(checkResult)
                {
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ON_THE_WAY:
//                        num_2.rangeValue = 90
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_CORRECT:
                        num_2.rangeValue = 100
                        num_2.changeNum = 1
                        num_2.showRefresh = true
                        num_2.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_SYSTEM
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ERROR:
                        num_2.rangeValue = num_2.nowRange
                        num_2.changeNum = 0
                        num_2.rectColor = 1
                        num_2.showRefresh = true
                        break
                }
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_HEAT_SYSTEM:
                switch(checkResult)
                {
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ON_THE_WAY:
//                        num_3.rangeValue = 90
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_CORRECT:
                        num_3.rangeValue = 100
                        num_3.changeNum = 1
                        num_3.showRefresh = true
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ERROR:
                        num_3.rangeValue = num_3.nowRange
                        num_3.changeNum = 0
                        num_3.rectColor = 1
                        num_3.showRefresh = true
                        break
                }
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_MIXED_SYSTEM:
                switch(checkResult)
                {
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ON_THE_WAY:
//                        num_4.rangeValue = 90
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_CORRECT:
                        num_4.rangeValue = 100
                        num_4.changeNum = 1
                        num_4.showRefresh = true
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ERROR:
                        num_4.rangeValue = num_4.nowRange
                        num_4.changeNum = 0
                        num_4.rectColor = 1
                        num_4.showRefresh = true
                        break
                }
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_SUBPRESSURE_SYSTEM:
                switch(checkResult)
                {
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ON_THE_WAY:
//                        num_5.rangeValue = 90
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_CORRECT:
                        num_5.rangeValue = 100
                        num_5.changeNum = 1
                        num_5.showRefresh = true
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ERROR:
                        num_5.rangeValue = num_5.nowRange
                        num_5.changeNum = 0
                        num_5.rectColor = 1
                        num_5.showRefresh = true
                        break
                }
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ULTRATILTRATION_SYSTEM:
                switch(checkResult)
                {
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ON_THE_WAY:
//                        num_6.rangeValue = 90
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_CORRECT:
                        num_6.rangeValue = 100
                        num_6.changeNum = 1
                        num_6.showRefresh = true
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ERROR:
                        num_6.rangeValue = num_6.nowRange
                        num_6.changeNum = 0
                        num_6.rectColor = 1
                        num_6.showRefresh = true
                        break
                }
                break
//            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_WEIGHT_SYSTEM:
//                switch(checkResult)
//                {
//                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ON_THE_WAY:
////                        num_7.rangeValue = 90
//                        break
//                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_CORRECT:
//                        num_7.rangeValue = 100
//                        num_7.changeNum = 1
//                        num_7.showRefresh = true
//                        break
//                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ERROR:
//                        num_7.rangeValue = num_7.nowRange
//                        num_7.changeNum = 0
//                        num_7.rectColor = 1
//                        num_7.showRefresh = true
//                        break
//                }
//                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BLOOD_SYSTEM:
                switch(checkResult)
                {
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ON_THE_WAY:
//                        num_8.rangeValue = 90
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_CORRECT:
                        num_8.rangeValue = 100
                        num_8.changeNum = 1
                        num_8.showRefresh = true
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ERROR:
                        num_8.rangeValue = num_8.nowRange
                        num_8.changeNum = 0
                        num_8.rectColor = 1
                        num_8.showRefresh = true
                        break
                }
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_HEPARIN_SYSTEM:
                switch(checkResult)
                {
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ON_THE_WAY:
//                        num_9.rangeValue = 90
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_CORRECT:
                        num_9.rangeValue = 100
                        num_9.changeNum = 1
                        num_9.showRefresh = true
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ERROR:
                        num_9.rangeValue = num_9.nowRange
                        num_9.changeNum = 0
                        num_9.rectColor = 1
                        num_9.showRefresh = true
                        break
                }
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_MONITOR_SYSTEM:
                switch(checkResult)
                {
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ON_THE_WAY:
//                        num_10.rangeValue = 90
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_CORRECT:
                        num_10.rangeValue = 100
                        num_10.changeNum = 1
                        num_10.showRefresh = true
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ERROR:
                        num_10.rangeValue = num_10.nowRange
                        num_10.changeNum = 0
                        num_10.rectColor = 1
                        num_10.showRefresh = true
                        break
                }
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_CHOKED_FLOW_SYSTEM:
                switch(checkResult)
                {
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ON_THE_WAY:
//                        num_11.rangeValue = 90
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_CORRECT:
                        num_11.rangeValue = 100
                        num_11.changeNum = 1
                        num_11.showRefresh = true
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ERROR:
                        num_11.rangeValue = num_11.nowRange
                        num_11.changeNum = 0
                        num_11.rectColor = 1
                        num_11.showRefresh = true
                        break
                }
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_FLUID_INFUSION_SYSTEM:
                switch(checkResult)
                {
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ON_THE_WAY:
//                        num_12.rangeValue = 90
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_CORRECT:
                        num_12.rangeValue = 100
                        num_12.changeNum = 1
                        num_12.showRefresh = true
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ERROR:
                        num_12.rangeValue = num_12.nowRange
                        num_12.changeNum = 0
                        num_12.rectColor = 1
                        num_12.showRefresh = true
                        break
                }
                break
            case Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_SYSTEM:
                switch(checkResult)
                {
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ON_THE_WAY:
//                        num_13.rangeValue = 90
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_CORRECT:
                        num_13.rangeValue = 100
                        num_13.changeNum = 1
                        num_13.showRefresh = true
                        num_13.selfCheckItem = Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_SYSTEM
                        break
                    case Common.SystemSelfCheckResultStatusType.SELF_CHECK_ERROR:
                        num_13.rangeValue = num_13.nowRange
                        num_13.changeNum = 0
                        num_13.rectColor = 1
                        num_13.showRefresh = true
                        break
                }
                break
            }
        }
    }

    SystemSelfCheckItem
    {
        id:num_1
        anchors.leftMargin: parent.width/14/15
        anchors.topMargin: 15
        anchors.top: parent.top
        anchors.left: parent.left
        checkname: qsTr("供水系统自检")
        selfCheckItem: Common.SystemSelfCheckItemType.CHECK_ITEM_OF_WATER_SYSTEM
    }
    SystemSelfCheckItem
    {
        id:num_2
        anchors.leftMargin: parent.width/14/15
        anchors.bottomMargin: 15
        anchors.bottom: parent.bottom
        anchors.left: num_1.right
        checkname: qsTr("平衡腔自检")
        selfCheckItem: Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BALANCE_SYSTEM
    }
    SystemSelfCheckItem
    {
        id:num_3
        anchors.leftMargin: parent.width/14/15
        anchors.topMargin: 15
        anchors.top: parent.top
        anchors.left: num_2.right
        checkname: qsTr("加热系统自检")
        selfCheckItem: Common.SystemSelfCheckItemType.CHECK_ITEM_OF_HEAT_SYSTEM
    }
    SystemSelfCheckItem
    {
        id:num_4
        anchors.leftMargin: parent.width/14/15
        anchors.bottomMargin: 15
        anchors.bottom: parent.bottom
        anchors.left: num_3.right
        checkname: qsTr("配液系统自检")
        selfCheckItem: Common.SystemSelfCheckItemType.CHECK_ITEM_OF_MIXED_SYSTEM
    }
    SystemSelfCheckItem
    {
        id:num_5
        anchors.leftMargin: parent.width/14/15
        anchors.topMargin: 15
        anchors.top: parent.top
        anchors.left: num_4.right
        checkname: qsTr("负压系统自检")
        selfCheckItem: Common.SystemSelfCheckItemType.CHECK_ITEM_OF_SUBPRESSURE_SYSTEM
    }
    SystemSelfCheckItem
    {
        id:num_6
        anchors.leftMargin: parent.width/14/15
        anchors.bottomMargin: 15
        anchors.bottom: parent.bottom
        anchors.left: num_5.right
        checkname: qsTr("超滤系统自检")
        selfCheckItem: Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ULTRATILTRATION_SYSTEM
    }
//    SystemSelfCheckItem
//    {
//        id:num_7
//        anchors.leftMargin: parent.width/14/15
//        anchors.topMargin: 15
//        anchors.top: parent.top
//        anchors.left: num_6.right
//        checkname: qsTr("称重系统自检")
//        selfCheckItem: Common.SystemSelfCheckItemType.CHECK_ITEM_OF_WEIGHT_SYSTEM
//    }
    Rectangle
    {
        id:num_7
        width: parent.width/14
        height: parent.height/3
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        anchors.left: num_6.right
        anchors.leftMargin: width/15
    }
    SystemSelfCheckItem
    {
        id:num_8
        anchors.leftMargin: parent.width/14/15
        anchors.bottomMargin: 15
        anchors.bottom: parent.bottom
        anchors.left: num_7.right
        checkname: qsTr("血路系统自检")
        selfCheckItem: Common.SystemSelfCheckItemType.CHECK_ITEM_OF_BLOOD_SYSTEM
    }
    SystemSelfCheckItem
    {
        id:num_9
        anchors.leftMargin: parent.width/14/15
        anchors.topMargin: 15
        anchors.top: parent.top
        anchors.left: num_8.right
        checkname: qsTr("抗凝系统自检")
        selfCheckItem: Common.SystemSelfCheckItemType.CHECK_ITEM_OF_HEPARIN_SYSTEM
    }
    SystemSelfCheckItem
    {
        id:num_10
        anchors.leftMargin: parent.width/14/15
        anchors.bottomMargin: 15
        anchors.bottom: parent.bottom
        anchors.left: num_9.right
        checkname: qsTr("监测系统自检")
        selfCheckItem: Common.SystemSelfCheckItemType.CHECK_ITEM_OF_MONITOR_SYSTEM
    }
    SystemSelfCheckItem
    {
        id:num_11
        anchors.leftMargin: parent.width/14/15
        anchors.topMargin: 15
        anchors.top: parent.top
        anchors.left: num_10.right
        checkname: qsTr("阻流夹自检")
        selfCheckItem: Common.SystemSelfCheckItemType.CHECK_ITEM_OF_CHOKED_FLOW_SYSTEM
    }
    SystemSelfCheckItem
    {
        id:num_12
        anchors.leftMargin: parent.width/14/15
        anchors.bottomMargin: 15
        anchors.bottom: parent.bottom
        anchors.left: num_11.right
        checkname: qsTr("补液系统自检")
        selfCheckItem: Common.SystemSelfCheckItemType.CHECK_ITEM_OF_FLUID_INFUSION_SYSTEM
    }
    SystemSelfCheckItem
    {
        id:num_13
        anchors.leftMargin: parent.width/14/15
        anchors.topMargin: 15
        anchors.top: parent.top
        anchors.left: num_12.right
        checkname: qsTr("内毒素滤器自检")
        selfCheckItem: Common.SystemSelfCheckItemType.CHECK_ITEM_OF_ENDOTOXIN_SYSTEM
    }

    BloodControl
    {
        id:bloodControl
        anchors.horizontalCenter: root.horizontalCenter
        anchors.top: root.top
        anchors.topMargin: 5
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
