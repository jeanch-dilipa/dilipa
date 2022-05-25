import QtQuick 2.12
import QtQml 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.12

Window
{
    id:rootwindow
    width: rootWIDTH
    height: rootHEIGHT
    visible: true

    property var rootWIDTH: 640
    property var rootHEIGHT: 500
    property var version:1.0
    property bool connectstatus: false
    property bool cardrecordsstatus: false
    property var therapeuticwin

    title: qsTr("IC_Card_")+version

    Connections
    {
        target: REPEATER
        onSignalconnectbtnclick:
        {
            if(isclick)
                connectbtn.clicked()
        }
        onSignalconnectresult:
        {
            if(isconnect)
            {
                connectbtn.text=qsTr("连接成功")
                connectstatus=true
            }
            else
            {
                connectbtn.text=qsTr("连接断开")
                connectstatus=false
            }
        }
        onSignalICbasicinfo:
        {
            if(card_style&&UID!="0")
                uid.text=qsTr("IC卡 UID："+UID)
            else if(!card_style&&UID!="0")
                uid.text=qsTr("CPU卡 UID："+UID)
            else
            {
                uid.text=""
                cardtype.currentIndex=0
                username.text="name"
                usergender.currentIndex=0
                userbirthday.text="birthday"
                userstature.text="stature"
                useruf_before_weight.text="weight"
                useruf_after_weight.text="weight"
                therapeuticwin.destroy()
            }
        }
        onSignaluserbasicinfo:
        {
            cardtype.currentIndex=card_type===Propertydefine.Card_type.Unopencard ? 0 : card_type===Propertydefine.Card_type.Patientcard ? 1 : 2
            username.text=name
            usergender.currentIndex=gender===Propertydefine.Gender_type.Unknown ? 0 : gender===Propertydefine.Gender_type.Man ? 1: 2
            userbirthday.text=birthday
            userstature.text=stature
            useruf_before_weight.text=uf_before_weight
            useruf_after_weight.text=uf_after_weight

            if(cardtype.currentIndex===1)
            {
                var c=Qt.createComponent("Therapeutic.qml")
                therapeuticwin = c.createObject(therapeutic)
            }
        }
        onSignalcardcordsinfo:
        {
            model.append({indexnum:currentindex.toString(),chargeTime:chargetime,machineid:machineID})
        }
    }

    /*UID*/
    Text
    {
        id: uid
        x: 20
        y: 25
        font.pointSize: rootWIDTH*0.02
    }

    /*debugmsg*/
    Debugmsg
    {
        id:debug
        width: 300
        height: rootHEIGHT+30
    }

    RoundButton
    {
        id:debugmsg
        width: rootWIDTH*0.1
        height: width*0.5
        text:qsTr("debugmsg")
        anchors.margins: 5
        anchors.right: parent.right
        background: Rectangle
        {
            radius:parent.height
            color:Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
        }
        onClicked:
        {
            if(debug.visible)
            {
                debug.visible=false
            }
            else
            {
                debug.show()
                debug.x=rootwindow.x+rootWIDTH
                debug.y=rootwindow.y
            }
        }
    }

    /*connectstatus*/
    RoundButton
    {
        id:connectbtn
        width: rootWIDTH*0.1
        height: width*0.5
        text:qsTr("连接")
        anchors.margins: 5
        anchors.top: debugmsg.bottom
        anchors.right: parent.right
        background: Rectangle
        {
            radius:parent.height
            color:Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
        }
        onClicked:
        {
            if(!connectstatus)
            {
                text=qsTr("连接中...")
                REPEATER.signalstartconnect()
            }
        }
    }

    /*basicinfo*/
    RoundButton
    {
        id:readbasicinfo
        width: parent.width*0.2
        height: width*0.2
        text:qsTr("读取卡信息")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: -(width+50)/2
        anchors.bottom: basicinfo.top
        background: Rectangle
        {
            radius:parent.height
            color:Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
        }
        onClicked:
        {
            REPEATER.signalstartconnect()
        }
    }
    RoundButton
    {
        id:writebasicinfo
        width: parent.width*0.2
        height: width*0.2
        text:qsTr("开卡")
        anchors.leftMargin: 50
        anchors.left: readbasicinfo.right
        anchors.bottom: basicinfo.top
        background: Rectangle
        {
            radius:parent.height
            color:Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
        }
        onClicked:
        {
            if(cardtype.currentIndex===0)
            {
                message.show()
                message.isresetcard=true    //清卡
                message.messagelabeltext=qsTr("是否标记为未开卡？")
            }
            else
            {
                if(checkbasicinfo())
                {
                    var card_type=cardtype.currentIndex===1 ? Propertydefine.Card_type.Patientcard : Propertydefine.Card_type.Maintenancecard
                    var gender=usergender.currentIndex===1 ? Propertydefine.Gender_type.Man : Propertydefine.Gender_type.Woman
                    REPEATER.signalwriteuserbasicinfo(card_type,username.text,gender,userbirthday.text,userstature.text,useruf_before_weight.text,useruf_after_weight.text)
                }
                else
                {
                    message.show()
                    message.messagelabeltext=qsTr("请确认开卡信息？")
                }
            }
        }
    }
    GroupBox
    {
        id:basicinfo
        title: qsTr("基本信息：")
        anchors.top: uid.bottom
        anchors.topMargin: 40
        height: 85
        width: parent.width
        Column
        {
            anchors.fill: parent
            Row
            {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 50
                height: 30
                ComboBox
                {
                    id: cardtype
                    width: 90
                    height: 30
                    editable: false //是否可编辑
                    model: ListModel
                    {
                        id:cardtypemodel
                        ListElement{text:"未开卡"}
                        ListElement{text:"患者卡"}
                        ListElement{text:"维护卡"}
                    }
                    background: Rectangle
                    {
                        radius:parent.width/2
                        color:"white"
                    }
                    onAccepted:
                    {
                        if(find(editText)===-1)
                            cardtypemodel.append({text:editText})
                    }
                }
                Row
                {
                    anchors.verticalCenter: parent.verticalCenter
                    Text
                    {
                        text: qsTr("姓名：")
                    }
                    TextInput
                    {
                        id: username
                    }
                }
                ComboBox
                {
                    id: usergender
                    x:62
                    width: 80
                    height: 30
                    editable: false //是否可编辑
                    model: ListModel
                    {
                        id:usergendermodel
                        ListElement{text:"未知"}
                        ListElement{text:"男"}
                        ListElement{text:"女"}
                    }
                    background: Rectangle
                    {
                        radius:parent.width/2
                        color:"white"
                    }
                    onAccepted:
                    {
                        if(find(editText)===-1)
                            cardtypemodel.append({text:editText})
                    }
                }
            }
            Row
            {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 40
                height: 20
                Row
                {
                    Text
                    {
                        text: qsTr("出生日期：")
                    }
                    TextInput
                    {
                        id: userbirthday
                    }
                }
                Row
                {
                    Text
                    {
                        text: qsTr("身高：")
                    }
                    TextInput
                    {
                        id: userstature
                    }
                    Text
                    {
                        text: qsTr("cm")
                    }
                }
                Row
                {
                    Text
                    {
                        text: qsTr("透前体重：")
                    }
                    TextInput
                    {
                        id: useruf_before_weight
                    }
                    Text
                    {
                        text: qsTr("kg")
                    }
                }
                Row
                {
                    Text
                    {
                        text: qsTr("透后体重：")
                    }
                    TextInput
                    {
                        id: useruf_after_weight
                    }
                    Text
                    {
                        text: qsTr("kg")
                    }
                }
            }
        }
    }

    /*therapeuticschedule*/
    Rectangle
    {
        id:therapeutic
        width: rootWIDTH
        height: 300
        anchors.topMargin: 15
        anchors.top: basicinfo.bottom
        Label
        {
            anchors.centerIn: parent
            text: qsTr("无此权限")
            font.pointSize:therapeutic.height*0.1
            color: "gray"
        }
    }

    /*cardrecords*/
    RoundButton
    {
        id:cardrecords
        y:rootHEIGHT-height
        width: rootWIDTH*0.1
        height: width*0.5
        text:qsTr("刷卡记录")
        anchors.margins: 5
        anchors.left: parent.left
        background: Rectangle
        {
            radius:parent.height
            color:Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
        }
        onClicked:
        {
            if(!cardrecordsstatus)
            {
                rootwindow.height+=200
                cardrecordsstatus=!cardrecordsstatus
                REPEATER.signalcardrecordsrequst()
            }
            else
            {
                rootwindow.height-=200
                cardrecordsstatus=!cardrecordsstatus
            }
        }
    }

    Rectangle
    {
        id:cardrecordslist
        width: rootWIDTH
        height: 180
        anchors.top: cardrecords.bottom
        anchors.topMargin: 20

        ListView
        {
            anchors.fill: parent
            model: model
            delegate:Text
            {
                width:rootWIDTH
                Row
                {
                    anchors.horizontalCenter:parent.horizontalCenter
                    spacing: 100
                    Label{text: indexnum}
                    Label{text: chargeTime}
                    Label{text: machineid}
                }
            }
        }

        ListModel
        {
            id:model
            ListElement{indexnum:"序号";chargeTime:"刷卡时间";machineid:"机器编号"}
        }
    }

    /*Messagepop_up*/
    Messagepop_up
    {
        id:message
    }
    function  checkbasicinfo()
    {
        if(username.text==="")return 0
        if(usergender.currentIndex===0)return 0
        if(userbirthday.text==="")return 0
        if(userstature.text==="")return 0
        if(useruf_after_weight.text==="")return 0
        if(useruf_before_weight.text==="")return 0
        return 1
    }

}
