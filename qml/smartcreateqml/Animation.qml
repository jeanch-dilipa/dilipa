import QtQuick 2.0

Rectangle
{
    id:root
    width: parent.width
    height: parent.height-20

    states: [
            State {
                name: "stop"
                PropertyChanges { target: red; color: "red" }
                PropertyChanges { target: green; color: "black" }
            },
            State {
                name: "go"
                PropertyChanges { target: red; color: "black" }
                PropertyChanges { target: green; color: "green" }
            }
        ]
    Rectangle
    {
        id:red
        width: 30
        height: width
        radius: width/2
        color: "red"
        anchors.top: root.top
        anchors.right: root.right
        state: "stop"
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                red.state = (red.state == "stop"? "go" : "stop")
                console.log(red.state)
                console.log(red.color)
            }
        }
    }
    Rectangle
    {
        id:green
        width: 30
        height: width
        radius: width/2
        color: "black"
        anchors.right: red.left
    }

    Rectangle
    {
        id:r1
        y:parent.height-height
        width: parent.width/10
        height: parent.height/10
        anchors.left: root.left
        color: Qt.rgba(Math.random(),Math.random(),Math.random())
        border.color: Qt.lighter(color)

        NumberAnimation on y        //同步动画
        {
            to:10
            duration:2000
        }
        NumberAnimation on opacity
        {
            to:0
            duration:2000
        }
    }
    Rectangle
    {
        id:r2
        y:parent.height-height
        width: parent.width/10
        height: parent.height/10
        color: Qt.rgba(Math.random(),Math.random(),Math.random())
        border.color: Qt.lighter(color)
        anchors.horizontalCenter: root.horizontalCenter
        Behavior on y           //控制动画
        {
            NumberAnimation{duration: 2000}
        }
        MouseArea
        {
            anchors.fill:r2
            onClicked: r2.y=10
        }
    }
    Rectangle
    {
        id:r3
        y:parent.height-height
        width: parent.width/10
        height: parent.height/10
        color: Qt.rgba(Math.random(),Math.random(),Math.random())
        anchors.right: root.right
        border.color: Qt.lighter(color)
        NumberAnimation             //独立动画
        {
            id:num
            target: r3
            properties: "y"
            from:r3.y
            to:10
            duration: 10000
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked: num.start()
            onDoubleClicked: num.stop()
        }
    }

    Image {
        x:0
        y:0
        id: pinwheel
        width: 30
        height: 30
        source: "qrc:/pinwheel.png"
        MouseArea
        {
            anchors.fill:parent
            onClicked: paranum.start()
        }
        ParallelAnimation
        {
            id:paranum
            RotationAnimation
            {
                target: pinwheel
                properties: "rotation"
                to:720
                duration:5000
            }
            SequentialAnimation         //连续动画
            {
                ParallelAnimation       //平行动画
                {
                    NumberAnimation
                    {
                        target: pinwheel
                        from:0
                        to:root.width/2
                        duration: 2000
                        properties: "x"
                    }
                    NumberAnimation
                    {
                        target: pinwheel
                        from:0
                        to:root.height/3*1
                        duration: 2000
                        properties: "y"
                        easing.type: Easing.OutInCirc
                    }
                }
                ParallelAnimation
                {
                    NumberAnimation
                    {
                        target: pinwheel
                        from:root.width/2
                        to:0
                        duration: 2000
                        properties: "x"
                    }
                    NumberAnimation
                    {
                        target: pinwheel
                        from:root.height/3*1
                        to:root.height-pinwheel.height
                        duration: 2000
                        properties: "y"
                        easing.type: Easing.OutBounce
                    }
                }
                ParallelAnimation
                {
                    NumberAnimation
                    {
                        target: pinwheel
                        from:0
                        to:root.width/2
                        duration: 3000
                        properties: "x"
                    }
                    NumberAnimation
                    {
                        target: pinwheel
                        from:root.height-pinwheel.height
                        to:root.height/3*2
                        duration: 3000
                        properties: "y"
                        easing.type: Easing.OutInCirc
                    }
                }
                ParallelAnimation
                {
                    NumberAnimation
                    {
                        target: pinwheel
                        from:root.width/2
                        to:root.width
                        duration: 2000
                        properties: "x"
                    }
                    NumberAnimation
                    {
                        target: pinwheel
                        from:root.height/3*2
                        to:root.height-pinwheel.height
                        duration: 2000
                        properties: "y"
                        easing.type: Easing.OutBounce
                    }
                }
            }
        }
    }
}
