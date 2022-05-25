import QtQuick 2.12
import QtQml 2.12
import QtQuick.Controls 2.5

Rectangle
{
    id:root
    width: 640//parent.width
    height: 300//parent.height
    anchors.centerIn: parent

    Connections
    {
        target: REPEATER
        onSignaltherepeuticscheduleinfo1:
        {
            doctorname.text=doctorName
            updatetime.text=updateTime
            therapeuticmodel.currentIndex=therapeuticModel
            dialystateflow.text=dialystateFlow
            naconcentration.text=naConcentration
            hco3concentration.text=hco3Concentration
            dialystatetemp.text=dialystateTemp
            anticoagulationways.currentIndex=anticoagulationWays
            anticoagulationdose.text=anticoagulationDose
        }
        onSignaltherepeuticscheduleinfo2:
        {
            anticoagulationstoptime.text=anticoagulationStoptime
            therapeutictime.text=therapeuticTime
            uftotal.text=ufTotal
            bloodflow.text=bloodFlow
            dilution.currentIndex=diluTion
            substitutiontotal.text=substitutionTotal
            ktv.text=kTv
            dryweight.text=dryWeight
        }
    }

    /*operation_therapeutic*/
    RoundButton
    {
        id:readtherapeutic
        width: parent.width*0.2
        height: width*0.2
        text:qsTr("读取治疗方案")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: -(width+50)/2
        background: Rectangle
        {
            radius:parent.height
            color:Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
        }
        onClicked:
        {
            REPEATER.signaltherapeuticschedule()
        }
    }
    RoundButton
    {
        id:writetherapeutic
        width: parent.width*0.2
        height: width*0.2
        text:qsTr("写入治疗方案")
        anchors.margins: 50
        anchors.left: readtherapeutic.right
        background: Rectangle
        {
            radius:parent.height
            color:Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
        }
        onClicked:
        {

        }
    }

    Column
    {
        anchors.centerIn: parent
        Row
        {
            spacing: 100
            height: 40
            anchors.horizontalCenter: parent.horizontalCenter
            Row
            {
               anchors.verticalCenter: parent.verticalCenter
               Label
               {
                    text: qsTr("医生姓名：")
               }
               TextInput
               {
                    id:doctorname
               }
            }
            Row
            {
                anchors.verticalCenter: parent.verticalCenter
               Label
               {
                    text: qsTr("更新时间：")
               }
               TextInput
               {
                    id:updatetime
               }
            }
            Row
            {
                Label
                {
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("治疗模式：")
                }
                ComboBox
                {
                    id: therapeuticmodel
                    width: 90
                    height: 40
                    editable: false
                    model: ListModel
                    {
                        id:therapeuticmodellist
                        ListElement{text:"无"}
                        ListElement{text:"HD"}
                        ListElement{text:"IUF"}
                        ListElement{text:"HF"}
                        ListElement{text:"HDF"}
                    }
                    background: Rectangle
                    {
                        radius:parent.width/2
                        color:"white"
                    }
                    onAccepted:
                    {
                        if(find(editText)===-1)
                            therapeuticmodellist.append({text:editText})
                    }
                }
            }
        }
        Row
        {
            spacing: 50
            height: 40
            anchors.horizontalCenter: parent.horizontalCenter
            Row
            {
                anchors.verticalCenter: parent.verticalCenter
               Label
               {
                    text: qsTr("透析液流量：")
               }
               TextInput
               {
                    id:dialystateflow
               }
               Label
               {
                    text: qsTr(" ml/min")
               }
            }
            Row
            {
                anchors.verticalCenter: parent.verticalCenter
               Label
               {
                    text: qsTr("Na+:")
               }
               TextInput
               {
                    id:naconcentration
               }
               Label
               {
                    text: qsTr(" mmol/l")
               }
            }
            Row
            {
                anchors.verticalCenter: parent.verticalCenter
               Label
               {
                    text: qsTr("HCO3-:")
               }
               TextInput
               {
                    id:hco3concentration
               }
               Label
               {
                    text: qsTr(" mmol/l")
               }
            }
            Row
            {
                anchors.verticalCenter: parent.verticalCenter
               Label
               {
                    text: qsTr("透析液温度：")
               }
               TextInput
               {
                    id:dialystatetemp
               }
               Label
               {
                    text: qsTr(" ℃")
               }
            }
        }
        Row
        {
            spacing: 60
            height: 40
            anchors.horizontalCenter: parent.horizontalCenter
            Row
            {
                Label
                {
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("抗凝方式：")
                }
                ComboBox
                {
                    id: anticoagulationways
                    width: 110
                    height: 40
                    editable: false
                    model: ListModel
                    {
                        id:anticoagulationwaysmodel
                        ListElement{text:"无抗凝"}
                        ListElement{text:"肝素抗凝"}
                    }
                    background: Rectangle
                    {
                        radius:parent.width/2
                        color:"white"
                    }
                    onAccepted:
                    {
                        if(find(editText)===-1)
                            anticoagulationwaysmodel.append({text:editText})
                    }
                }
            }
            Row
            {
                anchors.verticalCenter: parent.verticalCenter
               Label
               {
                    text: qsTr("抗凝剂量：")
               }
               TextInput
               {
                    id:anticoagulationdose
               }
               Label
               {
                    text: qsTr(" ml/h")
               }
            }
            Row
            {
                anchors.verticalCenter: parent.verticalCenter
               Label
               {
                    text: qsTr("抗凝提前停止时间：")
               }
               TextInput
               {
                    id:anticoagulationstoptime
               }
               Label
               {
                    text: qsTr(" min")
               }
            }
        }
        Row
        {
            spacing: 50
            height: 40
            anchors.horizontalCenter: parent.horizontalCenter
            Row
            {
                anchors.verticalCenter: parent.verticalCenter
               Label
               {
                    text: qsTr("治疗时间：")
               }
               TextInput
               {
                    id:therapeutictime
               }
               Label
               {
                    text: qsTr(" min")
               }
            }
            Row
            {
                anchors.verticalCenter: parent.verticalCenter
               Label
               {
                    text: qsTr("超滤总量：")
               }
               TextInput
               {
                    id:uftotal
               }
               Label
               {
                    text: qsTr(" ml")
               }
            }
            Row
            {
                anchors.verticalCenter: parent.verticalCenter
               Label
               {
                    text: qsTr("血流量：")
               }
               TextInput
               {
                    id:bloodflow
               }
               Label
               {
                    text: qsTr(" ml/min")
               }
            }
            Row
            {
                anchors.verticalCenter: parent.verticalCenter
               Label
               {
                    text: qsTr("干体重：")
               }
               TextInput
               {
                    id:dryweight
               }
               Label
               {
                    text: qsTr(" kg")
               }
            }
        }
        Row
        {
            spacing: 80
            height: 40
            anchors.horizontalCenter: parent.horizontalCenter
            Row
            {
                Label
                {
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("稀释方式：")
                }
                ComboBox
                {
                    id: dilution
                    width: 90
                    height: 30
                    editable: false
                    model: ListModel
                    {
                        id:dilutionmodel
                        ListElement{text:"后稀释"}
                        ListElement{text:"前稀释"}
                    }
                    background: Rectangle
                    {
                        radius:parent.width/2
                        color:"white"
                    }
                    onAccepted:
                    {
                        if(find(editText)===-1)
                            dilutionmodel.append({text:editText})
                    }
                }
            }
            Row
            {
                anchors.verticalCenter: parent.verticalCenter
               Label
               {
                    text: qsTr("置换液总量:")
               }
               TextInput
               {
                    id:substitutiontotal
               }
               Label
               {
                    text: qsTr(" ml")
               }
            }
            Row
            {
                anchors.verticalCenter: parent.verticalCenter
               Label
               {
                    text: qsTr("Kt/V目标：")
               }
               TextInput
               {
                    id:ktv
               }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#c0c0c0";formeditorZoom:0.8999999761581421}
}
##^##*/
