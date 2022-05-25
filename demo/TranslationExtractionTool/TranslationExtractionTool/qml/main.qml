import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import Qt.labs.platform 1.0
import QtGraphicalEffects 1.0

Window {
    id: rootWindow;
    visible: true;
    width: 650;
    height: 480;
    minimumWidth: 650;
    minimumHeight: 350;
    property string version: "V0.03";
    title: qsTr("ts与xlsx转换工具（内测版）") + " " + version;

    ScrollView{
        id: srollView;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.bottom: middleRowFlow.top;
        anchors.margins: 10;
        clip: true;

        Flow{
            id: fileItemFlow;
            width: srollView.width;
            spacing: 10;
            flow: Qt.LeftToRight;
            property int tsCount: 0; //添加的ts文件数量
            property int xlsxCount: 0; //添加的xlsx文件数量
            onTsCountChanged: {addFileCountChanged()}
            onXlsxCountChanged: {addFileCountChanged()}

            add: Transition {
                NumberAnimation{ properties: "opacity"; from: 0; to: 1.0; duration: 1000; easing.type: Easing.OutQuart }
            }
            move: Transition {
                NumberAnimation{ properties: "x,y"; duration: 500; easing.type: Easing.OutCubic }
            }

            onChildrenChanged: {
                srollFlowEmptyHintText.visible = (children.length === 0);
                clearBtn.enabled = (children.length !== 0);
            }
        }
    }

    Component{
        id: importFileItem;
        ImportFileItem {}
    }

    //还没添加文件时的提示文字
    Text{
        id: srollFlowEmptyHintText;
        anchors.centerIn: srollView;
        text: qsTr("请拖入或按“+”添加文件");
        font.pixelSize: 30;
        color: Qt.rgba(0.5, 0.5, 0.5, 0.5);
    }

    //拖动文件进入（这个不能放ScrollView里面，不然滑动条不出来）
    DropArea {
        anchors.fill: srollView;
        onDropped: {
            if(drop.hasUrls)
            {
                resolveFileUrls(signalHandler.resolveDirectory(drop.urls));
            }
        }
    }

    //添加文件对话框
    Component{
        id: addFileDialog;
        FileDialog{
            fileMode: FileDialog.OpenFiles;
            nameFilters: [qsTr("ts或xlsx文件") + "(*.ts; *.xlsx)"];
            onAccepted: {
                resolveFileUrls(currentFiles);
                destroy();
            }
            onRejected: {destroy();}
        }
    }

    //解析要添加的文件路径
    function resolveFileUrls(fileUrls)
    {
        var children = fileItemFlow.children;
        for(var i = 0; i < fileUrls.length; i++)
        {
            var filePath = fileUrls[i].toString().slice(8); //删除"file:///"前缀
            var fileSuffix = filePath.slice(filePath.lastIndexOf(".")+1); //获取文件后缀名
            if(fileSuffix === "ts" || fileSuffix === "xlsx")
            {
                //查找是否已经添加该文件
                var alreadyAdd = false;
                for(var j = 0; j < children.length; j++)
                {
                    if(children[j].path === filePath)
                    {
                        alreadyAdd = true;
                        break;
                    }
                }

                if(!alreadyAdd)
                {   //未添加则添加
                    importFileItem.createObject(fileItemFlow).setFilePath(filePath, fileSuffix);
                }
            }
        }
    }

    //添加的文件数量发生变化
    function addFileCountChanged()
    {
        if(fileItemFlow.xlsxCount > 0 && fileItemFlow.tsCount === 0)
        {   //有添加xlsx文件，没有添加ts文件
            exportTypeBtn.selectedNum = 1; //只能导出ts文件
            exportTypeBtn.enabled = false;
        }
        else if(fileItemFlow.tsCount > 0 && fileItemFlow.xlsxCount === 0)
        {   //有添加ts文件，没有添加xlsx文件
            exportTypeBtn.selectedNum = 0; //只能导出xlsx文件
            exportTypeBtn.enabled = false;
        }
        else
        {
            exportTypeBtn.enabled = true;
        }
        judgeSelectFolder();
    }

    //判断输出位置是否选择文件夹（还是选择一个文件）
    function judgeSelectFolder(selectedNumChanged)
    {
        var isOutFolderOld = outputField.isOutFolder; //之前是否是文件夹输出
        if((exportTypeBtn.selectedNum === 0 && fileItemFlow.tsCount > 1 && !singleFileCbx.checked)
                || (exportTypeBtn.selectedNum === 1 && fileItemFlow.xlsxCount > 1))
        {   //选择文件夹：导出xlsx，有多个ts需要导出，且未选择导出到单个xlsx时；或导出ts，有多个xlsx需要导出时
            outputField.isOutFolder = true;
            outputField.placeholderText = qsTr("填写要保存的目录");
        }
        else
        {   //选择导出文件
            outputField.isOutFolder = false;
            outputField.placeholderText = qsTr("填写要保存的文件地址");
        }
        singleFileCbx.visible = (exportTypeBtn.selectedNum === 0 && fileItemFlow.tsCount > 1); //导出只有1个ts文件时，隐藏单个文件选项

        //自动生成输出路径
        if(fileItemFlow.children.length === 1 && outputField.text === "")
        {   //还没有填写，自动生成一个目标位置（仅添加第一个文件时生成）
            var firstPath = fileItemFlow.children[0].path;
            outputField.text = firstPath.slice(0, firstPath.lastIndexOf(".")+1) + (exportTypeBtn.selectedNum === 0 ? "xlsx" : "ts");
        }
        else if(isOutFolderOld != outputField.isOutFolder || selectedNumChanged === true)
        {   //输出类型发生改变
            var nowPath = outputField.text; //当前填的路径
            if(nowPath.indexOf(".", nowPath.lastIndexOf("/")) >= 0)
            {   //从最后一个"/"的位置开始找，如果有"."认为是一个文件名
                nowPath = nowPath.slice(0, nowPath.lastIndexOf("/")); //去除最后的文件名，保留目录
            }
            while(nowPath[nowPath.length-1] === "/")
            {   //去除最后的'/'
                nowPath = nowPath.slice(0, nowPath.length-1);
            }

            if(outputField.isOutFolder)
            {   //输出到目录
                outputField.text = nowPath;
            }
            else
            {   //输出到文件
                if((exportTypeBtn.selectedNum === 0 ? fileItemFlow.tsCount : fileItemFlow.xlsxCount) !== 0)
                {   //文件不为空
                    var findPath = "";
                    for(var i = 0; i < fileItemFlow.children.length; i++)
                    {   //找到第一个需要导出的文件
                        if(fileItemFlow.children[i].type === (exportTypeBtn.selectedNum === 0 ? 1 : 0))
                        {
                            findPath = fileItemFlow.children[i].path;
                            break;
                        }
                    }
                    if(findPath !== "")
                    {   //找到文件
                        var fileName = findPath.slice(findPath.lastIndexOf("/")+1, findPath.lastIndexOf(".")+1); //提取文件名（不带后缀）
                        fileName += (exportTypeBtn.selectedNum === 0 ? "xlsx" : "ts");
                        outputField.text = nowPath + "/" + fileName;
                    }
                }
                else
                {   //清空文件时会走到这里，同时清空输出目录
                    outputField.text = "";
                }
            }
        }
    }

    //--------------------------底部上面的-----------------------------<
    Flow{
        id: middleRowFlow;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: bottomRowLayout.top;
        anchors.margins: 10;
        spacing: 9;
        add: Transition {
            NumberAnimation{ properties: "opacity"; from: 0; to: 1.0; duration: 1000; easing.type: Easing.OutQuart }
        }
        property bool addTransition: false;
        Transition {
            id: flowMoveTransition;
            NumberAnimation{ properties: "x"; duration: 500; easing.type: Easing.OutCubic; }
        }

        Text{
            text: qsTr("导出类型：");
            font.pixelSize: 14;
            height: exportTypeBtn.height;
            verticalAlignment: Text.AlignVCenter;
        }

        BinaryButton{
            id: exportTypeBtn;
            leftText: ".xlsx";
            rightText: ".ts";
            onSelectedNumChanged: {
                if(middleRowFlow.move === null)
                {   //首次更改时才加动画，不然程序启动的时候就会有动画不好看
                    middleRowFlow.move = flowMoveTransition;
                }
                judgeSelectFolder(true);
                markUnfinishedCbx.visible = (selectedNum == 1);
            }
        }

        NormalCheckBox{
            id: singleFileCbx;
            height: exportTypeBtn.height;
            text: qsTr("导出单个xlsx");
            font.pixelSize: 14;
            visible: false;
            onCheckedChanged: {
                judgeSelectFolder();
            }
        }

        NormalCheckBox{
            id: skipObsoleteCbx;
            height: exportTypeBtn.height;
            text: qsTr("跳过失效的");
            font.pixelSize: 14;
            checked: true;
        }

        NormalCheckBox{
            id: markUnfinishedCbx;
            height: exportTypeBtn.height;
            text: qsTr("ts更新项标记") + "\"?\"";
            font.pixelSize: 14;
            checked: true;
            visible: false;
        }
    }

    //-------------------------添加和删除按钮---------------------------<
    Row {
        anchors.verticalCenter: middleRowFlow.verticalCenter;
        anchors.right: parent.right;
        anchors.margins: 10;
        spacing: 6;
        NormalButton { //添加按钮
            text: "+";
            circleStyle: true;
            fontPixelSize: 20;

            onClicked: {
                addFileDialog.createObject(rootWindow).visible = true;
            }
        }

        NormalButton { //清除按钮
            id: clearBtn;
            text: "×";
            fontPixelSize: 18;
            circleStyle: true;
            hoverColor: "#EE4000";
            enabled: false;

            onClicked: { //清除全部项目
                var children = fileItemFlow.children;
                for(var i = 0; i < children.length; i++)
                {
                    children[i].destroy();
                }
                fileItemFlow.xlsxCount = 0;
                fileItemFlow.tsCount = 0;
            }
        }
    }

    //-----------------------------底部-------------------------------<
    RowLayout{
        id: bottomRowLayout;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        anchors.margins: 10;
        spacing: 8;

        Text {
            text: qsTr("导出位置：");
            font.pixelSize: 14;
        }

        CustomTextField{
            id: outputField;
            Layout.fillWidth: true;
            rightPadding: 37; //给打开文件夹按钮留位置
            placeholderText: qsTr("填写要保存的文件地址");
            property bool isOutFolder: false; //是否输出位置选择文件夹

            onTextChanged: {
                exportBtn.enabled = (text !== "");
            }

            DropArea {
                anchors.fill: outputField;
                onDropped: {
                    if(drop.hasUrls)
                    {
                        outputField.text = drop.urls[0].toString().slice(8);
                    }
                }
            }

            //浏览导出位置按钮
            Button {
                id: browseBtn;
                width: 21; //6:5的图片
                height: 18;
                anchors.right: parent.right;
                anchors.verticalCenter: parent.verticalCenter;
                anchors.margins: 5;
                background: Image {
                    source: "qrc:/folderIcon.png";
                    layer.enabled: true;
                    layer.effect: ColorOverlay{
                        color: browseBtn.enabled ? (browseBtn.checkable ? (browseBtn.checked ? "#03A9F4" : "gray") : (browseBtn.pressed ? "#1C628D" : (browseBtn.hovered ? "#44CF16" : "#03A9F4"))) : "lightGray";
                        Behavior on color { ColorAnimation{ duration: 500; easing.type: Easing.OutCubic } }
                    }
                }

                onClicked: {
                    var dialog;
                    if(outputField.isOutFolder)
                    {   //要选择文件夹（批量导出）
                        dialog = saveFolderDialog.createObject(rootWindow);
                    }
                    else
                    {   //导出单个文件
                        dialog = saveFileDialog.createObject(rootWindow);
                        if(exportTypeBtn.selectedNum === 0)
                        {   //导出xlsx
                            dialog.nameFilters = [qsTr("Excel文件") + "(*.xlsx)"];
                        }
                        else
                        {   //导出ts
                            dialog.nameFilters = [qsTr("ts文件") + "(*.ts)"];
                        }
                    }
                    dialog.visible = true;
                }
            }

            //选择输出文件/目录对话框
            Component{
                id: saveFileDialog;
                FileDialog{ //选择文件
                    fileMode: FileDialog.SaveFile;
                    onAccepted: {
                        outputField.text = currentFile.toString().slice(8);
                        destroy();
                    }
                    onRejected: {destroy();}
                }
            }
            Component{
                id: saveFolderDialog;
                FolderDialog{  //选择目录
                    onAccepted: {
                        outputField.text = currentFolder.toString().slice(8);
                        destroy();
                    }
                    onRejected: {destroy();}
                }
            }
        }

        //导出按钮
        NormalButton{
            id: exportBtn;
            text: qsTr("导出");
            enabled: false;

            onClicked: {
                //取出所有输入文件路径
                var children = fileItemFlow.children;
                var srcFiles = new Array;
                for(var i = 0; i < children.length; i++)
                {
                    var item = children[i];
                    if((exportTypeBtn.selectedNum === 0 && item.type === 1)
                            || (exportTypeBtn.selectedNum === 1 && item.type === 0))
                    {
                        srcFiles.push(item.path);
                    }
                }

                signalHandler.signalExport(outputField.text, srcFiles, exportTypeBtn.selectedNum, singleFileCbx.checked, skipObsoleteCbx.checked, markUnfinishedCbx.checked);
                enabled = false;
            }
        }
    }

    Connections{
        target: signalHandler;
        onSignalExportFinished: { //导出结束信号
            exportBtn.enabled = true;
        }
    }

    //右下角消息提示框
    ShowMessageDialog{
        id: showMessageDialog;
        Component.onCompleted: {
            signalHandler.signalShowMessage.connect(showMessageDialog.showMessage);
        }
    }
}
