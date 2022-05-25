import QtQuick 2.0
import QtQuick.XmlListModel 2.0

Rectangle
{
    id:root
    width: parent.width
    height: parent.height

//    XmlListModel        //xml模型
//    {
//        id: imageModel

//        source: "http://feeds.nationalgeographic.com/ng/photography/photo-of-the-day/"
//        query: "/rss/channel/item"

//        XmlRole { name: "title"; query: "title/string()" }
//        XmlRole { name: "imageSource"; query: "substring-before(substring-after(description/string(), 'img src=\"'), '\"')" }
//    }

    ListView
    {
        id: listView

        anchors.fill: parent

        model: imageModel
        delegate: imageDelegate
        section.property: "nation"
        section.delegate: sectiondelegate

        Component
        {
            id: imageDelegate
            Rectangle
            {
                width: root.width
                height: root.height
                Text
                {
                    anchors.fill: parent
                    anchors.centerIn: parent
                    text: title
                    font.pointSize: 16
                    color: "blue"
                }
            }
        }

    }
    ListModel
    {
        id:imageModel
        ListElement{name:"a";nation:"123"}
        ListElement{name:"b";nation:"456"}
        ListElement{name:"c";nation:"789"}
        ListElement{name:"d";nation:"123"}
        ListElement{name:"e";nation:"123"}
        ListElement{name:"f";nation:"123"}
        ListElement{name:"g";nation:"789"}
        ListElement{name:"h";nation:"123"}
        ListElement{name:"i";nation:"123"}
        ListElement{name:"j";nation:"456"}
        ListElement{name:"k";nation:"123"}
        ListElement{name:"l";nation:"123"}
    }

    Component
    {
        id:sectiondelegate
        Rectangle
        {
            width: root.width
            height: 30
            Text
            {
                anchors.fill: parent
                anchors.centerIn: parent
                text: section
                font.pointSize: 16
                color: "red"
            }
        }
    }
}
