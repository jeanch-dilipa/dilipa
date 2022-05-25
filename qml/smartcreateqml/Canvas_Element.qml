import QtQuick 2.0

Rectangle
{
    id:root
    width: parent.width
    height: parent.height
    property var operation : [      //组合模式大全
        'source-over', 'source-in', 'source-over',
        'source-atop', 'destination-over', 'destination-in',
        'destination-out', 'destination-atop', 'lighter',
        'copy', 'xor', 'qt-clear', 'qt-destination',
        'qt-multiply', 'qt-screen', 'qt-overlay', 'qt-darken',
        'qt-lighten', 'qt-color-dodge', 'qt-color-burn',
        'qt-hard-light', 'qt-soft-light', 'qt-difference',
        'qt-exclusion'
        ]

    Image
    {
        id: image
        width: parent.width/2
        height: parent.height
        anchors.left: root.left
        cache: false
    }
    Timer
    {
        interval: 1000
        repeat: true
        running: true
        triggeredOnStart: true
        onTriggered: canvas.requestPaint()
    }
    Canvas
    {
        id:canvas
        width: parent.width/2
        height: parent.height
        anchors.left: image.right
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                var url=canvas.save("f:1.png")//canvas.toDataURL("image/png")
                console.log("image.url=",url)
                image.source=""
                image.source="file:///f:1.png"
            }
        }
        onPaint:
        {
            var ctx=getContext("2d")
            ctx.fillStyle=Qt.rgba(Math.random(),Math.random(),Math.random())
            ctx.beginPath()
            ctx.arc(Math.random()*parent.width/2,Math.random()*parent.height,Math.random()*100,0,360)
            ctx.closePath()
            ctx.stroke()




//            var ctx = getContext("2d")
//            ctx.fillStyle = "#33a9ff"
//            for(var i=0; i<operation.length; i++)
//            {
//                for(var j=0;j<25;j++)
//                {
//                    ctx.globalCompositeOperation =operation[i]  // "xor"                //组合模式
//                    ctx.beginPath()
//                    ctx.arc(Math.random()*root.width, Math.random()*root.height, 20, 0, 2*Math.PI)
//                    ctx.closePath()
//                    ctx.fill()
//                }
//            }


//            var ctx=getContext("2d")
//            ctx.lineWidth=4         //画笔宽度
//            ctx.strokeStyle="blue"      //颜色
//            ctx.fillStyle="steeblue"        //填充色
//            ctx.beginPath()             //开始
//            ctx.moveTo(50,50)           //移动到开始点
//            ctx.lineTo(150,50)
//            ctx.lineTo(150,150)
//            ctx.lineTo(50,150)
//            ctx.lineTo(50,50)
//            ctx.closePath()             //结束
//            ctx.fill()              //填充
//            ctx.stroke()            //绘制路径

//            ctx.fillRect(200,200,100,100)     //填充矩形
//            ctx.clearRect(225,225,50,50)      //清除矩形
//            ctx.strokeRect(198,198,104,104)       //绘制矩形

//            var gradient=ctx.createLinearGradient(200,50,300,150)       //渐变从点(200,50)到(300,150)
//            gradient.addColorStop(0,"blue")
//            gradient.addColorStop(0.5,"red")
//            gradient.addColorStop(1,"green")
//            ctx.fillStyle=gradient
//            ctx.fillRect(200,50,100,100)

////            ctx.fillStyle="black"
////            ctx.fillRect(0,0,canvas.width,canvas.height)

//            ctx.shadowColor="red"       //阴影颜色
//            ctx.shadowOffsetX=2         //偏移
//            ctx.shadowOffsetY=2
//            ctx.shadowBlur=10           //模糊
//            ctx.font='100px sans-serif'
//            ctx.fillStyle="#33a9ff"
//            ctx.fillText("dilipa",50,250)

////            ctx.drawImage("qrc:/pinwheel.png",300,100)        //有问题
////            ctx.save()
//            ctx.strokeStyle = "red"
////            ctx.translate(300,0)
//            ctx.beginPath()
//            ctx.moveTo(10,10)
//            ctx.lineTo(105,10)
//            ctx.lineTo(55,105)
//            ctx.closePath()
//            ctx.clip()
////            ctx.drawImage("pinwheel.png", 10, 10)
//            ctx.stroke()

////            ctx.strokeRect(300,0,100,100)
////            ctx.rotate(Math.PI/2)
////            ctx.strokeRect(350,0,100,100)

        }
//        Component.onCompleted: loadImage("qrc:/pinwheel.png")
    }
}
