import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3

//import test 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MouseArea
    {
        anchors.fill: parent
        onClicked:
        {
            Hello.dosomething(Hello.Red)
        }
    }

    Connections
    {
        target: Hello
        onChange:Hello.cslot("HelloGreen")
    }

//    signal choose(string str)

//    function qmlfun(string)
//    {
//        console.log("qmlfuntion",string)

//        return "string"
//    }

//    Text {
//        id: show
//        objectName: "name"
//        font.pixelSize: 48
//        text: qsTr("请首字母大写")
//    }

//    MouseArea {
//        anchors.fill: parent
//        onClicked:
//        {
//            hello.show(TEST.Blue)
//            hello.change()
//            hello.str="12";
//            choose("123")
//        }
//    }

//    TEST {
//        id:hello
//        onChange:dosomething(TEST.Green)
//        onStrChanged:
//        {
//            title=hello.str
//            console.log("strchange")
//        }
//    }

//    Text {
//        id: hello_world
//        x: 252
//        y: 184
//        text: qsTr("hello world")
//        horizontalAlignment: Text.AlignLeft
//        font.pixelSize: 50
//        //        anchors.centerIn: parent    //锚点居中
//        anchors.verticalCenter: parent.verticalCenter
//        anchors.horizontalCenter: parent.horizontalCenter

//        property alias newname: hello_world.text
//        signal showcolor(color color_t)
//        onShowcolor: button.text=color_t

//        Connections
//        {
//            target: button
//            onClicked:console.log("click")
//        }
//        Component.onCompleted: hello_world.showcolor.connect(settext)

//        //属性绑定
////        width: 20
////        width: parent.width
////        width: Math.random()
////        width: parent.width>100?200:100
////        width:
////        {
////            if(parent.width>100)
////                return 1000
////            else
////                return 20
////        }
//        width: setWidth()
//    }
//    function setwidth(){return 1000}

//    Button {
//        id: button
//        x: 270
//        y: 327
//        text: hello_world.newname

//        onClicked:{
//            //                    settext();     //信号处理器（槽）
//            hello_world.color=Qt.rgba(Math.random(),Math.random(),Math.random())
//            hello_world.showcolor(hello_world.color)
//        }

//        Keys.onSpacePressed: width=Qt.binding(function(){return hello_world.width})
//    }

//    ListView {
//        id: listView
//        x: 84
//        y: 31
//        width: 207
//        height: 186
//        model: ListModel
//        {
//            id:listmodel
//            Component.onCompleted:
//            {
//                for(var i=0;i<10;i++)
//                    listmodel.append({"name":"Item"+i})
//            }
//        }
//        delegate: Text {
//            text: index+" "+name
//            color:hello_world.color
//        }
//    }


//    function settext(){
//        button.width=200;
//        hello_world.text="connect"
//    }
}
