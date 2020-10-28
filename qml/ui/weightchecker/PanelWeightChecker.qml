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

    UiScrollView
    {
        id: scrollView
        anchors.fill: parent

        contentWidth    : parent.width > 1693 ? parent.width : 1693
        contentHeight   : panelHistogramTrends.y + panelHistogramTrends.height + 40

        Item{
            id : scrollContent
            anchors.fill: parent

            PanelWeightSelectDeviceProduct
            {
                id : panelSelectDeviceProduct
                height: 93

                anchors.right       : panelWeightReport.left
                anchors.rightMargin : 20
                anchors.left        : parent.left
                anchors.leftMargin  : 20
                anchors.top         : parent.top
                anchors.topMargin   : 20

            }

            Item{
                id : panelWeightReport
                height: 93
                width: 439

                anchors.right       : parent.right
                anchors.rightMargin : 20
                anchors.top         : parent.top
                anchors.topMargin   : 20
            }

            PanelWeightProductSummary
            {
                id : panelWeightProductSummary
                height: 418

                anchors.top         : panelSelectDeviceProduct.bottom
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
                anchors.top         : panelSelectDeviceProduct.bottom
                anchors.topMargin   : 20
            }

            RowLayout{
                id : panelHistogramTrends
                height: 600
                spacing: 20

                anchors.top         : panelWeightProductSummary.bottom
                anchors.topMargin   : 20
                anchors.right       : parent.right
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

        }
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/
