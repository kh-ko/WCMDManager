import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import EnumDefine 1.0
import PanelMetalDetectHistoryModel 1.0

import "../../control/."

Rectangle {
    id : panel

    width : 439
    height: 778

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

    PanelMetalDetectHistoryModel{
        id : panelmodel

        onSignalEventChangedIsLoading: { loadList() }
    }

    Component.onCompleted:
    {
        loadList()
    }

    UiLabel
    {
        id : labelTitle

        color : "#FFFFFF"
        text  : qsTr("Detect history")
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
    }


    RowLayout{
        id : header
        height: 55
        anchors.top: labelTitle.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        spacing: 20

        UiLabel{
            text: qsTr("P NO")
            Layout.preferredWidth: 80
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
        }

        UiLabel{
            text: qsTr("P name")
            Layout.preferredWidth: 300
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
        }

        UiLabel{
            text: qsTr("Time")
            Layout.preferredWidth: 130
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

            property int    pno                 : 0
            property string pname               : "일이삼사오륙칠팔구십일이삼사오"
            property string time                : "08:09:09"
            property real   limitCriteriaFe     : 2.5
            property real   limitCriteriaSus    : 2.5
            property int    totalCount          : 999999
            property int    ngCount             : 999900
            property real   ngRate              : ngCount / totalCount

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
                spacing: 10

                UiLabel{
                    text: panelmodel.getPNO(dataIdx)
                    Layout.preferredWidth: 80
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment  : Text.AlignVCenter

                    color: "#FFFFFF"
                }

                UiLabel{
                    text: panelmodel.getPName(dataIdx)
                    Layout.preferredWidth: 300
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment  : Text.AlignVCenter

                    color: "#FFFFFF"
                }

                UiLabel{
                    text: panelmodel.getTime(dataIdx)
                    Layout.preferredWidth: 130
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment  : Text.AlignVCenter

                    color: "#FFFFFF"
                }
            }
        }
    }
}
