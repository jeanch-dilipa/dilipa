import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import Qt.labs.platform 1.0
import QtQuick.Layouts 1.11

Window {
    id: rootWindow;
    visible: true;
    width: 650;
    height: 480;
    minimumWidth: 650;
    minimumHeight: 350;
    property string version: "V2.00";
    title: qsTr(" SWS 升级包打包工具") + " " + version;

    Component{
        id: updateFileItemCom;
        UpdateFileItem {}
    }

    ScrollView{
        id: srollView;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.bottom: middleRowLayout.top;
        anchors.margins: 10;
        clip: true;

        Flow{
            id: srollFlow;
            width: srollView.width;
            spacing: 10;
            flow: Qt.LeftToRight;

            add: Transition {
                NumberAnimation{ properties: "opacity"; from: 0; to: 1.0; duration: 1000; easing.type: Easing.OutQuart }
            }
            move: Transition {
                NumberAnimation{ properties: "x,y"; duration: 500; easing.type: Easing.OutCubic }
            }

            onChildrenChanged: {
                clearBtn.enabled = (children.length !== 0);
                srollFlowEmptyHintText.visible = (children.length === 0);
            }
        }
    }

    //拖动文件进入（这个不能放ScrollView里面，不然滑动条不出来）
    DropArea {
        anchors.fill: srollView;
        onDropped: {
            if(drop.hasUrls)
            {
                resolveFileUrls(updatePacking.resolveDirectory(drop.urls));
            }
        }
    }

    Item {
        id: srollFlowEmptyHintText;
        anchors.fill: srollView;

        Text{
            anchors.centerIn: parent;
            text: qsTr("请添加需要打包的升级文件");
            font.pixelSize: 30;
            color: Qt.rgba(0.5, 0.5, 0.5, 0.5);
        }

        MouseArea{
            anchors.fill: parent;
            onDoubleClicked: {
                addFileDialog.visible = true;
            }
        }
    }

    //用于显示升级项所有文件列表的弹窗
    UpdateFileListDialog {
        id: updateFileListDialog;
        visible: false;
        x: (parent.width - width)/2;
        y: (parent.height - height)/2;
    }

    //左下角消息弹窗
    ShowMessageDialog {
        id: showMessageDialog;
    }

    //接收来自C++的信号
    Connections{
        target: updatePacking;
        onSignalShowMessage: {
            showMessageDialog.showMessage(msg);
        }
        onSignalPackFinished: {
            packingBtn.enabled = true;
        }
    }

    //--------------------------底部上面的-----------------------------<
    RowLayout{
        id: middleRowLayout;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: bottomRowLayout.top;
        anchors.margins: 10;
        spacing: 6;

        Text {
            text: qsTr("升级包版本：");
            font.pixelSize: 14;
        }
        CustomTextField {
            id: packetVerField
            implicitWidth: 95;
            text: "V6.2.01 F";
            validator: RegExpValidator{regExp: /^V[1-9]\.\d\.\d{2} [A-Z]$/;}
            placeholderText: "如:V6.2.01 F";
        }

        Text {
            text: "   " + qsTr("无需重启主控最低版本：");
            font.pixelSize: 14;
        }
        CustomTextField {
            id: minNoRebootVerField;
            implicitWidth: 95;
            text: "V6.0.01 A";
            validator: RegExpValidator{regExp: /^V[1-9]\.\d\.\d{2} [A-Z]$/;}
            placeholderText: "如:V6.1.01 Q";
        }

        Item{ //占位用
            Layout.fillWidth: true;
        }

        NormalButton { //添加按钮
            text: "+";
            circleStyle: true;
            fontPixelSize: 20;
            hoverRotate: true;

            onClicked: { addFileDialog.visible = true; }
        }

        NormalButton { //清除按钮
            id: clearBtn;
            text: "×";
            circleStyle: true;
            fontPixelSize: hovered ? 21 : 18;
            hoverColor: "#EE4000";
            enabled: false;
            Behavior on fontPixelSize {
                NumberAnimation{ duration: 300; easing.type: Easing.OutCubic; }
            }

            onClicked: { //清除全部项目
                var children = srollFlow.children;
                for(var i = 0; i < children.length; i++)
                {
                    children[i].destroy();
                }
            }
        }
    }

    //添加文件对话框
    FileDialog{
        id: addFileDialog;
        fileMode: FileDialog.OpenFiles;
        nameFilters: [qsTr("升级文件") + " (SWS-6000-Revolution; *.db; *.qm; *.bin; compatibility)"];
        onAccepted: {
            resolveFileUrls(currentFiles);
        }
    }

    //解析选择的文件
    function resolveFileUrls(fileUrls)
    {
        for(var i = 0; i < fileUrls.length; i++)
        {
            var fileTotalName = fileUrls[i].toString();
            if(fileTotalName.indexOf("file:///") >= 0)
            {   //若有"file:///"前缀，删除
                fileTotalName = fileTotalName.slice(8);
            }
            var fileName = fileTotalName.slice(fileTotalName.lastIndexOf("/") + 1);
            if(fileName === "SWS-6000-Revolution")
            {   //主控程序
                addUpdateFileToItem("MainPro", fileName, fileTotalName);
            }
            else if(fileName === "SWS6000.db" || fileName === "Interface_control.db")
            {   //数据库
                addUpdateFileToItem("Database", fileName, fileTotalName);
            }
            else if(fileName.match(/^sws-6000_.+\.qm$/))
            {   //语言
                addUpdateFileToItem("Language", fileName, fileTotalName);
            }
            else if(fileName.match(/^HSB_V\d\.\d\d\.bin$/))
            {   //水路板
                addUpdateFileToItem("HSB", fileName, fileTotalName);
            }
            else if(fileName.match(/^BSB_V\d\.\d\d\.bin$/))
            {   //血路板
                addUpdateFileToItem("BSB", fileName, fileTotalName);
            }
            else if(fileName.match(/^HPC_V\d\.\d\d\.bin$/))
            {   //肝素板
                addUpdateFileToItem("HPC", fileName, fileTotalName);
            }
            else if(fileName.match(/^CPC_V\d\.\d\d\.bin$/))
            {   //配液超滤板
                addUpdateFileToItem("CPC", fileName, fileTotalName);
            }
            else if(fileName.match(/^MOB_V\d\.\d\d\.bin$/))
            {   //监控板
                addUpdateFileToItem("MOB", fileName, fileTotalName);
            }
            else if(fileName.match(/^AVP_V\d\.\d\d\.bin$/))
            {   //动静脉压板
                addUpdateFileToItem("AVP", fileName, fileTotalName);
            }
            else if(fileName.match(/^HPB_V\d\.\d\d\.bin$/))
            {   //水路压力板
                addUpdateFileToItem("HPB", fileName, fileTotalName);
            }
            else if(fileName.match(/^PSB_V\d\.\d\d\.bin$/))
            {   //电源板
                addUpdateFileToItem("PSB", fileName, fileTotalName);
            }
            else if(fileName.match(/^RCM_V\d\.\d\d\.bin$/))
            {   //实时清除率监测板
                addUpdateFileToItem("RCM", fileName, fileTotalName);
            }
            else if(fileName.match(/^BVM_V\d\.\d\d\.bin$/))
            {   //血温血容板
                addUpdateFileToItem("BVM", fileName, fileTotalName);
            }
            else if(fileName.match(/^CRB_V\d\.\d\d\.bin$/))
            {   //读卡器板
                addUpdateFileToItem("CRB", fileName, fileTotalName);
            }
            else if(fileName.match(/^compatibility$/))
            {   //软硬件兼容表
                addUpdateFileToItem("Comp", fileName, fileTotalName);
            }
        }
    }

    //添加一个文件到对应的升级项中
    function addUpdateFileToItem(fileType, fileName, fileTotalName){
        var children = srollFlow.children;
        var obj = undefined;

        //先查找有没有已经添加的类型
        for(var i = 0; i < children.length; i++)
        {
            if(children[i].type === fileType)
            {
                obj = children[i];
                break;
            }
        }

        if(obj === undefined)
        {   //没有找到，创建一个
            obj = updateFileItemCom.createObject(srollFlow);
            obj.showFileArray.connect(showFileList);
            obj.type = fileType;
        }
        if(obj.fileArray.indexOf(fileTotalName) < 0)
        {   //没有此文件才添加
            var index = obj.fileNameArray.indexOf(fileName);
            if(index < 0)
            {   //没有文件重名，直接添加
                obj.fileArray.push(fileTotalName);
                obj.fileNameArray.push(fileName);
                obj.refreshShow();
            }
            else
            {   //有文件重名，替换
                obj.fileArray[index] = fileTotalName;
            }
        }
    }

    //显示某个项目中的所有文件（槽）
    function showFileList(fileArray, dialogTitle, backColor){
        updateFileListDialog.dialogTitle = dialogTitle;
        updateFileListDialog.fileArray = fileArray;
        backColor.a = 0.85;
        updateFileListDialog.backColor = backColor;
        updateFileListDialog.visible = true;
    }

    //-----------------------------底部-------------------------------<
    RowLayout{
        id: bottomRowLayout;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        anchors.margins: 10;
        spacing: 6;

        Text {
            text: qsTr("存放位置：") + "   ";
            font.pixelSize: 14;
        }

        CustomTextField {
            id: outputFileField;
            Layout.fillWidth: true;
            onTextChanged: {
                packingBtn.enabled = !(text === "");
            }
            placeholderText: qsTr("填写要保存的文件地址");
        }

        NormalButton {
            text: qsTr("选择");
            onClicked: {
                outputFileDialog.visible = true;
            }
        }

        NormalButton {
            id: packingBtn;
            enabled: false;
            text: qsTr("打包");
            signal startPacking(var packetName, var packetVer, var fileList, var assignVerList, var minNoRebootVer);
            Component.onCompleted: {
                startPacking.connect(updatePacking.slotPacking);
            }

            onClicked: {
                enabled = false;

                var children = srollFlow.children;
                var fileTotalArray = new Array; //所有要打包的文件
                var assignVerList = new Array;  //主控、数据库、语言要分配的版本
                for(var i = 0; i < children.length; i++) //遍历所有升级项
                {
                    var obj = children[i];
                    for(var j = 0; j < obj.fileArray.length; j++) //遍历升级项中的文件列表
                    {
                        fileTotalArray.push(obj.fileArray[j]);
                    }

                    if(obj.type === "MainPro" || obj.type === "Database" || obj.type === "Language")
                    {
                        if(obj.assignVersion !== "")
                        {
                            assignVerList.push(obj.type + "," + obj.assignVersion);
                        }
                    }
                }

                startPacking(outputFileField.text, packetVerField.text, fileTotalArray, assignVerList, minNoRebootVerField.text);
            }
        }
    }

    FileDialog{ //输出升级包位置选择文件对话框
        id: outputFileDialog;
        fileMode: FileDialog.SaveFile;
        nameFilters: [qsTr("SWS升级包文件") + " (*.sws)"];
        currentFile: Qt.resolvedUrl("file:///untitledPacket");

        onAccepted: {
            outputFileField.text = currentFile.toLocaleString().slice(8);
        }
    }
}
