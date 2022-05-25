import QtQuick 2.0

Rectangle
{
    id: topmain
    x: 0
    y: 0
    visible: false
    signal pleasemin()
    signal pleasemax(var ismax)
    property bool ismax: false


    Text
    {
        id: showmotivational
        text: qsTr("花太多时间去想剩下的生命，反而忘了好好地生活")
        anchors.verticalCenter: topmain.verticalCenter
        font.pixelSize: 20
        font.family:"Arial"
    }


    Rectangle
    {
        id:nxq
        width: 75
        height: 25
        anchors.right: topmain.right
        anchors.top: topmain.top

        Rectangle
        {
            id:min
            width: 20
            height: 20
            anchors.right: max.left
            anchors.top: nxq.top
            anchors.topMargin: 5
            anchors.rightMargin: 5

            MouseArea
            {
                anchors.fill:min
                hoverEnabled: true      //生效鼠标监听
                onClicked: topmain.pleasemin()
                onEntered:
                {
                    min1.border.color="blue"
                }
                onExited:
                {
                     min1.border.color="gray"
                }
            }
            Rectangle
            {
                id:min1
                width: 14
                height: 2
                border.color: "gray"
                border.width: 2
                anchors.centerIn: min
            }

        }
        Rectangle
        {
            id:max
            x: 562
            y: 0
            width: 20
            height: 20
            anchors.right: quit.left
            anchors.top: nxq.top
            anchors.topMargin: 5    //边距
            anchors.rightMargin: 5

            MouseArea
            {
                anchors.fill:max
                hoverEnabled: true      //生效鼠标监听
                onClicked:
                {
                    if(ismax===false)
                        ismax=true
                    else
                        ismax=false
                    topmain.pleasemax(ismax)
                }


                onEntered:
                {
                    max1.border.color="blue"
                }
                onExited:
                {
                     max1.border.color="gray"
                }
            }
            Rectangle
            {
                id:max1
                width: 14
                height: 12
                radius: 2       //圆角
                border.color: "gray"
                border.width: 2
                anchors.centerIn: max
            }
        }
        Rectangle
        {
            id:quit
            width: 20
            height: 20
            anchors.right: nxq.right
            anchors.top: nxq.top
            anchors.topMargin: 5
            anchors.rightMargin: 5
//移入变色
            MouseArea
            {
                anchors.fill:quit
                hoverEnabled: true
                onClicked: Qt.quit()
                onEntered:
                {
                    quit1.border.color="red"
                    quit2.border.color="red"
                }
                onExited:
                {
                     quit1.border.color="gray"
                     quit2.border.color="gray"
                }
            }

            Rectangle
            {
                id:quit1
                width: 18
                height: 2
                rotation: 45
                border.color: "gray"
                border.width: 2
                anchors.centerIn: quit
            }
            Rectangle
            {
                id:quit2
                width: 18
                height: 2
                rotation: -45   //旋转
                border.color: "gray"
                border.width: 2
                anchors.centerIn: quit
            }
        }
    }
    Rectangle
    {
        id:crossline
        width: topmain.width
        height: 1
        color: "gray"
        anchors.bottom: topmain.bottom
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
