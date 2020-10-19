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
    property int wcEventType        : EnumDefine.EVENT_TYPE_WEIGHT_NORMAL
    property int mdSenstivity       : 0
    property int mdSignal           : 0
    property int currWeight         : 0
    property int tareWeight         : 0
    property int underWeight        : 0
    property int underWarningWeight : 0
    property int normalWeight       : 0
    property int overWarningWeight  : 0
    property int overWeight         : 0
    property var totalCnt           : 0
    property var mdNGCnt            : 0
    property var underCnt           : 0
    property var underWCnt          : 0
    property var normalCnt          : 0
    property var overWCnt           : 0
    property var overCnt            : 0
    property var etcErrCnt          : 0
    property var tradeTotalWeight   : 0

    property var tradeCnt    : panel.normalCnt + panel.underWCnt + panel.overWCnt
    property string tradeWeightPostFix : panel.tradeTotalWeight > 999999999 ? " t" :
                                         panel.tradeTotalWeight > 999999    ? " kg":
                                                                              " g"
    property var convertedTradeWeight  : panel.tradeTotalWeight > 999999999 ? panel.tradeTotalWeight /  1000000000:
                                         panel.tradeTotalWeight > 999999    ? panel.tradeTotalWeight /  1000000   :
                                                                              panel.tradeTotalWeight /  1000
    id: panel
    height: 564
    width: 790

    RowLayout{
        id : rowTitle
        height: 42
        spacing: 20

        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        UiLabel{
            id : mdTitle
            color: "#ffffff"
            text: qsTr("Metal detector")
            width : 150
            font.pixelSize : 20

            Layout.preferredWidth: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
        }


        Item {
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            Layout.fillWidth: true

            UiLabel{
                id : wcTitle
                color: "#ffffff"
                text: qsTr("Weight checker")
                width : 150
                font.pixelSize : 20

                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
            }

            UiLabelText{
                text: (panel.tareWeight / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
                icon: "component/image/tare.png"
                labelBgWidth: height - 4
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.left: wcTitle.right
                anchors.leftMargin: 20
                anchors.right: parent.right
                anchors.rightMargin: 0
            }
        }
    }

    RowLayout{
        id : rowCurrValue
        height: 137
        spacing: 20

        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: rowTitle.bottom
        anchors.topMargin: 10

        UiMetalGauge{
            bgHeight: 30
            senstivity : panel.mdSenstivity
            signal     : panel.mdSignal
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
        }


        Item{
            id: element
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            Layout.fillWidth: true

            UiWeightIndicator{
                eventType  : panel.wcEventType
                weight     : panel.currWeight

                anchors.bottom: wcGauge.top
                anchors.bottomMargin: 6
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0

            }

            UiWeightGauge{
                id : wcGauge
                eventType     : panel.wcEventType
                under         : panel.underWeight
                underWarning  : panel.underWarningWeight
                normal        : panel.normalWeight
                overWarning   : panel.overWarningWeight
                over          : panel.overWeight
                weight        : panel.currWeight
                height: 50
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
            }

        }
    }

    Rectangle{
        id : divider
        height: 2
        color : "#26ffffff"
        width: parent.width
        anchors.top: rowCurrValue.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter

    }

    UiLabel{
        id : statisticsTitle
        height: 42
        color: "#ffffff"
        text: qsTr("Statistcs")
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        font.pixelSize : 20


        anchors.top: divider.bottom
        anchors.topMargin: 10
    }

    RowLayout{
        id : total
        height: 42
        spacing: 10
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: statisticsTitle.bottom
        anchors.topMargin: 10

        UiLabelText{
            text: panel.tradeCnt === 0 ? "0.0 g" : ((panel.tradeTotalWeight/panel.tradeCnt)/1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
            label: qsTr("Trade average weight")
            labelBgWidth: 200
            Layout.preferredWidth: 323
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        UiLabelText{
            text: panel.convertedTradeWeight.toLocaleString(ViewManager.locale, 'f', 1) + panel.tradeWeightPostFix
            label: qsTr("Trade total weight")
            labelBgWidth: 167
            Layout.preferredWidth: 299
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        UiLabelText{
            text: panel.totalCnt.toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
            label: qsTr("Total")
            labelBgWidth: 75
            Layout.preferredWidth: 200
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

    UiLabelProgressBar{
        id : mdNG
        label: qsTr("Metal NG")
        labelBgWidth : 200
        eventColor: "#d9001b"
        maxValue: panel.totalCnt
        value   : panel.mdNGCnt
        value01 : panel.mdSenstivity.toLocaleString(ViewManager.locale, 'f', 0) + " mv"
        value02 : ((panel.mdNGCnt/panel.totalCnt) * 100).toLocaleString(ViewManager.locale, 'f', 2) + " %"
        value03 : panel.mdNGCnt.toLocaleString(ViewManager.locale, 'f', 0) + " pcs"

        anchors.top: total.bottom
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
    }

    UiLabelProgressBar{
        id : wcOverNG
        label: qsTr("Weight over NG")
        labelBgWidth : 200
        eventColor: "#F59A23"
        maxValue: panel.totalCnt
        value   : panel.overCnt
        value01 : (panel.overWeight / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
        value02 : ((panel.overCnt/panel.totalCnt) * 100).toLocaleString(ViewManager.locale, 'f', 2) + " %"
        value03 : panel.overCnt.toLocaleString(ViewManager.locale, 'f', 0) + " pcs"

        anchors.top: mdNG.bottom
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
    }

    UiLabelProgressBar{
        id : wcNormal
        label: qsTr("Weight normal")
        labelBgWidth : 200
        isNonHighlight: true
        maxValue: panel.totalCnt
        value   : panel.normalCnt
        value01 : (panel.normalWeight / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
        value02 : ((panel.normalCnt/panel.totalCnt) * 100).toLocaleString(ViewManager.locale, 'f', 2) + " %"
        value03 : panel.normalCnt.toLocaleString(ViewManager.locale, 'f', 0) + " pcs"

        anchors.top: wcOverNG.bottom
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
    }

    UiLabelProgressBar{
        id : wcUnderNG
        eventColor: "#d9001b"
        label: qsTr("Weight under NG")
        labelBgWidth : 200
        maxValue: panel.totalCnt
        value   : panel.underCnt
        value01 : (panel.underWeight / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
        value02 : ((panel.underCnt/panel.totalCnt) * 100).toLocaleString(ViewManager.locale, 'f', 2) + " %"
        value03 : panel.underCnt.toLocaleString(ViewManager.locale, 'f', 0) + " pcs"

        anchors.top: wcNormal.bottom
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
    }

    UiLabelProgressBar{
        id : wcEtcNG
        eventColor: "#434343"
        label: qsTr("Weight etc NG")
        labelBgWidth : 200
        maxValue: panel.totalCnt
        value   : panel.etcErrCnt
        value01 : ""
        value02 : ((panel.etcErrCnt/panel.totalCnt) * 100).toLocaleString(ViewManager.locale, 'f', 2) + " %"
        value03 : panel.etcErrCnt.toLocaleString(ViewManager.locale, 'f', 0) + " pcs"

        anchors.top: wcUnderNG.bottom
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
    }
}
