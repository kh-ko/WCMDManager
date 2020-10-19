import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import ViewManager 1.0

import "../../control/."

Rectangle {
    property bool isEditMode : false

    function addDate(value, idx)
    {
        dateListModel.append({"dateValue":value,"idx":idx})
    }

    function clearDate()
    {
        dateList.selectDateIdx = -1
        dateListModel.clear()
    }

    function selectDateIdx(idx)
    {
        dateList.selectDateIdx = idx;
    }

    function getSelectedDateIdx()
    {
        return dateList.selectDateIdx;
    }

    id: control
    width: 162
    color: "#333333"
    anchors.top: headerPanel.bottom
    anchors.topMargin: 0
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 0
    anchors.left: parent.left
    anchors.leftMargin: 0

    signal signalEventClickLoad()
    signal signalEventClickEdit()
    signal signalEventClickPrint()
    signal signalEventSelectDate(int idx)

    UiButton{
        id :btnLoad

        width: 88
        height: 42
        isTextBtn: true
        text: qsTr("Load")
        fontColor : "#FFFFFF"
        colType: EnumDefine.BTN_COLOR_TYPE_BLUE
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 20
        anchors.leftMargin: 20
        anchors.rightMargin: 20

        onSignalEventClicked: {
            control.signalEventClickLoad();
        }
    }

    ListView{
        property int selectDateIdx : -1

        id : dateList
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: btnEdit.top
        anchors.bottomMargin: 20
        anchors.top: btnLoad.bottom
        anchors.topMargin: 20

        model : dateListModel
        clip : true

        ListModel{
            id :dateListModel
        }

        delegate: Rectangle {
            height: 30
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0

            color : dateList.selectDateIdx == idx ? "#0085FF" :"#00000000"
            border.width: 2
            border.color: mouseItem.containsMouse ? "#0085FF" : "#00000000"

            UiLabel{
                color : "#FFFFFF"
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                text: dateValue
            }

            Rectangle{
                anchors.fill: parent
                color : "#59000000"
                visible: mouseItem.isPress && mouseItem.containsMouse
            }

            MouseArea{
                property bool isPress : false

                id : mouseItem
                anchors.fill: parent
                hoverEnabled: true

                onPressed: { isPress = true}
                onReleased: { isPress = false}
                onClicked:
                {
                    dateList.selectDateIdx = idx
                }
            }
        }

        onSelectDateIdxChanged: {
            if(dateList.selectDateIdx < 0)
                return;

            control.signalEventSelectDate(dateList.selectDateIdx)
        }
    }

    UiButton {
        id: btnEdit
        height: 42
        text: control.isEditMode? qsTr("Lock") : qsTr("Edit")
        iconSource: control.isEditMode? "image_icon/lock.png" : "image_icon/unlock.png"
        colType : control.isEditMode? EnumDefine.BTN_COLOR_TYPE_BLUE : EnumDefine.BTN_COLOR_TYPE_DEFAULT

        anchors.bottom: btnPrint.top
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20

        onSignalEventClicked: {
            control.signalEventClickEdit()
        }

    }

    UiButton {
        id: btnPrint
        height: 42
        text: qsTr("Print")
        iconSource: "image_icon/print.png"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20

        onSignalEventClicked: {
            control.signalEventClickPrint()
        }
    }
}
