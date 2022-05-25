import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQml 2.3

Rectangle
{
    id:root
    width: 640
    height: 480

    Rectangle
    {
        id:colorselect
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

                                colorselect.colortool=parent.color
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
        width: 640
        height: 450
//        anchors.top: colorselect.bottom

        property var realx
        property var realy
        property bool iscreate: false
        property color setcolor:colorselect.colortool     //        property color Color:color.colortool  一直报错QQmlComponent: Component is not ready结果是因为用了Color内部关键字，慎之又慎
        property var pointcurve: [0]
        property var currentpoint: 0
        property bool isall: false
        onPaint:
        {
            var ctx= canvas.getContext("2d")
            ctx.lineWidth=2
            ctx.strokeStyle=setcolor
            ctx.beginPath()
            if(!canvas.isall)
            {
                if(currentpoint === 0)
                {
                    ctx.moveTo(0,0)
                }
                else
                {
                    ctx.moveTo((currentpoint - 1) / 640 * canvas.width,canvas.pointcurve[currentpoint - 1] * canvas.height)
                }
                ctx.lineTo(currentpoint / 640 * canvas.width,canvas.pointcurve[currentpoint] * canvas.height)
            }
            else
            {
                ctx.moveTo(0,0)
                for(var i = 0;i < canvas.pointcurve.length;i++)
                {
                    ctx.lineTo(i / 640 * canvas.width,canvas.pointcurve[i] * canvas.height)
                }
            }
            ctx.stroke()
        }
        Timer
        {
            repeat: true
            interval: 100
            running: true
            onTriggered:
            {
                canvas.isall = false
                canvas.pointcurve.push(Math.random(100))
                canvas.currentpoint +=1
                canvas.requestPaint()
            }
        }

        MouseArea
        {
            id:area
            anchors.fill: parent
            drag.target: canvas
            drag.axis: Drag.XandYAxis

            onWheel:
            {
                canvas.isall = true
                if(wheel.angleDelta.y > 0)
                {
                    canvas.x -= canvas.width*0.5/canvas.width*mouseX
                    canvas.width *= 1.5
                    canvas.y -= canvas.height*0.2/canvas.height*mouseY
                    canvas.height *= 1.2
                }
                else
                {
                    canvas.x += canvas.width/3/canvas.width*mouseX
                    canvas.width *= 2/3
                    canvas.y += canvas.height/6/canvas.height*mouseY
                    canvas.height *= 5/6
                }
            }
            onDoubleClicked:
            {
                canvas.isall = true
                if(canvas.width < 6400 || canvas.height < 4800)
                {
                    canvas.x -= canvas.width*0.5/canvas.width*mouseX
                    canvas.width *= 1.5
                    canvas.y -= canvas.height*0.2/canvas.height*mouseY
                    canvas.height *= 1.2
                }
                else
                {
                    canvas.x += canvas.width/3/canvas.width*mouseX
                    canvas.width *= 2/3
                    canvas.y += canvas.height/6/canvas.height*mouseY
                    canvas.height *= 5/6
                }
            }
        }
    }
}
