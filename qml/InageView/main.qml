import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import Qt.labs.platform 1.1

Window
{
    id:rootwindow
    visible: true

    property var rootWIDTH: 640
    property var rootHEIGHT: 480
    property var version: 0.1
    property var imagelist: []
    property var currentimage: 0

    width: 640
    height: 480
    opacity: 0.5
    title: qsTr("ImageView_"+version+"_tough")

    /*filedialog*/
    FileDialog
    {
        id:openfile
        title: qsTr("选择图片")
        fileMode: FileDialog.OpenFiles
        folder: ""
        nameFilters: ["所有文件(*.png;*.jpg;*.bmp;*.gif;*.jpeg;*.*)"]
        onAccepted:
        {
            var reimageid=0
            for(var i=0;i<files.length;i++)
            {
                var recheck=0
                for(var j=0;j<imagelist.length;j++)
                {
                    if(imagelist[j]===files[i])
                    {
                        recheck=1
                        reimageid=j
                    }
                }
                if(!recheck)
                {
                    imagelist[imagelist.length]=files[i]
                    imagemodel.append({imagesource:files[i]})
                }
            }
            if(reimageid)
                currentimage=reimageid
            else
                currentimage=imagelist.length ? imagelist.length-1 : 0
            thumbnail.contentWidth=imagelist.length>1 ? imagelist.length*image_preview.height : image_preview.height
        }
    }

    onCurrentimageChanged:
    {
        current_show_image.source=imagelist[currentimage]
    }

    /*image_view*/
    Flickable
    {
        id:image_view
        width: parent.width-image_control.width
        height: parent.height-image_preview.height

        MouseArea
        {
            anchors.fill: parent
            onWheel:
            {
                if(Qt.ControlModifier & wheel.modifiers)                //旋转
                    current_show_image.rotation+=wheel.angleDelta.y/120*1
                else
                    current_show_image.scale+=wheel.angleDelta.y/120/10             //缩放
            }
        }

        Image
        {
            id:current_show_image
            smooth: true
            mipmap: true        //缩放时过渡
            antialiasing: true          //抗锯齿
            MouseArea
            {
                anchors.fill: parent
                drag.target: parent
                drag.axis: Drag.XAndYAxis           //水平+垂直拖动
//                drag.minimumX: 20-current_show_image.width
//                drag.maximumX: image_view.width-20
//                drag.minimumY: 20-current_show_image.height
//                drag.maximumY: image_view.height-20
            }
        }
    }

    /*image_control*/
    Rectangle
    {
        id:image_control
        width: parent.width*0.2
        height: parent.height-image_preview.height
        anchors.top: parent.top
        anchors.right: parent.right

        /*control_list*/
        ListView
        {
            id:control_list
            anchors.fill: parent
            model: 1
            delegate:control_element

            property var upimage:"qrc:/src/pick_up.png"
            property var downimage:"qrc:/src/pick_down.png"

            Component
            {
                id:control_element
                Rectangle
                {
                    /*image_operation*/
                    id:image_operation
                    anchors.fill: parent
                    /*image_select*/
                    Rectangle
                    {
                        id:image_select
                        width: image_control.width-2
                        height:image_control.height*(downheight/image_control.height)
                        anchors.horizontalCenter: parent.horizontalCenter
                        property var upheight: select_text.height
                        property var downheight: select_text.height+select.height+last_image.height+next_image.height+6
                        clip: true
                        Text
                        {
                            id:select_text
                            anchors.top: parent.top
                            text: qsTr("文件选项")
                            font.pointSize: 10*(2-16/select.height)
                            font.family: "微软雅黑"
                        }
                        Image
                        {
                            id: pick_up
                            source: "qrc:/src/pick_down.png"
                            scale: 0.8*(2-16/select.height)
                            anchors.right: parent.right
                            anchors.top: parent.top
                            MouseArea
                            {
                                anchors.fill: parent
                                onClicked:
                                {
                                    parent.source=(parent.source==control_list.downimage ? control_list.upimage : control_list.downimage)
                                    image_select.height=(image_select.height==image_select.downheight ? image_select.upheight : image_select.downheight)
                                }
                            }
                        }
                        RoundButton
                        {
                            id:select
                            width: image_control.width/2
                            height: image_control.height/23
                            anchors.topMargin: 2
                            anchors.top: select_text.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: qsTr("打开图片")
                            background: Rectangle
                            {
                                radius:parent.width/2
                                color:Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
                            }
                            onClicked: openfile.open()
                        }
                        RoundButton
                        {
                            id:last_image
                            width: image_control.width/2
                            height: image_control.height/23
                            anchors.topMargin: 2
                            anchors.top: select.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: qsTr("上一张")
                            background: Rectangle
                            {
                                radius:parent.width/2
                                color:Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
                            }
                            onClicked: if(currentimage-1>=0)currentimage--
                        }
                        RoundButton
                        {
                            id:next_image
                            width: image_control.width/2
                            height: image_control.height/23
                            anchors.topMargin: 2
                            anchors.top: last_image.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: qsTr("下一张")
                            background: Rectangle
                            {
                                radius:parent.width/2
                                color:Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
                            }
                            onClicked: if(currentimage+1<imagelist.length)currentimage++
                        }
                    }
                    /*image_function*/
                    Rectangle
                    {
                        id:image_function
                        anchors.top: image_select.bottom
                        width: image_control.width-2
                        height:image_control.height*(downheight/image_control.height)
                        anchors.horizontalCenter: parent.horizontalCenter
                        property var upheight: select_text.height
                        property var downheight: select_text.height+select.height+last_image.height+next_image.height+6
                        clip: true
                        Text
                        {
                            id:function_text
                            anchors.top: parent.top
                            text: qsTr("图片处理")
                            font.pointSize: 10*(2-16/select.height)
                            font.family: "微软雅黑"
                        }
                        Image
                        {
                            source: "qrc:/src/pick_down.png"
                            scale: 0.8*(2-16/select.height)
                            anchors.right: parent.right
                            anchors.top: parent.top
                            MouseArea
                            {
                                anchors.fill: parent
                                onClicked:
                                {
                                    parent.source=(parent.source==control_list.downimage ? control_list.upimage : control_list.downimage)
                                    image_function.height=(image_function.height==image_function.downheight ? image_function.upheight : image_function.downheight)
                                }
                            }
                        }
                        Image
                        {
                            id:rectangle_Ellipse
                            source: "qrc:/src/Rectangle_Ellipse.png"
                            anchors.topMargin: 2
                            anchors.top: function_text.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }
                    /*image_message*/

                    /*image_better*/

                }
            }
        }
    }

    /*image_preview*/
    Rectangle
    {
        id:image_preview
        width: parent.width
        height: parent.height*0.2
        anchors.bottom: parent.bottom

        /*thumbnail*/
        ScrollView
        {
            id:thumbnail
            anchors.fill: parent
            ScrollBar.horizontal.policy:ScrollBar.horizontal.size>1 ? ScrollBar.AlwaysOff : ScrollBar.AlwaysOn
//            QML中的ScrollView继承自Pane,而Pane中由于其Content Sizing属性,
//            当只有一个元素的时候;就会自动再调节( resize)这个单独元素的大小,使这个单独的元素适应ScrollView的大小;
//            从而导致ScrollView的滚动条因为没有边界超出而没有必要滑动;或者直接是导致滚动条不出现

            MouseArea
            {
                anchors.fill: parent
                onWheel:
                {

                    var current=currentimage
                    if(current>=0&&current<=imagelist.length-1)
                    {
                        current+=wheel.angleDelta.y/120
                        if(current<0)
                            current=0
                        if(current>imagelist.length-1)
                            current=imagelist.length-1
                        console.log(current,imagelist.length)
                    }
                    currentimage=current
                    thumbnail.ScrollBar.horizontal.position =(1-thumbnail.ScrollBar.horizontal.size)*currentimage/(imagelist.length-1)              //滚动条位置调节
                }
            }

            /*show*/
            Row
            {
                anchors.fill: parent
                spacing: 20
                anchors.topMargin: (image_preview.height-implicitHeight)/2
                Repeater
                {
                    model:imagemodel
                    Button
                    {
                        implicitWidth: implicitHeight
                        implicitHeight:image_preview.height*0.8
                        onClicked:
                        {
                            currentimage=index
                            thumbnail.ScrollBar.horizontal.position =(1-thumbnail.ScrollBar.horizontal.size)*currentimage/(imagelist.length-1)
                        }
                        background: Rectangle
                        {
                            id:showcurrent
                            color:Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
                            radius:5
                            border.width:2
                            border.color:Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
                        }

                        Image
                        {
                            anchors.fill: parent
                            anchors.margins: 5
                            antialiasing: true
                            fillMode: Image.PreserveAspectFit
                            source: imagesource
                        }
                    }
                }
                ListModel
                {
                    id:imagemodel
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.8999999761581421}
}
##^##*/
