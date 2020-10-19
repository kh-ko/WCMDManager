import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import EnumDefine 1.0

import "../../control/."

Item {
    property int  spliterHeight : 20
    id: panel

    width : 1693
    height: 1080

    signal signalClickedOperateReport()
    signal signalClickedCheckupReport();

    UiScrollView
    {
        id: scrollView
        anchors.fill: parent

        contentWidth    : parent.width > 1693 ? parent.width : 1693
        contentHeight   : (leftPanel.height > rightPanel.height ? leftPanel.height : rightPanel.height) + leftPanel.anchors.topMargin *2

        Item{
            id : scrollContent
            anchors.fill: parent

            Item
            {
                id: leftPanel
                height              : spliterStatistics.y + spliterStatistics.height
                anchors.top         : parent.top
                anchors.topMargin   : 20
                anchors.left        : parent.left
                anchors.leftMargin  : 20
                anchors.right       : rightPanel.left
                anchors.rightMargin : 20

                PanelMetalManagementInfo
                {
                    id : panelMetalManagementInfo

                    anchors.bottom      : spliterManInfo.top
                    anchors.bottomMargin: 0
                    anchors.right       : parent.right
                    anchors.rightMargin : 0
                    anchors.left        : parent.left
                    anchors.leftMargin  : 0
                    anchors.top         : parent.top
                    anchors.topMargin   : 0

                }

                UiVSpliter{
                    id : spliterManInfo

                    height              : panel.spliterHeight
                    anchors.top         : parent.top
                    anchors.topMargin   : 93
                    anchors.right       : parent.right
                    anchors.rightMargin : 0
                    anchors.left        : parent.left
                    anchors.leftMargin  : 0

                    isDisable           : true
                }

                PanelMetalCheckupHistory
                {
                    id : panelMetalCheckupHistory

                    anchors.bottom      : spliterCheckupHistory.top
                    anchors.bottomMargin: 0
                    anchors.right       : parent.right
                    anchors.rightMargin : 0
                    anchors.left        : parent.left
                    anchors.leftMargin  : 0
                    anchors.top         : spliterManInfo.bottom
                    anchors.topMargin   : 0
                }

                UiVSpliter{
                    id : spliterCheckupHistory

                    height              : panel.spliterHeight
                    anchors.top         : spliterManInfo.bottom
                    anchors.topMargin   : 418
                    anchors.right       : parent.right
                    anchors.rightMargin : 0
                    anchors.left        : parent.left
                    anchors.leftMargin  : 0

                    minGap              :  200
                }

                PanelMetalOperateHistory
                {
                    id : panelMetalOperateHistory

                    anchors.bottom      : spliterOperateHistory.top
                    anchors.bottomMargin: 0
                    anchors.right       : parent.right
                    anchors.rightMargin : 0
                    anchors.left        : parent.left
                    anchors.leftMargin  : 0
                    anchors.top         : spliterCheckupHistory.bottom
                    anchors.topMargin   : 0
                }

                UiVSpliter{
                    id : spliterOperateHistory

                    height              : panel.spliterHeight
                    anchors.top         : spliterCheckupHistory.bottom
                    anchors.topMargin   : 418
                    anchors.right       : parent.right
                    anchors.rightMargin : 0
                    anchors.left        : parent.left
                    anchors.leftMargin  : 0

                    minGap              :  200
                }

                PanelMetalStatistics
                {
                    id : panelMetalStatistics

                    anchors.bottom      : spliterStatistics.top
                    anchors.bottomMargin: 0
                    anchors.right       : parent.right
                    anchors.rightMargin : 0
                    anchors.left        : parent.left
                    anchors.leftMargin  : 0
                    anchors.top         : spliterOperateHistory.bottom
                    anchors.topMargin   : 0
                }

                UiVSpliter{
                    id : spliterStatistics

                    height              : panel.spliterHeight
                    anchors.top         : spliterOperateHistory.bottom
                    anchors.topMargin   : 344
                    anchors.right       : parent.right
                    anchors.rightMargin : 0
                    anchors.left        : parent.left
                    anchors.leftMargin  : 0

                    isDisable           : true
                }
            }
            Item
            {
                id : rightPanel

                width               : 439
                height              : spliterDetectHistory.y + spliterDetectHistory.height
                anchors.top         : parent.top
                anchors.topMargin   : 20
                anchors.right       : parent.right
                anchors.rightMargin : 20

                PanelMetalPrintReport
                {
                    id : panelMetalPrintReport

                    anchors.bottom      : spliterPrintReport.top
                    anchors.bottomMargin: 0
                    anchors.right       : parent.right
                    anchors.rightMargin : 0
                    anchors.left        : parent.left
                    anchors.leftMargin  : 0
                    anchors.top         : parent.top
                    anchors.topMargin   : 0

                    onSignalClickedOperateReport :
                    {
                        panel.signalClickedOperateReport()
                    }

                    onSignalClickedCheckupReport :
                    {
                        panel.signalClickedCheckupReport();
                    }
                }

                UiVSpliter{
                    id : spliterPrintReport

                    height              : panel.spliterHeight
                    anchors.top         : parent.top
                    anchors.topMargin   : 93
                    anchors.right       : parent.right
                    anchors.rightMargin : 0
                    anchors.left        : parent.left
                    anchors.leftMargin  : 0

                    isDisable           : true
                }

                PanelMetalCalendar
                {
                    id : panelMetalCalendar

                    anchors.bottom      : spliterCalendar.top
                    anchors.bottomMargin: 0
                    anchors.right       : parent.right
                    anchors.rightMargin : 0
                    anchors.left        : parent.left
                    anchors.leftMargin  : 0
                    anchors.top         : spliterPrintReport.bottom
                    anchors.topMargin   : 0
                }

                UiVSpliter{
                    id : spliterCalendar

                    height              : panel.spliterHeight
                    anchors.top         : spliterPrintReport.bottom
                    anchors.topMargin   : 418
                    anchors.right       : parent.right
                    anchors.rightMargin : 0
                    anchors.left        : parent.left
                    anchors.leftMargin  : 0

                    isDisable           : true
                }

                PanelMetalDetectHistory
                {
                    id : panelMetalDetectHistory

                    anchors.bottom      : spliterDetectHistory.top
                    anchors.bottomMargin: 0
                    anchors.right       : parent.right
                    anchors.rightMargin : 0
                    anchors.left        : parent.left
                    anchors.leftMargin  : 0
                    anchors.top         : spliterCalendar.bottom
                    anchors.topMargin   : 0
                }

                UiVSpliter{
                    id : spliterDetectHistory

                    height              : panel.spliterHeight
                    anchors.top         : spliterCalendar.bottom
                    anchors.topMargin   : 778
                    anchors.right       : parent.right
                    anchors.rightMargin : 0
                    anchors.left        : parent.left
                    anchors.leftMargin  : 0

                    minGap              :  200
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.25}
}
##^##*/
