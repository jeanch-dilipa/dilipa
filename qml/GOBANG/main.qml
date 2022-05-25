import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

ApplicationWindow
{
    id:rootwindow
    width: 400
    height: 400
    visible: true
    opacity: 0.5

    property var version: 0.1
    title: qsTr("gobang_"+version+"_rough")

    /*Chessboard*/
    Chessboard
    {
        id:chessboard
    }

}
