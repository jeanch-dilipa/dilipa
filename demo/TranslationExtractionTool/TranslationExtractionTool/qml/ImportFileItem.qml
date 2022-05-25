import QtQuick 2.11
import QtQuick.Controls 2.4

Rectangle{
    width: 200;
    height: 80;
    radius: 10;
    color: backgroundMouseArea.parentColor;
    property string path; //文件路径
    property int type; //类型（0-xlsx，1-ts）
    property color itemColor; //颜色
    signal showPath(var filePath);

    Behavior on color{ ColorAnimation {duration: 500; easing.type: Easing.OutCubic} }

    //设置文件路径
    function setFilePath(filePath, fileType) {
        path = filePath; //这个要写在前面，其他地方要用

        if(fileType === "ts")
        {
            type = 1;
            itemColor = Qt.rgba(0.25, 0.80, 0.32, 0.5);
            titleText.text = "Translation file";
            parent.tsCount++;
        }
        else if(fileType === "xlsx")
        {
            type = 0;
            itemColor = Qt.rgba(0.52, 0.75, 0.62, 0.5);
            titleText.text = "Excel Document";
            parent.xlsxCount++;
        }
        else
        {
            return;
        }

        fileNameText.text = filePath.slice(filePath.lastIndexOf("/") + 1);
    }

    Component{
        id: showFileDetailDialog;
        ShowFileDetailDialog{}
    }

    MouseArea {
        id: backgroundMouseArea;
        property bool hovered: false;
        property color parentColor: hovered ? (pressed ? Qt.rgba(itemColor.r - 0.1, itemColor.g - 0.1, itemColor.b - 0.1, 1) : Qt.rgba(itemColor.r + 0.2, itemColor.g + 0.2, itemColor.b + 0.2, 1)) : itemColor;
        hoverEnabled: true;
        anchors.fill: parent;
        onEntered: { hovered = true; }
        onExited: { hovered = false; }
        onClicked: {
            showPath(path);
            var detailDialog = showFileDetailDialog.createObject(parent.parent.parent.parent);
            detailDialog.filePath = path;
            detailDialog.visible = true;
        }
    }

    //标题
    Text {
        id: titleText;
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.margins: 6;
        font.pixelSize: 14;
    }

    //文件名
    Text {
        id: fileNameText;
        anchors.top: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;
        font.pixelSize: 14;
        width: parent.width - 5;
        elide: Text.ElideMiddle; //超过控件长度则省略
        horizontalAlignment: Text.AlignHCenter; //内容水平居中
    }

    //关闭按钮
    Button {
        anchors.top: parent.top;
        anchors.right: parent.right;
        background: Item{}
        width: 25;
        height: 25;

        contentItem: Text {
            text: "×";
            font.pixelSize: 20;
            font.bold: true;
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
            color: parent.pressed ? "darkRed" : (parent.hovered ? "red" : "black");

            Behavior on color { ColorAnimation {duration: 300; easing.type: Easing.OutCubic} }
        }

        onClicked: {
            parent.destroy();
            if(type === 0)
            {
               parent.parent.xlsxCount--;
            }
            else
            {
                parent.parent.tsCount--;
            }
        }
    }
}
