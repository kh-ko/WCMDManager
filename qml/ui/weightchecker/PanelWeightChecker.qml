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

    signal signalClickedReport();

    UiScrollView
    {
        id: scrollView
        anchors.fill: parent

        contentWidth    : parent.width > 1693 ? parent.width : 1693
        contentHeight   : panelHistogramTrends.y + panelHistogramTrends.height + 40

        Item{
            id : scrollContent
            anchors.fill: parent

            RowLayout {
                id: panelWCTop
                height: 93
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                spacing: 20
                anchors.topMargin: 20
                anchors.rightMargin: 20
                anchors.leftMargin: 20

                PanelWeightManagementInfo{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 942
                }


                PanelWeightSelectDeviceProduct
                {
                    id : panelSelectDeviceProduct
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 400

                }

                PanelWeightPrintReport{
                    id : panelWeightReport

                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 220

                    onSignalClickedReport :
                    {
                        panel.signalClickedReport()
                    }
                }
            }

            PanelWeightProductSummary
            {
                id : panelWeightProductSummary
                height: 418

                anchors.top         : panelWCTop.bottom
                anchors.topMargin   : 20
                anchors.right       : panelWeightCalendar.left
                anchors.rightMargin : 20
                anchors.left        : parent.left
                anchors.leftMargin  : 20

            }

            PanelWeightCalendar{
                id : panelWeightCalendar
                height: 418
                width: 439

                anchors.right       : parent.right
                anchors.rightMargin : 20
                anchors.top         : panelWCTop.bottom
                anchors.topMargin   : 20
            }

            ColumnLayout{
                id : panelHistogramTrends
                height: 1220
                spacing: 20

                anchors.top         : panelWeightProductSummary.bottom
                anchors.topMargin   : 20
                anchors.right       : panelHistory.left
                anchors.rightMargin : 20
                anchors.left        : parent.left
                anchors.leftMargin  : 20

                PanelWeightHistogram{
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                }

                PanelWeightTrends{
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
            }

            PanelWeightHistory{
                id : panelHistory
                height: 1220; width : 439
                anchors.top: panelWeightCalendar.bottom; anchors.topMargin : 20; anchors.right : parent.right; anchors.rightMargin : 20
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
