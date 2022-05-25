import QtQuick 2.9
import QtQml 2.3

Rectangle
{
    id:root
    width: 400
    height: 400
    anchors.centerIn: parent

    property int h: 5
    property var vose: 0
    property int mX: parent.width
    property var waternum: 0.01

    property var value: 60

    Canvas
    {
        id:canvas
        anchors.fill: parent
        onPaint:
        {
            var ctx = getContext("2d")
            ctx.clearRect(0,0,canvas.width,canvas.height)
            ctx.save();
            ctx.beginPath();
            var point=[]
            for(var x = 0;x < 400;x++)
            {
                var y = root.h*Math.sin(root.vose + Math.PI * x * root.waternum)
                point.push([x,y + root.height - root.value])
                ctx.lineTo(x,y + root.height - root.value)
            }
            ctx.lineTo(root.mX,root.height)
            ctx.lineTo(0,root.mX)
            ctx.lineTo(point[0][0],point[0][1])
            ctx.stroke()
            ctx.fillStyle = "#00bfff"
            ctx.fill()
            ctx.restore()
        }
    }
    Timer
    {
        id:timer
        running: true
        interval: 50
        repeat: true
        onTriggered:
        {
            root.value+=3
            root.vose += 0.3
            canvas.requestPaint()
        }
    }
//    MouseArea
//    {
//        anchors.fill: parent
//        onClicked:
//        {
//            timer.start()
//        }
//    }
}
