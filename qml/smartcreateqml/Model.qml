import QtQuick 2.0

Rectangle
{
    id:root
    width: parent.width
    height: parent.height

    ListView
    {
        id:listview
        anchors.fill: parent
        model:listmodel
        delegate:delegeitem
    }

    ListModel
    {
        id:listmodel
        ListElement{name:"losih1";txt:"ksughfiugrfiowgufiowgfo1"}
        ListElement{name:"losih2";txt:"ksughfiugrfiowgufiowgfo2"}
        ListElement{name:"losih3";txt:"ksughfiugrfiowgufiowgfo3"}
        ListElement{name:"losih4";txt:"ksughfiugrfiowgufiowgfo4"}
        ListElement{name:"losih5";txt:"ksughfiugrfiowgufiowgfo5"}
    }

    Component
    {
        id:delegeitem
        Item
        {
            id:showitem
            width:parent.width
            height: 30

            Rectangle
            {
                height: 30
                width: parent.width
                anchors.left: parent.left
                color: "red"
                Text {
                    text: name
                    anchors.centerIn: parent
                }
            }
            Rectangle
            {
                id: image
                color: "black"
                anchors.right: parent.right
                width: 26
                height: 26
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked: parent.state="expand"
            }

            Rectangle
            {
                id:tt
                anchors.top: image.bottom
                anchors.right: parent.right
                width: 26
                height: 26
                opacity: 0
                color: "blue"
                Text {
                    text: txt
                    anchors.centerIn: parent
                }
            }
            Rectangle
            {
                id:close
                width:30
                height: 30
                anchors.right: parent.right
                opacity: 0
                color: "green"
                MouseArea
                {
                    anchors.fill: parent
                    onClicked: showitem.state=""
                }
            }
            state: ""
            states:
            [
                State
                {
                    name: "expand"
                    PropertyChanges{target: showitem;height:listview.height}
                    PropertyChanges { target: image; width: listview.width; height: listview.height-80;}
                    PropertyChanges{target: tt;opacity:1;width: listview.width; height: 80}
                    PropertyChanges{target: close;opacity:1}
                    PropertyChanges{target: showitem.ListView.view;contentY:showitem.y;interactive:false}
                }
            ]
            transitions:
            [
                Transition
                {
                    NumberAnimation
                    {
                        duration: 200
                        properties: "height,width,anchors.rightMargin,anchors.topMargin,opacity,contentY"
                    }
                }
            ]
        }

    }





//    Rectangle
//    {
//        id:addbtu
//        width: parent.width
//        height: 20
//        color: Qt.rgba(Math.random(),Math.random(),Math.random())
//        Text {
//            id: text
//            anchors.centerIn: parent
//            text: qsTr("add item")
//        }
//        MouseArea
//        {
//            anchors.fill:parent
//            onClicked:themodel.append({number:++parent.count})
//        }
//        property int count: 8
//    }
//    ListModel
//    {
//        id:themodel
//        ListElement{number:1}
//        ListElement{number:2}
//        ListElement{number:3}
//        ListElement{number:4}
//        ListElement{number:5}
//        ListElement{number:6}
//        ListElement{number:7}
//        ListElement{number:8}
//    }

//    GridView
//    {
//        id:gridview
//        width: parent.width
//        height: parent.height
//        anchors.top: addbtu.bottom
//        model: themodel
//        clip: true
//        delegate: delegateitem
//        anchors.margins: 10

//        cellWidth: 30
//        cellHeight: 30
//        Component
//        {
//            id:delegateitem
//            Rectangle
//            {
//                id:item
//                width: 25
//                height: 25
//                color: Qt.rgba(Math.random(),Math.random(),Math.random())
//                Text {
//                    text: number
//                }
//                MouseArea
//                {
//                    anchors.fill: parent
//                    onClicked:
//                    {
//                        if(!item.GridView.delayRemove)
//                            themodel.remove(index)
//                    }
//                }

//                GridView.onRemove:SequentialAnimation
//                {
//                    PropertyAction{target:item;properties: "GridView.delayRemove";value: true }
//                    NumberAnimation{target: item;properties: "scale";to:0;duration: 200;easing.type: Easing.InOutQuad}
//                    PropertyAction{target:item;properties: "GridView.delayRemove";value: true }
//                }
//                GridView.onAdd:SequentialAnimation
//                {
//                    NumberAnimation{target: item;properties: "scale";from:0;to:1;duration: 200}
//                }
//            }
//        }
//    }




//    Column
//    {
//        spacing: 2
//        Repeater
//        {
//            model: ["as","ada","sf"]
//            Rectangle
//            {
//                width: 100
//                height: 30
//                color: Qt.rgba(Math.random(),Math.random(),Math.random())
//                Text {
//                    anchors.centerIn: parent
//                    id: text
//                    text: modelData+index
//                }
//            }
//        }
//        Repeater
//        {
//            model: ListModel
//            {
//                ListElement{name:"1";surfaceColor: "red"}
//                ListElement{name:"2";surfaceColor: "green"}
//                ListElement{name:"3";surfaceColor: "blue"}

//            }
//            Rectangle
//            {
//                width: 100
//                height: 30
//                color: surfaceColor
//                Text {
//                    anchors.centerIn: parent
//                    id: text1
//                    text: name
//                }
//            }
//        }
//    }
//    GridView//    ListView
//    {
//        width: root.width
//        height: root.height
//        anchors.fill:parent
//        anchors.margins:15
//        clip: true
//        model: 100

//        cellHeight:25       //网格视图控制内容
//        cellWidth:35

//        delegate:numberDelegate
////        spacing: 5
//        header: heade       //页眉页脚
//        footer: foot

//        highlight: highlightcomponent
//        focus: true

//        boundsBehavior: Flickable.DragOverBounds          //视图末尾行为
//        snapMode: ListView.SnapToItem       //元素停止位置
//        orientation: ListView.Horizontal        //视图方向
//        layoutDirection: Qt.RightToLeft         //元素方向
//        highlightRangeMode:ListView.ApplyRange      //高亮行为

//        flow:GridView.BottomToTop
//        layoutDirection:GridView.RightToLeft

//        Component
//        {
//            id:highlightcomponent
//            Rectangle
//            {
//                width: ListView.view.width
//                height: 20
//                color: "blue"
//            }
//        }

//        Component
//        {
//            id:heade
//            Rectangle
//            {
//                width: 30
//                height: 20
//                color: "blue"
//            }
//        }
//        Component
//        {
//            id:foot
//            Rectangle
//            {
//                width: 30
//                height: 20
//                color: "green"
//            }
//        }
//        Component
//        {
//            id:numberDelegate
//            Rectangle
//            {
//                width: 30
//                height: 20
//                color: "red"
////                opacity: 0
//                Text {
//                    text: index
//                    anchors.centerIn: parent
//                }
//            }
//        }
//    }
}
