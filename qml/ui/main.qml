import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import EnumDefine 1.0
import ViewManager 1.0
import MainModel 1.0
import MouseEventSpy 1.0

import "../control/."
import "."
import "./weightchecker/."
import "./metaldetector/."
import "./report/."

ApplicationWindow {
    property int selMenu    : EnumDefine.MENU_METAL_DETECTOR
    property int previousX
    property int previousY

    id          : window
    visible     : true
    width       : 1024//640
    height      : 680//480
    title       : qsTr("WCMD Manager program") + " v" + mainModel.mVersion
    minimumHeight: 680
    minimumWidth: 1000

    MainModel{
        id :mainModel

        Component.onCompleted: { console.debug("[ApplicationWindow] create instance") }//onCommandLoadLanguage()}
    }

    Rectangle
    {
        id : rootContainer

        width                   : parent.width / ViewManager.scale//parent.width < 1920 ? 1920 : parent.width
        height                  : parent.height / ViewManager.scale// (parent.height * width) / parent.width
        anchors.verticalCenter  : parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        scale                   : ViewManager.scale // parent.width < 1920 ? parent.width / 1920 : 1

        //onScaleChanged: { ViewManager.scale = rootContainer.scale }

        color : "#131313"

        PanelLeftMenu
        {
            id : leftMenu

            width               : 225
            anchors.bottom      : parent.bottom
            anchors.bottomMargin: 0
            anchors.top         : parent.top
            anchors.topMargin   : 0

            selMenu: mainModel.mSelMenu

            onSignalEventClickedMetalDetector: {
                mainModel.onCommandSelMenu(EnumDefine.MENU_METAL_DETECTOR)
            }

            onSignalEventClickedWeightChecker: {
                mainModel.onCommandSelMenu(EnumDefine.MENU_WEIGHT_CHECKER)
            }

            onSignalEventClickedMonitoring: {

                dialogMonitoringList.open();
            }

            onSignalEventClickedAddHistory: {
                mainModel.onCommandAddHistory(fileUrls);
                var dlgCopyProgress = dialogCopyProgress.createObject(window,{"model" : mainModel});
                dlgCopyProgress.open();
            }

            onSignalEventClickedSync: {
                panelSync.open();
            }

            onSignalEventClickedSetting: {
                var settingWin = winSettingComponent.createObject(window);
                settingWin.open();
            }
        }

        PanelMetalDetector
        {
            anchors.left        : leftMenu.right
            anchors.leftMargin  : 2
            anchors.right       : parent.right
            anchors.rightMargin : 0
            anchors.bottom      : parent.bottom
            anchors.bottomMargin: 0
            anchors.top         : parent.top
            anchors.topMargin   : 0

            visible: mainModel.mSelMenu == EnumDefine.MENU_METAL_DETECTOR

            onSignalClickedOperateReport :
            {
                var reportDialog = dialogMDOPReportComponent.createObject(window);
                reportDialog.open(mainModel.onCommandGetSelYear(), mainModel.onCommandGetSelMonth(), mainModel.onCommandGetSelDay());
            }

            onSignalClickedCheckupReport:
            {
                var reportDialog = dialogMDCheckReportComponent.createObject(window);
                reportDialog.open(mainModel.onCommandGetSelYear(), mainModel.onCommandGetSelMonth(), mainModel.onCommandGetSelDay());
            }
        }

        PanelWeightChecker
        {
            anchors.left        : leftMenu.right
            anchors.leftMargin  : 0
            anchors.right       : parent.right
            anchors.rightMargin : 0
            anchors.bottom      : parent.bottom
            anchors.bottomMargin: 0
            anchors.top         : parent.top
            anchors.topMargin   : 0//35 / parent.scale

            visible: mainModel.mSelMenu == EnumDefine.MENU_WEIGHT_CHECKER

            onSignalClickedReport :
            {
                var reportDialog = dialogWCReportComponent.createObject(window);
                reportDialog.open(mainModel.onCommandGetSelYear(), mainModel.onCommandGetSelMonth(), mainModel.onCommandGetSelDay());
            }
        }

        PanelSync{
            id: panelSync
        }
    }

    DialogMonitoringList
    {
        id : dialogMonitoringList
    }

    Rectangle{
        id: rectangle
        anchors.fill: parent
        color: "#d9000000"

        visible: mainModel.mIsLoading

        BusyIndicator{
            running: true
            width: 300
            height: 300
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

        }

        MouseArea{
            anchors.fill: parent
            onClicked: {}
        }
    }


    Component{
        id : dialogMDOPReportComponent
        PanelMDOPReportWindow{
        }
    }

    Component{
        id : dialogMDCheckReportComponent
        PanelMDCheckReportWindow{
        }
    }

    Component{
        id : dialogWCReportComponent
        PanelWCReportWindow{
        }
    }

    Component{
        id : winSettingComponent
        WindowSetting{
        }
    }

    Component{
        id : dialogCopyProgress
        PanelHistoryCopyProgress{
            height: 100
            width: 700
        }
    }

    Connections {
        target: MouseEventSpy
        onMouseEventZoomIn: {
            var newScale = ViewManager.scale + 0.01
            ViewManager.scale = newScale > 1.0 ? 1.0 : newScale
        }
        onMouseEventZoomOut: {
            var newScale = ViewManager.scale - 0.01
            ViewManager.scale = newScale < 0.5 ? 0.5 : newScale
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:2}
}
##^##*/
