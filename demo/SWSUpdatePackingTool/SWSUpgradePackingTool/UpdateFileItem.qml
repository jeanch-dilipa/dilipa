import QtQuick 2.11
import QtQuick.Controls 2.4

Rectangle{
    width: 200;
    height: 80;
    radius: 10;
    property int numbers: 2; //文件个数
    property var fileArray : new Array; //所有文件名（包括路径）
    property var fileNameArray : new Array; //所有文件名（不包括路径）
    property string type; //类型
    property bool isModuleBoard: true; //是否是模块板
    property string assignVersion; //指定版本
    color: backgroundMouseArea.parentColor;
    signal showFileArray(var fileArray, var dialogTitle, var backColor);
    signal showTxtFile(var filePath);

    //刷新显示
    function refreshShow()
    {
        var sufixText = fileArray.length > 1 ? (" × " + fileArray.length) : ""; //显示文件数量
        switch(type)
        {
        case "MainPro":
            titleText.text = qsTr("主控程序") + sufixText;
            isModuleBoard = false;
            break;
        case "Database":
            titleText.text = qsTr("数据库") + sufixText;
            isModuleBoard = false;
            break;
        case "Language":
            titleText.text = qsTr("语言") + sufixText;
            isModuleBoard = false;
            break;
        case "LanguageIni":
            titleText.text = qsTr("语言配置文件") + sufixText;
            isModuleBoard = false;
            break;
        case "HSB":
            titleText.text = qsTr("水路板") + sufixText;
            break;
        case "BSB":
            titleText.text = qsTr("血路板") + sufixText;
            break;
        case "HPC":
            titleText.text = qsTr("肝素板") + sufixText;
            break;
        case "CPC":
            titleText.text = qsTr("配液超滤板") + sufixText;
            break;
        case "MOB":
            titleText.text = qsTr("监控板") + sufixText;
            break;
        case "AVP":
            titleText.text = qsTr("动静脉压板") + sufixText;
            break;
        case "HPB":
            titleText.text = qsTr("水路压力板") + sufixText;
            break;
        case "PSB":
            titleText.text = qsTr("电源板") + sufixText;
            break;
        case "RCM":
            titleText.text = qsTr("实时清除率监测板") + sufixText;
            break;
        case "BVM":
            titleText.text = qsTr("血温血容板") + sufixText;
            break;
        case "CRB":
            titleText.text = qsTr("读卡器板") + sufixText;
            break;
        case "Comp":
            titleText.text = qsTr("软硬件兼容表") + sufixText;
            isModuleBoard = false;
            break;
        default:
            break;
        }
        centerFileText.text = fileNameArray[0] + (fileNameArray.length > 1 ? " ..." : "");
    }

    Behavior on color{ ColorAnimation {duration: 500; easing.type: Easing.OutCubic} }

    MouseArea {
        id: backgroundMouseArea;
        property bool hovered: false;
        property color randomColor;
        property color parentColor: hovered ? (pressed ? Qt.rgba(randomColor.r - 0.1, randomColor.g - 0.1, randomColor.b - 0.1, 1) : Qt.rgba(randomColor.r + 0.2, randomColor.g + 0.2, randomColor.b + 0.2, 1)) : randomColor;
        hoverEnabled: true;
        anchors.fill: parent;
        Component.onCompleted: { //最开始生成一个随机的颜色
            randomColor = Qt.hsla(Math.random(), 0.82, 0.82, 1);
        }
        onEntered: { hovered = true; }
        onExited: { hovered = false; }
        onClicked: {
            showFileArray(fileArray, titleText.text, randomColor);
        }
        pressAndHoldInterval: 800;
        onPressAndHold: {   //长按显示文本文件内容
            if(type === "Comp" || type === "LanguageIni")
            {
                showTxtFile(fileArray[0]);
            }
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
        id: centerFileText;
        anchors.centerIn: parent;
        font.pixelSize: 14;
    }

    Item{   //指定版本
        anchors.fill: parent;
        visible: (type === "MainPro" || type === "Database" || type === "Language");
        NormalButton {
            id: assignVerBtn;
            anchors.left: parent.left;
            anchors.bottom: parent.bottom;
            anchors.margins: 6;
            circleStyle: true;
            circleWidth: 18;
            fontPixelSize: 12;
            text: "√";
            checkable: true;
            onCheckedChanged: {
                assignVersion = checked ? assignVerTextField.text : "";
            }
        }

        Text {
            id: assignVerText;
            anchors.left: assignVerBtn.right;
            anchors.verticalCenter: assignVerBtn.verticalCenter;
            anchors.margins: 6;
            text: qsTr("指定版本") + " ";
            font.pixelSize: 15;
            color: assignVerBtn.checked ? "black" : "gray";
        }

        RegExpValidator{
            id: regExpValidator;
        }

        TextField {
            id: assignVerTextField;
            width: 88;
            height: 30;
            anchors.left: assignVerText.right;
            anchors.verticalCenter: assignVerText.verticalCenter;
            visible: assignVerBtn.checked;
            validator: regExpValidator;
            selectByMouse: true;
            font.pixelSize: 14;
            font.bold: true;
            background : Rectangle {
                anchors.bottom: parent.bottom;
                anchors.bottomMargin: 3;
                height: 2; //压成一条线放在底部
                width: parent.width;
                border.width: 1;
                border.color: "black";
            }
            onTextChanged: {
                assignVersion = assignVerBtn.checked ? text : "";
            }
        }
    }

    onTypeChanged: {    //初始化指定版本的字符，供提示用
        regExpValidator.regExp = (type === "MainPro" ? /^V[1-9]\.\d\.\d{2} [A-Z]$/ : /^V\d\.\d{2}$/);
        assignVerTextField.text = (type === "MainPro" ? "V6.1.01 P" : "V2.00");
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

            Behavior on color {
                ColorAnimation {duration: 300; easing.type: Easing.OutCubic}
            }
        }

        onClicked: {
            parent.destroy();
        }
    }
}
