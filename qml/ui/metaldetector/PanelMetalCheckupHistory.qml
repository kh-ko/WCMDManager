import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import EnumDefine 1.0
import PanelMetalCheckupHistoryModel 1.0

import "../../control/."

Rectangle {
    id : panel

    width : 1196
    height: 418

    color : "#333333"
    radius: 10

    function loadList()
    {
        listModel.clear()

        if(panelmodel.mIsLoading)
            return;

        for(var i = 0; i < panelmodel.getListSize(); i ++)
        {
            listModel.append({"dataIdx" : i})
        }
    }

    PanelMetalCheckupHistoryModel{
        id : panelmodel

        onSignalEventChangedIsLoading: { if(mIsLoading == false){ loadList() } }
    }

    Component.onCompleted:
    {
        loadList()
    }

    UiLabel
    {
        color : "#FFFFFF"
        text  : qsTr("Checkup history")
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
    }

    UiInputText{
        id : inputCheckupCycle

        width: 287
        height: 42
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        inputText: panelmodel.mMDCheckupCycle
        labelText: qsTr("Checkup cycle")
        labelWidth: 142

        isDisable:  true
    }

    RowLayout{
        id : header
        height: 55
        anchors.top: inputCheckupCycle.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        UiLabel{
            text: qsTr("P NO")
            Layout.preferredWidth: 59
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
        }

        UiLabel{
            text: qsTr("P name")
            Layout.preferredWidth: 250
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
        }

        UiLabel{
            text: qsTr("Time")
            Layout.preferredWidth: 85
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
        }

        UiLabel{
            text: qsTr("Limit criteria<br>(Fe)")
            Layout.preferredWidth: 110
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
        }

        UiLabel{
            text: qsTr("Limit criteria<br>(Sus)")
            Layout.preferredWidth: 110
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
        }

        UiLabel{
            text: qsTr("Judgment<br>(Fe) 1 st.")
            Layout.preferredWidth: 110
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
        }

        UiLabel{
            text: qsTr("Judgment<br>(Fe) 2 st.")
            Layout.preferredWidth: 110
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
        }

        UiLabel{
            text: qsTr("Judgment<br>(Fe) 3 st.")
            Layout.preferredWidth: 110
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
        }

        UiLabel{
            text: qsTr("Judgment<br>(Sus) 1 st.")
            Layout.preferredWidth: 110
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
        }

        UiLabel{
            text: qsTr("Judgment<br>(Sus) 2 st.")
            Layout.preferredWidth: 110
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
        }

        UiLabel{
            text: qsTr("Judgment<br>(Sus) 3 st.")
            Layout.preferredWidth: 110
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
        }
    }

    Rectangle{
        id : divider

        height: 2
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        color: "#26ffffff"
        anchors.top: header.bottom
        anchors.topMargin: 0
    }

    ListView{
        id: list
        spacing: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.top: divider.bottom
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20

        model: listModel
        clip: true

        ListModel
        {
            id: listModel
        }

        delegate: Rectangle
        {
            id : item
            height: 50
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            color : "#00000000"


            MouseArea{
                id : mouseAreaItem
                anchors.fill: parent
                hoverEnabled: true
                onContainsMouseChanged:
                {
                    if (containsMouse)
                        parent.color = "#0085FF";
                    else
                        parent.color = "#00000000";
                }
            }

            RowLayout{
                height: 55
                anchors.fill: parent

                UiLabel{
                    text: ("000" + panelmodel.getPNO(dataIdx)).slice(-3)
                    Layout.preferredWidth: 59
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment  : Text.AlignVCenter

                    color: "#FFFFFF"
                }

                UiLabel{
                    text: panelmodel.getPName(dataIdx)
                    Layout.preferredWidth: 250
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment  : Text.AlignVCenter

                    color: "#FFFFFF"
                }

                UiLabel{
                    text: panelmodel.getTime(dataIdx)
                    Layout.preferredWidth: 85
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment  : Text.AlignVCenter

                    color: "#FFFFFF"
                }

                UiLabel{
                    text: panelmodel.getLimCriteriaFe()
                    Layout.preferredWidth: 110
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment  : Text.AlignVCenter

                    color: "#FFFFFF"
                }

                UiLabel{
                    text: panelmodel.getLimCriteriaSus()
                    Layout.preferredWidth: 110
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment  : Text.AlignVCenter

                    color: "#FFFFFF"
                }

                UiLabel{
                    text: panelmodel.getJudgFe01(dataIdx) ? "PASS" : "FAIL"
                    Layout.preferredWidth: 110
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment  : Text.AlignVCenter

                    color: panelmodel.getJudgFe01(dataIdx) ? "#FFFFFF" : "#D9001B"
                }

                UiLabel{
                    text: panelmodel.getJudgFe02(dataIdx) ? "PASS" : "FAIL"
                    Layout.preferredWidth: 110
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment  : Text.AlignVCenter

                    color: panelmodel.getJudgFe02(dataIdx) ? "#FFFFFF" : "#D9001B"
                }

                UiLabel{
                    text: panelmodel.getJudgFe03(dataIdx) ? "PASS" : "FAIL"
                    Layout.preferredWidth: 110
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment  : Text.AlignVCenter

                    color: panelmodel.getJudgFe03(dataIdx) ? "#FFFFFF" : "#D9001B"
                }

                UiLabel{
                    text: panelmodel.getJudgSus01(dataIdx) ? "PASS" : "FAIL"
                    Layout.preferredWidth: 110
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment  : Text.AlignVCenter

                    color: panelmodel.getJudgSus01(dataIdx) ? "#FFFFFF" : "#D9001B"
                }

                UiLabel{
                    text: panelmodel.getJudgSus02(dataIdx) ? "PASS" : "FAIL"
                    Layout.preferredWidth: 110
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment  : Text.AlignVCenter

                    color: panelmodel.getJudgSus02(dataIdx) ? "#FFFFFF" : "#D9001B"
                }

                UiLabel{
                    text: panelmodel.getJudgSus03(dataIdx) ? "PASS" : "FAIL"
                    Layout.preferredWidth: 110
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment  : Text.AlignVCenter

                    color: panelmodel.getJudgSus03(dataIdx) ? "#FFFFFF" : "#D9001B"
                }
            }
        }
    }
}
