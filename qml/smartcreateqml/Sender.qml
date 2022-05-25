import QtQuick 2.0

Rectangle
{
    width: parent.width
    height: parent.height
    anchors.centerIn: parent
    Rectangle
    {
        id: sender
        width: 150
        height: width
        radius: width/2
        x:parent.width/8
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#d82cf56e"
            }

            GradientStop {
                position: 0.479
                color: "#714aec"
            }

            GradientStop {
                position: 1
                color: "#de4aec"
            }
        }
        anchors.verticalCenter:parent.verticalCenter
        MouseArea
        {
            anchors.fill:parent
            onPressed:
            {
                sender.width--
                recivel.width++
                canvas.requestPaint()
            }
        }
    }
    Canvas
    {   id:canvas
        anchors.fill:parent
        onPaint:
        {
            var ctx=canvas.getContext("2d")
            var gad=ctx.createLinearGradient(80+sender.width,0,475-recivel.width/2,0)   //渐变区域
            gad.addColorStop(0,Qt.rgba(0,0,0,0.9))
            gad.addColorStop(0.5,Qt.rgba(44,0,40,0.5))
            gad.addColorStop(1,Qt.rgba(79,53,0,0.2))
            ctx.fillStyle=gad
            ctx.beginPath()
//            ctx.moveTo(80+sender.width,240)
//            ctx.lineTo(475-recivel.width/2,240)
            ctx.fillRect(80+sender.width,230,475-recivel.width/2-80-sender.width,10)
            ctx.stroke()
        }
    }
    Rectangle
    {
        id: recivel
        width: 150
        height: width
        color: "#714aec"
        radius: width/2
        x:parent.width/8*5
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#714aec"
            }

            GradientStop {
                position: 0.479
                color: "#de4aec"
            }

            GradientStop {
                position: 1
                color: "#d82cf56e"
            }
        }
        anchors.verticalCenter:parent.verticalCenter
        MouseArea
        {
            anchors.fill:parent
            onPressed:
            {
                recivel.width--
                sender.width++
                canvas.requestPaint()
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.8999999761581421}
}
##^##*/
