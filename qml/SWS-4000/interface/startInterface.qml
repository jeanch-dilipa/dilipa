import QtQuick 2.0

Rectangle
{
    id:startView
    width: $G_DATA.m_rootWindowWidth
    height: $G_DATA.m_rootWindowHeight

    Image
    {
        id: backGroundimage
        anchors.fill: parent
//        source: "qrc:/new/prefix1/image/background.png"
    }

    Image
    {
        id: bootLogo
        y: parent.height
        anchors.horizontalCenter: startView.horizontalCenter
//        source: "qrc:/new/prefix1/image/boot-logo-sws.png"
        NumberAnimation
        {
            id:bootLogoAnimation
            running: true
            target: bootLogo
            properties: "y"
            from:bootLogo.y
            to: 110
            duration: 2000
        }
        onYChanged:
        {
            if(y == 110)
            {
                DISPATHER.signal_createSystemSelfCheck()
            }

        }
    }

    MouseArea
    {
        anchors.fill: parent
        property point pos: "0,0"
        onPressed:
        {
            pos = Qt.point(mouse.x,mouse.y)
        }
        onReleased:
        {
            if(pos.x - mouse.x > 100 && bootLogoAnimation.running == true)
            {
                DISPATHER.signal_createDetectInterface()
            }
            else if(pos.x - mouse.x < -100 && bootLogoAnimation.running == true)
            {
                DISPATHER.signal_createCorrectInterface()
            }
        }
    }

}
