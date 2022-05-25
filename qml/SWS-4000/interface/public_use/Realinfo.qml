import QtQuick 2.5
import QtQuick.Controls 2.5
import QtQuick.Window 2.3
import QtGraphicalEffects 1.0

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

    Rectangle
    {
        id:root
        width: rootw.width-20
        height: rootw.height-20
        anchors.centerIn: parent
        radius: 10

        Rectangle
        {
            id:watersupply
            width: parent.width * 0.24
            height: parent.height * 0.48
            anchors.leftMargin: parent.width * 0.005
            anchors.topMargin: parent.height * 0.015
            anchors.top: parent.top
            anchors.left: parent.left
            radius: 10
            color: "#0acf97"

            Column
            {
                anchors.fill: parent
                spacing: 10
                Label
                {
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    text: qsTr("供水系统")
                }
                Column
                {
                    width: parent.width
                    height: parent.height-25
                    spacing: 5
                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("YJ1:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            id:yj1
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("通")
                            horizontalAlignment: Text.AlignHCenter
                            color: ("white")
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }

                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("YJ1:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            id:yj2
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("通")
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }

                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("YJ1:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            id:yj3
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("通")
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }
                }
            }
        }

        Rectangle
        {
            id:balance
            width: parent.width * 0.24
            height: parent.height * 0.48
            anchors.leftMargin: parent.width * 0.005
            anchors.topMargin: parent.height * 0.015
            anchors.top: watersupply.bottom
            anchors.left: parent.left
            radius: 10
            color: "#0acf97"

            Column
            {
                anchors.fill: parent
                spacing: 10
                Label
                {
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    text: qsTr("平衡系统")
                }
                Column
                {
                    width: parent.width
                    height: parent.height-25
                    spacing: 5
                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("DP:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            id: dp
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("11")
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }

                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("YP:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            id:yp
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("12")
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }

                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("YJ1:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            id:dp2
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("2")
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }
                }
            }
        }

        Rectangle
        {
            id:warm
            width: parent.width * 0.24
            height: parent.height * 0.28
            anchors.leftMargin: parent.width * 0.01
            anchors.topMargin: parent.height * 0.015
            anchors.top: parent.top
            anchors.left: watersupply.right
            radius: 10
            color: "#0acf97"

            Column
            {
                anchors.fill: parent
                spacing: 10
                Label
                {
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    text: qsTr("加热系统")
                }
                Column
                {
                    width: parent.width
                    height: parent.height-25
                    spacing: 5
                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("wg1:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            id:wg1
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("35")
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("℃")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }

                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("WG2:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            id:wg2
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("40")
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("℃")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }

                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("WG3:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            id:wg3
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("36")
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("℃")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }
                }
            }

        }

        Rectangle
        {
            id:liquid
            width: parent.width * 0.24
            height: parent.height * 0.68
            anchors.leftMargin: parent.width * 0.01
            anchors.topMargin: parent.height * 0.015
            anchors.top: warm.bottom
            anchors.left: balance.right
            radius: 10
            color: "#0acf97"

            Column
            {
                anchors.fill: parent
                spacing: 10
                Label
                {
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    text: qsTr("配液系统")
                }
                Column
                {
                    width: parent.width
                    height: parent.height-25
                    spacing: 5
                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("DG1:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            id: dg1
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("3")
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("mS/cm")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }

                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("DG2:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            id:dg2
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("13")
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("mS/cm")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }

                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("DG3:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            id: dg3
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("13")
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("mS/cm")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }
                }
            }

        }

        Rectangle
        {
            id:negativePressure
            width: parent.width * 0.24
            height: parent.height * 0.38
            anchors.leftMargin: parent.width * 0.01
            anchors.topMargin: parent.height * 0.015
            anchors.top: parent.top
            anchors.left: warm.right
            radius: 10
            color: "#0acf97"

            Column
            {
                anchors.fill: parent
                spacing: 10
                Label
                {
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    text: qsTr("负压系统")
                }
                Column
                {
                    width: parent.width
                    height: parent.height-25
                    spacing: 5
                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("DG1:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("3")
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("mS/cm")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }

                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("DG2:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("13")
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("mS/cm")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }
                }
            }

        }

        Rectangle
        {
            id:ultrafil
            width: parent.width * 0.24
            height: parent.height * 0.18
            anchors.leftMargin: parent.width * 0.01
            anchors.topMargin: parent.height * 0.015
            anchors.top: negativePressure.bottom
            anchors.left: warm.right
            radius: 10
            color: "#0acf97"

            Column
            {
                anchors.fill: parent
                spacing: 10
                Label
                {
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    text: qsTr("超滤系统")
                }
                Column
                {
                    width: parent.width
                    height: parent.height-25
                    spacing: 5
                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("DG1:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("3")
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("mS/cm")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }

                 }
            }

        }

        Rectangle
        {
            id: blood
            width: parent.width * 0.24
            height: parent.height * 0.38
            anchors.leftMargin: parent.width * 0.01
            anchors.topMargin: parent.height * 0.015
            anchors.top: ultrafil.bottom
            anchors.left: warm.right
            radius: 10
            color: "#0acf97"

            Column
            {
                anchors.fill: parent
                spacing: 10
                Label
                {
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    text: qsTr("血路系统")
                }
                Column
                {
                    width: parent.width
                    height: parent.height-25
                    spacing: 5
                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("DG1:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("3")
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("mS/cm")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }

                 }
            }
        }

        Rectangle
        {
            id: antifreeing
            width: parent.width * 0.24
            height: parent.height * 0.18
            anchors.leftMargin: parent.width * 0.01
            anchors.topMargin: parent.height * 0.015
            anchors.top: parent.top
            anchors.left: negativePressure.right
            radius: 10
            color: "#0acf97"

            Column
            {
                anchors.fill: parent
                spacing: 10
                Label
                {
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    text: qsTr("抗凝系统")
                }
                Column
                {
                    width: parent.width
                    height: parent.height-25
                    spacing: 5
                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("DG1:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("3")
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("mS/cm")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }
                }
            }
        }

        Rectangle
        {
            id:monitor
            width: parent.width * 0.24
            height: parent.height * 0.18
            anchors.leftMargin: parent.width * 0.01
            anchors.topMargin: parent.height * 0.015
            anchors.top: antifreeing.bottom
            anchors.left: negativePressure.right
            radius: 10
            color: "#0acf97"

            Column
            {
                anchors.fill: parent
                spacing: 10
                Label
                {
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    text: qsTr("监测系统")
                }
                Column
                {
                    width: parent.width
                    height: parent.height-25
                    spacing: 5
                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("DG1:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("3")
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("mS/cm")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }
                }
            }
        }

        Rectangle
        {
            id:chokeclip
            width: parent.width * 0.24
            height: parent.height * 0.18
            anchors.leftMargin: parent.width * 0.01
            anchors.topMargin: parent.height * 0.015
            anchors.top: monitor.bottom
            anchors.left: negativePressure.right
            radius: 10
            color: "#0acf97"

            Column
            {
                anchors.fill: parent
                spacing: 10
                Label
                {
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    text: qsTr("阻流夹系统")
                }
                Column
                {
                    width: parent.width
                    height: parent.height-25
                    spacing: 5
                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("DG1:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("3")
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("mS/cm")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }
                }
            }
        }

        Rectangle
        {
            id:fluid
            width: parent.width * 0.24
            height: parent.height * 0.18
            anchors.leftMargin: parent.width * 0.01
            anchors.topMargin: parent.height * 0.015
            anchors.top: chokeclip.bottom
            anchors.left: negativePressure.right
            radius: 10
            color: "#0acf97"

            Column
            {
                anchors.fill: parent
                spacing: 10
                Label
                {
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    text: qsTr("补液系统")
                }
                Column
                {
                    width: parent.width
                    height: parent.height-25
                    spacing: 5
                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("DG1:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("3")
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("mS/cm")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }
                }
            }
        }

        Rectangle
        {
            id:endotoxin
            width: parent.width * 0.24
            height: parent.height * 0.18
            anchors.leftMargin: parent.width * 0.01
            anchors.topMargin: parent.height * 0.015
            anchors.top: fluid.bottom
            anchors.left: negativePressure.right
            radius: 10
            color: "#0acf97"

            Column
            {
                anchors.fill: parent
                spacing: 10
                Label
                {
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    text: qsTr("内毒素系统")
                }
                Column
                {
                    width: parent.width
                    height: parent.height-25
                    spacing: 5
                    Row
                    {
                        width: parent.width
                        height: 20
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("DG1:")
                            horizontalAlignment: Text.AlignRight
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.4
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("3")
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }
                        Label
                        {
                            width: parent.width*0.3
                            height: parent.height
                            font.pointSize: 12
                            text: qsTr("mS/cm")
                            horizontalAlignment: Text.AlignLeft
                            color: "white"
                        }
                    }
                }
            }
        }

    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
