import QtQuick 2.0

Rectangle
{
    id:root
    width: parent.width
    height: parent.height
    property variant colorarray: ["red","blue","green"]
    property variant easings : [                    //缓冲曲线动画
        "Linear", "InQuad", "OutQuad", "InOutQuad",
        "InCubic", "InSine", "InCirc", "InElastic",
        "InBack", "InBounce" ]

    Grid
    {
        anchors.fill:parent
        anchors.centerIn: parent
        spacing: 8
        Repeater
        {
            model:easings
            Rectangle
            {
                width: 56
                height: width
                property int colorindex:Math.floor(Math.random()*3)
                color:colorarray[colorindex]
                border.color: Qt.lighter(color)
                Text {
                    anchors.centerIn: parent
                    text: modelData
                    color: "#000000"
                }
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        num.restart()
                        num.easing.type=modelData
                    }
                }
            }
        }
    }

    Rectangle
    {
        id:run
        width: 20
        height: width
        color: "black"
        x:root.width-20
        y:0
    }

    NumberAnimation
    {
        id:num
        target:run
        from:0
        to:root.height-run.height
        properties:"y"
        duration:2000
    }
}
