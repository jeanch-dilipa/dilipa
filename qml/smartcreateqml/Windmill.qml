import QtQuick 2.0

Image
{

    width: parent.width
    height: parent.height
    id: background
    source: "qrc:/background.png"
    anchors.centerIn: parent
    property var dura: 250
    Image
    {
        id: pinwheel
        source: "qrc:/pinwheel.png"
        anchors.centerIn: parent
        Behavior on rotation        //动画效果
        {
            NumberAnimation
            {
                duration: dura
            }
        }
    }
    Image
    {
        height: parent.height/2
        id: pole
        source: "qrc:/pole.png"
        anchors.bottom: background.bottom
        anchors.horizontalCenter: background.horizontalCenter
    }

    Component.onCompleted: focus=true

    Keys.onPressed:
    {
        switch(event.key)
        {
        case Qt.Key_Up:
            pinwheel.rotation+=50
//            pinwheel.blurRadius=200
            if(dura>10)
                dura-=10
            break
        case Qt.Key_Down:
            pinwheel.rotation-=50
            if(dura>10)
                dura-=10
            break
        }
//        time.start()
    }

//    Timer
//    {
//        id:time
//        interval: dura
//        repeat: true
//        triggered:
//        {
//            if(dura<250)
//                dura+=10
//            if(dura===250)
//                time.stop()
//        }
//    }
}
