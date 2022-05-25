import QtQuick 2.0
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0

Button
{
    id: root
    property color backgroundDefaultColor: "#0acf97"                                                        //底色
    property color backgroundPressedColor: Qt.darker(backgroundDefaultColor, 1.2)                           //命中颜色
    property color contentItemTextColor: "white"                                                            //文字颜色
    property color spreadColor: "#a8a8a8a8"                                                                 //命中标记
    property var backgroundradius: 3                                                                        //角度
    property var textfontpointsize: 15                                                                      //字号
    property color currentColor: backgroundDefaultColor                                                     //当前颜色
    property bool doNotHint: false                                                                          //命中不改变颜色

    /*parameter*/
    property var value: 0
    property var snap_value: 0
    property var def_value: 0
    property var max_value: 0
    property var min_value: 0
    property var gain: 0
    property var description: qsTr("")

    text: "Button"
    contentItem: Text
    {
        text: root.text
        color: root.contentItemTextColor
        font.pixelSize: textfontpointsize
        font.family: "Arial"
        font.weight: Font.Thin
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle
    {
        color: currentColor
        radius: backgroundradius
        layer.enabled: true
        layer.effect: DropShadow
        {
            transparentBorder: true
            color: spreadColor
            samples: 20
        }
    }

    onDoNotHintChanged:
    {
        if(doNotHint === true)
        {
            backgroundPressedColor = backgroundDefaultColor
        }
        else
        {
            backgroundPressedColor = Qt.darker(backgroundDefaultColor,1.2)
        }
    }
    onPressed:
    {
        root.currentColor = backgroundPressedColor
    }
    onReleased:
    {
        root.currentColor = backgroundDefaultColor
    }
}
