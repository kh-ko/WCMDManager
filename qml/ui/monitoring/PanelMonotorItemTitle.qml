import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0

import "./component/."

Item {
    property bool   isVMode   : false
    property bool   isAlarm   : false
    property bool   isComm    : false
    property bool   isRun     : false
    property int    dNum      : 1
    property string dName     : "일이삼사오륙칠팔구십일이삼사오"
    property int    pNum      : 1
    property string pName     : "일이삼사오륙칠팔구십일이삼사오"


    id: panel

    width : 870
    height: 77

    Item {
        id : indicator
        height: 35
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        UiIndicator{
            id : runIndi
            width: 15
            height: 15
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: commIndi.left
            anchors.rightMargin: 20
            onImage: "component/image/run_enable_indi.png"
            offImage: "component/image/run_disable_indi.png"

            isOn: panel.isRun
        }

        UiIndicator{
            id : commIndi
            width: 15
            height: 15
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: alarmIndi.left
            anchors.rightMargin: 20
            onImage: "component/image/comm_enable_indi.png"
            offImage: "component/image/comm_disable_indi.png"

            isOn: panel.isComm
        }

        UiIndicator{
            id : alarmIndi
            width: 15
            height: 15
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 0
            offImage: "component/image/alarm_diable_indi.png"
            onImage: "component/image/alarm_enalbe_indi.png"

            isOn: panel.isAlarm
        }
    }

    RowLayout{
        anchors.top: indicator.bottom
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        visible: panel.isVMode == false
        spacing: 20

        UiLabelText
        {
            height: 42
            Layout.preferredWidth: 1
            Layout.fillWidth: true
            label: qsTr("Device")
            labelBgWidth: 113

            text: ("000" + panel.dNum).slice(-3) + " " + panel.dName
        }
        UiLabelText
        {
            height: 42
            Layout.preferredWidth: 1
            Layout.fillWidth: true
            label: qsTr("Product")
            labelBgWidth: 113

            text: ("000" + panel.pNum).slice(-3) + " " + panel.pName
        }
    }

    ColumnLayout{
        anchors.top: indicator.bottom
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        visible: panel.isVMode
        spacing: 10

        UiLabelText
        {
            height: 42
            Layout.preferredWidth: 1
            Layout.fillWidth: true
            label: qsTr("Device")
            labelBgWidth: 113

            text: ("000" + panel.dNum).slice(-3) + " " + panel.dName
        }
        UiLabelText
        {
            height: 42
            Layout.preferredWidth: 1
            Layout.fillWidth: true
            label: qsTr("Product")
            labelBgWidth: 113

            text: ("000" + panel.pNum).slice(-3) + " " + panel.pName
        }
    }
}


