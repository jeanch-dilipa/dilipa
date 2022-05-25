import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Window 2.12

Window
{
    flags:"WindowMinMaxButtonsHint"
    title: qsTr("debugmsg")

    Connections
    {
        target: REPEATER
        onSignaldebugserialport:
        {
            model.append({debugmsg:debugmessage})
            listView.currentIndex=listView.currentIndex+1
        }
    }

    ListView
    {
        id:listView
        anchors.fill: parent
        model:model
        delegate: Text
        {
            width:parent.width
            text:debugmsg
            wrapMode:Text.WordWrap      //换行模式
            fontSizeMode:Text.Fit
            minimumPixelSize:10
        }
    }

    ListModel
    {
        id:model
    }
}


