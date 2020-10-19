import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import EnumDefine 1.0
import PanelMetalManagementInfoModel 1.0

import "../../control/."
import "."

Rectangle {
    property real preWidth : 0

    id : panel

    width : 1196
    height: 93

    color : "#333333"
    radius: 10

    PanelMetalManagementInfoModel
    {
        id : model
    }

    RowLayout
    {
        anchors.right: btnEdit.left
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        anchors.topMargin: 20

        Item{
            id : itemDeviceNumber

            Layout.fillHeight: true
            Layout.preferredWidth: 12
            Layout.fillWidth: true

            UiLabel{
                anchors.top         : parent.top
                anchors.topMargin   : 0
                anchors.right       : parent.right
                anchors.rightMargin : 0
                anchors.left        : parent.left
                anchors.leftMargin  : 0

                text: qsTr("Device number")
            }

            UiLabel{
                anchors.bottom       : parent.bottom
                anchors.bottomMargin : 0
                anchors.right        : parent.right
                anchors.rightMargin  : 0
                anchors.left         : parent.left
                anchors.leftMargin   : 0

                color : "#FFFFFF"
                text  : ("000" + model.mDNum).slice(-3)
            }
        }

        Item
        {
            id : itemCompany

            Layout.fillHeight: true
            Layout.preferredWidth: 12
            Layout.fillWidth: true

            UiLabel{
                anchors.top         : parent.top
                anchors.topMargin   : 0
                anchors.right       : parent.right
                anchors.rightMargin : 0
                anchors.left        : parent.left
                anchors.leftMargin  : 0

                text: qsTr("Company")
            }

            UiLabel{
                anchors.bottom       : parent.bottom
                anchors.bottomMargin : 0
                anchors.right        : parent.right
                anchors.rightMargin  : 0
                anchors.left         : parent.left
                anchors.leftMargin   : 0

                color : "#FFFFFF"
                text  : model.mCompany
            }
        }

        Item
        {
            id : itemDepartment

            Layout.fillHeight: true
            Layout.preferredWidth: 12
            Layout.fillWidth: true

            UiLabel{
                anchors.top         : parent.top
                anchors.topMargin   : 0
                anchors.right       : parent.right
                anchors.rightMargin : 0
                anchors.left        : parent.left
                anchors.leftMargin  : 0

                text: qsTr("Department")
            }

            UiLabel{
                anchors.bottom       : parent.bottom
                anchors.bottomMargin : 0
                anchors.right        : parent.right
                anchors.rightMargin  : 0
                anchors.left         : parent.left
                anchors.leftMargin   : 0

                color : "#FFFFFF"
                text  : model.mDepartment
            }
        }

        Item
        {
            id : itemPosition

            Layout.fillHeight: true
            Layout.preferredWidth: 12
            Layout.fillWidth: true

            UiLabel{
                anchors.top         : parent.top
                anchors.topMargin   : 0
                anchors.right       : parent.right
                anchors.rightMargin : 0
                anchors.left        : parent.left
                anchors.leftMargin  : 0

                text: qsTr("Position")
            }

            UiLabel{
                anchors.bottom       : parent.bottom
                anchors.bottomMargin : 0
                anchors.right        : parent.right
                anchors.rightMargin  : 0
                anchors.left         : parent.left
                anchors.leftMargin   : 0

                color : "#FFFFFF"
                text  : model.mPosition
            }
        }

        Item
        {
            id : itemName

            Layout.fillHeight: true
            Layout.preferredWidth: 12
            Layout.fillWidth: true

            UiLabel{
                anchors.top         : parent.top
                anchors.topMargin   : 0
                anchors.right       : parent.right
                anchors.rightMargin : 0
                anchors.left        : parent.left
                anchors.leftMargin  : 0

                text: qsTr("Name")
            }

            UiLabel{
                anchors.bottom       : parent.bottom
                anchors.bottomMargin : 0
                anchors.right        : parent.right
                anchors.rightMargin  : 0
                anchors.left         : parent.left
                anchors.leftMargin   : 0

                color : "#FFFFFF"
                text  : model.mName
            }
        }

        Item
        {
            id : itemLimitCriteriaFe

            Layout.fillHeight: true
            Layout.preferredWidth: 12
            Layout.fillWidth: true

            UiLabel{
                anchors.top         : parent.top
                anchors.topMargin   : 0
                anchors.right       : parent.right
                anchors.rightMargin : 0
                anchors.left        : parent.left
                anchors.leftMargin  : 0

                text: qsTr("Limit criteria(Fe)")
            }

            UiLabel{
                anchors.bottom       : parent.bottom
                anchors.bottomMargin : 0
                anchors.right        : parent.right
                anchors.rightMargin  : 0
                anchors.left         : parent.left
                anchors.leftMargin   : 0

                color : "#FFFFFF"
                text  : model.mLimCriteriaFe
            }
        }

        Item
        {
            id : itemLimitCriteriaSus

            Layout.fillHeight: true
            Layout.preferredWidth: 12
            Layout.fillWidth: true

            UiLabel{
                anchors.top         : parent.top
                anchors.topMargin   : 0
                anchors.right       : parent.right
                anchors.rightMargin : 0
                anchors.left        : parent.left
                anchors.leftMargin  : 0

                text: qsTr("Limit criteria(Sus)")
            }

            UiLabel{
                anchors.bottom       : parent.bottom
                anchors.bottomMargin : 0
                anchors.right        : parent.right
                anchors.rightMargin  : 0
                anchors.left         : parent.left
                anchors.leftMargin   : 0

                color : "#FFFFFF"
                text  : model.mLimCriteriaSus
            }
        }

        Item
        {
            id : itemHaccp

            Layout.fillHeight: true
            Layout.preferredWidth: 10
            Layout.fillWidth: true

            clip: true

            UiLabel{
                anchors.top         : parent.top
                anchors.topMargin   : 0
                anchors.right       : parent.right
                anchors.rightMargin : 0
                anchors.left        : parent.left
                anchors.leftMargin  : 0

                text: qsTr("HACCP")
            }

            UiLabel{
                anchors.bottom       : parent.bottom
                anchors.bottomMargin : 0
                anchors.right        : parent.right
                anchors.rightMargin  : 0
                anchors.left         : parent.left
                anchors.leftMargin   : 0

                color : "#FFFFFF"
                text  : model.mHACCP
            }
        }
    }

    UiButton{
        id: btnEdit

        width: 60
        height: 60
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 20

        text: ""
        iconSource: "image_icon/edit.png"

        onSignalEventClicked: {
            deviceListModel.clear()

            for(var i = 0; i < model.onCommandGetDListSize(); i ++)
            {
                var value =("000" + model.onCommandGetDNum(i)).slice(-3) + " " +  model.onCommandGetDName(i);
                var tag =("000" + model.onCommandGetDNum(i)).slice(-3);
                deviceListModel.append({"itemValue":value,"itemTag":tag})
            }

            popupInfoEditor.open(model.mDNum, model.mDName, model.mCompany, model.mDepartment, model.mPosition, model.mName, model.mLimCriteriaFe, model.mLimCriteriaSus, model.mHACCP, model.mMDCheckupCycle)
        }

    }

    PopupMetalManagementInfoEditor{
        id : popupInfoEditor
        anchors.top: parent.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        height: 900
        width : 600
        deviceList: deviceListModel

        ListModel{
            id : deviceListModel
        }

        onSignalEventChagnedValue: {
            model.onCommandSetManagementInfo(dNum, dName, company, department, position, name, limitCriteriaFe, limitCriteriaSus, haccp, checkupcycle)
        }
    }
}

/*##^##
Designer {
    D{i:1;anchors_width:1060}
}
##^##*/
