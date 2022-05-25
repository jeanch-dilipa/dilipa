import QtQuick 2.0

Item {
    implicitWidth: 90;
    implicitHeight: 30;
    property string leftText; //左边的文本
    property string rightText; //右边的文本
    property int selectedNum: 0; //当前选择的项（0为左边，1为右边）

    onSelectedNumChanged: {
        if(selectedNum === 0)
        {   //选中左边
            selectedRec.x = 0;
            selectedRec.width = width/2 + 10;
            unselectedRec.x = width - unselectedRec.width;
            leftTextText.color = "white";
            rightTextText.color = "#9B9B9B";
        }
        else
        {   //选中右边
            selectedRec.width = width/2 + 5;
            selectedRec.x = width - selectedRec.width + 5;
            unselectedRec.x = 0;
            leftTextText.color = "#9B9B9B";
            rightTextText.color = "white";
        }
    }

    MouseArea{
        anchors.fill: parent;
        onClicked: {
            selectedNum = !selectedNum;
            parent.focus = true; //鼠标点击获取焦点（可以使其他控件失去焦点，保证一些功能正常使用）
        }
    }

    //左边的选项
    Text{
        id: leftTextText;
        text: leftText;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: parent.left;
        anchors.leftMargin: 10;
        horizontalAlignment: Text.AlignHCenter;
        font.pixelSize: 14;
        font.bold: true;
        z: 2;
        color: "white";
        Behavior on color {
            ColorAnimation { duration: 300; }
        }
    }

    //右边的选项
    Text{
        id: rightTextText;
        text: rightText;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.right: parent.right;
        anchors.rightMargin: 15;
        horizontalAlignment: Text.AlignRight;
        font.pixelSize: 14;
        font.bold: true;
        z: 2;
        color: "#9B9B9B";
        Behavior on color {
            ColorAnimation { duration: 300; }
        }
    }

    //选中的Rec
    Rectangle{
        id: selectedRec;
        width: parent.width/2 + 10;
        height: parent.height;
        radius: 5;
        color: "#03A9F4";
        z: 1;
        Behavior on x {
            NumberAnimation{duration: 300;}
        }
    }

    //未选中的Rec
    Rectangle{
        id: unselectedRec;
        width: parent.width/2 + 10;
        height: parent.height;
        radius: 5;
        color: "#DDE1E1";
        x: parent.width - width;
        Behavior on x {
            NumberAnimation{duration: 300;}
        }
    }
}
