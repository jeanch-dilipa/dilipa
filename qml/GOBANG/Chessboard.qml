import QtQuick 2.0

Rectangle
{
    id:root
    anchors.fill: parent

    property var linenum:20
    property var endlong: parent.width/linenum
    property var across: parent.height/linenum
    property int player: 1
    property int chessX:0
    property int chessY:0
    property bool play: true
    property bool end: false


    Component.onCompleted:
    {
        focus=true
        GOBANG.signal_initchess(linenum)
    }

    Canvas
    {
        id:paintchessboard
        anchors.fill: root
        onPaint:
        {
            var ctx=getContext("2d")
            ctx.strokeStyle="black"
            ctx.lineWidth=2
            for(var i=1;i<linenum;i++)
            {
                ctx.beginPath()
                ctx.moveTo(2*endlong,i*across)
                ctx.lineTo((linenum-2)*endlong,i*across)
                ctx.closePath()
                ctx.stroke()
            }
            for(var j=1;j<linenum;j++)
            {
                ctx.beginPath()
                ctx.moveTo(j*endlong,2*across)
                ctx.lineTo(j*endlong,(linenum-2)*across)
                ctx.closePath()
                ctx.stroke()
            }
        }
    }

    Canvas
    {
        id:paint_later
        anchors.fill: root
        onPaint:
        {
            var ctx=getContext("2d")
            if(!end)
            {
                if(play)
                {
                    if(0!=chessX&&0!=chessY)
                    {

                        if(2==player)
                            ctx.fillStyle="black"
                        else
                            ctx.fillStyle="red"
                        ctx.beginPath()
                        ctx.arc(chessX*endlong, chessY*across, endlong/2-0.5, 0, 2*Math.PI)
                        ctx.closePath()
                        ctx.fill()
                    }
                }
                else
                {
                    ctx.fillStyle="white"
                    ctx.beginPath()
                    ctx.arc(chessX*endlong, chessY*across, endlong/2+0.5, 0, 2*Math.PI)
                    ctx.closePath()
                    ctx.fill()
                    ctx.beginPath()
                    ctx.moveTo(chessX*endlong-endlong/2-0.5,chessY*across)
                    ctx.lineTo(chessX*endlong+endlong/2+0.5,chessY*across)
                    ctx.closePath()
                    ctx.stroke()
                    ctx.beginPath()
                    ctx.moveTo(chessX*endlong,chessY*across-across/2-0.5)
                    ctx.lineTo(chessX*endlong,chessY*across+across/2+0.5)
                    ctx.closePath()
                    ctx.stroke()
                    console.log(chessX)
                }
            }
            else
            {
                for(var i=1;i<linenum;i++)
                    for(var j=1;j<linenum;j++)
                    {
                        chessX=i
                        chessY=j
                        ctx.fillStyle="white"
                        ctx.beginPath()
                        ctx.arc(chessX*endlong, chessY*across, endlong/2+0.5, 0, 2*Math.PI)
                        ctx.closePath()
                        ctx.fill()
                        ctx.beginPath()
                        ctx.moveTo(chessX*endlong-endlong/2-0.5,chessY*across)
                        ctx.lineTo(chessX*endlong+endlong/2+0.5,chessY*across)
                        ctx.closePath()
                        ctx.stroke()
                        ctx.beginPath()
                        ctx.moveTo(chessX*endlong,chessY*across-across/2-0.5)
                        ctx.lineTo(chessX*endlong,chessY*across+across/2+0.5)
                        ctx.closePath()
                        ctx.stroke()
                    }
            }
        }
    }

    MouseArea
    {
        id:move_later
        anchors.fill: root
        onClicked:
        {
            play=true
            chessX=Math.round(mouseX/endlong)
            chessY=Math.round(mouseY/across)
            if(0==chessX)chessX=1
            if(20==chessX)chessX=19
            if(0==chessY)chessY=1
            if(20==chessY)chessY=19
            player=player==1?2:1
            paint_later.requestPaint()
            GOBANG.signal_recordchess(chessX,chessY,player)
            GOBANG.signal_detectionchess();
        }
    }

    Keys.onPressed:
    {
        switch(event.key)
        {
        case Qt.Key_Up:
            player=player==1?2:1
            GOBANG.signal_takeback()
            break
        }
    }

    Connections
    {
        target: GOBANG
        onSignal_repaint:
        {
            chessX=X
            chessY=Y
            play=false
            paint_later.requestPaint()
        }
        onSignal_voctory:
        {
            if(play===1)
            {
                vctory.text=qsTr("red ")+str
                seq.start()
            }
            else
            {
                vctory.text=qsTr("black ")+str
                seq.start()
            }
//            GOBANG.signal_clearchess()
//            end=true
//            paint_later.requestPaint()
        }
    }

    Rectangle
    {
        id:vc
        width: parent.width/3
        height: width
        radius: width/2
        opacity: 0
        color: Qt.rgba(Math.random(),Math.random(),Math.random())
        Text {
            id: vctory
            anchors.centerIn: parent
            text: qsTr("vctory")
            font.pixelSize: parent.width/3
        }

        SequentialAnimation
        {
            id:seq
            NumberAnimation
            {
                target: vc
                properties: "opacity"
                to:1
                duration: 500
            }
            NumberAnimation
            {
                target: vc
                properties: "opacity"
                to:0
                duration: 10000
            }
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
