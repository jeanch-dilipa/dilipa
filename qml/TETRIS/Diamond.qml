import QtQuick 2.0

Rectangle
{
    id:root
    width: parent.width/3*2
    height: parent.height
    border.width: 2
    border.color: "black"

    property int columnnum: 12
    property int blockwidth: width/columnnum
    property int rownum: height/blockwidth
    property variant blockspace: [[]]

    Component.onCompleted:
    {

        TETRIS.signal_initblockspace(columnnum,rownum+4)
        time.start()
        focus=true
    }

    Connections
    {
        target: TETRIS
        function onSignal_newblockspace(m_row, m_column, m_isblock)
        {
            if(m_row===blockspace.length)
                blockspace.push([])
            blockspace[m_row][m_column]=m_isblock
        }
        function onSignal_spacedatasendend()
        {
            paintblock.requestPaint()
        }
        function onSignal_gameover()
        {
            time.stop()
            console.log(qsTr("gameover"))
        }
    }

    Canvas
    {
        id:paintblock
        anchors.fill: root
        onPaint:
        {
            var ctx=getContext("2d")
            for(var i=0;i<rownum+4;i++)
                for(var j=0;j<columnnum;j++)
                {
                    if(1===blockspace[i][j])
                    {
                        ctx.fillStyle="green"
                        ctx.fillRect(j*blockwidth,(i-4)*blockwidth,blockwidth,blockwidth)
                    }
                    else
                    {
                        ctx.clearRect(j*blockwidth,(i-4)*blockwidth,blockwidth,blockwidth)
                    }
                }
        }
    }

    Keys.onPressed:
    {
        switch(event.key)
        {
            case Qt.Key_Left:
                TETRIS.signal_move_left_right_down("left")
                break
            case Qt.Key_Right:
                TETRIS.signal_move_left_right_down("right")
                break
            case Qt.Key_Up:
                TETRIS.signal_change_block();
                break
            case Qt.Key_Down:
                TETRIS.signal_move_left_right_down("down")
                break
            case Qt.Key_Backspace:
                time.stop
                break
        }
    }


    Timer
    {
        id:time
        interval: 300
        repeat: true
        onTriggered:
        {
            TETRIS.signal_blockdrop()
        }
    }
}

