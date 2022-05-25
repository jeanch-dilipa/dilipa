import QtQuick 2.12
import QtQuick.Controls 2.5


ApplicationWindow
{
    id:rootwindow
    width: 400
    height: 300
    property var version: 0.1

    visible: true
//    flags: Qt.WindowSystemMenuHint        //开启后不接受拖放
    title: qsTr("Md5_Upk_tool_"+version)

    /*File_path*/
    File_path
    {
        id:file_path
        anchors.top: parent.top
    }

    /*File_addnew*/
    File_addnew
    {
        id:file_addnew
        anchors.top: file_path.bottom
    }

    /*File_droparea*/
    File_droparea
    {
        id:file_droparea
        parent: file_path
    }

    //add&clear
    Rectangle
    {
        id:add
        width: parent.width/10
        height: width
        radius: width/2
        anchors.verticalCenter:parent.verticalCenter
        Rectangle
        {
            id:add1
            width: parent.width*0.7
            height: width/5
            radius: width/2
            border.width: 2
            color: border.color
            border.color: Qt.rgba(Math.random(),Math.random(),Math.random())
            anchors.centerIn: parent
        }
        Rectangle
        {
            id:add2
            width: parent.width*0.7
            height: width/5
            radius: width/2
            border.width: 2
            color: border.color
            border.color: add1.color
            rotation: 90
            anchors.centerIn: parent
        }
        MouseArea
        {
            anchors.fill: add
            hoverEnabled: true
            onEntered: add1.border.color=Qt.rgba(Math.random(),Math.random(),Math.random())
            onExited: add1.border.color=Qt.rgba(Math.random(),Math.random(),Math.random())
        }
    }

    Rectangle
    {
        id:clear
        width: parent.width/10
        height: width
        radius: width/2
        anchors.right: parent.right
        anchors.verticalCenter:parent.verticalCenter
        Rectangle
        {
            id:clear1
            width: parent.width*0.7
            height: width/5
            radius: width/2
            border.width: 2
            color: border.color
            border.color: Qt.rgba(Math.random(),Math.random(),Math.random())
            anchors.centerIn: parent
        }
        MouseArea
        {
            anchors.fill: clear
            hoverEnabled: true
            onEntered: clear1.border.color=Qt.rgba(Math.random(),Math.random(),Math.random())
            onExited: clear1.border.color=Qt.rgba(Math.random(),Math.random(),Math.random())
            onClicked:
            {
                file_path.cleaermodel()
                for(var i=0;i<file_path.filepathlist.length;i++)
                    file_path.filepathlist[i]=""
            }
        }
    }

    Rectangle
    {
        x:parent.width
        y:file_addnew.y-height-10
        id:showinfo
        width: showtext.text.length*10
        height: showtext.font.pixelSize+5
        radius: width/4
        color: Qt.rgba(Math.random(),Math.random(),Math.random())
        clip: true
        Text
        {
            id:showtext
            text: qsTr("error")
            anchors.centerIn: parent
            font.pixelSize: 15
        }
        Connections
        {
            target: fileio
            onShowinfo:
            {
                console.log(info)
                showtext.text=info
                seq.start()
            }
        }
        SequentialAnimation
        {
            id:seq
            NumberAnimation
            {
                target: showinfo
                properties: "x"
                to:rootwindow.width/2-showinfo.width/2
                duration: 500
            }
            NumberAnimation
            {
                target: showinfo
                properties: "opacity"
                to:1
                duration: 2000
            }
            NumberAnimation
            {
                target: showinfo
                properties: "opacity"
                to:0
                duration: 2000
            }
            NumberAnimation
            {
                target: showinfo
                properties: "x"
                to:rootwindow.width
                duration: 0
            }
            NumberAnimation
            {
                target: showinfo
                properties: "opacity"
                to:rootwindow.width
                duration: 1
            }
        }
    }

}
