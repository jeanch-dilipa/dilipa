import QtQuick 2.0

Rectangle
{
    id:root
    width: parent.width
    height: parent.height

    PathView
    {
        anchors.fill: parent

        delegate: flipCardDelegate
        model: 100

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

        pathItemCount: 8       //显示数量

        preferredHighlightBegin: 0.5        //可见代理项
        preferredHighlightEnd: 0.5
    }
    Component {
        id: flipCardDelegate

        Item {
            id: wrapper

            width: parent.width
            height: 100

            visible: PathView.onPath

            scale: PathView.itemScale
            z: PathView.itemZ

            property variant rotX: PathView.itemAngle
            transform: Rotation { axis { x: 1; y: 0; z: 0 } angle: wrapper.rotX; origin { x: 32; y: 32; } }

            Rectangle {
                anchors.fill: parent
                color: "lightGray"
                border.color: "black"
                border.width: 3
                smooth: true
            }

            Text {
                anchors.centerIn: parent
                text: index
                font.pixelSize: 30
            }
        }
    }


}
