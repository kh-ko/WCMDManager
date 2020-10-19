import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import EnumDefine 1.0
import ViewManager 1.0

import "./component/."
import "../../control/."

Item {
    property int wcEventType : EnumDefine.EVENT_TYPE_WEIGHT_NORMAL
    property int currWeight  : 0
    property var totalCnt    : 0
    property var wcNGCnt     : 0
    property var mdNGCnt     : 0

    id: panel
    height: 146
    width: 415

    ColumnLayout{
        id : row01
        spacing: 10

        anchors.fill: parent

        Item {
            height: 42
            Layout.preferredWidth: 1
            Layout.fillWidth: true

            UiLabel{
                id : wcTitle
                color: "#ffffff"
                text: qsTr("current weight")
                width : 150
                font.pixelSize : 20

                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
            }

            UiWeightIndicator{
                anchors.left: wcTitle.right
                anchors.leftMargin: 20
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                eventType : panel.wcEventType
                weight : panel.currWeight
            }
        }

        UiLabelProgressBar{
            height: 42
            value02Width: 0
            label: "Metal NG"
            value01: panel.totalCnt == 0 ? "0.00 %" : ((panel.mdNGCnt / panel.totalCnt)*100).toLocaleString(ViewManager.locale, 'f', 2) + " %"
            value01Width: 80
            value03: (panel.mdNGCnt).toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
            maxValue : panel.totalCnt
            value  : panel.mdNGCnt
            eventColor: "#d9001b"

            Layout.preferredWidth: 1
            Layout.fillWidth: true
        }


        UiLabelProgressBar{
            height: 42
            value02Width: 0
            label: "Weight NG"
            value01:  panel.totalCnt == 0 ? "0.00 %" : ((panel.wcNGCnt / panel.totalCnt)*100).toLocaleString(ViewManager.locale, 'f', 2) + " %"
            value01Width: 80
            value03: (panel.wcNGCnt).toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
            eventColor: "#d9001b"
            maxValue : panel.totalCnt
            value  : panel.wcNGCnt

            Layout.preferredWidth: 1
            Layout.fillWidth: true
        }
    }
}
