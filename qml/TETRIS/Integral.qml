import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle
{
    id:root
    width: parent.width/3
    height: parent.height
    border.width: 2
    border.color: "black"

    property int nextblocknum
    property int integralnum: 0
    property variant specialblock1:[[0,1,0,0],[0,1,0,0],[0,1,0,0],[0,1,0,0]]
    property variant specialblock2:[[0,0,0,0],[0,0,0,0],[0,1,1,0],[0,1,1,0]]
    property variant specialblock3:[[0,0,0,0],[0,1,0,0],[0,1,0,0],[0,1,1,0]]
    property variant specialblock4:[[0,0,0,0],[0,0,1,0],[0,0,1,0],[0,1,1,0]]
    property variant specialblock5:[[0,0,0,0],[0,0,0,0],[0,1,0,0],[1,1,1,0]]

    Connections
    {
        target: TETRIS
        function onSignal_nextblock(nextblock)
        {
            nextblocknum=nextblock
        }

        function onSignal_integral()
        {
            integralnum+=100
        }
    }

    onNextblocknumChanged:
    {
        paint.requestPaint()
    }

    Text
    {
        id: showintegral
        anchors.top: nextblock.bottom
        anchors.horizontalCenter: root.horizontalCenter
        anchors.topMargin: 30
        text: qsTr("累计积分：")+integralnum
        font.pixelSize: 15
    }

    Rectangle
    {
        id:nextblock
        width: root.width/3*2
        height: width
        anchors.horizontalCenter: root.horizontalCenter
        anchors.top: root.top
        anchors.topMargin: 50

        Canvas
        {
            id:paint
            anchors.fill: parent
            onPaint:
            {
                var ctx=getContext("2d")
                switch(nextblocknum)
                {
                    case 0:
                        for(var i=0;i<4;i++)
                            for(var j=0;j<4;j++)
                            {
                                if(1===specialblock1[i][j])
                                {
                                    ctx.fillStyle="red"
                                    ctx.fillRect(j*paint.width/4,i*paint.width/4,paint.width/4,paint.width/4)
                                }
                                else
                                {
                                    ctx.clearRect(j*paint.width/4,i*paint.width/4,paint.width/4,paint.width/4)
                                }
                            }
                        break
                    case 1:
                        for(i=0;i<4;i++)
                            for(j=0;j<4;j++)
                            {
                                if(1===specialblock2[i][j])
                                {
                                    ctx.fillStyle="red"
                                    ctx.fillRect(j*paint.width/4,i*paint.width/4,paint.width/4,paint.width/4)
                                }
                                else
                                {
                                    ctx.clearRect(j*paint.width/4,i*paint.width/4,paint.width/4,paint.width/4)
                                }
                            }
                        break
                    case 2:
                        for(i=0;i<4;i++)
                            for(j=0;j<4;j++)
                            {
                                if(1===specialblock3[i][j])
                                {
                                    ctx.fillStyle="red"
                                    ctx.fillRect(j*paint.width/4,i*paint.width/4,paint.width/4,paint.width/4)
                                }
                                else
                                {
                                    ctx.clearRect(j*paint.width/4,i*paint.width/4,paint.width/4,paint.width/4)
                                }
                            }
                        break
                    case 3:
                        for(i=0;i<4;i++)
                            for(j=0;j<4;j++)
                            {
                                if(1===specialblock4[i][j])
                                {
                                    ctx.fillStyle="red"
                                    ctx.fillRect(j*paint.width/4,i*paint.width/4,paint.width/4,paint.width/4)
                                }
                                else
                                {
                                    ctx.clearRect(j*paint.width/4,i*paint.width/4,paint.width/4,paint.width/4)
                                }
                            }
                        break
                    case 4:
                        for(i=0;i<4;i++)
                            for(j=0;j<4;j++)
                            {
                                if(1===specialblock5[i][j])
                                {
                                    ctx.fillStyle="red"
                                    ctx.fillRect(j*paint.width/4,i*paint.width/4,paint.width/4,paint.width/4)
                                }
                                else
                                {
                                    ctx.clearRect(j*paint.width/4,i*paint.width/4,paint.width/4,paint.width/4)
                                }
                            }
                        break
                }
                ctx.fill()
            }
        }
    }
}
