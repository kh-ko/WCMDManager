import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import EnumDefine 1.0
import PanelWCHistoryModel 1.0
import ViewManager 1.0

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

        for(var i = 0; i < panelmodel.onCommandGetListSize(); i ++)
        {
            listModel.append({"dataIdx" : i})
        }
    }

    PanelWCHistoryModel{
        id : panelmodel

        onSignalEventChangedHistory: {loadList()}
    }

    Component.onCompleted:
    {
        loadList()
    }



    UiLabel
    {
        id : labelTitle

        color : "#FFFFFF"
        text  : qsTr("History")
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
    }

    UiComboBox{
        id : filterCombo

        property bool isOnlyNG : true

        height: 42; width: 300

        anchors.top: labelTitle.bottom; anchors.topMargin: 20; anchors.left: parent.left; anchors.leftMargin: 20

        labelText: qsTr("Filter")
        labelWidth: 120

        inputText: isOnlyNG ? filterListModel.get(0).itemValue : filterListModel.get(1).itemValue

        listModel: filterListModel

        ListModel{
            id : filterListModel

            ListElement
            {
                    itemValue: qsTr("Only NG")
                    itemTag: 0
            }
            ListElement
            {
                    itemValue: qsTr("All")
                    itemTag: 1
            }
        }

        onSignalEventClick: {
            isOnlyNG = (tag === 0)
        }
    }


    RowLayout{
        id : header
        height: 55
        anchors.top: filterCombo.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        spacing: 20

        UiLabel{
            text: qsTr("Time")
            Layout.preferredWidth: 130
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignLeft
            verticalAlignment  : Text.AlignVCenter
        }

        UiLabel{
            text: qsTr("Event")
            Layout.preferredWidth: 130
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignLeft
            verticalAlignment  : Text.AlignVCenter
        }

        UiLabel{
            text: qsTr("Value")
            Layout.preferredWidth: 100
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignLeft
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

            property var eventType : panelmodel.onCommandGetType(dataIdx)
            property var eventTime : panelmodel.onCommandGetTime(dataIdx)
            property var eventValue : panelmodel.onCommandGetValue(dataIdx)

            height: (filterCombo.isOnlyNG == false ||
                    (item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_UNDER          ||
                     item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_OVER           ||
                     item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_ETCERROR       ||
                     item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_ETC_METAL_ERROR)) ? 50 : 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            color : "#00000000"

            visible : height === 50

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
                    text: item.eventTime
                    Layout.preferredWidth: 130
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment  : Text.AlignVCenter

                    color: "#FFFFFF"
                }

                Item{
                    Layout.preferredWidth: 130
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Image{
                        id : eventIcon
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                        source: item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_NORMAL              ? "" :
                                item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_UNDER_WARNING       ? "" :
                                item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_OVER_WARNING        ? "" :
                                item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_UNDER               ? "" :
                                item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_OVER                ? "" :
                                item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_ETCERROR            ? "" :
                                item.eventType === EnumDefine.EVENT_TYPE_APP_START                  ? "" :
                                item.eventType === EnumDefine.EVENT_TYPE_APP_EXIT                   ? "" :
                                item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_STATIC_CARI         ? "" :
                                item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_DYNAMIC_CARI        ? "" :
                                item.eventType === EnumDefine.EVENT_TYPE_RUN                        ? "" :
                                item.eventType === EnumDefine.EVENT_TYPE_STOP                       ? "" :
                                item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_ETC_METAL_ERROR     ? "" : ""
                    }

                    UiLabel{
                        height: 50
                        anchors.left: eventIcon.right; anchors.leftMargin: 20; anchors.right: parent.right;
                        color: "#FFFFFF"
                        text:   item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_NORMAL              ? qsTr("Normal") :
                                item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_UNDER_WARNING       ? qsTr("Under warning") :
                                item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_OVER_WARNING        ? qsTr("Over warning") :
                                item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_UNDER               ? qsTr("Under") :
                                item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_OVER                ? qsTr("Over") :
                                item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_ETCERROR            ? qsTr("Etc") :
                                item.eventType === EnumDefine.EVENT_TYPE_APP_START                  ? qsTr("Power ON") :
                                item.eventType === EnumDefine.EVENT_TYPE_APP_EXIT                   ? qsTr("Power OFF") :
                                item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_STATIC_CARI         ? qsTr("Static Calib") :
                                item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_DYNAMIC_CARI        ? qsTr("Dynamic Calib") :
                                item.eventType === EnumDefine.EVENT_TYPE_RUN                        ? qsTr("Run") :
                                item.eventType === EnumDefine.EVENT_TYPE_STOP                       ? qsTr("Stop") :
                                item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_ETC_METAL_ERROR     ? qsTr("Metal detect") : ""
                    }
                }

                UiLabel{
                    Layout.preferredWidth: 100
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#FFFFFF"
                    text:   item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_NORMAL        ||
                            item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_UNDER_WARNING ||
                            item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_OVER_WARNING  ||
                            item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_OVER_WARNING  ||
                            item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_UNDER         ||
                            item.eventType === EnumDefine.EVENT_TYPE_WEIGHT_OVER          ? (item.eventValue / 1000).toLocaleString(ViewManager.locale, 'f', 1) : ""

                }
            }
        }
    }
}
