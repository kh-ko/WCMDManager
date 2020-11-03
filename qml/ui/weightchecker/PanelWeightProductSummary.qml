import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import EnumDefine 1.0
import ViewManager 1.0
import PanelWCProductSummaryModel 1.0

import "../../control/."

Rectangle {
    id : panel

    width : 1196
    height: 418

    color : "#333333"
    radius: 10

    PanelWCProductSummaryModel{
        id : model
    }

    UiLabel
    {
        id: title
        color : "#FFFFFF"
        text  : qsTr("Product summary")
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
    }

    RowLayout{
        id : header
        height: 55
        anchors.top: title.bottom
        spacing: 20
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 126
        anchors.right: tareWeightText.left
        anchors.rightMargin: 40

        UiLabel{
            text: qsTr("Setting value")
            Layout.preferredWidth: 100
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
        }

        UiLabel{
            text: qsTr("Count")
            Layout.preferredWidth: 100
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
        }

        UiLabel{
            text: qsTr("Total weight")
            Layout.preferredWidth: 100
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
        }

        UiLabel{
            text: qsTr("Avg weight")
            Layout.preferredWidth: 100
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
        }

        UiLabel{
            text: qsTr("Rate")
            Layout.preferredWidth: 80
            Layout.fillWidth: true
            Layout.fillHeight: true

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignVCenter
        }

        UiLabel{
            text: qsTr("SD (CV)")
            Layout.preferredWidth: 170
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
        anchors.right: tareWeightText.left
        anchors.rightMargin: 20

        color: "#26ffffff"
        anchors.top: header.bottom
        anchors.topMargin: 0
    }

    UiBarGraph{
        id: totalBar
        height: 42
        anchors.left: parent.left
        anchors.right: header.right
        anchors.top: divider.bottom
        barColor: "#333333"
        labelText: qsTr("Total")
        anchors.rightMargin: -20
        anchors.leftMargin: 20
        anchors.topMargin: 20
        min : 0
        max : 1
        value: 1

        RowLayout{
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 106
            anchors.rightMargin: 20

            spacing: 20

            UiLabel{
                color: "#ffffff"
                text: ""
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: (model.mTotalCnt).toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                property string postFix : model.mTotalWeight > 999999999 ? " t" :
                                          model.mTotalWeight > 999999    ? " kg": " g"
                property var weight     : model.mTotalWeight > 999999999 ? model.mTotalWeight /  1000000000:
                                          model.mTotalWeight > 999999    ? model.mTotalWeight /  1000000: model.mTotalWeight / 1000
                color: "#ffffff"
                text: weight.toLocaleString(ViewManager.locale, 'f', 1) + postFix
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: (model.mTotalAvgWeight / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: ""
                Layout.preferredWidth: 80
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: (model.mTotalSD / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g (" + (model.mTotalCV > 1000 ? (model.mTotalCV).toLocaleString(ViewManager.locale, 'e', 3) + " %)" : (model.mTotalCV).toLocaleString(ViewManager.locale, 'f', 3) + " %)")
                Layout.preferredWidth: 170
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }
        }

    }

    UiBarGraph{
        id: tradeBar
        height: 42
        anchors.left: parent.left
        anchors.right: header.right
        anchors.top: totalBar.bottom
        labelText: qsTr("Trade")
        anchors.rightMargin: -20
        anchors.leftMargin: 20
        anchors.topMargin: 10

        min : 0
        max : model.mTotalCnt
        value : model.mTradeCnt

        RowLayout{
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 106
            anchors.rightMargin: 20

            spacing: 20

            UiLabel{
                color: "#ffffff"
                text: (model.mTradeSettingValue / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: (model.mTradeCnt).toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                property string postFix : model.mTradeWeight > 999999999 ? " t" :
                                          model.mTradeWeight > 999999    ? " kg": " g"
                property var weight     : model.mTradeWeight > 999999999 ? model.mTradeWeight /  1000000000:
                                          model.mTradeWeight > 999999    ? model.mTradeWeight /  1000000: model.mTradeWeight / 1000
                color: "#ffffff"
                text: weight.toLocaleString(ViewManager.locale, 'f', 1) + postFix
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: (model.mTradeAvgWeight / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: model.mTotalCnt === 0 ? "0.00 %" : ((model.mTradeCnt / model.mTotalCnt) * 100).toLocaleString(ViewManager.locale, 'f', 2) + " %"
                Layout.preferredWidth: 80
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: (model.mTradeSD / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g (" + (model.mTradeCV > 1000 ? (model.mTotalCV).toLocaleString(ViewManager.locale, 'e', 3) + " %)" : (model.mTradeCV).toLocaleString(ViewManager.locale, 'f', 3) + " %)")
                Layout.preferredWidth: 170
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }
        }
    }

    UiBarGraph{
        id: overBar
        height: 42
        anchors.left: parent.left
        anchors.right: header.right
        anchors.top: tradeBar.bottom
        barColor: "#f59a23"
        labelText: qsTr("Over")
        anchors.rightMargin: -20
        anchors.leftMargin: 20
        anchors.topMargin: 10

        min : 0
        max : model.mTotalCnt
        value : model.mOverCnt

        RowLayout{
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 106
            anchors.rightMargin: 20

            spacing: 20

            UiLabel{
                color: "#ffffff"
                text: (model.mOverSettingValue / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: (model.mOverCnt).toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: ""
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: ""
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: model.mTotalCnt === 0 ? "0.00 %" : ((model.mOverCnt / model.mTotalCnt) * 100).toLocaleString(ViewManager.locale, 'f', 2) + " %"
                Layout.preferredWidth: 80
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: ""
                Layout.preferredWidth: 170
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }
        }
    }

    UiBarGraph{
        id: underBar
        height: 42
        anchors.left: parent.left
        anchors.right: header.right
        anchors.top: overBar.bottom
        barColor: "#d9001b"
        labelText: qsTr("Under")
        anchors.rightMargin: -20
        anchors.leftMargin: 20
        anchors.topMargin: 10

        min : 0
        max : model.mTotalCnt
        value : model.mUnderCnt

        RowLayout{
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 106
            anchors.rightMargin: 20

            spacing: 20

            UiLabel{
                color: "#ffffff"
                text: (model.mUnderSettingValue / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: (model.mUnderCnt).toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: ""
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: ""
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: model.mTotalCnt === 0 ? "0.00 %" : ((model.mUnderCnt / model.mTotalCnt) * 100).toLocaleString(ViewManager.locale, 'f', 2) + " %"
                Layout.preferredWidth: 80
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: ""
                Layout.preferredWidth: 170
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }
        }
    }

    UiBarGraph{
        id: etcNGBar
        height: 42
        anchors.left: parent.left
        anchors.right: header.right
        anchors.top: underBar.bottom
        barColor: "#535353"
        labelText: qsTr("Etc NG")
        anchors.rightMargin: -20
        anchors.leftMargin: 20
        anchors.topMargin: 10

        min : 0
        max : model.mTotalCnt
        value : model.mEtcCnt

        RowLayout{
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 106
            anchors.rightMargin: 20

            spacing: 20

            UiLabel{
                color: "#ffffff"
                text: ""
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: (model.mEtcCnt).toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: ""
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: ""
                Layout.preferredWidth: 100
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: model.mTotalCnt === 0 ? "0.00 %" : ((model.mEtcCnt / model.mTotalCnt) * 100).toLocaleString(ViewManager.locale, 'f', 2) + " %"
                Layout.preferredWidth: 80
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }

            UiLabel{
                color: "#ffffff"
                text: ""
                Layout.preferredWidth: 170
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignRight
                verticalAlignment  : Text.AlignVCenter
            }
        }
    }

    UiInputText{
        id: tareWeightText
        width: 212
        height: 42
        anchors.right: parent.right
        anchors.top: totalBar.top
        labelText: qsTr("Tare weight")
        labelWidth: 105
        anchors.topMargin: 0
        anchors.rightMargin: 20
        isDisable: true

        inputText: (model.mTareWeight / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"

    }

    UiInputText{
        id: maxWeightText
        width: 212
        height: 42
        anchors.right: parent.right
        anchors.top: overBar.top
        labelText: qsTr("Max weight")
        labelWidth: 105
        anchors.topMargin: 0
        anchors.rightMargin: 20
        isDisable: true

        inputText: (model.mMaxWeight / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"

    }

    UiInputText{
        id: minWeightText
        width: 212
        height: 42
        anchors.right: parent.right
        anchors.top: underBar.top
        labelText: qsTr("Min weight")
        labelWidth: 105
        anchors.topMargin: 0
        anchors.rightMargin: 20
        isDisable: true

        inputText: (model.mMinWeight / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"

    }
}
