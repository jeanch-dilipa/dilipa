import QtQuick 2.0
import QtQuick.Controls 2.12


Rectangle
{
    id:root
    width: parent.width
    anchors.fill:parent
    anchors.centerIn: parent
    ScrollView
    {
        anchors.fill: parent
        ListView
        {
            width: parent.width
            model: 10
            delegate: ItemDelegate
            {
                width: parent.width
                height:30
//                Text {
//                    text: "Item 烧开后咖妃kusgfsggskgvfkisfk科恒股份拉跨郭飞歌" + (index + 1)
//                    font.pixelSize: 30
//                    width: parent.width
//                    color: Qt.lighter("blue")           //高亮
//                    color: Qt.darker("blue")        //暗黑
//                    elide: Text.ElideMiddle         //中间省略
//                    wrapMode: Text.WordWrap         //超长换行（前提设置宽度）
//                    verticalAlignment: Text.AlignTop    //垂直对齐效果
//                    clip: true      //超界剪裁
//                    scale:1.5      //缩放
//                    rotation: 30        //旋转
//                    opacity: 0.5        //透明度
//                    smooth: true       //平滑
//                    visible: true       //可见
//                    focus: true         //接收输入焦点
//                }


//                FocusScope      //焦点区域
//                {
//                    width:parent.width
//                    height:parent.height
//                    Rectangle
//                    {
//                        width: input1.width
//                        height: input1.height
//                        color: Qt.rgba(Math.random(),Math.random(),Math.random())
//                        border.color: Qt.darker(color)
//                        anchors.left: parent.left
//                    }
//                    TextInput
//                    {
//                        id:input1
//                        width: parent.width/2
//                        height: parent.height/2
//                        text: qsTr("input")+(index+1)
//                        anchors.left: parent.left
//                        focus: true
//                        KeyNavigation.tab: input2
//                    }
//                    Rectangle
//                    {
//                        width: input2.width
//                        height: input2.height
//                        color: Qt.rgba(Math.random(),Math.random(),Math.random())
//                        border.color: Qt.darker(color)
//                        anchors.left: input1.right
//                    }
//                    TextInput
//                    {
//                        id:input2
//                        width: parent.width/2
//                        height: parent.height/2
//                        text: qsTr("input")+(index+2)
//                        anchors.left: input1.right
//                        focus: true
//                        KeyNavigation.tab: input
//                    }
//                    Rectangle
//                    {
//                        width: input.width
//                        height: input.height
//                        color: Qt.rgba(Math.random(),Math.random(),Math.random())
//                        border.color: Qt.darker(color)
//                        anchors.top: input1.bottom
//                    }
//                    TextEdit
//                    {
//                        id:input
//                        width: parent.width
//                        height: parent.height/2
//                        text: qsTr("sufj")+(index+1)
//                        anchors.top: input1.bottom
//                        KeyNavigation.tab: input1
//                    }
//                }
                state:"stop"
                states:
                [
                    State
                    {
                        name: "stop"
                        PropertyChanges
                        {
                            target: red
                            color:"red"
                        }
                        PropertyChanges
                        {
                            target: green
                            color:"black"
                        }
                    },
                    State{
                        name: "go"
                        PropertyChanges
                        {
                            target: red
                            color:"black"
                        }
                        PropertyChanges
                        {
                            target: green
                            color:"green"
                        }
                    }
                ]
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        parent.state=(parent.state==="stop"?"go":"stop")
                    }
                }
                Rectangle
                {
                    id:red
                    width: 30
                    height: width
                    radius: width/2
                    color: "red"
                    anchors.top: parent.top
                }
                Rectangle
                {
                    id:green
                    width: 30
                    height: width
                    radius: width/2
                    color: "black"
                    anchors.left: red.right
                }
            }
        }
    }
}
