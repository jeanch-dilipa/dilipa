import QtQuick 2.0

PathView
{
    id:root
    width: parent.width-add.width*2
    height: parent.height-file_addnew.height
    anchors.horizontalCenter: parent.horizontalCenter

    signal cleaermodel()
    onCleaermodel:
    {
        fileio.clearrootfilepath()
        themodel.clear()
    }

    property var filenum:0
    property variant filepathlist: [""]
    property var rootfilepath: ""

    delegate: flipCardDelegate
    model: themodel

    ListModel
    {
        id:themodel
    }


    path: Path
    {
        startX: root.width/2
        startY: 0

        PathAttribute { name: "itemZ"; value: 0 }           //路径属性层级、角度、缩放
        PathAttribute { name: "itemAngle"; value: -90.0; }
        PathAttribute { name: "itemScale"; value: 0.5; }
        PathLine { x: root.width/2; y: root.height*0.4; }
        PathPercent { value: 0.48; }
        PathLine { x: root.width/2; y: root.height*0.5; }
        PathAttribute { name: "itemAngle"; value: 0.0; }
        PathAttribute { name: "itemScale"; value: 1.0; }
        PathAttribute { name: "itemZ"; value: 100 }
        PathLine { x: root.width/2; y: root.height*0.6; }
        PathPercent { value: 0.52; }
        PathLine { x: root.width/2; y: root.height; }
        PathAttribute { name: "itemAngle"; value: 90.0; }
        PathAttribute { name: "itemScale"; value: 0.5; }
        PathAttribute { name: "itemZ"; value: 0 }
    }

    pathItemCount: 8       //显示数量
    preferredHighlightBegin: 0.5        //可见代理项
    preferredHighlightEnd: 0.5

    Component
    {
        id: flipCardDelegate

        Item {
            id: fileitem
            width: parent.width
            height: root.height/5

            visible: PathView.onPath

            scale: PathView.itemScale
            z: PathView.itemZ

            property variant rotX: PathView.itemAngle
            transform: Rotation { axis { x: 1; y: 0; z: 0 } angle: fileitem.rotX; origin { x: 32; y: 32; } }

            MouseArea
            {
                anchors.fill: fileitem
                onWheel:
                {
                    wheel.accepted=true
                    if(wheel.angleDelta.y>0)
                        root.incrementCurrentIndex()
                    else if(wheel.angleDelta.y<0)
                        root.decrementCurrentIndex()
                }
            }

            Rectangle
            {
                id:itemrect
                anchors.fill: parent
                color: Qt.lighter(Qt.rgba(Math.random(),Math.random(),Math.random()))
                radius: width/2
                smooth: true

                Text
                {
                    anchors.centerIn: itemrect
                    text: filename
                    font.pixelSize: itemrect.height/2
                }
                MouseArea
                {
                    anchors.fill: itemrect
                    onClicked: root.currentIndex=index
                }
               Text
               {
                    anchors.bottom: itemrect.bottom
                    width: itemrect.width
                    height: itemrect.height/4
                    text: qsTr("src:")+thefilepath+filename
                    font.pixelSize: itemrect.height/4
                    horizontalAlignment: Text.AlignHCenter
               }

                Rectangle
                {
                    id:removeitem
                    width: root.width/20
                    height: width
                    color: parent.color
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.topMargin: 5
                    anchors.rightMargin: 8

                    MouseArea
                    {
                        anchors.fill:removeitem
                        hoverEnabled: true
                        onClicked:
                        {
                            if(themodel.count===1)
                            {
                                fileio.clearrootfilepath()
                                for(var i=0;i<filepathlist.length;i++)
                                    filepathlist[i]=""
                            }
                            themodel.remove(index)
                        }
                        onEntered:
                        {
                            quit1.border.color="red"
                            quit2.border.color="red"
                        }
                        onExited:
                        {
                             quit1.border.color="gray"
                             quit2.border.color="gray"
                        }
                    }

                    Rectangle
                    {
                        id:quit1
                        width: removeitem.width-2
                        height: 2
                        rotation: 45
                        border.color: "gray"
                        border.width: 2
                        anchors.centerIn: removeitem
                    }
                    Rectangle
                    {
                        id:quit2
                        width: removeitem.width-2
                        height: 2
                        rotation: -45   //旋转
                        border.color: "gray"
                        border.width: 2
                        anchors.centerIn: removeitem
                    }
                }
            }
        }
    }

    Connections
    {
        target: fileio
        onIsneedfile:
        {
            rootfilepath=rootpath
            checkfile(filepath)
            addfile(filepath)
        }
    }

    function addfile(filepath)
    {
        var filename=filepath.slice(filepath.lastIndexOf("/")+1,filepath.lastIndexOf("."))        //提取文件名
        var thefilepath=filepath.slice(8,filepath.lastIndexOf("/"))
        themodel.append({filename:filename,thefilepath:thefilepath})
    }
    function checkfile(filepath)
    {
        var isexist=false
        for(var i=0;i<filepathlist.length;i++)
            if(filepathlist[i]===filepath)
                isexist=true
        if(!isexist)
        {
            filepathlist[themodel.count]=filepath
        }
    }

}
