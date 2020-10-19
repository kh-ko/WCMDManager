import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import EnumDefine 1.0

import "../../control/."

Item {
    property real scaledValue   : 1.0

    property int  dimHeight     : 35 / scaledValue
    property int  spliterHeight : 20
    id: panel

    width : 1695
    height: 1080

    signal signalClickedOperateReport()
    signal signalClickedCheckupReport();

    ScrollView
    {
        id: scrollView

        anchors.fill: parent

        clip            : true
        contentWidth    : parent.width
        contentHeight   : (leftPanel.height > rightPanel.height ? leftPanel.height : rightPanel.height) + dimHeight

        Item
        {
            id: leftPanel
            height              : spliterStatistics.y + spliterStatistics.height
            anchors.top         : parent.top
            anchors.topMargin   : panel.dimHeight
            anchors.left        : parent.left
            anchors.leftMargin  : 20
            anchors.right       : rightPanel.left
            anchors.rightMargin : 20

            Rectangle
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

            Rectangle
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

            Rectangle
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

            Rectangle
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

                height              : panel.dimHeight
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
            anchors.topMargin   : panel.dimHeight
            anchors.right       : parent.right
            anchors.rightMargin : 20

            Rectangle
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

               /* onSignalClickedOperateReport :
                {
                    panel.signalClickedOperateReport()
                }

                onSignalClickedCheckupReport :
                {
                    panel.signalClickedCheckupReport();
                }*/
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

            PanelWeightCalendar
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

            Rectangle
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

                height              : panel.dimHeight
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

    Rectangle{
        id : rectUpDim

        height: panel.dimHeight
        gradient: Gradient {
            GradientStop {
                position: 0.351
                color: "#131313"
            }

            GradientStop {
                position: 1
                color: "#00000000"
            }
        }
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
    }

    Rectangle{
        id : rectDownDim

        height: panel.dimHeight
        gradient: Gradient {

            GradientStop {
                position: 0
                color: "#00000000"
            }

            GradientStop {
                position: 0.649
                color: "#131313"
            }


        }
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom:  parent.bottom
        anchors.bottomMargin: 0
    }
}


/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/
