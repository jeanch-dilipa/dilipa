import QtQuick 2.0
import QtQuick.Controls 2.5
import "SqliteSet.js" as DB

Rectangle
{
    id:root
    width: 300
    height: 770
    anchors.left: parent.left
    anchors.bottom: parent.bottom
    clip: true

//    Component.onCompleted:
//    {
//        DB.initdatabase()
//        DB.selectdata("")
//    }

    Connections
    {
        target: SIMPLE_MANGER
        onSignal_returnregionlist:
        {
            if(gradelist[0]==="0")
                listmodeladdregion0(regionlist,gradelist)
            if(gradelist[0]==="1")
                listmodeladdregion1(regionrow,regionlist,gradelist)
        }
    }

    ListModel
    {
        id:region_model
        Component.onCompleted:
        {
            SIMPLE_MANGER.signal_selectregion("Provincial_region","Provincial_region_name","Provincial_region_grade","1")
        }
    }

    Component
    {
        id:region_delegate
        Column
        {
            id:region_list
            Row
            {
                id:region_row
                Item
                {
                    height: 1
                    width: model.grade*20
                }
                Text
                {
                    text:(region_list.children.length>2?region_list.children[1].visible?qsTr("- "):qsTr("+ "):qsTr("  "))
                    font.pointSize: 12
                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:
                        {
                            for(var i=1;i<region_list.children.length-1;++i)
                                region_list.children[i].visible=!region_list.children[i].visible
                        }
                    }
                }
                Rectangle
                {
                    width: root.width-model.grade*20
                    height: region_name.height
                    Text
                    {
                        id:region_name
                        text: model.region
                        font.pointSize: 12
                    }
                    MouseArea
                    {
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked:
                        {
                            for(var i=1;i<region_list.children.length-1;++i)
                                region_list.children[i].visible=!region_list.children[i].visible
                        }
                        onEntered: parent.color=Qt.rgba(141/255,205/255,156/255,0.5)
                        onExited: parent.color="white"
                    }
                }
            }
            Repeater
            {
                model:subordinate
                delegate: region_delegate
            }
        }
    }

    ListView
    {
        id:region_data
        anchors.fill: parent
        model:region_model
        delegate: region_delegate
    }

    function listmodeladdregion0(regionlist,gradelist)
    {
        for(var i=0;i<regionlist.length;i++)
        {
            region_model.append({region:regionlist[i],grade:gradelist[i],subordinate:[]})
        }
        for(i=0;i<regionlist.length;i++)
        {
            SIMPLE_MANGER.signal_selectregion("Municipal_area","Municipal_area_name","Municipal_area_grade","superior="+(i+1))
        }
    }
    function listmodeladdregion1(regionrow,regionlist,gradelist)
    {
        for(var i=0;i<regionlist.length;i++)
        {
            region_model.get(regionrow).subordinate.append({region:regionlist[i],grade:gradelist[i],subordinate:[]})
        }
    }
}
