import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle
{
    width: parent.width
    height: parent.height
    Rectangle
    {
        id: rect
        width: 200
        height: 200
        radius: 100
        color: Qt.rgba(Math.random(),Math.random(),Math.random())
        antialiasing: true
        anchors.centerIn: parent
        property var price:30

        Text
        {
            text: String("%1%").arg(rect.price)
            anchors.centerIn: parent
        }
        Canvas
        {
            id:canvas
            antialiasing: true      //毛刺
            anchors.fill:parent
            width: 200
            height: 200
            onPaint:
            {
                var ctx= canvas.getContext("2d")
//                ctx.fillStyle=Qt.rgba(rect.price/100,1-rect.price/100,rect.price/100)
//                ctx.clearRect(0,0,parent.width,parent.height)
                ctx.strokeStyle =Qt.rgba(rect.price/100,1-rect.price/100,rect.price/100)
                ctx.lineWidth = 10
                ctx.beginPath()
//                ctx.fillRect(80,80,rect.width*rect.price/100,rect.height)
                ctx.arc(canvas.width/2,canvas.height/2,canvas.width/2-ctx.lineWidth,-Math.PI/2,-Math.PI/2+rect.price/50*Math.PI,false)
                ctx.stroke()        //填充路径
            }
        }

        Component.onCompleted: focus=true       //在界面初始化时设置否则键盘事件无效
        Keys.onPressed:
        {
            switch(event.key)
            {
            case Qt.Key_Up:
                if(rect.price<100)
                    rect.price++
                break
            case Qt.Key_Down:
                if(rect.price>0)
                    rect.price--
                break
            }
            canvas.requestPaint()
        }
    }
}


/*##^##
Designer {
    D{i:0;formeditorZoom:2}
}
##^##*/
