import QtQuick 2.0
import QtQuick.Controls 2.5

import "qrc:/common"
import "../Custom_model"

Rectangle
{
    id:root
    width: 1024
    height: 90
    property var currentPage: Common.ControlInterface.Selfinspection

    CustomButton
    {
        id:selfinspection
        width: root.width/8
        height: root.height/3*2
        anchors.verticalCenter: root.verticalCenter
        anchors.left: root.left
        anchors.leftMargin: width/8
        text: qsTr("self-inspection");
        textfontpointsize: 17
        backgroundradius: width/3
        property var bindingPage: Common.ControlInterface.Selfinspection
        property bool optional: true

        spreadColor: "red"

        onClicked:
        {
            if(optional === true)
            {
                if(bindingPage !== currentPage)
                {
                    interfaceManager(currentPage,bindingPage)
                    currentPage = bindingPage
                }
            }
        }
        onOptionalChanged:
        {
            if(optional === false)
            {
                selfinspection.backgroundDefaultColor = "gray"
            }
            else
            {
                selfinspection.backgroundDefaultColor = "#0acf97"
            }
        }
    }

    CustomButton
    {
        id:schema
        width: root.width/8
        height: root.height/3*2
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: selfinspection.right
        anchors.leftMargin: width/8
        text: qsTr("schema");
        textfontpointsize: 17
        backgroundradius: width/3
        property var bindingPage: Common.ControlInterface.Schema
        property bool optional: true
        onClicked:
        {
            if(optional === true)
            {
                if(bindingPage !== currentPage)
                {
                    interfaceManager(currentPage,bindingPage)
                    currentPage = bindingPage
                }
            }
        }
        onOptionalChanged:
        {
            if(optional === false)
            {
                selfinspection.backgroundDefaultColor = "gray"
            }
            else
            {
                selfinspection.backgroundDefaultColor = "#0acf97"
            }
        }
    }

    CustomButton
    {
        id:intend
        width: root.width/8
        height: root.height/3*2
        anchors.verticalCenter: root.verticalCenter
        anchors.left: schema.right
        anchors.leftMargin: width/8
        text: qsTr("intend");
        textfontpointsize: 17
        backgroundradius: width/3
        backgroundDefaultColor: "gray"
        property var bindingPage: Common.ControlInterface.Intend
        property bool optional: false
        onClicked:
        {
            if(optional === true)
            {
                if(bindingPage !== currentPage)
                {
                    interfaceManager(currentPage,bindingPage)
                    currentPage = bindingPage
                }
            }
        }
        onOptionalChanged:
        {
            if(optional === false)
            {
                selfinspection.backgroundDefaultColor = "gray"
            }
            else
            {
                selfinspection.backgroundDefaultColor = "#0acf97"
            }
        }
    }

    CustomButton
    {
        id:install
        width: root.width/8
        height: root.height/3*2
        anchors.verticalCenter: root.verticalCenter
        anchors.left: intend.right
        anchors.leftMargin: width/8
        text: qsTr("install");
        textfontpointsize: 17
        backgroundradius: width/3
        backgroundDefaultColor: "gray"
        property var bindingPage: Common.ControlInterface.Install
        property bool optional: false
        onClicked:
        {
            if(optional === true)
            {
                if(bindingPage !== currentPage)
                {
                    interfaceManager(currentPage,bindingPage)
                    currentPage = bindingPage
                }
            }
        }
        onOptionalChanged:
        {
            if(optional === false)
            {
                selfinspection.backgroundDefaultColor = "gray"
            }
            else
            {
                selfinspection.backgroundDefaultColor = "#0acf97"
            }
        }
    }

    CustomButton
    {
        id:treat
        width: root.width/8
        height: root.height/3*2
        anchors.verticalCenter: root.verticalCenter
        anchors.left: install.right
        anchors.leftMargin: width/8
        text: qsTr("treat");
        textfontpointsize: 17
        backgroundradius: width/3
        backgroundDefaultColor: "gray"
        property var bindingPage: Common.ControlInterface.Treat
        property bool optional: false
        onClicked:
        {
            if(optional === true)
            {
                if(bindingPage !== currentPage)
                {
                    interfaceManager(currentPage,bindingPage)
                    currentPage = bindingPage
                }
            }
        }
        onOptionalChanged:
        {
            if(optional === false)
            {
                selfinspection.backgroundDefaultColor = "gray"
            }
            else
            {
                selfinspection.backgroundDefaultColor = "#0acf97"
            }
        }
    }

    CustomButton
    {
        id:deplane
        width: root.width/8
        height: root.height/3*2
        anchors.verticalCenter: root.verticalCenter
        anchors.left: treat.right
        anchors.leftMargin: width/8
        text: qsTr("deplane");
        textfontpointsize: 17
        backgroundradius: width/3
        backgroundDefaultColor: "gray"
        property var bindingPage: Common.ControlInterface.Deplane
        property bool optional: false
        onClicked:
        {
            if(optional === true)
            {
                if(bindingPage !== currentPage)
                {
                    interfaceManager(currentPage,bindingPage)
                    currentPage = bindingPage
                }
            }
        }
        onOptionalChanged:
        {
            if(optional === false)
            {
                selfinspection.backgroundDefaultColor = "gray"
            }
            else
            {
                selfinspection.backgroundDefaultColor = "#0acf97"
            }
        }
    }

    CustomButton
    {
        id: disinfection
        width: root.width/8
        height: root.height/3*2
        anchors.verticalCenter: root.verticalCenter
        anchors.left: deplane.right
        anchors.leftMargin: width/8
        text: qsTr("disinfection");
        textfontpointsize: 17
        backgroundradius: width/3
        backgroundDefaultColor: "gray"
        property var bindingPage: Common.ControlInterface.Disinfection
        property bool optional: false
        onClicked:
        {
            if(optional === true)
            {
                if(bindingPage !== currentPage)
                {
                    interfaceManager(currentPage,bindingPage)
                    currentPage = bindingPage
                }
            }
        }
        onOptionalChanged:
        {
            if(optional === false)
            {
                selfinspection.backgroundDefaultColor = "gray"
            }
            else
            {
                selfinspection.backgroundDefaultColor = "#0acf97"
            }
        }
    }

    function interfaceManager(_srcInterface_,_objInterface_)
    {
        switch (_srcInterface_)
        {
            case Common.ControlInterface.Selfinspection:
                DISPATHER.signal_destroySystemSelfCheck()
                selfinspection.spreadColor = "#a8a8a8a8"
                break
            case Common.ControlInterface.Schema:
                DISPATHER.signal_destroySchema()
                schema.spreadColor = "#a8a8a8a8"
                break
            case Common.ControlInterface.Intend:
                break
            case Common.ControlInterface.Install:
                break
            case Common.ControlInterface.Treat:
                break
            case Common.ControlInterface.Deplane:
                break
            case Common.ControlInterface.Disinfection:
                break
        }
        switch (_objInterface_)
        {
            case Common.ControlInterface.Selfinspection:
                DISPATHER.signal_createSystemSelfCheck()
                selfinspection.spreadColor = "red"
                break
            case Common.ControlInterface.Schema:
                DISPATHER.signal_createSchema()
                schema.spreadColor = "red"
                break
            case Common.ControlInterface.Intend:
                break
            case Common.ControlInterface.Install:
                break
            case Common.ControlInterface.Treat:
                break
            case Common.ControlInterface.Deplane:
                break
            case Common.ControlInterface.Disinfection:
                break
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
