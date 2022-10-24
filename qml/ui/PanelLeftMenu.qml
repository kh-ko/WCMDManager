import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.0
import EnumDefine 1.0
import FontManager 1.0

import "../control/."

Item {
    property int selMenu : EnumDefine.MENU_METAL_DETECTOR

    signal signalEventClickedMetalDetector();
    signal signalEventClickedWeightChecker();
    signal signalEventClickedMonitoring();
    signal signalEventClickedSync();
    signal signalEventClickedSetting();
    signal signalEventClickedAddHistory(var fileUrls);

    id : panel

    width : 225
    height: 1080

    UiScrollView{
        anchors.fill: parent

        contentHeight: parent.height < 920 ? 920 : parent.height
        contentWidth : parent.width

        Rectangle{
            anchors.fill: parent
            color : "#333333"

            Rectangle {
                id: rectLogo
                height: 220
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0

                color: "#0085ff"

/*
                Image {
                    id: image
                    //width: 194
                    //height: 77
                    anchors.fill: parent
                    //anchors.verticalCenterOffset: -28
                    //anchors.horizontalCenterOffset: 0
                    //anchors.verticalCenter: parent.verticalCenter
                    //anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.PreserveAspectFit
                    source: "image_icon/icon_soluray.png"
                }
*/
                
                Image {
                    id: image2
                    x: 38
                    y: 156
                    fillMode: Image.PreserveAspectFit
                    source: "image_icon/novasen_text_logo.png"
                }
            }

            Rectangle{
                property bool isHover : false

                id: menuMetalDetector
                height: 125
                anchors.top: rectLogo.bottom
                anchors.topMargin: 100
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0

                color : "#00000000"
                border.width : 2
                border.color: menuMetalDetector.isHover && panel.selMenu !== EnumDefine.MENU_METAL_DETECTOR ? "#0085FF" : "#00000000"

                Text{
                    text: qsTr("Metal detector")
                    font.pixelSize: 20
                    anchors.left: parent.left
                    anchors.leftMargin: 36
                    anchors.verticalCenter: parent.verticalCenter

                    font.family: FontManager.nanumGothicBName
                    color: panel.selMenu === EnumDefine.MENU_METAL_DETECTOR ? "#6fb300" : "#acacac"
                }

                Rectangle{
                    width: 13
                    color: "#6fb300"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0

                    visible: panel.selMenu === EnumDefine.MENU_METAL_DETECTOR
                }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true

                    onContainsMouseChanged: {
                        menuMetalDetector.isHover = containsMouse
                    }

                    onClicked: {
                        panel.signalEventClickedMetalDetector()
                    }
                }
            }

            Rectangle
            {
                property bool isHover : false

                id: menuWeightChecker
                height: 125
                anchors.top: menuMetalDetector.bottom
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0

                color : "#00000000"
                border.width : 2
                border.color: menuWeightChecker.isHover && panel.selMenu !== EnumDefine.MENU_WEIGHT_CHECKER?  "#0085FF" : "#00000000"

                Text{
                    text: qsTr("Weight checker")
                    font.pixelSize: 20
                    anchors.left: parent.left
                    anchors.leftMargin: 36
                    anchors.verticalCenter: parent.verticalCenter

                    font.family: FontManager.nanumGothicBName
                    color: panel.selMenu === EnumDefine.MENU_WEIGHT_CHECKER ? "#0085FF" : "#acacac"
                }

                Rectangle{
                    width: 13
                    color: "#0085FF"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0

                    visible: panel.selMenu === EnumDefine.MENU_WEIGHT_CHECKER
                }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true

                    onHoveredChanged: {
                        menuWeightChecker.isHover = containsMouse
                    }

                    onClicked: {
                        panel.signalEventClickedWeightChecker()
                    }
                }
            }

            UiButton{
                id : btnMonitoring
                width                   : 185
                height                  : 60
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom          : btnImportFile.top
                anchors.bottomMargin    : 20

                text        : qsTr("Monitoring")
                iconSource  : "image_icon/monitoring.png"

                colType     : EnumDefine.BTN_COLOR_TYPE_BLUE

                onSignalEventClicked:  {
                    panel.signalEventClickedMonitoring();
                }
            }

            UiButton{
                id : btnImportFile
                width                   : 185
                height                  : 60
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom          : btnSync.top
                anchors.bottomMargin    : 20

                text        : qsTr("Add history")
                iconSource  : "image_icon/add_history.png"

                colType     : EnumDefine.BTN_COLOR_TYPE_BLUE

                onSignalEventClicked:  {
                    fileDialog.open()
                }
            }

            UiButton{
                id : btnSync
                width                   : 185
                height                  : 60
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom          : btnSetting.top
                anchors.bottomMargin    : 20

                text        : qsTr("Sync")
                iconSource  : "image_icon/refresh.png"

                colType     : EnumDefine.BTN_COLOR_TYPE_BLUE

                onSignalEventClicked:  {
                    panel.signalEventClickedSync();
                }
            }

            UiButton{
                id : btnSetting
                width                   : 185
                height                  : 60
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom          : parent.bottom
                anchors.bottomMargin    : 20

                text        : qsTr("Setting")
                iconSource  : "image_icon/setting.png"

                colType     : EnumDefine.BTN_COLOR_TYPE_BLUE

                onSignalEventClicked:  {
                    panel.signalEventClickedSetting();
                }
            }
        }
    }

    /*
    UiButton{
        width                   : 185
        height                  : 60
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom          : parent.bottom
        anchors.bottomMargin    : 20

        text        : qsTr("Add history")
        iconSource  : "image_icon/add_history.png"

        colType     : EnumDefine.BTN_COLOR_TYPE_BLUE

        onSignalEventClicked:  {
            fileDialog.visible = true
        }
    }
*/
    FileDialog{
        id: fileDialog
            title: "Please choose a file"
            folder: "c:"
            selectFolder: true

            onAccepted: {
                console.log("[debug]" +fileDialog.fileUrl)
                panel.signalEventClickedAddHistory(fileDialog.fileUrl)
                //Qt.quit()
            }
            onRejected: {
                console.log("Canceled")
                //Qt.quit()
            }
            visible : false
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}D{i:2;anchors_width:200}
}
##^##*/
