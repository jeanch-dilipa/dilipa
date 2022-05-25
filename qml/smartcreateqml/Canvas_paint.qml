import QtQuick 2.0

Rectangle
{
    id:root
    width: parent.width
    height: parent.height

    Rectangle
    {
        id:color
        width:parent.width
        height:30

        property color colortool:"red"
        PathView
        {
            anchors.fill:parent
            model:50
            delegate: pathdelege
            path: Path
            {
                 startX: 0; startY: 15

                 PathAttribute { name: "itemz";value: 0}
                 PathAttribute { name: "itemscale"; value: 0.5; }
                 PathLine{x:root.width*0.4;y:15}
                 PathPercent { value: 0.33; }
                 PathLine{x:root.width*0.5;y:15}
                 PathAttribute { name: "itemz"; value: 100.0; }
                 PathAttribute { name: "itemscale"; value: 1.0; }
                 PathLine{x:root.width*0.6;y:15}
                 PathPercent { value: 0.63; }
                 PathLine{x:root.width;y:15}
                 PathAttribute { name: "itemz"; value: 0.0; }
                 PathAttribute { name: "itemscale"; value: 0.5; }
            }

            pathItemCount: 16
            preferredHighlightBegin: 0.5        //可见代理项__可解决报错undefined问题
            preferredHighlightEnd: 0.5
            Component
            {
                id:pathdelege

                Item
                {
                    width: 25
                    height: 25
                    visible: PathView.onPath
                    scale: PathView.itemscale
                    z:PathView.itemz
                    Rectangle
                    {
                        width: 25
                        height: 25
                        color: Qt.rgba(Math.random(),Math.random(),Math.random())
                        MouseArea
                        {
                            anchors.fill: parent
                            onClicked:
                            {

                                color.colortool=parent.color
                                console.log(color.colortool)
                            }
                        }
                    }
                }
            }
        }
    }

    Canvas
    {
        id:canvas
        width: parent.width
        height: parent.height-color.height
        anchors.top: color.bottom

        property var realx
        property var realy
        property bool iscreate: false
        property color setcolor:color.colortool     //        property color Color:color.colortool  一直报错QQmlComponent: Component is not ready结果是因为用了Color内部关键字，慎之又慎
        onPaint:
        {
            var ctx= canvas.getContext("2d")
            ctx.lineWidth=2
            ctx.strokeStyle=setcolor
            ctx.beginPath()
            ctx.moveTo(realx,realy)
            realx=area.mouseX
            realy=area.mouseY
            ctx.lineTo(realx,realy)
            ctx.stroke()
        }

        MouseArea
        {
            id:area
            anchors.fill: parent
            onPressed:
            {
                canvas.iscreate=true
                canvas.realx=mouseX
                canvas.realy=mouseY
            }
            onReleased:
            {
                canvas.iscreate=false
            }
            onPositionChanged:
            {
                if(canvas.iscreate)
                    canvas.requestPaint()
            }
        }
    }
}
